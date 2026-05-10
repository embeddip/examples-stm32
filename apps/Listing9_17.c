/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *gH = NULL, *gV = NULL, *magnitudeOut = NULL,
      *phaseOut = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gH);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gV);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &magnitudeOut);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &phaseOut);

serial->init();

serial->capture(inImg);

gaussianGradients(inImg, gH, gV, 1.2f);

gradientMagnitude(gH, gV, magnitudeOut);

gradientPhase(gH, gV, phaseOut);

convertTo(gH);

serial->send(gH);

convertTo(gV);

serial->send(gV);

convertTo(magnitudeOut);

serial->send(magnitudeOut);

convertTo(phaseOut);

serial->send(phaseOut);
/* USER CODE END 2 */
