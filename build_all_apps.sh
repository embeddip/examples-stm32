#!/bin/bash

# Build All Apps Script
# This script builds each app from apps/ by injecting USER CODE blocks
# from listing files into the main.c template.

set -e  # Exit on error

# Configuration - dynamically determine project root
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$SCRIPT_DIR"
APPS_DIR="$PROJECT_ROOT/apps"
MAIN_C_PATH="$PROJECT_ROOT/Core/Src/main.c"
BUILD_DIR="$PROJECT_ROOT/build/Debug"
OUTPUT_BASE_DIR="$PROJECT_ROOT/apps/build_outputs"
BUILD_PRESET="Debug"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
log_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
log_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
log_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
log_error() { echo -e "${RED}[ERROR]${NC} $1"; }

# Inject USER CODE blocks from a listing file into main.c template.
# Arguments:
#   1) listing file
#   2) template main.c backup
#   3) output main.c path
inject_user_blocks() {
    local listing_file="$1"
    local template_file="$2"
    local output_file="$3"

    awk '
    function extract_tag(line, begin_kw,   t) {
        t = line
        sub("^.*\\/\\* " begin_kw "[[:space:]]+", "", t)
        sub("[[:space:]]*\\*\\/.*$", "", t)
        gsub(/^[[:space:]]+|[[:space:]]+$/, "", t)
        return t
    }

    # Pass 1: read listing and cache block contents by tag.
    FNR == NR {
        if ($0 ~ /\/\* USER CODE BEGIN[[:space:]]+/) {
            in_src = 1
            src_tag = extract_tag($0, "USER CODE BEGIN")
            next
        }
        if (in_src && $0 ~ /\/\* USER CODE END[[:space:]]+/) {
            in_src = 0
            src_tag = ""
            next
        }
        if (in_src) {
            src_blocks[src_tag] = src_blocks[src_tag] $0 ORS
        }
        next
    }

    # Pass 2: print template, replacing only matching USER CODE blocks.
    {
        if (!skip_dst && $0 ~ /\/\* USER CODE BEGIN[[:space:]]+/) {
            dst_tag = extract_tag($0, "USER CODE BEGIN")

            if (dst_tag in src_blocks) {
                print $0
                printf "%s", src_blocks[dst_tag]
                skip_dst = 1
                skip_tag = dst_tag
                next
            }
        }

        if (skip_dst) {
            if ($0 ~ /\/\* USER CODE END[[:space:]]+/) {
                end_tag = extract_tag($0, "USER CODE END")
                if (end_tag == skip_tag) {
                    print $0
                    skip_dst = 0
                    skip_tag = ""
                }
            }
            next
        }

        print
    }
    ' "$listing_file" "$template_file" > "$output_file"
}

# Check if apps directory exists
if [ ! -d "$APPS_DIR" ]; then
    log_error "Apps directory not found: $APPS_DIR"
    exit 1
fi

# Backup original main.c
log_info "Backing up original main.c..."
BACKUP_MAIN="$MAIN_C_PATH.backup.$(date +%Y%m%d_%H%M%S)"
cp "$MAIN_C_PATH" "$BACKUP_MAIN"
log_success "Backup created: $BACKUP_MAIN"

# Create output directory
mkdir -p "$OUTPUT_BASE_DIR"

# Counter for stats
total_apps=0
successful_builds=0
failed_builds=0
declare -a failed_app_list

