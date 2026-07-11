# Embedded Digital Image Processing with Microcontrollers: STM32 Examples

Source repository: https://github.com/embeddip/examples-stm32

This repository contains STM32 examples and support files for the book *Embedded Digital Image Processing with Microcontrollers*. The project targets STM32F746-based development with STM32CubeMX-generated support files, CMake, and the GNU Arm Embedded toolchain.

## Contents

- `Core/`: STM32 application source and headers.
- `Drivers/`: STM32 HAL, CMSIS, CMSIS-DSP, and CMSIS-NN files.
- `Middlewares/`: third-party middleware used by selected examples.
- `LIBJPEG/`: JPEG support files.
- `embedDIP/`: local copy of the embedded digital image processing library.
- `apps/`: listing applications that can be built by replacing `Core/Src/main.c`.
- `build_all_apps.sh`: script for compiling the listing applications.
- `CMakePresets.json`: CMake presets for Debug, Release, RelWithDebInfo, and MinSizeRel builds.

## Requirements

- CMake 3.22 or newer
- Ninja
- GNU Arm Embedded toolchain with `arm-none-eabi-gcc`
- STM32CubeMX or STM32 VS Code tooling for project regeneration or board-specific changes
- STM32F746 target board, such as STM32F746G-DISCO

## Build

Configure the Debug build:

```bash
cmake --preset Debug
```

Build the Debug configuration:

```bash
cmake --build build/Debug
```

Other available presets are `Release`, `RelWithDebInfo`, and `MinSizeRel`.

## Build All Listing Applications

Build every file in `apps/`:

```bash
./build_all_apps.sh
```

The script copies each listing application into `Core/Src/main.c`, builds it, saves the generated artifacts, and restores the original `main.c`. Build logs and generated artifacts are written under `apps/build_outputs/`.

## Branches

The STM32 examples are organized across branches:

| Branch | Contents |
| --- | --- |
| [`main`](https://github.com/embeddip/examples-stm32/tree/main) | Default STM32F746 project branch. |
| [`main-c-apps`](https://github.com/embeddip/examples-stm32/tree/main-c-apps) | C listing applications. |
| [`main-cpp-apps`](https://github.com/embeddip/examples-stm32/tree/main-cpp-apps) | C++ listing applications. |
| [`main-c-ai-apps`](https://github.com/embeddip/examples-stm32/tree/main-c-ai-apps) | C AI listing applications. |
| [`main-cpp-ai-apps`](https://github.com/embeddip/examples-stm32/tree/main-cpp-ai-apps) | C++ AI listing applications. |
| [`main-c-tfmicro-app`](https://github.com/embeddip/examples-stm32/tree/main-c-tfmicro-app) | TensorFlow Lite Micro C applications. |

## Related Repositories

- Core library: https://github.com/embeddip/embedDIP
- Python UART transfer tool: https://github.com/embeddip/PyDIPLink
- ESP32 examples: https://github.com/embeddip/examples-esp32

## License

See the license files included with this repository and with the third-party components under `Drivers/`, `Middlewares/`, and `LIBJPEG/`.
