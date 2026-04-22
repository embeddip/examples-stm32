/* USER CODE BEGIN Includes */
#include "embedDIP.h"
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *rgbImg = NULL, *rgb565Img = NULL, *rgbRoundTripImg = NULL;
Image *grayOrig = NULL, *grayRoundTrip = NULL, *diffImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &rgbImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &rgb565Img);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &rgbRoundTripImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &grayOrig);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &grayRoundTrip);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &diffImg);

serial->capture(rgbImg);

cvtColor(rgbImg, rgb565Img, CVT_RGB888_TO_RGB565);
cvtColor(rgb565Img, rgbRoundTripImg, CVT_RGB565_TO_RGB888);

cvtColor(rgbImg, grayOrig, CVT_RGB888_TO_GRAYSCALE);
cvtColor(rgbRoundTripImg, grayRoundTrip, CVT_RGB888_TO_GRAYSCALE);

difference(grayOrig, grayRoundTrip, diffImg);
convertTo(diffImg);
serial->send(diffImg);
/* USER CODE END 2 */
