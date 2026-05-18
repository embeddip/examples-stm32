/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *rgbImg = NULL, *hsiImg = NULL, *mask = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &rgbImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_HSI, &hsiImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &mask);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &outImg);

serial->init();

serial->capture(rgbImg);

cvtColor(rgbImg, hsiImg, CVT_RGB888_TO_HSI);

uint8_t lower[3] = {0, 0, 0};
uint8_t upper[3] = {26, 255, 255};

inRange(hsiImg, mask, lower, upper);

serial->send(mask);

_and_(rgbImg, mask, outImg);

serial->send(outImg);
/* USER CODE END 2 */
