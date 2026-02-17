# GitHub Actions Workflows

This directory contains automated CI/CD workflows for the STM32 examples project.

## 📋 Available Workflows

### 1. **build.yml** - STM32 Build Workflow
**Triggers:** Push/PR to main or develop branches

**What it does:**
- ✅ Downloads and caches ARM GNU Toolchain (13.2.rel1)
- ✅ Configures CMake project with Ninja generator
- ✅ Builds firmware for STM32F7
- ✅ Shows binary size analysis
- ✅ Uploads build artifacts (.elf, .bin, .hex)

**Performance:**
- First run: ~1.5 minutes
- Cached runs: ~20 seconds

**Artifacts:**
- Available for 30 days after build
- Download from Actions tab → Build run → Artifacts section

---

### 2. **code-quality.yml** - Static Analysis Workflow
**Triggers:** Push/PR to main or develop branches

**What it does:**
- 🔍 Runs cppcheck static analysis
- 🎨 Checks code formatting (clang-format)
- 📊 Generates code statistics
- 📝 Scans for TODO/FIXME comments
- 🔎 Checks for common issues (assert, printf, NULL vs nullptr)

**Artifacts:**
- Cppcheck XML report (30 days retention)

---

## 🚀 Usage

### View Build Status
Go to: `https://github.com/YOUR_USERNAME/examples-stm32/actions`

### Add Status Badge to README
```markdown
[![Build Status](https://github.com/YOUR_USERNAME/examples-stm32/actions/workflows/build.yml/badge.svg)](https://github.com/YOUR_USERNAME/examples-stm32/actions)
```

### Download Build Artifacts
1. Go to Actions tab
2. Click on a successful build run
3. Scroll to "Artifacts" section
4. Download `stm32-firmware-XXXXXX.zip`

### Local Testing
To test the same build locally:
```bash
# Download toolchain (first time only)
cd ~
wget https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz
tar xf arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz

# Add to PATH
export PATH=$HOME/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi/bin:$PATH

# Build
mkdir -p build && cd build
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/gcc-arm-none-eabi.cmake
ninja
```

### Code Formatting
To auto-format your code:
```bash
# Install clang-format
sudo apt-get install clang-format

# Format all C/C++ files
find embedDIP CoreCPP -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \
  | grep -v "Drivers/" \
  | xargs clang-format -i
```

---

## 🔧 Customization

### Change Build Type
Edit `build.yml` line 53:
```yaml
-DCMAKE_BUILD_TYPE=Release  # Change to Debug for debug builds
```

### Add More Branches
Edit trigger sections in both workflows:
```yaml
on:
  push:
    branches: [ main, develop, feature/* ]  # Add your branches here
```

### Modify Cppcheck Rules
Edit `code-quality.yml` cppcheck command (line 50+):
```yaml
cppcheck \
  --enable=all \  # Enable all checks
  --error-exitcode=1 \  # Fail CI on errors
  # ... other options
```

---

## 📊 Performance Optimization

### Toolchain Caching
The workflows use GitHub Actions cache to store the ARM toolchain:
- **Cache Key:** `arm-gnu-toolchain-13.2.rel1-x86_64-{OS}`
- **Size:** ~460 MB
- **Expiry:** 7 days of inactivity

### Build Caching (Optional)
To add CMake build cache:
```yaml
- name: Cache CMake Build
  uses: actions/cache@v3
  with:
    path: build
    key: cmake-build-${{ hashFiles('**/CMakeLists.txt') }}
```

---

## 🐛 Troubleshooting

### Build Fails with "toolchain not found"
- Check if ARM toolchain download succeeded
- Verify PATH is set correctly
- Check toolchain cache status

### Code Quality Fails
- Review cppcheck output in job logs
- Check formatting issues
- Run locally to debug

### Slow First Build
- Normal! Downloading 460MB toolchain takes time
- Subsequent builds use cache (~20 seconds)
- Consider using Docker image for even faster builds

---

## 📚 References

- [ARM GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- [CMake Documentation](https://cmake.org/documentation/)
- [Cppcheck Manual](http://cppcheck.sourceforge.net/manual.pdf)
- [GitHub Actions Cache](https://docs.github.com/en/actions/using-workflows/caching-dependencies-to-speed-up-workflows)

---

**Last Updated:** February 2026
