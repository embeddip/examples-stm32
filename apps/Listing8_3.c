/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *fftImg = NULL, *magnitudeImg = NULL, *phaseImg = NULL,
      *outImg = NULL;
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &fftImg);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &magnitudeImg);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &phaseImg);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &outImg);

serial->init();

serial->capture(inImg);
fft(inImg, fftImg);
fftshift(fftImg);
_abs_(fftImg, magnitudeImg);
_phase_(fftImg, phaseImg);

polarToCart(magnitudeImg, phaseImg, outImg);
fftshift(outImg);
ifft(outImg, outImg);
convertTo(outImg);
serial->send(outImg);
/* USER CODE END 2 */