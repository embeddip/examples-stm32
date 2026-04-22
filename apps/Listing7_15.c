/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL, *outImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &inImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_GRAYSCALE, &outImg);

float lowPassFilter3x3[3][3];
for (int i = 0; i < 3; ++i)
  for (int j = 0; j < 3; ++j)
    lowPassFilter3x3[i][j] = 1.0f / 9.0f;

float lowPassFilter5x5[5][5];
for (int i = 0; i < 5; ++i)
  for (int j = 0; j < 5; ++j)
    lowPassFilter5x5[i][j] = 1.0f / 25.0f;

serial->capture(inImg);

filter2D(inImg, outImg, &lowPassFilter3x3[0][0], 3);

convertTo(outImg);
serial->send(outImg);

filter2D(inImg, outImg, &lowPassFilter5x5[0][0], 5);

convertTo(outImg);
serial->send(outImg);
/* USER CODE END 2 */
