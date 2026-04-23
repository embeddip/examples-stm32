#include <embedDIP.hpp>
#include <main.hpp>
#include "nn_mnist.h"
#include "nn_mnist_data.h"

using namespace embedDIP;

#define IMG_SIZE 28
#define IMG_PIXELS (IMG_SIZE * IMG_SIZE)
#define NUM_CLASSES 10

AI_ALIGNED(4)
static ai_u8 activations[AI_NN_MNIST_DATA_ACTIVATIONS_SIZE];

AI_ALIGNED(4)
static ai_float input_data[IMG_PIXELS];

AI_ALIGNED(4)
static ai_float output_data[NUM_CLASSES];

static ai_handle network = AI_HANDLE_NULL;
static ai_buffer *ai_input;
static ai_buffer *ai_output;

void model_init(void) {
  const ai_handle acts[] = {activations};

  ai_nn_mnist_create_and_init(&network, acts, NULL);

  ai_input = ai_nn_mnist_inputs_get(network, NULL);
  ai_output = ai_nn_mnist_outputs_get(network, NULL);
}

void model_inference(void) {
  ai_input[0].data = AI_HANDLE_PTR(input_data);
  ai_output[0].data = AI_HANDLE_PTR(output_data);

  ai_nn_mnist_run(network, ai_input, ai_output);
}

uint8_t get_predicted_digit(void) {
  uint8_t max_idx = 0;
  float max_val = output_data[0];

  for (uint8_t i = 1; i < NUM_CLASSES; i++) {
    if (output_data[i] > max_val) {
      max_val = output_data[i];
      max_idx = i;
    }
  }
  return max_idx;
}

int application() {
  embedDIP::Serial serial(&stm32_uart);
  embedDIP::Image inImg(IMG_SIZE, IMG_SIZE, IMAGE_FORMAT_GRAYSCALE);

  serial.init();

  const ai_handle acts[] = {activations};

  ai_nn_mnist_create_and_init(&network, acts, NULL);
  ai_input = ai_nn_mnist_inputs_get(network, NULL);
  ai_output = ai_nn_mnist_outputs_get(network, NULL);

  serial.capture(inImg);

  uint8_t *pixels = (uint8_t *)inImg.pixels();
  for (int i = 0; i < IMG_PIXELS; ++i) {
    input_data[i] = ((float)pixels[i]) / 255.0f;
  }

  ai_input[0].data = AI_HANDLE_PTR(input_data);
  ai_output[0].data = AI_HANDLE_PTR(output_data);
  ai_nn_mnist_run(network, ai_input, ai_output);

  uint8_t predicted_digit = get_predicted_digit();
  serial.send1D(&predicted_digit, sizeof(uint8_t), 1, SERIAL_DATA_OTHER);

  while (1) {
    ;
  }
}
