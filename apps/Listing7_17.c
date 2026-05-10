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

float filter[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};

serial->capture(inImg);

filter2D(inImg, outImg, &filter[0][0], 3);
normalize(outImg);
convertTo(outImg);

serial->send(outImg);
/* USER CODE END 2 */
