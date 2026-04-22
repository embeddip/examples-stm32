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

powerTransform(inImg, outImg_1, 2.0f);
convertTo(outImg_1);

serial->send(outImg_1);

powerTransform(inImg, outImg_2, 1.0f / 2.0f);
convertTo(outImg_2);

serial->send(outImg_2);
/* USER CODE END 2 */