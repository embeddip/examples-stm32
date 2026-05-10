#include "main.h"
#include <embedDIP.hpp>
#include "camvid_model_data.h"

using namespace embedDIP;

#define IMG_SIZE 128
#define IMG_PIXELS (IMG_SIZE * IMG_SIZE)
#define IN_CHANNELS 3
#define OUT_CHANNELS 4
#define BACKGROUND_CLASS_ID 3
#define TFLM_ARENA_SIZE_BYTES (4 * 1024 * 1024)

extern "C" int tlfm_camvid_init(const unsigned char *model_data,
                                 unsigned int model_data_len);
extern "C" int tlfm_camvid_infer(const uint8_t *rgb_pixels, uint8_t *class_map,
                                  uint8_t *confidence_map);

static const uint8_t class_colors[OUT_CHANNELS][3] = {
    {255, 0, 0},   // class 0: road
    {0, 255, 0},   // class 1: vehicles
    {255, 255, 0}, // class 2: pedestrians
    {0, 0, 0}      // class 3: background
};

int application() {
  embedDIP::Serial serial(&stm32_uart);
  serial.init();

  memory_init(TFLM_ARENA_SIZE_BYTES);

  embedDIP::Image inImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_RGB888);
  embedDIP::Image classImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image confImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);
  embedDIP::Image visImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_RGB888);
  embedDIP::Image overlayImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_RGB888);

  uint8_t class_map[IMG_PIXELS] = {0};
  uint8_t confidence_map[IMG_PIXELS] = {0};

  if (tlfm_camvid_init(g_camvid_model_data, g_camvid_model_data_len) != 0) {
    while (1);
  }

  serial.capture(inImg);

  const uint8_t *rgb_pixels = reinterpret_cast<const uint8_t *>(inImg.pixels());
  if (tlfm_camvid_infer(rgb_pixels, class_map, confidence_map) != 0) {
    while (1);
  }

  // 1) original input
  serial.send(inImg);

  // 2) class index map (0..255)
  memcpy(classImg.pixels(), class_map, IMG_PIXELS);
  serial.send(classImg);

  // 3) confidence map (0..255)
  memcpy(confImg.pixels(), confidence_map, IMG_PIXELS);
  serial.send(confImg);

  // 4) colorized map
  uint8_t *vis_pixels = reinterpret_cast<uint8_t *>(visImg.pixels());
  for (int i = 0; i < IMG_PIXELS; ++i) {
    const uint8_t cls = static_cast<uint8_t>((class_map[i] * (OUT_CHANNELS - 1) + 127) / 255);
    vis_pixels[3 * i + 0] = class_colors[cls][0];
    vis_pixels[3 * i + 1] = class_colors[cls][1];
    vis_pixels[3 * i + 2] = class_colors[cls][2];
  }
  serial.send(visImg);

  // 5) overlay
  uint8_t *overlay_pixels = reinterpret_cast<uint8_t *>(overlayImg.pixels());
  for (int i = 0; i < IMG_PIXELS; ++i) {
    const uint8_t cls = static_cast<uint8_t>((class_map[i] * (OUT_CHANNELS - 1) + 127) / 255);

    const uint8_t src_r = rgb_pixels[3 * i + 0];
    const uint8_t src_g = rgb_pixels[3 * i + 1];
    const uint8_t src_b = rgb_pixels[3 * i + 2];

    if (cls == BACKGROUND_CLASS_ID) {
      overlay_pixels[3 * i + 0] = src_r;
      overlay_pixels[3 * i + 1] = src_g;
      overlay_pixels[3 * i + 2] = src_b;
    } else {
      const uint8_t mask_r = class_colors[cls][0];
      const uint8_t mask_g = class_colors[cls][1];
      const uint8_t mask_b = class_colors[cls][2];
      overlay_pixels[3 * i + 0] =
          static_cast<uint8_t>(((uint16_t)src_r * 55U + (uint16_t)mask_r * 45U) / 100U);
      overlay_pixels[3 * i + 1] =
          static_cast<uint8_t>(((uint16_t)src_g * 55U + (uint16_t)mask_g * 45U) / 100U);
      overlay_pixels[3 * i + 2] =
          static_cast<uint8_t>(((uint16_t)src_b * 55U + (uint16_t)mask_b * 45U) / 100U);
    }
  }
  serial.send(overlayImg);

  while (1);
}
