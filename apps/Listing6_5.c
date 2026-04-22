/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
camera_t *camera = &stm32_ov5640;
display_t *display = &stm32_ota5180a;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
display->init();
camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

Image *cameraImg = NULL, *serialImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &serialImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &cameraImg);

serial->init();
display->init();
camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

camera->capture(SINGLE, cameraImg);
display->show(cameraImg);
HAL_Delay(1000);
serial->capture(serialImg);
display->show(serialImg);
/* USER CODE END 2 */
