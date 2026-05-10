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

Image *previewRgb = NULL, *gray = NULL, *edges = NULL, *clean = NULL;
Image *gradH = NULL, *gradV = NULL, *mag = NULL;
Image *overlay = NULL, *displayRgb = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &previewRgb);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gray);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &edges);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &clean);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gradH);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gradV);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &mag);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &overlay);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &displayRgb);

camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
display->init();

camera->capture(CONTINUOUS, previewRgb);
display->show(previewRgb);

float kernelX[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
float kernelY[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
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
        current_mode = (current_mode + 1) % 3;

      } else {
        camera->stop();
        cvtColor(previewRgb, gray, CVT_RGB565_TO_GRAYSCALE);

        Image *result = NULL;
        switch (current_mode) {
        case 0: // LoG-based edge mask.
          logFilter(gray, edges, 1.4f);
          convertTo(edges);
          grayscaleOtsu(edges, clean);
          negative(clean, clean);
          result = clean;
          break;

        case 1: // Gaussian gradients + magnitude.
          gaussianGradients(gray, gradH, gradV, 1.2f);
          gradientMagnitude(gradH, gradV, mag);
          convertTo(mag);
          grayscaleOtsu(mag, clean);
          result = clean;
          break;

        case 2: // Sobel + magnitude.
          filter2D(gray, gradH, (const float *)kernelX, 3);
          convertTo(gradH);
          filter2D(gray, gradV, (const float *)kernelY, 3);
          convertTo(gradV);
          gradientMagnitude(gradH, gradV, mag);
          convertTo(mag);
          grayscaleOtsu(mag, clean);
          result = clean;
          break;
        }

        cvtColor(result, displayRgb, CVT_GRAYSCALE_TO_RGB565);
        display->show(displayRgb);
        serial->send(result);
        serial->send1D(&current_mode, sizeof(int), 1, SERIAL_DATA_OTHER);

        camera->capture(CONTINUOUS, previewRgb);
        display->show(previewRgb);
      }
    }
  }
/* USER CODE END WHILE */
