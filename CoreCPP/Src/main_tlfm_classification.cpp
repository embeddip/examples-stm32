#include "main.h"
#include "nn_mnist_model_data.h"
#include <embedDIP.hpp>
// #include "cnn_mnist_model_data.h"

using namespace embedDIP;

#define IMG_SIZE 28
#define IMG_PIXELS (IMG_SIZE * IMG_SIZE)
#define TFLM_ARENA_SIZE_BYTES (4 * 1024 * 1024)

extern "C" int tlfm_cls_init(const unsigned char *model_data, unsigned int model_data_len);
extern "C" int tlfm_cls_infer(const uint8_t *pixels, int pixel_count, uint8_t *class_id);

int application()
{
    // CMake switch note:
    // For segmentation build entrypoint, use main_segmentation.cpp instead of this file.
    embedDIP::Serial serial(&stm32_uart);

    memory_init(TFLM_ARENA_SIZE_BYTES);

    embedDIP::Image inImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);

    serial.init();
    if (tlfm_cls_init(g_nn_mnist_model_data, g_nn_mnist_model_data_len) != 0) {
        // For CNN model switch:
        // tlfm_cls_init(g_cnn_mnist_model_data, g_cnn_mnist_model_data_len)
        while (1) {
            ;
        }
    }

    serial.capture(inImg);

    const uint8_t *pixels = reinterpret_cast<const uint8_t *>(inImg.pixels());
    uint8_t class_id = 0;
    if (tlfm_cls_infer(pixels, IMG_PIXELS, &class_id) != 0) {
        while (1) {
            ;
        }
    }
    serial.send1D(&class_id, sizeof(uint8_t), 1, SERIAL_DATA_OTHER);

    while (1) {
        ;
    }
}
