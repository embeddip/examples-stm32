/* USER CODE BEGIN Includes */
#include <embedDIP.h>
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

Image *inImg = NULL, *filteredImg = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &filteredImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg);

camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE);
display->init();

camera->capture(CONTINUOUS, inImg);
display->show(inImg);

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
        // Single click: cycle through modes
        current_mode = (current_mode + 1) % 4;

      } else {
        // Double click: capture and process image
        camera->stop();

        // Apply selected processing mode
        switch (current_mode) {
        case 0: // HistEq + Median filter
          histEq(inImg, filteredImg);
          medianFilter(filteredImg, outImg, 3);
          convertTo(outImg);
          break;

        case 1: // Negative
          negative(inImg, outImg);
          convertTo(outImg);
          break;

        case 2: // Gamma correction (1.5)
          powerTransform(inImg, outImg, 1.5f);
          convertTo(outImg);
          break;

        case 3: // Sharpen (high-pass + add)
          filter2D(inImg, filteredImg, (const float *)sharpenKernel, 3);
          add(inImg, filteredImg, outImg);
          convertTo(outImg);
          break;
        }

        serial->send(outImg);

        camera->capture(CONTINUOUS, inImg);
      }
    }
  }
/* USER CODE END WHILE */
