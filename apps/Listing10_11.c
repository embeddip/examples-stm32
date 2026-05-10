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

Image *previewRgb = NULL, *gray = NULL, *denoised = NULL, *bin = NULL,
      *morph = NULL;
Image *labels = NULL, *displayRgb = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &previewRgb);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gray);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &denoised);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &bin);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &morph);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &labels);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &displayRgb);

camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
display->init();

camera->capture(CONTINUOUS, previewRgb);
display->show(previewRgb);

Kernel k;
getStructuringElement(&k, MORPH_ELLIPSE, 3);
const float blur3x3[9] = {
    1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
    1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
};
uint32_t numOfLabel;

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
        current_mode = (current_mode + 1) % 4;

      } else {
        camera->stop();
        cvtColor(previewRgb, gray, CVT_RGB565_TO_GRAYSCALE);
        filter2D(gray, denoised, blur3x3, 3);
        convertTo(denoised);

        switch (current_mode) {
        case 0: // Binary mask
          grayscaleThreshold(denoised, bin, 140);
          cvtColor(bin, morph, CVT_COPY);
          break;

        case 1: // Binary + opening
          grayscaleThreshold(denoised, bin, 140);
          opening(bin, morph, &k, 2);
          break;

        case 2: // Binary + closing
          grayscaleThreshold(denoised, bin, 140);
          closing(bin, morph, &k, 2);
          break;

        case 3: // Smart inspection
          grayscaleThreshold(denoised, bin, 140);
          opening(bin, morph, &k, 2);
          connectedComponents(morph, labels, &numOfLabel);
          normalize(labels);
          negative(labels, labels);
          cvtColor(labels, morph, CVT_COPY);
          break;
        }

        cvtColor(morph, displayRgb, CVT_GRAYSCALE_TO_RGB565);
        display->show(displayRgb);
        serial->send(morph);
        camera->capture(CONTINUOUS, previewRgb);
        display->show(previewRgb);
      }
    }
  }
/* USER CODE END WHILE */
