#!/usr/bin/env bash

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEST_SCRIPT="$SCRIPT_DIR/test_app_flow.sh"
COMMANDS_FILE="$SCRIPT_DIR/app_commands.txt"
FAIL_FAST=false
DRY_RUN=false
RESET_BETWEEN_RUNS=true
RESET_CMD="st-flash reset"
RESET_WAIT_SECS="1"
RUN_ID="$(date +%Y%m%d_%H%M%S)"
SUMMARY_FILE="$SCRIPT_DIR/test_logs/batch_run_${RUN_ID}.log"

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
    cat <<USAGE
Usage:
  $(basename "$0") [options]

Options:
  --file <path>      Commands manifest file (default: $COMMANDS_FILE)
  --fail-fast        Stop on first failed command
  --dry-run          Print commands without executing
  --no-reset-between-runs
                     Do not reset board after each run
  --reset-cmd <cmd>  Reset command (default: "$RESET_CMD")
  --reset-wait <sec> Wait time after reset (default: $RESET_WAIT_SECS)
  -h, --help         Show this help

Manifest format:
  - One command per line
  - Empty lines and lines starting with # are ignored
  - Each line can be either:
    1) args for test_app_flow.sh (recommended), e.g.:
       --app listing7_1 --expected-outputs 2
    2) a full command containing test_app_flow.sh

Optional env var:
  TEST_FLOW_DEFAULT_ARGS
    Appended to every command line.
    Example:
      TEST_FLOW_DEFAULT_ARGS='--port /dev/ttyACM0 --baud 2000000 --headless'
USAGE
}

trim_line() {
    local s="$1"
    s="${s#"${s%%[![:space:]]*}"}"
    s="${s%"${s##*[![:space:]]}"}"
    printf '%s' "$s"
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --file)
            COMMANDS_FILE="${2:-}"
            shift 2
            ;;
        --fail-fast)
            FAIL_FAST=true
            shift
            ;;
        --dry-run)
            DRY_RUN=true
            shift
            ;;
        --no-reset-between-runs)
            RESET_BETWEEN_RUNS=false
            shift
            ;;
        --reset-cmd)
            RESET_CMD="${2:-}"
            shift 2
            ;;
        --reset-wait)
            RESET_WAIT_SECS="${2:-}"
            shift 2
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

if [[ ! -f "$TEST_SCRIPT" ]]; then
    log_error "Missing test runner script: $TEST_SCRIPT"
    exit 1
fi

if [[ ! -f "$COMMANDS_FILE" ]]; then
    log_error "Commands file not found: $COMMANDS_FILE"
    exit 1
fi

if ! [[ "$RESET_WAIT_SECS" =~ ^[0-9]+$ ]]; then
    log_error "--reset-wait must be a non-negative integer (seconds)."
    exit 1
fi

mkdir -p "$(dirname "$SUMMARY_FILE")"

line_no=0
total=0
passed=0
failed=0
skipped=0

{
    echo "========================================"
    echo "Batch Run Summary"
    echo "Date: $(date)"
    echo "Commands File: $COMMANDS_FILE"
    echo "Default Args: ${TEST_FLOW_DEFAULT_ARGS:-<none>}"
    echo "Reset Between Runs: $RESET_BETWEEN_RUNS"
    echo "Reset Cmd: $RESET_CMD"
    echo "Reset Wait: ${RESET_WAIT_SECS}s"
    echo "========================================"
} > "$SUMMARY_FILE"

while IFS= read -r raw_line || [[ -n "$raw_line" ]]; do
    line_no=$((line_no + 1))
    line="$(trim_line "$raw_line")"

    if [[ -z "$line" || "$line" == \#* ]]; then
        skipped=$((skipped + 1))
        continue
    fi

    total=$((total + 1))

    if [[ "$line" == *"test_app_flow.sh"* ]]; then
        cmd="$line"
    else
        cmd="\"$TEST_SCRIPT\" $line"
    fi

    if [[ -n "${TEST_FLOW_DEFAULT_ARGS:-}" ]]; then
        cmd="$cmd ${TEST_FLOW_DEFAULT_ARGS}"
    fi

    log_info "[$total] Running: $cmd"
    echo "[$total] $cmd" >> "$SUMMARY_FILE"

    if [[ "$DRY_RUN" == true ]]; then
        passed=$((passed + 1))
        echo "  -> DRY RUN" >> "$SUMMARY_FILE"
        continue
    fi

    set +e
    bash -lc "$cmd"
    rc=$?
    set -e

    if [[ $rc -eq 0 ]]; then
        passed=$((passed + 1))
        log_success "[$total] OK"
        echo "  -> OK" >> "$SUMMARY_FILE"
    else
        failed=$((failed + 1))
        log_error "[$total] FAILED (exit=$rc)"
        echo "  -> FAILED (exit=$rc)" >> "$SUMMARY_FILE"

        if [[ "$FAIL_FAST" == true ]]; then
            log_warning "Fail-fast enabled; stopping batch run."
            break
        fi
    fi

    if [[ "$RESET_BETWEEN_RUNS" == true ]]; then
        log_info "[$total] Resetting board: $RESET_CMD"
        set +e
        bash -lc "$RESET_CMD"
        reset_rc=$?
        set -e

        if [[ $reset_rc -ne 0 ]]; then
            log_warning "[$total] Reset command failed (exit=$reset_rc), continuing."
            echo "  -> RESET FAILED (exit=$reset_rc)" >> "$SUMMARY_FILE"
        else
            echo "  -> RESET OK" >> "$SUMMARY_FILE"
        fi

        if [[ "$RESET_WAIT_SECS" -gt 0 ]]; then
            sleep "$RESET_WAIT_SECS"
        fi
    fi
done < "$COMMANDS_FILE"

echo "" | tee -a "$SUMMARY_FILE"
{
    echo "========================================"
    echo "Executed: $total"
    echo "Passed:   $passed"
    echo "Failed:   $failed"
    echo "Skipped:  $skipped"
    echo "Summary:  $SUMMARY_FILE"
    echo "========================================"
} | tee -a "$SUMMARY_FILE"

if [[ "$failed" -gt 0 ]]; then
    exit 1
fi

exit 0
