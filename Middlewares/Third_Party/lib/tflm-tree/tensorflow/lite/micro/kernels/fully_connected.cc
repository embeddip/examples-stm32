/* Copyright 2025 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/lite/micro/kernels/fully_connected.h"

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/portable_tensor_utils.h"
#include "tensorflow/lite/kernels/internal/reference/fully_connected.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/fully_connected.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_log.h"

namespace tflite {
namespace {

void* FullyConnectedInit(TfLiteContext* context, const char* buffer,
                         size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context,
                                           sizeof(OpDataFullyConnected));
}

TfLiteStatus FullyConnectedPrepare(TfLiteContext* context, TfLiteNode* node) {
  MicroPrintf(">>> FC: FullyConnectedPrepare START");
  MicroContext* micro_context = GetMicroContext(context);

  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  auto* data = static_cast<OpDataFullyConnected*>(node->user_data);
  const auto params =
      static_cast<const TfLiteFullyConnectedParams*>(node->builtin_data);

  MicroPrintf(">>> FC: Allocating input tensor...");
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kFullyConnectedInputTensor);
  if (input == nullptr) {
    MicroPrintf(">>> FC: FAILED - input tensor is NULL!");
    while(1) {}
  }
  MicroPrintf(">>> FC: Input tensor OK, type=%d", input->type);

  MicroPrintf(">>> FC: Allocating filter tensor...");
  TfLiteTensor* filter = micro_context->AllocateTempInputTensor(
      node, kFullyConnectedWeightsTensor);
  if (filter == nullptr) {
    MicroPrintf(">>> FC: FAILED - filter tensor is NULL!");
    while(1) {}
  }
  MicroPrintf(">>> FC: Filter tensor OK, type=%d", filter->type);

  MicroPrintf(">>> FC: Allocating bias tensor...");
  TfLiteTensor* bias =
      micro_context->AllocateTempInputTensor(node, kFullyConnectedBiasTensor);
  MicroPrintf(">>> FC: Bias tensor %s", bias ? "OK" : "NULL (optional)");

  MicroPrintf(">>> FC: Allocating output tensor...");
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(
      node, kFullyConnectedOutputTensor);
  if (output == nullptr) {
    MicroPrintf(">>> FC: FAILED - output tensor is NULL!");
    while(1) {}
  }
  MicroPrintf(">>> FC: Output tensor OK, type=%d", output->type);

  MicroPrintf(">>> FC: Checking type compatibility...");
  if (input->type != output->type) {
    MicroPrintf(">>> FC: FAILED - input type %d != output type %d", input->type, output->type);
    while(1) {}
  }
  MicroPrintf(">>> FC: Types match OK");

  MicroPrintf(">>> FC: Validating type combination (input=%d, filter=%d)...", input->type, filter->type);
  if ((input->type == kTfLiteFloat32 && filter->type != kTfLiteFloat32) ||
      (input->type == kTfLiteInt8 &&
       (filter->type != kTfLiteInt8 && filter->type != kTfLiteInt4)) ||
      (input->type == kTfLiteInt16 && filter->type != kTfLiteInt8)) {
    MicroPrintf(">>> FC: FAILED - Input type: %s with filter type: %s not supported.",
                TfLiteTypeGetName(input->type),
                TfLiteTypeGetName(filter->type));
    while(1) {}
    return kTfLiteError;
  }
  MicroPrintf(">>> FC: Type combination valid");

  if (filter->type == kTfLiteInt4) {
    MicroPrintf(">>> FC: Handling Int4 filter...");
    int filter_size =
        RuntimeShape(filter->dims->size,
                     reinterpret_cast<const int32_t*>(filter->dims->data))
            .FlatSize();
    context->RequestScratchBufferInArena(context, filter_size,
                                         &data->filter_buffer_index);
  }

  MicroPrintf(">>> FC: Calling CalculateOpDataFullyConnected...");
  TfLiteStatus calc_status = CalculateOpDataFullyConnected(
                                 context, params->activation, input->type,
                                 input, filter, bias, output, data);
  if (calc_status != kTfLiteOk) {
    MicroPrintf(">>> FC: FAILED - CalculateOpDataFullyConnected returned %d", calc_status);
    while(1) {}
  }
  MicroPrintf(">>> FC: CalculateOpDataFullyConnected OK");

#ifdef USE_TFLM_COMPRESSION

  // Compression scratch buffers.
  // These will only be allocated if the tensor is compressed.
  if (micro_context->IsTensorCompressed(node, kFullyConnectedWeightsTensor) &&
      filter->type == kTfLiteInt4) {
    MicroPrintf("Compression not supported with INT4 tensors");
    return kTfLiteError;
  }
  data->weights_scratch_index =
      micro_context->AllocateDecompressionScratchBuffer(
          node, kFullyConnectedWeightsTensor);
  data->bias_scratch_index = micro_context->AllocateDecompressionScratchBuffer(
      node, kFullyConnectedBiasTensor);

#endif  // USE_TFLM_COMPRESSION

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(filter);
  if (bias != nullptr) {
    micro_context->DeallocateTempTfLiteTensor(bias);
  }
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

TfLiteStatus FullyConnectedEval(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->builtin_data != nullptr);
  const auto* params =
      static_cast<const TfLiteFullyConnectedParams*>(node->builtin_data);

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedInputTensor);
  const TfLiteEvalTensor* filter =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedWeightsTensor);
  const TfLiteEvalTensor* bias =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kFullyConnectedOutputTensor);

#ifdef USE_TFLM_COMPRESSION

  MicroContext* micro_context = GetMicroContext(context);

  const CompressionTensorData* weights_comp_td =
      micro_context->GetTensorCompressionData(node,
                                              kFullyConnectedWeightsTensor);
  const CompressionTensorData* bias_comp_td =
      micro_context->GetTensorCompressionData(node, kFullyConnectedBiasTensor);

#endif  // USE_TFLM_COMPRESSION

  TFLITE_DCHECK(node->user_data != nullptr);
  const auto& data =
      *(static_cast<const OpDataFullyConnected*>(node->user_data));

  // Checks in Prepare ensure input, output and filter types are all the same.
  switch (input->type) {
    case kTfLiteFloat32: {
      tflite::reference_ops::FullyConnected(
          FullyConnectedParamsFloat(params->activation),
          tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<float>(input),
          tflite::micro::GetTensorShape(filter),
#ifdef USE_TFLM_COMPRESSION
          tflite::micro::GetTensorData<float>(micro_context, filter,
                                              weights_comp_td,
                                              data.weights_scratch_index),
          tflite::micro::GetTensorShape(bias),
          tflite::micro::GetOptionalTensorData<float>(
              micro_context, bias, bias_comp_td, data.bias_scratch_index),
#else   // USE_TFLM_COMPRESSION
          tflite::micro::GetTensorData<float>(filter),
          tflite::micro::GetTensorShape(bias),
          tflite::micro::GetOptionalTensorData<float>(bias),
#endif  // USE_TFLM_COMPRESSION
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<float>(output));
      break;
    }

    case kTfLiteInt8: {
      switch (filter->type) {
        case kTfLiteInt4: {
          int8_t* unpacked_filter_data = static_cast<int8_t*>(
              context->GetScratchBuffer(context, data.filter_buffer_index));
          tflite::tensor_utils::UnpackDenseInt4IntoInt8(
              tflite::micro::GetTensorData<int8_t>(filter),
              tflite::micro::GetTensorShape(filter).FlatSize(),
              unpacked_filter_data);
          tflite::reference_integer_ops::FullyConnected(
              FullyConnectedParamsQuantized(data),
              tflite::micro::GetTensorShape(input),
              tflite::micro::GetTensorData<int8_t>(input),
              tflite::micro::GetTensorShape(filter), unpacked_filter_data,
              tflite::micro::GetTensorShape(bias),
              tflite::micro::GetOptionalTensorData<int32_t>(bias),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<int8_t>(output));
          break;
        }
        case kTfLiteInt8: {
          data.is_per_channel
              ? tflite::reference_integer_ops::FullyConnectedPerChannel(
                    FullyConnectedParamsQuantized(data),
                    data.per_channel_output_multiplier,
                    reinterpret_cast<const int*>(data.per_channel_output_shift),
                    tflite::micro::GetTensorShape(input),
                    tflite::micro::GetTensorData<int8_t>(input),
                    tflite::micro::GetTensorShape(filter),
#ifdef USE_TFLM_COMPRESSION
                    tflite::micro::GetTensorData<int8_t>(
                        micro_context, filter, weights_comp_td,
                        data.weights_scratch_index),
                    tflite::micro::GetTensorShape(bias),
                    tflite::micro::GetOptionalTensorData<int32_t>(
                        micro_context, bias, bias_comp_td,
                        data.bias_scratch_index),
#else   // USE_TFLM_COMPRESSION
                    tflite::micro::GetTensorData<int8_t>(filter),
                    tflite::micro::GetTensorShape(bias),
                    tflite::micro::GetOptionalTensorData<int32_t>(bias),
#endif  // USE_TFLM_COMPRESSION
                    tflite::micro::GetTensorShape(output),
                    tflite::micro::GetTensorData<int8_t>(output))
              : tflite::reference_integer_ops::FullyConnected(
                    FullyConnectedParamsQuantized(data),
                    tflite::micro::GetTensorShape(input),
                    tflite::micro::GetTensorData<int8_t>(input),
                    tflite::micro::GetTensorShape(filter),
#ifdef USE_TFLM_COMPRESSION
                    tflite::micro::GetTensorData<int8_t>(
                        micro_context, filter, weights_comp_td,
                        data.weights_scratch_index),
                    tflite::micro::GetTensorShape(bias),
                    tflite::micro::GetOptionalTensorData<int32_t>(
                        micro_context, bias, bias_comp_td,
                        data.bias_scratch_index),
#else   // USE_TFLM_COMPRESSION
                    tflite::micro::GetTensorData<int8_t>(filter),
                    tflite::micro::GetTensorShape(bias),
                    tflite::micro::GetOptionalTensorData<int32_t>(bias),
#endif  // USE_TFLM_COMPRESSION
                    tflite::micro::GetTensorShape(output),
                    tflite::micro::GetTensorData<int8_t>(output));
          break;
        }
        default: {
          MicroPrintf("Filter type %s (%d) not supported.",
                      TfLiteTypeGetName(filter->type), input->type);
          return kTfLiteError;
        }
      }
      break;
    }

    case kTfLiteInt16: {
      switch (filter->type) {
        case kTfLiteInt8: {
          const bool requires_int32_accum =
              (bias != nullptr && bias->type == kTfLiteInt32) ||
              (bias == nullptr && params->quantized_bias_type != kTfLiteInt64);
          if (requires_int32_accum) {
            data.is_per_channel
                ? tflite::reference_integer_ops::FullyConnectedPerChannel(
                      FullyConnectedParamsQuantized(data),
                      data.per_channel_output_multiplier,
                      reinterpret_cast<const int*>(
                          data.per_channel_output_shift),
                      tflite::micro::GetTensorShape(input),
                      tflite::micro::GetTensorData<int16_t>(input),
                      tflite::micro::GetTensorShape(filter),
#ifdef USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorData<int8_t>(
                          micro_context, filter, weights_comp_td,
                          data.weights_scratch_index),
                      tflite::micro::GetTensorShape(bias),
                      tflite::micro::GetOptionalTensorData<int32_t>(
                          micro_context, bias, bias_comp_td,
                          data.bias_scratch_index),
#else   // USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorData<int8_t>(filter),
                      tflite::micro::GetTensorShape(bias),
                      tflite::micro::GetOptionalTensorData<int32_t>(bias),
#endif  // USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorShape(output),
                      tflite::micro::GetTensorData<int16_t>(output))
                : tflite::reference_integer_ops::FullyConnected(
                      FullyConnectedParamsQuantized(data),
                      tflite::micro::GetTensorShape(input),
                      tflite::micro::GetTensorData<int16_t>(input),
                      tflite::micro::GetTensorShape(filter),
#ifdef USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorData<int8_t>(
                          micro_context, filter, weights_comp_td,
                          data.weights_scratch_index),
                      tflite::micro::GetTensorShape(bias),
                      tflite::micro::GetOptionalTensorData<int32_t>(
                          micro_context, bias, bias_comp_td,
                          data.bias_scratch_index),
#else   // USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorData<int8_t>(filter),
                      tflite::micro::GetTensorShape(bias),
                      tflite::micro::GetOptionalTensorData<int32_t>(bias),
#endif  // USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorShape(output),
                      tflite::micro::GetTensorData<int16_t>(output));
          } else {
            data.is_per_channel
                ? tflite::reference_integer_ops::FullyConnectedPerChannel(
                      FullyConnectedParamsQuantized(data),
                      data.per_channel_output_multiplier,
                      reinterpret_cast<const int*>(
                          data.per_channel_output_shift),
                      tflite::micro::GetTensorShape(input),
                      tflite::micro::GetTensorData<int16_t>(input),
                      tflite::micro::GetTensorShape(filter),
#ifdef USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorData<int8_t>(
                          micro_context, filter, weights_comp_td,
                          data.weights_scratch_index),
                      tflite::micro::GetTensorShape(bias),
                      tflite::micro::GetOptionalTensorData<int64_t>(
                          micro_context, bias, bias_comp_td,
                          data.bias_scratch_index),
#else   // USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorData<int8_t>(filter),
                      tflite::micro::GetTensorShape(bias),
                      tflite::micro::GetOptionalTensorData<int64_t>(bias),
#endif  // USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorShape(output),
                      tflite::micro::GetTensorData<int16_t>(output))
                : tflite::reference_integer_ops::FullyConnected(
                      FullyConnectedParamsQuantized(data),
                      tflite::micro::GetTensorShape(input),
                      tflite::micro::GetTensorData<int16_t>(input),
                      tflite::micro::GetTensorShape(filter),
#ifdef USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorData<int8_t>(
                          micro_context, filter, weights_comp_td,
                          data.weights_scratch_index),
                      tflite::micro::GetTensorShape(bias),
                      tflite::micro::GetOptionalTensorData<int64_t>(
                          micro_context, bias, bias_comp_td,
                          data.bias_scratch_index),
#else   // USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorData<int8_t>(filter),
                      tflite::micro::GetTensorShape(bias),
                      tflite::micro::GetOptionalTensorData<int64_t>(bias),
#endif  // USE_TFLM_COMPRESSION
                      tflite::micro::GetTensorShape(output),
                      tflite::micro::GetTensorData<int16_t>(output));
          }
          break;
        }
        default: {
          MicroPrintf("Filter type %s (%d) not supported.",
                      TfLiteTypeGetName(filter->type), input->type);
          return kTfLiteError;
        }
      }
      break;
    }

    default: {
      MicroPrintf("Input type %s (%d) not supported.",
                  TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
    }
  }
  return kTfLiteOk;
}

}  // namespace

TFLMRegistration Register_FULLY_CONNECTED() {
  return tflite::micro::RegisterOp(FullyConnectedInit, FullyConnectedPrepare,
                                   FullyConnectedEval);
}

TFLMInferenceRegistration RegisterInference_FULLY_CONNECTED() {
  return tflite::micro::RegisterOp(FullyConnectedEval);
}

}  // namespace tflite
