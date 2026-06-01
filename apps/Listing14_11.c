/* USER CODE BEGIN Includes */
#include "camvid_int8.h"
#include "camvid_int8_data.h"
#include <embedDIP.h>
#include <string.h>

#define IMG_PIXELS 128 * 128
#define IN_CHANNELS 3
#define OUT_CHANNELS 4
#define BACKGROUND_CLASS_ID 3
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
// External SDRAM: 8MB starting at 0xC0000000
AI_ALIGNED(4)
static ai_u8 *activations = (ai_u8 *)(0xC0000000);

// Place input/output buffers at the end of SDRAM
AI_ALIGNED(4)
static ai_i8 *output_data = (ai_i8 *)(0xC0800000 - AI_CAMVID_INT8_OUT_1_SIZE);

AI_ALIGNED(4)
static ai_i8 *input_data = (ai_i8 *)(0xC0800000 - AI_CAMVID_INT8_OUT_1_SIZE -
                                     AI_CAMVID_INT8_IN_1_SIZE);

AI_ALIGNED(4)
static uint8_t class_id_map[IMG_PIXELS];

static ai_handle network = AI_HANDLE_NULL;
static ai_buffer *ai_input;
static ai_buffer *ai_output;
/* USER CODE END PV */

/* USER CODE BEGIN 0 */
serial_t *serial = &stm32_uart;
display_t *display = &stm32_ota5180a;
// camera_t *camera = &stm32_ov5640;

void model_init(void) {
  ai_error err;
  const ai_handle acts[] = {activations};

  err = ai_camvid_int8_create_and_init(&network, acts, NULL);
  if (err.type != AI_ERROR_NONE)
    Error_Handler();

  ai_input = ai_camvid_int8_inputs_get(network, NULL);
  ai_output = ai_camvid_int8_outputs_get(network, NULL);
}

void model_inference(void) {
  ai_input[0].data = AI_HANDLE_PTR(input_data);
  ai_output[0].data = AI_HANDLE_PTR(output_data);

  if (ai_camvid_int8_run(network, ai_input, ai_output) != 1)
    Error_Handler();

  for (int i = 0; i < IMG_PIXELS; ++i) {
    int base = i * OUT_CHANNELS;
    int best_class = 0;
    ai_i8 best_score = output_data[base];

    for (int c = 1; c < OUT_CHANNELS; ++c) {
      ai_i8 score = output_data[base + c];
      if (score > best_score) {
        best_score = score;
        best_class = c;
      }
    }

    class_id_map[i] = (uint8_t)best_class;
  }
}
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
serial->init();
display->init();

// Use offset from SDRAM base for allocator pool start.
// Start allocator pool after the activation-buffer region.
memory_init(0x00140000);

// Create images for RGB input and outputs
Image *inImg = NULL;
Image *visImg = NULL;
Image *overlayImg = NULL;
Image *rgbWqvga = NULL;
createImageWH(128, 128, IMAGE_FORMAT_RGB888, &inImg);
// Image *cameraImg = NULL;
// Image *cameraRgbImg = NULL;
// createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565, &cameraImg);
// createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &cameraRgbImg);
createImageWH(128, 128, IMAGE_FORMAT_RGB888, &visImg);
createImageWH(128, 128, IMAGE_FORMAT_RGB888, &overlayImg);
createImage(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB888, &rgbWqvga);

// Initialize AI model
model_init();
// camera->init(IMAGE_RES_WQVGA, IMAGE_FORMAT_RGB565);

// Receive RGB image via serial (128x128x3)
serial->capture(inImg);
// camera->capture(SINGLE, cameraImg);
// cvtColor(cameraImg, cameraRgbImg, CVT_RGB565_TO_RGB888);
// resize(cameraRgbImg, inImg, 128, 128);

// Convert uint8 RGB [0..255] to int8 (QLinear scale=1/255, zero=-128)
uint8_t *in_pixels = (uint8_t *)inImg->pixels;
for (int i = 0; i < (IMG_PIXELS * IN_CHANNELS); ++i) {
  input_data[i] = (ai_i8)((int16_t)in_pixels[i] - 128);
}

// Run AI inference
model_inference();

// Define class colors for visualization
static const uint8_t class_colors[OUT_CHANNELS][3] = {
    {255, 0, 0},   // class 0: red (road)
    {0, 255, 0},   // class 1: green (vehicles)
    {255, 255, 0}, // class 2: yellow (pedestrians)
    {0, 0, 0}      // class 3: black (background)
};

// 1. Send original input
resize(inImg, rgbWqvga, rgbWqvga->width, rgbWqvga->height);
serial->send(rgbWqvga);

// 2. Send final colorized segmentation result (RGB888)
uint8_t *vis_pixels = (uint8_t *)visImg->pixels;
for (int i = 0; i < IMG_PIXELS; ++i) {
  uint8_t cls = class_id_map[i];
  vis_pixels[3 * i + 0] = class_colors[cls][0];
  vis_pixels[3 * i + 1] = class_colors[cls][1];
  vis_pixels[3 * i + 2] = class_colors[cls][2];
}
resize(visImg, rgbWqvga, rgbWqvga->width, rgbWqvga->height);
serial->send(rgbWqvga);

// 3. Send overlay (original image + segmentation color mask)
uint8_t *overlay_pixels = (uint8_t *)overlayImg->pixels;
for (int i = 0; i < IMG_PIXELS; ++i) {
  uint8_t cls = class_id_map[i];
  uint8_t src_r = in_pixels[3 * i + 0];
  uint8_t src_g = in_pixels[3 * i + 1];
  uint8_t src_b = in_pixels[3 * i + 2];

  if (cls == BACKGROUND_CLASS_ID) {
    // Keep background untouched in overlay
    overlay_pixels[3 * i + 0] = src_r;
    overlay_pixels[3 * i + 1] = src_g;
    overlay_pixels[3 * i + 2] = src_b;
  } else {
    uint8_t mask_r = class_colors[cls][0];
    uint8_t mask_g = class_colors[cls][1];
    uint8_t mask_b = class_colors[cls][2];

    // 55% source + 45% mask for clear visibility
    overlay_pixels[3 * i + 0] =
        (uint8_t)(((uint16_t)src_r * 55U + (uint16_t)mask_r * 45U) / 100U);
    overlay_pixels[3 * i + 1] =
        (uint8_t)(((uint16_t)src_g * 55U + (uint16_t)mask_g * 45U) / 100U);
    overlay_pixels[3 * i + 2] =
        (uint8_t)(((uint16_t)src_b * 55U + (uint16_t)mask_b * 45U) / 100U);
  }
}
resize(overlayImg, rgbWqvga, rgbWqvga->width, rgbWqvga->height);
serial->send(rgbWqvga);
/* USER CODE END 2 */
