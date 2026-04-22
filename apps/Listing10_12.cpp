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
  embedDIP::Image denoised(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image bin(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image morph(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image labels(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image displayRgb(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Camera camera(&stm32_ov5640);
  embedDIP::Display display(&stm32_ota5180a);

  serial.init();
  camera.init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  display.init();

  camera.capture(CONTINUOUS, previewRgb);
  display.show(previewRgb);

  embedDIP::Kernel k;
  k.getStructuringElement(MORPH_ELLIPSE, 3);

  vector<vector<float>> blur3x3 = {
      {1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f},
      {1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f},
      {1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f},
  };

  while (1) {

    if (button_flag && button_press_count > 0) {
      uint32_t now = HAL_GetTick();

      if ((now - button_press_time) > 500U /*ms*/) {
        button_flag = 0;
        uint8_t clicks = button_press_count;
        button_press_count = 0;

        if (clicks == 1) {
          current_mode = (current_mode + 1) % 4;

        } else {
          camera.stop();
          previewRgb.cvtColor(gray, CVT_RGB565_TO_GRAYSCALE);
          gray.filter2D(blur3x3, denoised);
          denoised.convertTo();

          switch (current_mode) {
          case 0: // Binary mask
            denoised.grayscaleThreshold(bin, 140);
            bin.cvtColor(morph, CVT_COPY);
            break;

          case 1: // Binary + opening
            denoised.grayscaleThreshold(bin, 140);
            bin.opening(morph, k, 2);
            break;

          case 2: // Binary + closing
            denoised.grayscaleThreshold(bin, 140);
            bin.closing(morph, k, 2);
            break;

          case 3: // Smart inspection
            denoised.grayscaleThreshold(bin, 140);
            bin.opening(morph, k, 2);
            morph.connectedComponents(labels, NULL);
            labels.normalize();
            labels.negative(labels);
            labels.cvtColor(morph, CVT_COPY);
            break;
          }

          morph.cvtColor(displayRgb, CVT_GRAYSCALE_TO_RGB565);
          display.show(displayRgb);
          serial.send(morph);

          camera.capture(CONTINUOUS, previewRgb);
          display.show(previewRgb);
        }
      }
    }
  }
}
