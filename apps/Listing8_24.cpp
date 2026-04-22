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

  // Processing path.
  embedDIP::Image grayWqvga(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image work256(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image tmp256(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image out256(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image fftImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image filterImg(256, 256, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image outWqvga(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image displayRgb(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Camera camera(&stm32_ov5640);
  embedDIP::Display display(&stm32_ota5180a);

  serial.init();
  camera.init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
  display.init();

  // Start live camera feed.
  camera.capture(CONTINUOUS, previewRgb);
  display.show(previewRgb);

  vector<vector<float>> sharpenKernel = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

  while (1) {

    if (button_flag && button_press_count > 0) {
      uint32_t now = HAL_GetTick();

      if ((now - button_press_time) > 500U /*ms*/) {
        button_flag = 0;
        uint8_t clicks = button_press_count;
        button_press_count = 0;

        if (clicks == 1) {
          current_mode = (current_mode + 1) % 5;

        } else {
          camera.stop();
          previewRgb.cvtColor(grayWqvga, CVT_RGB565_TO_GRAYSCALE);
          grayWqvga.resize(work256, 256, 256);
          work256.convertTo();

          switch (current_mode) {
          case 0: // Spatial denoise.
            work256.histEq(tmp256);
            tmp256.medianFilter(out256, 3);
            out256.convertTo();
            break;

          case 1: // Spatial sharpen.
            work256.filter2D(sharpenKernel, tmp256);
            work256.add(tmp256, out256);
            out256.convertTo();
            break;

          case 2: // FFT Gaussian low-pass.
            work256.fft(fftImg);
            fftImg.fftshift();
            filterImg.getFilter(FREQ_FILTER_GAUSSIAN_LOWPASS, 30.0f, 0.0f);
            fftImg.ffilter2D(filterImg, out256);
            out256.fftshift();
            out256.ifft(out256);
            out256.convertTo();
            break;

          case 3: // FFT Gaussian high-pass.
            work256.fft(fftImg);
            fftImg.fftshift();
            filterImg.getFilter(FREQ_FILTER_GAUSSIAN_HIGHPASS, 25.0f, 0.0f);
            fftImg.ffilter2D(filterImg, out256);
            out256.fftshift();
            out256.ifft(out256);
            out256.convertTo();
            break;

          case 4: // Highboost: original - LPF(original).
            work256.fft(fftImg);
            fftImg.fftshift();
            filterImg.getFilter(FREQ_FILTER_GAUSSIAN_LOWPASS, 20.0f, 0.0f);
            fftImg.ffilter2D(filterImg, tmp256);
            tmp256.fftshift();
            tmp256.ifft(tmp256);
            work256.difference(tmp256, out256);
            out256.convertTo();
            break;
          }

          // Show result on LCD and send to host.
          out256.resize(outWqvga, outWqvga.width(), outWqvga.height());
          outWqvga.convertTo();
          outWqvga.cvtColor(displayRgb, CVT_GRAYSCALE_TO_RGB565);
          display.show(displayRgb);
          serial.send(outWqvga);

          // Resume preview.
          camera.capture(CONTINUOUS, previewRgb);
          display.show(previewRgb);
        }
      }
    }
  }
}
