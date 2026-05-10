/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
camera_t *camera = &stm32_ov5640;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *wqvgaImg = NULL, *qqvgaImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &wqvgaImg);
createImage(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB565, &qqvgaImg);

camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
serial->init();

camera->capture(SINGLE, wqvgaImg);
serial->send(wqvgaImg);

camera->stop();
camera->setRes(IMAGE_RES_QQVGA);
camera->capture(SINGLE, qqvgaImg);
serial->send(qqvgaImg);
/* USER CODE END 2 */
