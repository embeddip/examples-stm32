/**
 * ============================================================================
 * embedDIP Example 02: Color Space Conversions
 * ============================================================================
 *
 * This example demonstrates:
 * - RGB888 to Grayscale conversion
 * - RGB565 to RGB888 conversion
 * - Image copy operations
 * - Working with different color formats
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

    // Example 1: RGB888 to Grayscale conversion
    embedDIP::Image rgbImg(IMAGE_RES_QVGA, IMAGE_FORMAT_RGB888);
    embedDIP::Image grayImg(IMAGE_RES_QVGA, IMAGE_FORMAT_GRAYSCALE);

    // Fill RGB image with gradient
    uint8_t* rgb_pixels = (uint8_t*)rgbImg.getPixels();
    for (int y = 0; y < rgbImg.getHeight(); y++) {
        for (int x = 0; x < rgbImg.getWidth(); x++) {
            int idx = (y * rgbImg.getWidth() + x) * 3;
            rgb_pixels[idx + 0] = (uint8_t)(x * 255 / rgbImg.getWidth()); // R
            rgb_pixels[idx + 1] = (uint8_t)(y * 255 / rgbImg.getHeight()); // G
            rgb_pixels[idx + 2] = 128; // B
        }
    }

    // Send original RGB image
    serial.send(rgbImg);

    // Convert to grayscale
    rgbImg.cvtColor(grayImg, CVT_RGB888_TO_GRAYSCALE);

    // Send grayscale result
    serial.send(grayImg);

    // Example 2: RGB565 to RGB888 conversion
    embedDIP::Image rgb565Img(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
    embedDIP::Image rgb888Img(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);

    // Fill RGB565 image with color blocks
    uint16_t* rgb565_pixels = (uint16_t*)rgb565Img.getPixels();
    for (int y = 0; y < rgb565Img.getHeight(); y++) {
        for (int x = 0; x < rgb565Img.getWidth(); x++) {
            if (y < rgb565Img.getHeight() / 3) {
                rgb565_pixels[y * rgb565Img.getWidth() + x] = 0xF800; // Red
            } else if (y < 2 * rgb565Img.getHeight() / 3) {
                rgb565_pixels[y * rgb565Img.getWidth() + x] = 0x07E0; // Green
            } else {
                rgb565_pixels[y * rgb565Img.getWidth() + x] = 0x001F; // Blue
            }
        }
    }

    // Send original RGB565 image
    serial.send(rgb565Img);

    // Convert to RGB888
    rgb565Img.cvtColor(rgb888Img, CVT_RGB565_TO_RGB888);

    // Send converted image
    serial.send(rgb888Img);

    // Example 3: Image copy operation
    embedDIP::Image srcImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
    embedDIP::Image dstImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

    // Fill source with pattern
    uint8_t* src_pixels = (uint8_t*)srcImg.getPixels();
    for (int y = 0; y < srcImg.getHeight(); y++) {
        for (int x = 0; x < srcImg.getWidth(); x++) {
            int distance = (x - srcImg.getWidth()/2) * (x - srcImg.getWidth()/2) +
                          (y - srcImg.getHeight()/2) * (y - srcImg.getHeight()/2);
            src_pixels[y * srcImg.getWidth() + x] = (distance < 10000) ? 255 : 0;
        }
    }

    // Send original
    serial.send(srcImg);

    // Copy image
    srcImg.cvtColor(dstImg, CVT_COPY);

    // Send copy
    serial.send(dstImg);

    // All conversions completed successfully

    while (1) {
        ;
    }
}
