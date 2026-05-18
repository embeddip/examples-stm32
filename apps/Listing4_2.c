/* USER CODE BEGIN Includes */
#include "embedDIP.h"
#include <string.h>
// Contains the image data in RGB565 format.
#include "image_data.h"
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();

Image *rgbImg = NULL;
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &rgbImg);

// Copy the pre-generated image array data to the image buffer.
// Note: rgbImg->size is number of pixels, multiply by depth (2 bytes for RGB565)
memcpy(rgbImg->pixels, image_data, rgbImg->size * rgbImg->depth);

// Transmit the processed image data over the serial interface.
serial->send(rgbImg);
/* USER CODE END 2 */