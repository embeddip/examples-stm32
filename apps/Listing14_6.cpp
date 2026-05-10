#include "main.h"
#include <embedDIP.hpp>
// #include "mobilenet_model_data.h"
#include "unet_model_data.h"
// #include "unet_s_model_data.h"

using namespace embedDIP;

#define IMG_SIZE 128
#define TFLM_ARENA_SIZE_BYTES (4 * 1024 * 1024)

extern "C" int tlfm_seg_init(const unsigned char *model_data,
                             unsigned int model_data_len);
extern "C" int tlfm_seg_infer(const uint8_t *pixels, uint8_t *mask);

// Separate entrypoint for segmentation main flow.
int application() {
  // CMake switch note:
  // For segmentation build entrypoint, use this file instead of main.cpp.
  embedDIP::Serial serial(&stm32_uart);

  memory_init(TFLM_ARENA_SIZE_BYTES);

  embedDIP::Image inImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image maskImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);

  serial.init();
  if (tlfm_seg_init(g_unet_model_data, g_unet_model_data_len) != 0) {
    // Model switch examples:
    // tlfm_seg_init(g_mobilenet_model_data, g_mobilenet_model_data_len);
    // tlfm_seg_init(g_unet_s_model_data, g_unet_s_model_data_len);
    while (1);
  }

  serial.capture(inImg);

  const uint8_t *pixels = reinterpret_cast<const uint8_t *>(inImg.pixels());
  uint8_t *mask = reinterpret_cast<uint8_t *>(maskImg.pixels());
  if (tlfm_seg_infer(pixels, mask) != 0) {
    while (1);
  }

  serial.send(maskImg);

  while (1);
}
