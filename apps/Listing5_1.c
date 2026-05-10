/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
camera_t *camera = &stm32_ov5640;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &inImg);

camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);
camera->capture(SINGLE, inImg);
/* USER CODE END 2 */