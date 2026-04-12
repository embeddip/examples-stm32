#include "mnist_inference.h"
#include "mnist_model_data.h"

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include <cstring>
#include <new> // For placement new

// SDRAM base address for STM32F746
#define SDRAM_BANK_ADDR ((uint32_t)0xC0000000)

namespace {
// Tensor arena - use external SDRAM for massive space!
// STM32F746 has 8MB SDRAM starting at 0xC0000000
constexpr int kTensorArenaSize = 4 * 1024 * 1024; // 4MB in SDRAM
uint8_t *tensor_arena = reinterpret_cast<uint8_t *>(SDRAM_BANK_ADDR);

// TFLite Micro objects
const tflite::Model *model = nullptr;
tflite::MicroInterpreter *interpreter = nullptr;
TfLiteTensor *input_tensor = nullptr;
TfLiteTensor *output_tensor = nullptr;

// Static storage for interpreter
uint8_t interpreter_buffer[sizeof(tflite::MicroInterpreter)];
} // namespace

extern "C" int mnist_init(void) {
  // Verify SDRAM is accessible
  MicroPrintf("Testing SDRAM access at 0x%08X...", SDRAM_BANK_ADDR);
  volatile uint32_t *sdram_test =
      reinterpret_cast<volatile uint32_t *>(SDRAM_BANK_ADDR);
  *sdram_test = 0xDEADBEEF;
  if (*sdram_test != 0xDEADBEEF) {
    MicroPrintf("SDRAM test FAILED! SDRAM not initialized!");
    while (1) {
    }
  }
  MicroPrintf("SDRAM test OK! Using %d KB tensor arena",
              kTensorArenaSize / 1024);

  // Load model
  MicroPrintf("Loading MNIST model...");
  model = tflite::GetModel(g_mnist_model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    MicroPrintf("Model schema mismatch! Expected %d, got %d",
                TFLITE_SCHEMA_VERSION, model->version());
    return -1;
  }
  MicroPrintf("Model loaded, size: %d bytes", g_mnist_model_data_len);

  // Add TONS of operations to find which one is missing
  MicroPrintf("Creating resolver with MANY operations...");
  static tflite::MicroMutableOpResolver<32> resolver;

  resolver.AddFullyConnected();
  resolver.AddReshape();
  resolver.AddSoftmax();
  resolver.AddRelu();
  resolver.AddRelu6();
  resolver.AddQuantize();
  resolver.AddDequantize();
  resolver.AddAdd();
  resolver.AddMul();
  resolver.AddSub();
  resolver.AddDiv();
  resolver.AddShape();
  resolver.AddPack();
  resolver.AddUnpack();
  resolver.AddExpandDims();
  resolver.AddSqueeze();
  resolver.AddConcatenation();
  resolver.AddStridedSlice();
  resolver.AddSlice();
  resolver.AddSplit();
  resolver.AddCast();
  resolver.AddPad();

  resolver.AddTranspose();

  MicroPrintf("All operations added successfully");

  // Create interpreter using placement new
  MicroPrintf("Creating interpreter with %d byte arena...", kTensorArenaSize);
  interpreter = new (interpreter_buffer)
      tflite::MicroInterpreter(model, resolver, tensor_arena, kTensorArenaSize);

  // Allocate tensors
  MicroPrintf("Allocating tensors...");
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    MicroPrintf("!!! AllocateTensors() FAILED with status: %d",
                allocate_status);
    MicroPrintf("!!! Tensor arena: %d bytes", kTensorArenaSize);
    MicroPrintf("!!! Try: 1) Retrain with simpler model 2) Check model file");
    return -1;
  }
  MicroPrintf("SUCCESS! Tensors allocated!");

  // Get input/output tensors
  input_tensor = interpreter->input(0);
  output_tensor = interpreter->output(0);

  // Log info
  MicroPrintf("MNIST model initialized");
  MicroPrintf("Input: %d bytes, type: %d", input_tensor->bytes,
              input_tensor->type);
  MicroPrintf("Output: %d bytes, type: %d", output_tensor->bytes,
              output_tensor->type);
  MicroPrintf("Arena used: %d / %d bytes", interpreter->arena_used_bytes(),
              kTensorArenaSize);

  return 0;
}

extern "C" int mnist_infer(const uint8_t *pixels, float *output) {
  if (!interpreter || !input_tensor || !output_tensor) {
    return -1;
  }

  // Copy and normalize input (uint8 -> float [0, 1])
  float *input_data = input_tensor->data.f;
  for (int i = 0; i < 28 * 28; i++) {
    input_data[i] = pixels[i] / 255.0f;
  }

  // Run inference
  if (interpreter->Invoke() != kTfLiteOk) {
    MicroPrintf("Invoke() failed");
    return -1;
  }

  // Copy output
  memcpy(output, output_tensor->data.f, 10 * sizeof(float));

  return 0;
}

extern "C" uint8_t mnist_get_prediction(const float *output) {
  uint8_t predicted = 0;
  float max_score = output[0];

  for (uint8_t i = 1; i < 10; i++) {
    if (output[i] > max_score) {
      max_score = output[i];
      predicted = i;
    }
  }

  return predicted;
}
