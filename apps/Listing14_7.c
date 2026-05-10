/* USER CODE BEGIN Includes */
#include "unet_fp32.h"
#include "unet_fp32_data.h"
#include <embedDIP.h>
#include <string.h>

#define IMG_SIZE (128)
#define IMG_PIXELS (IMG_SIZE * IMG_SIZE)
#define OUT_CHANNELS (2)
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
AI_ALIGNED(4)
static ai_u8 *activations = (ai_u8 *)(0xC0000000);

AI_ALIGNED(4)
static ai_float input_data[IMG_PIXELS];

AI_ALIGNED(4)
static ai_float output_data[IMG_PIXELS * 2];

AI_ALIGNED(4)
static uint8_t binary_mask[IMG_PIXELS];

static ai_handle network = AI_HANDLE_NULL;
static ai_buffer *ai_input;
static ai_buffer *ai_output;
/* USER CODE END PV */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
display_t *display = &stm32_ota5180a;

void model_init(void) {
  const ai_handle acts[] = {activations};

  ai_unet_fp32_create_and_init(&network, acts, NULL);
  ai_input = ai_unet_fp32_inputs_get(network, NULL);
  ai_output = ai_unet_fp32_outputs_get(network, NULL);
}

void model_inference(void) {
  ai_input[0].data = AI_HANDLE_PTR(input_data);
  ai_output[0].data = AI_HANDLE_PTR(output_data);

  ai_unet_fp32_run(network, ai_input, ai_output);

  for (int i = 0; i < IMG_PIXELS; ++i) {
    float pet_score = output_data[i * 2 + 1];
    binary_mask[i] = (pet_score > 0.5f) ? 255 : 0;
  }
}
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();
display->init();

memory_init(0x00140000);

Image *inImg = NULL;
createImageWH(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE, &inImg);

model_init();

serial->capture(inImg);

uint8_t *pixels = (uint8_t *)inImg->pixels;
for (int i = 0; i < IMG_PIXELS; ++i) {
  input_data[i] = ((float)pixels[i]) / 255.0f;
}

model_inference();

for (int i = 0; i < IMG_PIXELS; ++i) {
  float pet_score = output_data[i * 2 + 1];
  if (pet_score < 0.0f)
    pet_score = 0.0f;
  if (pet_score > 1.0f)
    pet_score = 1.0f;
  pixels[i] = (uint8_t)(pet_score * 255.0f);
}

memcpy(pixels, binary_mask, IMG_PIXELS);
serial->send(inImg);

/* USER CODE END 2 */