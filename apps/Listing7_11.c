/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *inImg = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg);

int histogram[256] = {0};

for (int img_idx = 0; img_idx < 4; ++img_idx) {
  serial->capture(inImg);

  histEq(inImg, outImg);

  convertTo(outImg);
  serial->send(outImg);

  histForm(outImg, histogram);
  serial->send1D(histogram, sizeof(int), 256, SERIAL_DATA_HISTOGRAM);
}
/* USER CODE END 2 */
