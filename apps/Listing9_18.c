/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *sX = NULL, *sY = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &sX);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &sY);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg);

static float kernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

static float kernelY[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

serial->capture(inImg);

filter2D(inImg, sX, &kernelX[0][0], 3);
convertTo(sX);
serial->send(sX);

filter2D(inImg, sY, &kernelY[0][0], 3);
convertTo(sY);
serial->send(sY);

gradientMagnitude(sX, sY, outImg);
convertTo(outImg);
serial->send(outImg);
/* USER CODE END 2 */
