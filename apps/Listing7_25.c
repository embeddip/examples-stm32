/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *inImg = NULL, *outImg = NULL, *rImg = NULL, *gImg = NULL, *bImg = NULL,
      *rImgOut = NULL, *gImgOut = NULL, *bImgOut = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &rImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &bImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &rImgOut);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gImgOut);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &bImgOut);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &outImg);

float lowPassFilter3x3[9] = {1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
                             1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
                             1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f};

serial->capture(inImg);
inImg->log = IMAGE_DATA_PIXELS; // Captured data is in pixels buffer

rgbSplit(inImg, rImg, gImg, bImg);

filter2D(rImg, rImgOut, lowPassFilter3x3, 3);
filter2D(gImg, gImgOut, lowPassFilter3x3, 3);
filter2D(bImg, bImgOut, lowPassFilter3x3, 3);

convertTo(rImgOut);
convertTo(gImgOut);
convertTo(bImgOut);

rgbMerge(rImgOut, gImgOut, bImgOut, outImg);

serial->send(outImg);

/* USER CODE END 2 */
