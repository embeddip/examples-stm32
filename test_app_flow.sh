#!/usr/bin/env bash

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR"
APPS_DIR="$PROJECT_ROOT/apps"
MAIN_C_PATH="$PROJECT_ROOT/Core/Src/main.c"

BUILD_PRESET="Debug"
BUILD_DIR=""
BIN_PATH=""
ELF_PATH=""
FLASH_ADDR="0x08000000"
ST_FLASH_FREQ_KHZ="1000"
ST_FLASH_CONNECT_UNDER_RESET=true
ST_FLASH_HOT_PLUG=false
FLASH_RETRIES="2"

APP_INPUT=""
PORT="/dev/ttyACM0"
BAUD="2000000"
IMAGE_PATH=""
TIMEOUT_SECS="120"
FLASH_CMD=""
HEADLESS_MODE="auto"
PYDIPLINK_BEFORE_FLASH=true
PYDIPLINK_STARTUP_DELAY_SECS="1"
EXPECTED_OUTPUTS="1"
declare -a PYDIPLINK_EXTRA_ARGS=()
PYDIPLINK_BG_PID=""
PYDIPLINK_STATUS_FILE=""

SKIP_BUILD=false
SKIP_FLASH=false
SKIP_RUN=false

LOG_DIR="$PROJECT_ROOT/test_logs"
RUN_ID="$(date +%Y%m%d_%H%M%S)"
LOG_FILE="$LOG_DIR/pydiplink_${RUN_ID}.log"
BACKUP_MAIN=""

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
log_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
log_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
log_error() { echo -e "${RED}[ERROR]${NC} $1" >&2; }

usage() {
    cat <<EOF
Usage:
  $(basename "$0") --app <app_name_or_path> [options]

Required:
  --app <name|path>        App file from apps/ (e.g. listing7_9) or full path

Options:
  --port <device>          Serial port for pydiplink (default: $PORT)
  --baud <rate>            Serial baud for pydiplink (default: $BAUD)
  --image <path>           Image path for pydiplink --image
  --preset <name>          CMake preset (default: $BUILD_PRESET)
  --timeout <seconds>      Max wait time for pydiplink (default: $TIMEOUT_SECS)
  --headless               Force headless pydiplink execution
  --no-headless            Disable headless mode (CI enables headless by default)
  --pydiplink-before-flash Start pydiplink first, then flash (default)
  --pydiplink-after-flash  Flash first, then start pydiplink
  --pydiplink-wait <sec>   Delay before flashing after pydiplink start (default: $PYDIPLINK_STARTUP_DELAY_SECS)
  --expected-outputs <n>   Required count of output cycles before finishing (default: $EXPECTED_OUTPUTS)
  --pydiplink-arg <arg>    Extra argument for pydiplink (repeatable)
  --flash-cmd "<command>"  Custom flash command. Use {bin} and {addr} placeholders.
                           Example: --flash-cmd "st-flash --reset write {bin} {addr}"
  --flash-addr <hex>       Flash address (default: $FLASH_ADDR)
  --st-flash-freq <kHz>    st-flash SWD frequency (default: $ST_FLASH_FREQ_KHZ)
  --st-flash-hot-plug      Use st-flash --hot-plug
  --no-st-flash-connect-under-reset
                           Disable st-flash --connect-under-reset
  --flash-retries <n>      Flash attempts with st-flash (default: $FLASH_RETRIES)
  --skip-build             Skip build step
  --skip-flash             Skip flash step
  --skip-run               Skip pydiplink run/check step
  -h, --help               Show this help

Success criteria (run step):
  - At least <expected-outputs> lines of: [PC] Image saved to:
  - At least <expected-outputs> lines of: [READER] STW: Complete
EOF
}

