/* USER CODE BEGIN Includes */
#include "embedDIP.h"
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *rgbImg = NULL, *rgb565Img = NULL, *grayImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &rgbImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &rgb565Img);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &grayImg);

serial->capture(rgbImg);

cvtColor(rgbImg, rgb565Img, CVT_RGB888_TO_RGB565);
serial->send(rgb565Img);

cvtColor(rgbImg, grayImg, CVT_RGB888_TO_GRAYSCALE);
serial->send(grayImg);

/* USER CODE END 2 */