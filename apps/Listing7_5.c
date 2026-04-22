/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *outImg_1 = NULL, *outImg_2 = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg_1);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg_2);

serial->capture(inImg);

uint8_t breakpoints1[] = {0, 128, 255};
uint8_t values1[] = {0, 32, 255};

piecewiseTransform(inImg, outImg_1, breakpoints1, values1, 3);
convertTo(outImg_1);

serial->send(outImg_1);

uint8_t breakpoints2[] = {0, 128, 255};
uint8_t values2[] = {0, 200, 255};

piecewiseTransform(inImg, outImg_2, breakpoints2, values2, 3);
convertTo(outImg_2);

serial->send(outImg_2);
/* USER CODE END 2 */