cleanup() {
    if [[ -n "${PYDIPLINK_BG_PID:-}" ]]; then
        kill "$PYDIPLINK_BG_PID" >/dev/null 2>&1 || true
    fi
    if [[ -n "${PYDIPLINK_STATUS_FILE:-}" ]]; then
        rm -f "$PYDIPLINK_STATUS_FILE" >/dev/null 2>&1 || true
    fi
    if [[ -n "$BACKUP_MAIN" && -f "$BACKUP_MAIN" ]]; then
        cp "$BACKUP_MAIN" "$MAIN_C_PATH"
        rm -f "$BACKUP_MAIN"
        log_info "Restored original main.c"
    fi
}

resolve_app_path() {
    local input="$1"

    if [[ -f "$input" ]]; then
        echo "$input"
        return
    fi

    if [[ -f "$APPS_DIR/$input" ]]; then
        echo "$APPS_DIR/$input"
        return
    fi

    log_error "App file not found: $input"
    log_error "Expected either an existing file path or $APPS_DIR/<app_name>"
    exit 1
}

run_flash() {
    ensure_bin_artifact

    if [[ -n "$FLASH_CMD" ]]; then
        local cmd="$FLASH_CMD"
        cmd="${cmd//\{bin\}/$BIN_PATH}"
        cmd="${cmd//\{addr\}/$FLASH_ADDR}"
        log_info "Flashing with custom command: $cmd"
        bash -lc "$cmd"
        return
    fi

    if command -v st-flash >/dev/null 2>&1; then
        local -a st_cmd
        st_cmd=(st-flash)
        if [[ "$ST_FLASH_CONNECT_UNDER_RESET" == true ]]; then
            st_cmd+=(--connect-under-reset)
        fi
        if [[ "$ST_FLASH_HOT_PLUG" == true ]]; then
            st_cmd+=(--hot-plug)
        fi
        if [[ -n "$ST_FLASH_FREQ_KHZ" ]]; then
            st_cmd+=(--freq="$ST_FLASH_FREQ_KHZ")
        fi

        local attempt
        for ((attempt=1; attempt<=FLASH_RETRIES; attempt++)); do
            log_info "Flashing with st-flash (attempt ${attempt}/${FLASH_RETRIES})"
            if "${st_cmd[@]}" --reset write "$BIN_PATH" "$FLASH_ADDR"; then
                return
            fi

            if (( attempt < FLASH_RETRIES )); then
                log_warning "Flash failed, resetting ST-Link target and retrying..."
                "${st_cmd[@]}" reset >/dev/null 2>&1 || true
                sleep 1
            fi
        done
        log_error "st-flash failed after ${FLASH_RETRIES} attempts."
        log_error "Try lower speed: --st-flash-freq 400"
        return
    fi

    log_error "No default flasher found (st-flash missing)."
    log_error "Use --flash-cmd to provide your flashing command."
    exit 1
}

find_objcopy_tool() {
    if command -v arm-none-eabi-objcopy >/dev/null 2>&1; then
        command -v arm-none-eabi-objcopy
        return 0
    fi

    local compiler_cmake=""
    compiler_cmake="$(find "$BUILD_DIR/CMakeFiles" -maxdepth 2 -type f -name CMakeCCompiler.cmake | head -n 1 || true)"
    if [[ -z "$compiler_cmake" ]]; then
        return 1
    fi

    local compiler_path=""
    compiler_path="$(sed -n 's/^set(CMAKE_C_COMPILER "\(.*\)")/\1/p' "$compiler_cmake" | head -n 1 || true)"
    if [[ -z "$compiler_path" ]]; then
        return 1
    fi

    local objcopy_candidate
    objcopy_candidate="$(dirname "$compiler_path")/arm-none-eabi-objcopy"
    if [[ -x "$objcopy_candidate" ]]; then
        echo "$objcopy_candidate"
        return 0
    fi

    return 1
}

