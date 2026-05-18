/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *outImg = NULL, *maskImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_MASK, &maskImg);

serial->init();
serial->capture(inImg);

Rectangle roi;
roi.x = 30;
roi.y = 55;
roi.width = 400;
roi.height = 200;

// tic();
// grabCutLite(inImg, maskImg, roi, 5);
grabCut(inImg, maskImg, roi, 5);
// uint32_t cycleCount = toc();

convertTo(maskImg);
serial->send(maskImg);

_and_(inImg, maskImg, outImg);
serial->send(outImg);
/* USER CODE END 2 */
