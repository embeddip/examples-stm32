# embedDIP Example Programs for STM32F7

This directory contains example programs demonstrating the usage of the embedDIP library on STM32F7 platform using the C++ wrapper API.

## 📚 Available Examples

### 01_basic_image_creation.cpp
**Topics Covered:**
- Creating images with predefined resolutions (VGA, QVGA, WQVGA, etc.)
- Creating images with custom width/height
- Working with different pixel formats (GRAYSCALE, RGB565, RGB888)
- Filling images with patterns
- Sending images via serial interface

**Key Classes & Methods:**
- `embedDIP::Image` - Image object constructor
- `getPixels()` - Access pixel data
- `getWidth()`, `getHeight()` - Get image dimensions
- `embedDIP::Serial` - Serial communication

### 02_color_conversion.cpp
**Topics Covered:**
- RGB888 to Grayscale conversion
- RGB565 to RGB888 conversion
- Image copy operations
- Working with different color formats
- Color space transformations

**Key Methods:**
- `cvtColor()` - Convert between color spaces
- `CVT_RGB888_TO_GRAYSCALE` - Conversion code
- `CVT_RGB565_TO_RGB888` - Conversion code
- `CVT_COPY` - Image copy operation

### 03_channel_management.cpp
**Topics Covered:**
- Allocating floating-point channels for advanced processing
- Working with multi-channel data (RGB, HSI)
- Channel-based image manipulation
- Accessing and modifying channel data
- HSI color space conversion

**Key Methods:**
- `createChals()` - Allocate floating-point channels
- `isChalsEmpty()` - Check if channels are allocated
- `getChannel()` - Access channel data
- Channel-based processing techniques

## 🔧 How to Use These Examples

These examples are designed to work with the STM32F7 project structure in this repository.

### Step-by-Step Instructions:

1. **Choose an example** you want to run (e.g., `01_basic_image_creation.cpp`)

2. **Copy the example file** to the CoreCPP/Src/ directory:
   ```bash
   cp examples-stm32/examples/01_basic_image_creation.cpp CoreCPP/Src/
   ```

3. **Backup or rename** the existing `main.cpp` (optional):
   ```bash
   cd CoreCPP/Src/
   mv main.cpp main_backup.cpp
   ```

4. **Rename the example** to `main.cpp`:
   ```bash
   mv 01_basic_image_creation.cpp main.cpp
   ```

5. **Build the project** using STM32CubeIDE or your build system:
   - Open the project in STM32CubeIDE
   - Click Build (Ctrl+B)
   - Wait for compilation to complete

6. **Flash to STM32F7** board:
   - Connect your STM32F7 board via USB
   - Click Run or Debug
   - The example will execute on the hardware

7. **View results** via serial interface:
   - Connect serial terminal (115200 baud, 8N1)
   - Images will be transmitted via the serial protocol
   - Use embedDIP viewer or compatible tool to visualize

## 📖 Learning Path

**Recommended order for beginners:**
1. **01_basic_image_creation.cpp** - Start here to understand image creation and basic operations
2. **02_color_conversion.cpp** - Learn color space conversions and format handling
3. **03_channel_management.cpp** - Advanced multi-channel processing and transformations

## 💡 Understanding the Code Structure

All examples follow this pattern:

```cpp
#include "main.h"
#include <embedDIP.hpp>

using namespace std;

int application() {
    // Initialize serial communication
    embedDIP::Serial serial(&stm32_uart);
    serial.init();

    // Create images
    embedDIP::Image img(IMAGE_RES_QVGA, IMAGE_FORMAT_GRAYSCALE);

    // Process images
    // ... your code here ...

    // Send results via serial
    serial.send(img);

    // Loop forever (embedded system requirement)
    while (1) {
        ;
    }
}
```

**Key Points:**
- The `application()` function is called from the main system initialization
- Hardware setup (clocks, peripherals) is handled by the HAL
- `stm32_uart` is a global UART device object defined in the project
- Images are automatically cleaned up when going out of scope (C++ RAII)
- The infinite loop at the end prevents the function from returning

## 🛠️ Common Patterns

### Creating Images
```cpp
// Standard resolution
embedDIP::Image img1(IMAGE_RES_QVGA, IMAGE_FORMAT_GRAYSCALE);

// Custom size
embedDIP::Image img2(320, 240, IMAGE_FORMAT_RGB888);
```

### Accessing Pixels
```cpp
uint8_t* pixels = (uint8_t*)img.getPixels();
pixels[y * img.getWidth() + x] = 255;
```

### Color Conversion
```cpp
embedDIP::Image src(IMAGE_RES_QVGA, IMAGE_FORMAT_RGB888);
embedDIP::Image dst(IMAGE_RES_QVGA, IMAGE_FORMAT_GRAYSCALE);
src.cvtColor(dst, CVT_RGB888_TO_GRAYSCALE);
```

### Channel Operations
```cpp
img.createChals(3); // Allocate 3 channels
float* channel0 = img.getChannel(0);
// Process channel data...
```

### Serial Communication
```cpp
embedDIP::Serial serial(&stm32_uart);
serial.init();
serial.capture(img);  // Capture from camera
serial.send(img);     // Send via serial
```

## 🔗 Additional Resources

- **embedDIP C++ API**: See `embedDIP/embedDIP.hpp` and `embedDIP/wrapper/`
- **embedDIP C API**: See `embedDIP/embedDIP.h`
- **Core Functions**: See `embedDIP/core/` directory
- **Image Processing**: See `embedDIP/imgproc/` directory
- **Device Drivers**: See `embedDIP/device/` directory
- **Project Documentation**: See `embedDIP/IMPROVEMENTS.md`

## 🐛 Troubleshooting

**Problem**: Build errors about missing `main.h`
- **Solution**: Make sure you copied the example to `CoreCPP/Src/` directory, not a different location

**Problem**: `stm32_uart` undefined reference
- **Solution**: This object is defined in the main project - ensure you're building within the STM32 project structure

**Problem**: Memory allocation failures
- **Solution**: Check heap size in your linker script (`.ld` file)
- **Solution**: Use smaller image resolutions (WQVGA instead of VGA)

**Problem**: Serial transmission not working
- **Solution**: Verify UART configuration matches your serial terminal settings
- **Solution**: Check that UART pins are correctly configured in CubeMX

**Problem**: Images appear corrupted
- **Solution**: Verify the pixel format matches what your viewer expects
- **Solution**: Use `convertTo()` method before sending if needed

## 📝 License

These examples are part of the embedDIP project and are licensed under MIT License.
See the LICENSE file in the embedDIP directory for details.

## 🤝 Contributing

Found a bug or have an idea for a new example?
Please open an issue or submit a pull request!

---

**Note**: These examples use the C++ wrapper API which provides RAII (Resource Acquisition Is Initialization) for automatic memory management. If you prefer the C API, refer to the embedDIP C headers and test files.
