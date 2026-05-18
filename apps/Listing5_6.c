/* USER CODE BEGIN Includes */
#include <embedDIP.h>
#include "libjpeg.h"
#include "compress.h"
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
camera_t *camera = &stm32_ov5640;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */

Image *inImg = NULL, *compressedImg = NULL;
createImage(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB565, &inImg);

// Create buffer for JPEG data (estimated max size)
// JPEG is typically 10-30% of raw size, allocate conservatively
createImageWH(inImg->width, inImg->height, IMAGE_FORMAT_RGB888,
              &compressedImg);

camera->init(IMAGE_RES_QQVGA, IMAGE_FORMAT_RGB565);
serial->init();

/* USER CODE END 2 */

/* Infinite loop */
/* USER CODE BEGIN WHILE */
while (1) {
  camera->capture(SINGLE, inImg);
  compress(inImg, compressedImg, IMAGE_COMP_JPEG, 75);
  serial->sendJPEG(compressedImg);
  camera->stop();
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
