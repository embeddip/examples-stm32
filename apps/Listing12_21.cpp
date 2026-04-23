#include "main.h"
#include "mnist_inference.h"
#include <embedDIP.hpp>

using namespace embedDIP;

#define IMG_SIZE 28
#define NUM_CLASSES 10

int application() {
  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Image inImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);

  serial.init();
  mnist_init();

  serial.capture(inImg);

  uint8_t *pixels = (uint8_t *)inImg.pixels();
  float output[NUM_CLASSES];
  mnist_infer(pixels, output);

  uint8_t predicted_digit = mnist_get_prediction(output);
  serial.send1D(&predicted_digit, sizeof(uint8_t), 1, SERIAL_DATA_OTHER);

  while (1) {
    ;
  }
}