ensure_bin_artifact() {
    if [[ -f "$BIN_PATH" ]]; then
        return 0
    fi

    if [[ ! -f "$ELF_PATH" ]]; then
        log_error "Missing ELF artifact: $ELF_PATH"
        log_error "Cannot generate BIN artifact."
        exit 1
    fi

    local objcopy_tool=""
    objcopy_tool="$(find_objcopy_tool || true)"
    if [[ -z "$objcopy_tool" ]]; then
        log_error "arm-none-eabi-objcopy not found in PATH/toolchain."
        log_error "Cannot generate BIN artifact from ELF."
        exit 1
    fi

    log_info "Generating BIN from ELF using: $objcopy_tool"
    "$objcopy_tool" -O binary "$ELF_PATH" "$BIN_PATH"

    if [[ ! -f "$BIN_PATH" ]]; then
        log_error "Failed to generate BIN artifact: $BIN_PATH"
        exit 1
    fi
}

is_ci_env() {
    [[ -n "${CI:-}" || -n "${GITHUB_ACTIONS:-}" || -n "${GITLAB_CI:-}" ]]
}

use_headless_mode() {
    case "$HEADLESS_MODE" in
        true) return 0 ;;
        false) return 1 ;;
        auto)
            if is_ci_env; then
                return 0
            fi
            return 1
            ;;
        *)
            return 1
            ;;
    esac
}

detect_pydiplink_headless_flag() {
    local help_text=""
    help_text="$(pydiplink --help 2>&1 || true)"

    local -a candidates=(
        "--headless"
        "--no-gui"
        "--no-display"
        "--no-visual"
        "--no-visuals"
        "--no-show"
    )
    local flag
    for flag in "${candidates[@]}"; do
        if grep -Fq -- "$flag" <<<"$help_text"; then
            echo "$flag"
            return 0
        fi
    done
    return 1
}

