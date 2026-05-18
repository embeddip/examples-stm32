/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *refImg = NULL, *srcImg = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &refImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &srcImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg);

int refHistogram[256] = {0};

serial->capture(refImg);

histForm(refImg, refHistogram);

serial->capture(srcImg);

histSpec(srcImg, outImg, refHistogram);
convertTo(outImg);

serial->send(outImg);
/* USER CODE END 2 */
