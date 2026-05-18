/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *inImg = NULL, *fftImg = NULL, *filter = NULL, *outImg = NULL;
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &fftImg);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &filter);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &outImg);

serial->capture(inImg);

fft(inImg, fftImg);
fftshift(fftImg);

getFilter(filter, FREQ_FILTER_IDEAL_HIGHPASS, 30, 0);

ffilter2D(fftImg, filter, outImg);

fftshift(outImg);
ifft(outImg, outImg);

convertTo(outImg);
serial->send(outImg);
/* USER CODE END 2 */
