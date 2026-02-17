/**
 * ============================================================================
 * embedDIP Example 03: Channel Management
 * ============================================================================
 *
 * This example demonstrates:
 * - Creating and managing image channels
 * - Channel allocation for advanced processing
 * - Working with multi-channel data
 * - Channel-based operations
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

    // Example 1: Create image and allocate channels
    embedDIP::Image img1(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);

    // Fill with test pattern
    uint8_t* pixels = (uint8_t*)img1.getPixels();
    for (int y = 0; y < img1.getHeight(); y++) {
        for (int x = 0; x < img1.getWidth(); x++) {
            int idx = (y * img1.getWidth() + x) * 3;
            pixels[idx + 0] = (uint8_t)((x + y) % 256); // R
            pixels[idx + 1] = (uint8_t)(x % 256);       // G
            pixels[idx + 2] = (uint8_t)(y % 256);       // B
        }
    }

    // Send original image
    serial.send(img1);

    // Allocate 3 floating-point channels for RGB processing
    img1.createChals(3);

    // Access and manipulate channel data
    if (!img1.isChalsEmpty()) {
        float* ch0 = img1.getChannel(0);
        float* ch1 = img1.getChannel(1);
        float* ch2 = img1.getChannel(2);

        // Example: Extract RGB values into separate channels
        for (int i = 0; i < img1.getWidth() * img1.getHeight(); i++) {
            ch0[i] = (float)pixels[i * 3 + 0]; // Red channel
            ch1[i] = (float)pixels[i * 3 + 1]; // Green channel
            ch2[i] = (float)pixels[i * 3 + 2]; // Blue channel
        }

        // Example: Manipulate channel data (apply scaling)
        for (int i = 0; i < img1.getWidth() * img1.getHeight(); i++) {
            ch0[i] *= 0.5f; // Reduce red intensity
            ch1[i] *= 1.2f; // Increase green intensity
            ch2[i] *= 0.8f; // Slightly reduce blue
        }

        // Write channels back to image
        for (int i = 0; i < img1.getWidth() * img1.getHeight(); i++) {
            pixels[i * 3 + 0] = (uint8_t)(ch0[i] > 255 ? 255 : ch0[i]);
            pixels[i * 3 + 1] = (uint8_t)(ch1[i] > 255 ? 255 : ch1[i]);
            pixels[i * 3 + 2] = (uint8_t)(ch2[i] > 255 ? 255 : ch2[i]);
        }

        // Send modified image
        serial.send(img1);
    }

    // Example 2: Grayscale image with single channel processing
    embedDIP::Image grayImg(IMAGE_RES_QVGA, IMAGE_FORMAT_GRAYSCALE);

    // Fill with gradient
    uint8_t* gray_pixels = (uint8_t*)grayImg.getPixels();
    for (int y = 0; y < grayImg.getHeight(); y++) {
        for (int x = 0; x < grayImg.getWidth(); x++) {
            gray_pixels[y * grayImg.getWidth() + x] = (uint8_t)(x * 255 / grayImg.getWidth());
        }
    }

    // Send original
    serial.send(grayImg);

    // Allocate single channel
    grayImg.createChals(1);

    if (!grayImg.isChalsEmpty()) {
        float* channel = grayImg.getChannel(0);

        // Convert to float and apply processing (example: histogram equalization prep)
        for (int i = 0; i < grayImg.getWidth() * grayImg.getHeight(); i++) {
            channel[i] = (float)gray_pixels[i];
        }

        // Apply some transformation (example: contrast enhancement)
        for (int i = 0; i < grayImg.getWidth() * grayImg.getHeight(); i++) {
            channel[i] = (channel[i] - 128.0f) * 1.5f + 128.0f;
            if (channel[i] < 0) channel[i] = 0;
            if (channel[i] > 255) channel[i] = 255;
        }

        // Write back to image
        for (int i = 0; i < grayImg.getWidth() * grayImg.getHeight(); i++) {
            gray_pixels[i] = (uint8_t)channel[i];
        }

        // Send processed result
        serial.send(grayImg);
    }

    // Example 3: Multi-channel operations with HSI color space
    embedDIP::Image hsiImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
    embedDIP::Image rgbForHSI(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888);

    // Create a simple colored pattern
    uint8_t* hsi_pixels = (uint8_t*)rgbForHSI.getPixels();
    for (int y = 0; y < rgbForHSI.getHeight(); y++) {
        for (int x = 0; x < rgbForHSI.getWidth(); x++) {
            int idx = (y * rgbForHSI.getWidth() + x) * 3;
            // Create a simple pattern for HSI conversion
            hsi_pixels[idx + 0] = (uint8_t)(255 * x / rgbForHSI.getWidth());
            hsi_pixels[idx + 1] = (uint8_t)(255 * y / rgbForHSI.getHeight());
            hsi_pixels[idx + 2] = 128;
        }
    }

    serial.send(rgbForHSI);

    // Convert to HSI (requires channels)
    rgbForHSI.createChals(3);
    rgbForHSI.cvtColor(hsiImg, CVT_RGB888_TO_HSI);

    // Send HSI result
    hsiImg.convertTo();
    serial.send(hsiImg);

    // All channel operations completed successfully

    while (1) {
        ;
    }
}
