/* USER CODE BEGIN Includes */
#include "embedDIP.h"
#include <string.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
volatile int button_flag = 0;
volatile uint32_t button_press_time = 0;
volatile uint8_t button_press_count = 0;
volatile int current_mode = 0;
/* USER CODE END PV */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
camera_t *camera = &stm32_ov5640;
display_t *display = &stm32_ota5180a;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
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
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *previewRgb = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &previewRgb);

// Processing path.
Image *grayWqvga = NULL, *work256 = NULL, *tmp256 = NULL, *out256 = NULL;
Image *fftImg = NULL, *filterImg = NULL;
Image *outWqvga = NULL, *displayRgb = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &grayWqvga);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &work256);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &tmp256);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &out256);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &fftImg);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &filterImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outWqvga);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &displayRgb);

camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
display->init();

// Start live camera feed.
camera->capture(CONTINUOUS, previewRgb);
display->show(previewRgb);

float sharpenKernel[9] = {0, -1, 0, -1, 4, -1, 0, -1, 0};

/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
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
        camera->stop();
        cvtColor(previewRgb, grayWqvga, CVT_RGB565_TO_GRAYSCALE);
        resize(grayWqvga, work256, 256, 256);
        convertTo(work256);

        switch (current_mode) {
        case 0: // Spatial denoise.
          histEq(work256, tmp256);
          medianFilter(tmp256, out256, 3);
          convertTo(out256);
          break;

        case 1: // Spatial sharpen.
          filter2D(work256, tmp256, (const float *)sharpenKernel, 3);
          add(work256, tmp256, out256);
          convertTo(out256);
          break;

        case 2: // FFT Gaussian low-pass.
          fft(work256, fftImg);
          fftshift(fftImg);
          getFilter(filterImg, FREQ_FILTER_GAUSSIAN_LOWPASS, 30.0f, 0.0f);
          ffilter2D(fftImg, filterImg, out256);
          fftshift(out256);
          ifft(out256, out256);
          convertTo(out256);
          break;

        case 3: // FFT Gaussian high-pass.
          fft(work256, fftImg);
          fftshift(fftImg);
          getFilter(filterImg, FREQ_FILTER_GAUSSIAN_HIGHPASS, 25.0f, 0.0f);
          ffilter2D(fftImg, filterImg, out256);
          fftshift(out256);
          ifft(out256, out256);
          convertTo(out256);
          break;

        case 4: // Highboost: original - LPF(original).
          fft(work256, fftImg);
          fftshift(fftImg);
          getFilter(filterImg, FREQ_FILTER_GAUSSIAN_LOWPASS, 20.0f, 0.0f);
          ffilter2D(fftImg, filterImg, tmp256);
          fftshift(tmp256);
          ifft(tmp256, tmp256);
          difference(work256, tmp256, out256);
          convertTo(out256);
          break;
        }

        // Show result on LCD and send to host.
        resize(out256, outWqvga, outWqvga->width, outWqvga->height);
        convertTo(outWqvga);
        cvtColor(outWqvga, displayRgb, CVT_GRAYSCALE_TO_RGB565);
        display->show(displayRgb);
        serial->send(outWqvga);

        // Resume preview.
        camera->capture(CONTINUOUS, previewRgb);
        display->show(previewRgb);
      }
    }
  }
/* USER CODE END WHILE */
