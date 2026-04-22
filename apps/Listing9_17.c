/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *gX = NULL, *gY = NULL, *magnitudeOut = NULL,
      *phaseOut = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gX);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &gY);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &magnitudeOut);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &phaseOut);

serial->init();

serial->capture(inImg);

gaussianGradients(inImg, gX, gY, 1.2f);

gradientMagnitude(gX, gY, magnitudeOut);

gradientPhase(gX, gY, phaseOut);

convertTo(gX);

serial->send(gX);

convertTo(gY);

serial->send(gY);

convertTo(magnitudeOut);

serial->send(magnitudeOut);

convertTo(phaseOut);

serial->send(phaseOut);
/* USER CODE END 2 */
