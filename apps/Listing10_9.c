/* USER CODE BEGIN Includes */
#include <embedDIP.h>
#include <string.h>
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
serial->send(inImg);

grayscaleThreshold(inImg, inImg, 80);
serial->send(inImg);

connectedComponents(inImg, outImg, NULL);

normalize(outImg);
negative(outImg, outImg);
serial->send(outImg);
/* USER CODE END 2 */
