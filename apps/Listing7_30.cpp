#include "main.hpp"
#include <embedDIP.hpp>

using namespace std;

volatile int button_flag = 0;
volatile int current_mode = 0;
volatile uint8_t button_press_count = 0;
volatile uint32_t button_press_time = 0;

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
  embedDIP::Image inImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image filteredImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outImg(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);

  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Camera camera(&stm32_ov5640);
  embedDIP::Display display(&stm32_ota5180a);

  serial.init();
  camera.init(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  display.init();

  camera.capture(CONTINUOUS, inImg);
  display.show(inImg);

  vector<vector<float>> sharpenKernel = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

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

          switch (current_mode) {
          case 0: // HistEq + Median filter
            inImg.histEq(filteredImg);
            filteredImg.medianFilter(outImg, 3);
            outImg.convertTo();
            break;

          case 1: // Negative
            inImg.negative(outImg);
            outImg.convertTo();
            break;

          case 2: // Gamma correction (1.5)
            inImg.powerTransform(outImg, 1.5f);
            outImg.convertTo();
            break;

          case 3: // Sharpen (high-pass + add)
            inImg.filter2D(sharpenKernel, filteredImg);
            inImg.add(filteredImg, outImg);
            outImg.convertTo();
            break;
          }

          serial.send(outImg);

          camera.capture(CONTINUOUS, inImg);
        }
      }
    }
  }
}