# Get list of all C listing apps (excluding build_outputs directory)
mapfile -t app_files < <(find "$APPS_DIR" -maxdepth 1 -type f -name "*.c" | grep -v "build_outputs" | sort)
total_apps=${#app_files[@]}

if [ $total_apps -eq 0 ]; then
    log_error "No .c app files found in $APPS_DIR"
    cp "$BACKUP_MAIN" "$MAIN_C_PATH"
    exit 1
fi

log_info "Found $total_apps apps to build"
echo ""

# Build each app
for app_path in "${app_files[@]}"; do
    app_name=$(basename "$app_path")

    echo "========================================"
    log_info "Building: $app_name"
    echo "========================================"

    app_output_dir="$OUTPUT_BASE_DIR/$app_name"

    # Create output directory for this app
    mkdir -p "$app_output_dir"

    # Inject app USER CODE blocks into main.c
    log_info "Injecting USER CODE blocks from $app_name into main.c..."
    inject_user_blocks "$app_path" "$BACKUP_MAIN" "$MAIN_C_PATH"

    # Clean previous build
    log_info "Cleaning previous build..."
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
    fi

    # Configure CMake
    log_info "Configuring CMake..."
    cd "$PROJECT_ROOT"
    if ! cmake --preset "$BUILD_PRESET" > "$app_output_dir/cmake_config.log" 2>&1; then
        log_error "CMake configuration failed for $app_name"
        log_info "Check $app_output_dir/cmake_config.log for details"
        failed_builds=$((failed_builds + 1))
        failed_app_list+=("$app_name")

        # Save error status
        echo "Build Status: FAILED (CMake Configuration)" > "$app_output_dir/build_info.txt"
        continue
    fi

    # Build
    log_info "Building $app_name..."
    if ! cmake --build "$BUILD_DIR" > "$app_output_dir/build.log" 2>&1; then
        log_error "Build failed for $app_name"
        log_info "Check $app_output_dir/build.log for details"

        # Extract error summary
        tail -50 "$app_output_dir/build.log" > "$app_output_dir/build_errors.txt"

        failed_builds=$((failed_builds + 1))
        failed_app_list+=("$app_name")

        # Save error status
        echo "Build Status: FAILED (Compilation)" > "$app_output_dir/build_info.txt"
        continue
    fi

    # Copy build artifacts
    log_info "Copying build artifacts..."
    artifact_count=0

    if [ -f "$BUILD_DIR/dip-vs.elf" ]; then
        cp "$BUILD_DIR/dip-vs.elf" "$app_output_dir/${app_name}.elf"
        artifact_count=$((artifact_count + 1))
        log_success "Copied: ${app_name}.elf"
    fi

    if [ -f "$BUILD_DIR/dip-vs.map" ]; then
        cp "$BUILD_DIR/dip-vs.map" "$app_output_dir/${app_name}.map"
        artifact_count=$((artifact_count + 1))
        log_success "Copied: ${app_name}.map"
    fi

    if [ -f "$BUILD_DIR/dip-vs.bin" ]; then
        cp "$BUILD_DIR/dip-vs.bin" "$app_output_dir/${app_name}.bin"
        artifact_count=$((artifact_count + 1))
        log_success "Copied: ${app_name}.bin"
    fi

    if [ -f "$BUILD_DIR/dip-vs.hex" ]; then
        cp "$BUILD_DIR/dip-vs.hex" "$app_output_dir/${app_name}.hex"
        artifact_count=$((artifact_count + 1))
        log_success "Copied: ${app_name}.hex"
    fi

    # Get build size info
    if [ -f "$app_output_dir/${app_name}.elf" ]; then
        if command -v arm-none-eabi-size &> /dev/null; then
            size_info=$(arm-none-eabi-size "$app_output_dir/${app_name}.elf" 2>/dev/null || echo "Size command failed")
        else
            size_info="arm-none-eabi-size not found in PATH"
        fi
    else
        size_info="ELF file not found"
    fi

    # Save build info
    cat > "$app_output_dir/build_info.txt" <<EOF
===========================================
Build Information: $app_name
===========================================

Build Date: $(date)
Build Preset: $BUILD_PRESET
Build Status: SUCCESS
Artifacts Saved: $artifact_count

Size Information:
$size_info

Build Location: $app_output_dir
EOF

    successful_builds=$((successful_builds + 1))
    log_success "✓ Build completed for $app_name ($artifact_count artifacts saved)"
    echo ""
done

# Restore original main.c
log_info "Restoring original main.c..."
cp "$BACKUP_MAIN" "$MAIN_C_PATH"
log_success "Original main.c restored"

# Generate summary report
SUMMARY_REPORT="$OUTPUT_BASE_DIR/BUILD_SUMMARY.txt"
cat > "$SUMMARY_REPORT" <<EOF
===========================================
        BUILD ALL APPS - SUMMARY
===========================================

Build Date: $(date)
Build Preset: $BUILD_PRESET

Total Apps: $total_apps
Successful Builds: $successful_builds
Failed Builds: $failed_builds

Success Rate: $(awk "BEGIN {printf \"%.1f\", ($successful_builds/$total_apps)*100}")%

EOF

if [ $failed_builds -gt 0 ]; then
    cat >> "$SUMMARY_REPORT" <<EOF
-------------------------------------------
Failed Apps:
-------------------------------------------
EOF
    for failed_app in "${failed_app_list[@]}"; do
        echo "  - $failed_app" >> "$SUMMARY_REPORT"
    done
fi

cat >> "$SUMMARY_REPORT" <<EOF

-------------------------------------------
Build Output Location: $OUTPUT_BASE_DIR
Original main.c Backup: $BACKUP_MAIN
-------------------------------------------
EOF

# Print summary to console
echo ""
echo "========================================"
echo "        BUILD SUMMARY"
echo "========================================"
log_info "Total apps: $total_apps"
log_success "Successful builds: $successful_builds"

if [ $failed_builds -gt 0 ]; then
    log_error "Failed builds: $failed_builds"
    echo ""
    log_error "Failed apps:"
    for failed_app in "${failed_app_list[@]}"; do
        echo "  - $failed_app"
    done
fi

echo ""
log_info "Build outputs: $OUTPUT_BASE_DIR"
log_info "Build summary: $SUMMARY_REPORT"
log_info "Original main.c backup: $BACKUP_MAIN"
echo "========================================"

# Exit with appropriate code
if [ $failed_builds -gt 0 ]; then
    exit 1
else
    exit 0
fi
