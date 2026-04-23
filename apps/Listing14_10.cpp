#include "main.hpp"
#include "mobilenetv2_fp32.h"
#include "mobilenetv2_fp32_data.h"
#include <embedDIP.hpp>

using namespace embedDIP;

#define IMG_SIZE (128)
#define IMG_PIXELS (IMG_SIZE * IMG_SIZE)
#define OUT_CHANNELS (2)

// External SDRAM: 8MB starting at 0xC0000000
AI_ALIGNED(4)
static ai_u8 *activations = (ai_u8 *)(0xC0000000);

AI_ALIGNED(4)
static ai_float input_data[IMG_PIXELS];

AI_ALIGNED(4)
static ai_float output_data[IMG_PIXELS * OUT_CHANNELS];

AI_ALIGNED(4)
static uint8_t binary_mask[IMG_PIXELS];

static ai_handle network = AI_HANDLE_NULL;
static ai_buffer *ai_input;
static ai_buffer *ai_output;

void model_init(void) {
  ai_error err;
  const ai_handle acts[] = {activations};

  err = ai_mobilenetv2_fp32_create_and_init(&network, acts, NULL);
  if (err.type != AI_ERROR_NONE)
    Error_Handler();

  ai_input = ai_mobilenetv2_fp32_inputs_get(network, NULL);
  ai_output = ai_mobilenetv2_fp32_outputs_get(network, NULL);
}

void model_inference(void) {
  ai_input[0].data = AI_HANDLE_PTR(input_data);
  ai_output[0].data = AI_HANDLE_PTR(output_data);

  if (ai_mobilenetv2_fp32_run(network, ai_input, ai_output) != 1)
    Error_Handler();

  for (int i = 0; i < IMG_PIXELS; ++i) {
    float pet_score = output_data[i * OUT_CHANNELS + 1];
    binary_mask[i] = (pet_score > 0.8f) ? 255 : 0;
  }
}

int application() {

  embedDIP::Serial serial(&stm32_uart);
  serial.init();

  // Use offset from SDRAM base for allocator pool start.
  // U-Net activations occupy 0x0013C000 bytes from 0xC0000000, so start pool
  // after that.
  memory_init(0x00140000);
  embedDIP::Image inImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image maskImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);

  model_init();

  serial.capture(inImg);
  serial.send(inImg);
  uint8_t *pixels = (uint8_t *)inImg.pixels();
  for (int i = 0; i < IMG_PIXELS; ++i) {
    input_data[i] = ((float)pixels[i]) / 255.0f;
  }

  model_inference();

  memcpy(maskImg.pixels(), binary_mask, IMG_PIXELS);
  serial.send(maskImg);

  HAL_Delay(10);

  while (1) {
    ;
  }
}
