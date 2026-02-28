/* USER CODE BEGIN Includes */
#include "embedDIP.h"
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *rgbImg = NULL, *grayImg = NULL, *yuvImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &rgbImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &grayImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_YUV, &yuvImg);

serial->capture(rgbImg);

cvtColor(rgbImg, grayImg, CVT_RGB888_TO_GRAYSCALE);
serial->send(grayImg);

cvtColor(rgbImg, yuvImg, CVT_RGB888_TO_YUV);
serial->send(yuvImg);
/* USER CODE END 2 */