build_pydiplink_cmd() {
    pydiplink_cmd=(pydiplink --port "$PORT" --baud "$BAUD")
    if [[ -n "$IMAGE_PATH" ]]; then
        pydiplink_cmd+=(--image "$IMAGE_PATH")
    fi

    if use_headless_mode; then
        local auto_headless_flag=""
        auto_headless_flag="$(detect_pydiplink_headless_flag || true)"
        if [[ -n "$auto_headless_flag" ]]; then
            pydiplink_cmd+=("$auto_headless_flag")
        fi
    fi

    if ((${#PYDIPLINK_EXTRA_ARGS[@]} > 0)); then
        pydiplink_cmd+=("${PYDIPLINK_EXTRA_ARGS[@]}")
    fi
}

start_pydiplink_background() {
    mkdir -p "$LOG_DIR"
    build_pydiplink_cmd
    PYDIPLINK_STATUS_FILE="$LOG_DIR/pydiplink_${RUN_ID}.status"
    rm -f "$PYDIPLINK_STATUS_FILE"

    log_info "Starting pydiplink first, then flash (timeout: ${TIMEOUT_SECS}s)"
    log_info "Command: ${pydiplink_cmd[*]}"
    log_info "Log file: $LOG_FILE"
    log_info "Required outputs before finish: $EXPECTED_OUTPUTS"
    log_info "Streaming pydiplink output to console"

    (
        set +e
        if use_headless_mode; then
            log_info "Headless mode enabled"
            env PYTHONUNBUFFERED=1 MPLBACKEND=Agg QT_QPA_PLATFORM=offscreen SDL_VIDEODRIVER=dummy DISPLAY= \
                timeout --foreground "${TIMEOUT_SECS}s" \
                "${pydiplink_cmd[@]}" 2>&1 | sed -u 's/^/[PYDIPLINK] /' | tee "$LOG_FILE"
        else
            env PYTHONUNBUFFERED=1 timeout --foreground "${TIMEOUT_SECS}s" \
                "${pydiplink_cmd[@]}" 2>&1 | sed -u 's/^/[PYDIPLINK] /' | tee "$LOG_FILE"
        fi
        echo "${PIPESTATUS[0]}" > "$PYDIPLINK_STATUS_FILE"
    ) &
    PYDIPLINK_BG_PID=$!
}

run_pydiplink_foreground() {
    mkdir -p "$LOG_DIR"
    build_pydiplink_cmd

    log_info "Starting pydiplink (timeout: ${TIMEOUT_SECS}s)"
    log_info "Command: ${pydiplink_cmd[*]}"
    log_info "Log file: $LOG_FILE"
    log_info "Required outputs before finish: $EXPECTED_OUTPUTS"
    log_info "Streaming pydiplink output to console"

    set +e
    if use_headless_mode; then
        log_info "Headless mode enabled"
        env PYTHONUNBUFFERED=1 MPLBACKEND=Agg QT_QPA_PLATFORM=offscreen SDL_VIDEODRIVER=dummy DISPLAY= \
            timeout --foreground "${TIMEOUT_SECS}s" \
            "${pydiplink_cmd[@]}" 2>&1 | sed -u 's/^/[PYDIPLINK] /' | tee "$LOG_FILE"
    else
        env PYTHONUNBUFFERED=1 timeout --foreground "${TIMEOUT_SECS}s" \
            "${pydiplink_cmd[@]}" 2>&1 | sed -u 's/^/[PYDIPLINK] /' | tee "$LOG_FILE"
    fi
    timeout_rc=${PIPESTATUS[0]}
    set -e

    if [[ "$timeout_rc" -eq 124 ]]; then
        log_warning "pydiplink timed out after ${TIMEOUT_SECS}s"
    elif [[ "$timeout_rc" -ne 0 ]]; then
        log_warning "pydiplink exited with code $timeout_rc"
    fi

    verify_run_log "$LOG_FILE"
}

wait_pydiplink_background() {
    if [[ -z "${PYDIPLINK_BG_PID:-}" ]]; then
        log_error "Internal error: pydiplink background PID is empty."
        exit 1
    fi

    local last_saved=-1
    local last_complete=-1
    while kill -0 "$PYDIPLINK_BG_PID" >/dev/null 2>&1; do
        local saved_count complete_count
        saved_count="$(count_marker "[PC] Image saved to:" "$LOG_FILE")"
        complete_count="$(count_marker "[READER] STW: Complete" "$LOG_FILE")"
        if [[ "$saved_count" -ne "$last_saved" || "$complete_count" -ne "$last_complete" ]]; then
            log_info "pydiplink progress: saved ${saved_count}/${EXPECTED_OUTPUTS}, complete ${complete_count}/${EXPECTED_OUTPUTS}"
            last_saved="$saved_count"
            last_complete="$complete_count"
        fi

        if has_success_markers "$LOG_FILE"; then
            log_success "Success markers detected; stopping pydiplink early."
            kill "$PYDIPLINK_BG_PID" >/dev/null 2>&1 || true
            wait "$PYDIPLINK_BG_PID" >/dev/null 2>&1 || true
            PYDIPLINK_BG_PID=""
            if [[ -n "$PYDIPLINK_STATUS_FILE" ]]; then
                rm -f "$PYDIPLINK_STATUS_FILE" >/dev/null 2>&1 || true
            fi
            verify_run_log "$LOG_FILE"
            return 0
        fi
        sleep 1
    done

    wait "$PYDIPLINK_BG_PID"
    PYDIPLINK_BG_PID=""

    timeout_rc=1
    if [[ -n "$PYDIPLINK_STATUS_FILE" && -f "$PYDIPLINK_STATUS_FILE" ]]; then
        timeout_rc="$(cat "$PYDIPLINK_STATUS_FILE" 2>/dev/null || echo 1)"
        rm -f "$PYDIPLINK_STATUS_FILE"
    fi

    if [[ "$timeout_rc" -eq 124 ]]; then
        log_warning "pydiplink timed out after ${TIMEOUT_SECS}s"
    elif [[ "$timeout_rc" -ne 0 ]]; then
        log_warning "pydiplink exited with code $timeout_rc"
    fi

    verify_run_log "$LOG_FILE"
}

count_marker() {
    local marker="$1"
    local log_file="$2"

    if [[ ! -f "$log_file" ]]; then
        echo 0
        return
    fi
    grep -Fc "$marker" "$log_file" || true
}

has_success_markers() {
    local log_file="$1"
    local saved_count complete_count
    saved_count="$(count_marker "[PC] Image saved to:" "$log_file")"
    complete_count="$(count_marker "[READER] STW: Complete" "$log_file")"
    [[ "$saved_count" -ge "$EXPECTED_OUTPUTS" && "$complete_count" -ge "$EXPECTED_OUTPUTS" ]]
}

verify_run_log() {
    local log_file="$1"
    local saved_count complete_count
    saved_count="$(count_marker "[PC] Image saved to:" "$log_file")"
    complete_count="$(count_marker "[READER] STW: Complete" "$log_file")"

    if [[ "$saved_count" -ge "$EXPECTED_OUTPUTS" && "$complete_count" -ge "$EXPECTED_OUTPUTS" ]]; then
        local saved_line
        saved_line="$(grep -F "[PC] Image saved to:" "$log_file" | tail -n 1 || true)"
        log_success "Flow completed successfully (saved=${saved_count}, complete=${complete_count}, required=${EXPECTED_OUTPUTS})."
        [[ -n "$saved_line" ]] && echo "$saved_line"
        return 0
    fi

    log_error "Flow did not complete successfully."
    log_error "Output count requirement not met (saved=${saved_count}, complete=${complete_count}, required=${EXPECTED_OUTPUTS})."
    log_info "Last 80 lines from log:"
    tail -n 80 "$log_file" || true
    return 1
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --app)
            APP_INPUT="${2:-}"
            shift 2
            ;;
        --port)
            PORT="${2:-}"
            shift 2
            ;;
        --baud)
            BAUD="${2:-}"
            shift 2
            ;;
        --image)
            IMAGE_PATH="${2:-}"
            shift 2
            ;;
        --preset)
            BUILD_PRESET="${2:-}"
            shift 2
            ;;
        --timeout)
            TIMEOUT_SECS="${2:-}"
            shift 2
            ;;
        --headless)
            HEADLESS_MODE="true"
            shift
            ;;
        --no-headless)
            HEADLESS_MODE="false"
            shift
            ;;
        --pydiplink-before-flash)
            PYDIPLINK_BEFORE_FLASH=true
            shift
            ;;
        --pydiplink-after-flash)
            PYDIPLINK_BEFORE_FLASH=false
            shift
            ;;
        --pydiplink-wait)
            PYDIPLINK_STARTUP_DELAY_SECS="${2:-}"
            shift 2
            ;;
        --expected-outputs)
            EXPECTED_OUTPUTS="${2:-}"
            shift 2
            ;;
        --pydiplink-arg)
            PYDIPLINK_EXTRA_ARGS+=("${2:-}")
            shift 2
            ;;
        --flash-cmd)
            FLASH_CMD="${2:-}"
            shift 2
            ;;
        --flash-addr)
            FLASH_ADDR="${2:-}"
            shift 2
            ;;
        --st-flash-freq)
            ST_FLASH_FREQ_KHZ="${2:-}"
            shift 2
            ;;
        --st-flash-hot-plug)
            ST_FLASH_HOT_PLUG=true
            shift
            ;;
        --no-st-flash-connect-under-reset|--no-st-flash-cur)
            ST_FLASH_CONNECT_UNDER_RESET=false
            shift
            ;;
        --flash-retries)
            FLASH_RETRIES="${2:-}"
            shift 2
            ;;
        --skip-build)
            SKIP_BUILD=true
            shift
            ;;
        --skip-flash)
            SKIP_FLASH=true
            shift
            ;;
        --skip-run)
            SKIP_RUN=true
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            log_error "Unknown argument: $1"
            usage
            exit 1
            ;;
    esac
