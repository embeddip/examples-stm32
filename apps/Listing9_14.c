/* USER CODE END 2 */ /* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *outImg = NULL, *maskImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &outImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &maskImg);

serial->init();
serial->capture(inImg);

Point seeds1[] = {{150, 150}};
colorRegionGrowing(inImg, maskImg, seeds1, 1, 0.20f);
serial->send(maskImg);

Point seeds2[] = {{310, 90}};
colorRegionGrowing(inImg, maskImg, seeds2, 1, 0.20f);
serial->send(maskImg);

Point seeds3[] = {{150, 150}, {310, 90}};
colorRegionGrowing(inImg, maskImg, seeds3, 2, 0.30f);
serial->send(maskImg);
/* USER CODE END 2 */
