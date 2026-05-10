#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

volatile int button_flag = 0;
volatile uint32_t button_press_time = 0;
volatile uint8_t button_press_count = 0;
volatile int current_mode = 0;

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin != GPIO_PIN_11) {
    return;
  }

  uint32_t now = HAL_GetTick();
  static uint32_t last_interrupt_time = 0;

  if ((now - last_interrupt_time) < 50U /*ms*/) {
    return;
  }
  last_interrupt_time = now;

  if (button_press_count > 0 && (now - button_press_time) <= 500U /*ms*/) {
    button_press_count++;
  } else {
    button_press_count = 1;
    button_press_time = now;
  }

  button_flag = 1;
}

int application() {
  embedDIP::Image previewRgb(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  embedDIP::Image gray(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image edges(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image clean(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image gradH(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image gradV(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image mag(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image displayRgb(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Camera camera(&stm32_ov5640);
  embedDIP::Display display(&stm32_ota5180a);

  serial.init();
  camera.init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  display.init();

  camera.capture(CONTINUOUS, previewRgb);
  display.show(previewRgb);

  vector<vector<float>> kernelX = {
      {-1, 0, 1},
      {-2, 0, 2},
      {-1, 0, 1},
  };

  vector<vector<float>> kernelY = {
      {1, 2, 1},
      {0, 0, 0},
      {-1, -2, -1},
  };

  while (1) {

    if (button_flag && button_press_count > 0) {
      uint32_t now = HAL_GetTick();

      if ((now - button_press_time) > 500U /*ms*/) {
        button_flag = 0;
        uint8_t clicks = button_press_count;
        button_press_count = 0;

        if (clicks == 1) {
          current_mode = (current_mode + 1) % 3;

        } else {
          camera.stop();
          previewRgb.cvtColor(gray, CVT_RGB565_TO_GRAYSCALE);

          embedDIP::Image *result = nullptr;
          switch (current_mode) {
          case 0: // LoG-based edge mask.
            gray.logFilter(edges, 1.4f);
            edges.convertTo();
            edges.grayscaleOtsu(clean);
            clean.negative(clean);
            result = &clean;
            break;

          case 1: // Gaussian gradients + magnitude.
            gray.gaussianGradients(gradH, gradV, 1.2f);
            mag.gradientMagnitude(gradH, gradV);
            mag.convertTo();
            mag.grayscaleOtsu(clean);
            result = &clean;
            break;

          case 2: // Sobel + magnitude.
            gray.filter2D(kernelX, gradH);
            gradH.convertTo();
            gray.filter2D(kernelY, gradV);
            gradV.convertTo();
            mag.gradientMagnitude(gradH, gradV);
            mag.convertTo();
            mag.grayscaleOtsu(clean);
            result = &clean;
            break;
          }

          result->cvtColor(displayRgb, CVT_GRAYSCALE_TO_RGB565);
          display.show(displayRgb);
          serial.send(*result);

          camera.capture(CONTINUOUS, previewRgb);
          display.show(previewRgb);
        }
      }
    }
  }
}
