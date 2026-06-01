#ifndef CNN_MNIST_INFERENCE_H
#define CNN_MNIST_INFERENCE_H

#include <cstdint>

#include "mnist_inference.h"
#include "cnn_mnist.h"
#include "cnn_mnist_data.h"

#define CNN_MNIST_IMG_SIZE 28
#define CNN_MNIST_IMG_PIXELS (CNN_MNIST_IMG_SIZE * CNN_MNIST_IMG_SIZE)
#define CNN_MNIST_NUM_CLASSES 10

namespace cnn_mnist_inference_detail {

AI_ALIGNED(4)
static ai_u8 activations[AI_CNN_MNIST_DATA_ACTIVATIONS_SIZE];

AI_ALIGNED(4)
static ai_float input_data[CNN_MNIST_IMG_PIXELS];

static ai_handle network = AI_HANDLE_NULL;
static ai_buffer *ai_input = nullptr;
static ai_buffer *ai_output = nullptr;

}  // namespace cnn_mnist_inference_detail

static inline void cnn_mnist_init() {
  if (cnn_mnist_inference_detail::network != AI_HANDLE_NULL) {
    return;
  }

  const ai_handle acts[] = {cnn_mnist_inference_detail::activations};
  ai_cnn_mnist_create_and_init(&cnn_mnist_inference_detail::network, acts, nullptr);

  cnn_mnist_inference_detail::ai_input =
      ai_cnn_mnist_inputs_get(cnn_mnist_inference_detail::network, nullptr);
  cnn_mnist_inference_detail::ai_output =
      ai_cnn_mnist_outputs_get(cnn_mnist_inference_detail::network, nullptr);
}

static inline void cnn_mnist_infer(const uint8_t *pixels, float *output) {
  for (int i = 0; i < CNN_MNIST_IMG_PIXELS; ++i) {
    cnn_mnist_inference_detail::input_data[i] =
        static_cast<float>(pixels[i]) / 255.0f;
  }

  cnn_mnist_inference_detail::ai_input[0].data =
      AI_HANDLE_PTR(cnn_mnist_inference_detail::input_data);
  cnn_mnist_inference_detail::ai_output[0].data = AI_HANDLE_PTR(output);

  ai_cnn_mnist_run(cnn_mnist_inference_detail::network,
                   cnn_mnist_inference_detail::ai_input,
                   cnn_mnist_inference_detail::ai_output);
}

#endif  // CNN_MNIST_INFERENCE_H