done

if [[ "$SKIP_BUILD" != true && -z "$APP_INPUT" ]]; then
    log_error "--app is required unless --skip-build is used."
    usage
    exit 1
fi

if ! [[ "$FLASH_RETRIES" =~ ^[1-9][0-9]*$ ]]; then
    log_error "--flash-retries must be a positive integer."
    exit 1
fi

if ! [[ "$PYDIPLINK_STARTUP_DELAY_SECS" =~ ^[0-9]+$ ]]; then
    log_error "--pydiplink-wait must be a non-negative integer (seconds)."
    exit 1
fi

if ! [[ "$EXPECTED_OUTPUTS" =~ ^[1-9][0-9]*$ ]]; then
    log_error "--expected-outputs must be a positive integer."
    exit 1
fi

case "$HEADLESS_MODE" in
    true|false|auto) ;;
    *)
        log_error "Invalid headless mode value."
        exit 1
        ;;
esac

BUILD_DIR="$PROJECT_ROOT/build/$BUILD_PRESET"
BIN_PATH="$BUILD_DIR/dip-vs.bin"
ELF_PATH="$BUILD_DIR/dip-vs.elf"

trap cleanup EXIT

if [[ "$SKIP_BUILD" != true ]]; then
    APP_PATH="$(resolve_app_path "$APP_INPUT")"
    APP_NAME="$(basename "$APP_PATH")"

    log_info "Building app: $APP_NAME"
    BACKUP_MAIN="$MAIN_C_PATH.backup.test.$RUN_ID"
    cp "$MAIN_C_PATH" "$BACKUP_MAIN"
    cp "$APP_PATH" "$MAIN_C_PATH"

    if [[ -d "$BUILD_DIR" ]]; then
        log_info "Cleaning build directory: $BUILD_DIR"
        rm -rf "$BUILD_DIR"
    fi

    log_info "Configuring CMake preset: $BUILD_PRESET"
    cmake --preset "$BUILD_PRESET"

    log_info "Building: $BUILD_DIR"
    cmake --build "$BUILD_DIR"

    ensure_bin_artifact
    log_success "Build produced: $BIN_PATH"
