#include "main.h"
#include "mnist_inference.h"
#include <embedDIP.hpp>

using namespace embedDIP;

#define IMG_SIZE 28
#define NUM_CLASSES 10

int application() {
  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Image inImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);

  // Initialize serial
  serial.init();

  // Initialize MNIST model
  if (mnist_init() != 0) {
    // Initialization failed
    while (1) {}
  }

  // Capture image from serial
  serial.capture(inImg);

  // Get pixel data
  uint8_t *pixels = (uint8_t *)inImg.pixels();

  // Run inference
  float output[NUM_CLASSES];
  if (mnist_infer(pixels, output) != 0) {
    // Inference failed
    while (1) {}
  }

  // Get predicted digit
  uint8_t predicted_digit = mnist_get_prediction(output);

  // Send result back
  serial.send1D(&predicted_digit, sizeof(uint8_t), 1, SERIAL_DATA_OTHER);

  HAL_Delay(10);

  while (1) {
    ;
  }
}

