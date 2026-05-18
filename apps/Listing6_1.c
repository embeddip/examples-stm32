/* USER CODE BEGIN Includes */
#include <embedDIP.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
display_t *display = &stm32_ota5180a;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
Image *inImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &inImg);

serial->init();
display->init();

serial->capture(inImg);
display->show(inImg);
/* USER CODE END 2 */