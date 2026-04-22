/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *outImg = NULL, *KittenMagnitude = NULL,
      *KittenPhase = NULL, *TabbyCatMagnitude = NULL, *TabbyCatPhase = NULL;
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &KittenMagnitude);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &KittenPhase);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &TabbyCatMagnitude);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &TabbyCatPhase);
createImageWH(256, 256, IMAGE_FORMAT_GRAYSCALE, &outImg);

// Get Kitten + fft
serial->capture(inImg);
fft(inImg, inImg);
_abs_(inImg, KittenMagnitude);
_phase_(inImg, KittenPhase);

// Get TabbyCat + fft
serial->capture(inImg);
fft(inImg, inImg);
_abs_(inImg, TabbyCatMagnitude);
_phase_(inImg, TabbyCatPhase);

// TabbyCat's magnitude with Kitten's phase
polarToCart(TabbyCatMagnitude, KittenPhase, outImg);
ifft(outImg, outImg);
convertTo(outImg);
serial->send(outImg);

// Kitten's magnitude with TabbyCat's phase
polarToCart(KittenMagnitude, TabbyCatPhase, outImg);
ifft(outImg, outImg);
convertTo(outImg);
serial->send(outImg);
/* USER CODE END 2 */