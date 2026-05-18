/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
camera_t *camera = &stm32_ov5640;
display_t *display = &stm32_ota5180a;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
display->init();
camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

Image *inImg_wqvga = NULL, *inImg_qvga = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &inImg_wqvga);
createImage(IMAGE_RES_QVGA, IMAGE_FORMAT_RGB565, &inImg_qvga);

camera->capture(SINGLE, inImg_wqvga);
display->show(inImg_wqvga);
HAL_Delay(1000);
camera->stop();

camera->setRes(IMAGE_RES_QVGA);
camera->capture(SINGLE, inImg_qvga);
display->show(inImg_qvga);
/* USER CODE END 2 */