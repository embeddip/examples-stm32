/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &outImg);

serial->init();

serial->capture(inImg);

// colorKMeans(inImg, outImg, 3);
colorKMeans(inImg, outImg, 5);

serial->send(outImg);
/* USER CODE END 2 */
