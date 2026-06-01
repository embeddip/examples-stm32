#ifndef MNIST_INFERENCE_H
#define MNIST_INFERENCE_H

#include <cstdint>

#include "nn_mnist.h"
#include "nn_mnist_data.h"

#define MNIST_IMG_SIZE 28
#define MNIST_IMG_PIXELS (MNIST_IMG_SIZE * MNIST_IMG_SIZE)
#define MNIST_NUM_CLASSES 10

namespace mnist_inference_detail {

AI_ALIGNED(4)
static ai_u8 activations[AI_NN_MNIST_DATA_ACTIVATIONS_SIZE];

AI_ALIGNED(4)
static ai_float input_data[MNIST_IMG_PIXELS];

static ai_handle network = AI_HANDLE_NULL;
static ai_buffer *ai_input = nullptr;
static ai_buffer *ai_output = nullptr;

}  // namespace mnist_inference_detail

static inline void mnist_init() {
  if (mnist_inference_detail::network != AI_HANDLE_NULL) {
    return;
  }

  const ai_handle acts[] = {mnist_inference_detail::activations};
  ai_nn_mnist_create_and_init(&mnist_inference_detail::network, acts, nullptr);

  mnist_inference_detail::ai_input =
      ai_nn_mnist_inputs_get(mnist_inference_detail::network, nullptr);
  mnist_inference_detail::ai_output =
      ai_nn_mnist_outputs_get(mnist_inference_detail::network, nullptr);
}

static inline void mnist_infer(const uint8_t *pixels, float *output) {
  for (int i = 0; i < MNIST_IMG_PIXELS; ++i) {
    mnist_inference_detail::input_data[i] =
        static_cast<float>(pixels[i]) / 255.0f;
  }

  mnist_inference_detail::ai_input[0].data =
      AI_HANDLE_PTR(mnist_inference_detail::input_data);
  mnist_inference_detail::ai_output[0].data = AI_HANDLE_PTR(output);

  ai_nn_mnist_run(mnist_inference_detail::network,
                  mnist_inference_detail::ai_input,
                  mnist_inference_detail::ai_output);
}

static inline uint8_t mnist_get_prediction(const float *output) {
  uint8_t max_idx = 0;
  float max_val = output[0];

  for (uint8_t i = 1; i < MNIST_NUM_CLASSES; ++i) {
    if (output[i] > max_val) {
      max_val = output[i];
      max_idx = i;
    }
  }

  return max_idx;
}

#endif  // MNIST_INFERENCE_H
