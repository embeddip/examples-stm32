/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *inImg = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg);

serial->capture(inImg);

// grayscaleKMeans(inImg, outImg, 3);
// grayscaleKMeans(inImg, outImg, 4);
grayscaleKMeans(inImg, outImg, 5);

convertTo(outImg);

serial->send(outImg);
/* USER CODE END 2 */
