/**
 * ============================================================================
 * embedDIP Example 01: Basic Image Creation
 * ============================================================================
 *
 * This example demonstrates:
 * - Creating images with predefined resolutions
 * - Creating images with custom width/height
 * - Working with different pixel formats
 * - Basic image operations
 *
 * To use this example:
 * 1. Copy this file to CoreCPP/Src/ directory
 * 2. Rename or replace main.cpp
 * 3. Build and flash to STM32F7
 *
 * Platform: STM32F7
 * ============================================================================
 */

#include "main.h"
#include <embedDIP.hpp>

using namespace std;

int application() {
    embedDIP::Serial serial(&stm32_uart);
    serial.init();

    // Example 1: Create image with standard resolution (QVGA = 320x240)
    embedDIP::Image img1(IMAGE_RES_QVGA, IMAGE_FORMAT_GRAYSCALE);

    // Fill image with gradient pattern
    uint8_t* pixels = (uint8_t*)img1.getPixels();
    for (int y = 0; y < img1.getHeight(); y++) {
        for (int x = 0; x < img1.getWidth(); x++) {
            pixels[y * img1.getWidth() + x] = (uint8_t)(x * 255 / img1.getWidth());
        }
    }

    // Send image via serial (optional - for visualization)
    serial.send(img1);

    // Example 2: Create RGB565 image
    embedDIP::Image img2(IMAGE_RES_QVGA, IMAGE_FORMAT_RGB565);

    // Fill with colored blocks
    uint16_t* rgb_pixels = (uint16_t*)img2.getPixels();
    for (int y = 0; y < img2.getHeight(); y++) {
        for (int x = 0; x < img2.getWidth(); x++) {
            if (y < 80) {
                rgb_pixels[y * img2.getWidth() + x] = 0xF800; // Red
            } else if (y < 160) {
                rgb_pixels[y * img2.getWidth() + x] = 0x07E0; // Green
            } else {
                rgb_pixels[y * img2.getWidth() + x] = 0x001F; // Blue
            }
        }
    }

    serial.send(img2);

    // Example 3: Create RGB888 image
    embedDIP::Image img3(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);

    // Fill with custom pattern
    uint8_t* rgb888_pixels = (uint8_t*)img3.getPixels();
    for (int i = 0; i < img3.getWidth() * img3.getHeight() * 3; i += 3) {
        rgb888_pixels[i + 0] = 255; // R
        rgb888_pixels[i + 1] = 128; // G
        rgb888_pixels[i + 2] = 64;  // B
    }

    serial.send(img3);

    // Example 4: Custom size image (100x100)
    embedDIP::Image img4(100, 100, IMAGE_FORMAT_GRAYSCALE);

    // Fill with checkerboard pattern
    uint8_t* check_pixels = (uint8_t*)img4.getPixels();
    for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 100; x++) {
            check_pixels[y * 100 + x] = ((x / 10 + y / 10) % 2) ? 255 : 0;
        }
    }

    serial.send(img4);

    // All images created successfully
    // Images will be automatically cleaned up when going out of scope

    while (1) {
        ;
    }
}
