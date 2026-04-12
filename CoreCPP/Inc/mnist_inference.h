#ifndef MNIST_INFERENCE_H
#define MNIST_INFERENCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Initialize the MNIST model
 * @return 0 on success, -1 on error
 */
int mnist_init(void);

/**
 * @brief Run inference on 28x28 grayscale image
 * @param pixels Pointer to 784 uint8_t pixel values (0-255)
 * @param output Pointer to output buffer (10 floats for class scores)
 * @return 0 on success, -1 on error
 */
int mnist_infer(const uint8_t* pixels, float* output);

/**
 * @brief Get predicted digit from output scores
 * @param output Pointer to 10 float scores
 * @return Predicted digit (0-9)
 */
uint8_t mnist_get_prediction(const float* output);

#ifdef __cplusplus
}
#endif

#endif // MNIST_INFERENCE_H
