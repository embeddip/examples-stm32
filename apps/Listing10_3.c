/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg);

serial->init();

serial->capture(inImg);

grayscaleThreshold(inImg, inImg, 80);

Kernel test;
getStructuringElement(&test, MORPH_ELLIPSE, 3);

erode(inImg, outImg, &test, 1);
negative(outImg, outImg);
serial->send(outImg);

erode(inImg, outImg, &test, 2);
negative(outImg, outImg);
serial->send(outImg);

erode(inImg, outImg, &test, 3);
negative(outImg, outImg);
serial->send(outImg);
/* USER CODE END 2 */