else
    log_warning "Skipping build step"
    if [[ "$SKIP_FLASH" != true ]]; then
        ensure_bin_artifact
    fi
fi

if [[ "$SKIP_RUN" != true ]]; then
    if ! command -v pydiplink >/dev/null 2>&1; then
        log_error "pydiplink not found in PATH"
        exit 1
    fi

    if [[ -n "$IMAGE_PATH" && ! -f "$IMAGE_PATH" ]]; then
        log_error "Image file not found: $IMAGE_PATH"
        exit 1
    fi
fi

if [[ "$SKIP_RUN" != true && "$SKIP_FLASH" != true && "$PYDIPLINK_BEFORE_FLASH" == true ]]; then
    start_pydiplink_background
    if [[ "$PYDIPLINK_STARTUP_DELAY_SECS" -gt 0 ]]; then
        log_info "Waiting ${PYDIPLINK_STARTUP_DELAY_SECS}s for pydiplink readiness before flash..."
        sleep "$PYDIPLINK_STARTUP_DELAY_SECS"
    fi
fi

if [[ "$SKIP_FLASH" != true ]]; then
    run_flash
    log_success "Flash completed"
else
    log_warning "Skipping flash step"
fi

if [[ "$SKIP_RUN" != true ]]; then
    if [[ "$SKIP_FLASH" != true && "$PYDIPLINK_BEFORE_FLASH" == true ]]; then
        wait_pydiplink_background
    else
        run_pydiplink_foreground
    fi
else
    log_warning "Skipping pydiplink run step"
fi

log_success "Test flow finished"
