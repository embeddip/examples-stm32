#include <cstdint>
#include <cstring>
#include <new>

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"

namespace
{

constexpr uint32_t kSdramBankAddr = 0xC0000000u;
constexpr int kTensorArenaSize = 4 * 1024 * 1024;
constexpr int kImagePixels = 128 * 128;

struct InferenceContext {
    const tflite::Model *model = nullptr;
    tflite::MicroInterpreter *interpreter = nullptr;
    TfLiteTensor *input = nullptr;
    TfLiteTensor *output = nullptr;
};

InferenceContext g_ctx;
uint8_t *g_tensor_arena = reinterpret_cast<uint8_t *>(kSdramBankAddr);
tflite::MicroMutableOpResolver<32> g_resolver;
bool g_resolver_initialized = false;
uint8_t g_interpreter_buffer[sizeof(tflite::MicroInterpreter)] = {};

void AddCommonOps(tflite::MicroMutableOpResolver<32> &resolver)
{
    resolver.AddConv2D();
    resolver.AddDepthwiseConv2D();
    resolver.AddTransposeConv();
    resolver.AddMaxPool2D();
    resolver.AddAveragePool2D();
    resolver.AddResizeNearestNeighbor();
    resolver.AddConcatenation();
    resolver.AddAdd();
    resolver.AddSub();
    resolver.AddMul();
    resolver.AddReshape();
    resolver.AddRelu();
    resolver.AddRelu6();
    resolver.AddLeakyRelu();
    resolver.AddLogistic();
    resolver.AddSoftmax();
    resolver.AddPad();
    resolver.AddPack();
    resolver.AddUnpack();
    resolver.AddStridedSlice();
    resolver.AddSlice();
    resolver.AddSplit();
    resolver.AddSplitV();
    resolver.AddTranspose();
    resolver.AddMean();
    resolver.AddQuantize();
    resolver.AddDequantize();
    resolver.AddCast();
    resolver.AddShape();
    resolver.AddExpandDims();
    resolver.AddSqueeze();
    resolver.AddFullyConnected();
}

int TensorHwc(const TfLiteTensor *tensor, int *h, int *w, int *c)
{
    if (!tensor || !tensor->dims || tensor->dims->size < 3) {
        return -1;
    }
    const TfLiteIntArray *dims = tensor->dims;
    const int n = dims->size;
    *h = dims->data[n - 3];
    *w = dims->data[n - 2];
    *c = dims->data[n - 1];
    return 0;
}

TfLiteTensor *LargestSpatialOutput(tflite::MicroInterpreter *interpreter)
{
    if (!interpreter || interpreter->outputs_size() <= 0) {
        return nullptr;
    }

    TfLiteTensor *best = interpreter->output(0);
    int best_score = -1;

    for (int i = 0; i < interpreter->outputs_size(); ++i) {
        TfLiteTensor *candidate = interpreter->output(i);
        int h = 0;
        int w = 0;
        int c = 0;
        int score = 0;

        if (TensorHwc(candidate, &h, &w, &c) == 0) {
            score = h * w * c;
        } else {
            score = static_cast<int>(candidate->bytes);
        }

        if (score > best_score) {
            best_score = score;
            best = candidate;
        }
    }

    return best;
}

int FillInputGray(const uint8_t *pixels, TfLiteTensor *input)
{
    if (!pixels || !input) {
        return -1;
    }

    int h = 0;
    int w = 0;
    int c = 0;
    if (TensorHwc(input, &h, &w, &c) != 0) {
        return -1;
    }

    const int spatial = h * w;
    const int n = (spatial < kImagePixels) ? spatial : kImagePixels;

    if (input->type == kTfLiteFloat32) {
        float *dst = input->data.f;
        for (int i = 0; i < n; ++i) {
            const float v = pixels[i] / 255.0f;
            for (int ch = 0; ch < c; ++ch) {
                dst[i * c + ch] = v;
            }
        }
        return 0;
    }

    if (input->type == kTfLiteUInt8) {
        const int bytes = static_cast<int>(input->bytes);
        const int copy_n = (bytes < kImagePixels) ? bytes : kImagePixels;
        memcpy(input->data.uint8, pixels, static_cast<size_t>(copy_n));
        return 0;
    }

    if (input->type == kTfLiteInt8) {
        int8_t *dst = input->data.int8;
        for (int i = 0; i < n; ++i) {
            const int8_t v = static_cast<int8_t>(static_cast<int>(pixels[i]) - 128);
            for (int ch = 0; ch < c; ++ch) {
                dst[i * c + ch] = v;
            }
        }
        return 0;
    }

    return -1;
}

int DecodeToMask(const TfLiteTensor *output, uint8_t *mask)
{
    if (!output || !mask) {
        return -1;
    }

    int h = 0;
    int w = 0;
    int c = 0;
    if (TensorHwc(output, &h, &w, &c) != 0) {
        return -1;
    }

    const int spatial = h * w;
    const int n = (spatial < kImagePixels) ? spatial : kImagePixels;

    if (output->type == kTfLiteFloat32) {
        const float *src = output->data.f;
        for (int i = 0; i < n; ++i) {
            if (c <= 1) {
                mask[i] = (src[i] > 0.5f) ? 255 : 0;
            } else {
                int best_idx = 0;
                float best_val = src[i * c];
                for (int ch = 1; ch < c; ++ch) {
                    const float v = src[i * c + ch];
                    if (v > best_val) {
                        best_val = v;
                        best_idx = ch;
                    }
                }
                mask[i] = static_cast<uint8_t>((best_idx * 255) / (c - 1));
            }
        }
        if (kImagePixels > n) {
            memset(mask + n, 0, static_cast<size_t>(kImagePixels - n));
        }
        return 0;
    }

    if (output->type == kTfLiteUInt8) {
        if (c <= 1) {
            memcpy(mask, output->data.uint8, static_cast<size_t>(n));
        } else {
            for (int i = 0; i < n; ++i) {
                mask[i] = output->data.uint8[i * c];
            }
        }
        if (kImagePixels > n) {
            memset(mask + n, 0, static_cast<size_t>(kImagePixels - n));
        }
        return 0;
    }

    if (output->type == kTfLiteInt8) {
        for (int i = 0; i < n; ++i) {
            const int8_t raw = output->data.int8[i * ((c > 0) ? c : 1)];
            mask[i] = static_cast<uint8_t>(static_cast<int>(raw) + 128);
        }
        if (kImagePixels > n) {
            memset(mask + n, 0, static_cast<size_t>(kImagePixels - n));
        }
        return 0;
    }

    return -1;
}

}  // namespace

extern "C" int tlfm_seg_init(const unsigned char *model_data, unsigned int model_data_len)
{
    if (!model_data || model_data_len == 0) {
        return -1;
    }

    if (g_ctx.interpreter) {
        return 0;
    }

    g_ctx.model = tflite::GetModel(model_data);
    if (!g_ctx.model || g_ctx.model->version() != TFLITE_SCHEMA_VERSION) {
        return -1;
    }

    if (!g_resolver_initialized) {
        AddCommonOps(g_resolver);
        g_resolver_initialized = true;
    }

    g_ctx.interpreter = new (g_interpreter_buffer)
        tflite::MicroInterpreter(g_ctx.model, g_resolver, g_tensor_arena, kTensorArenaSize);

    if (g_ctx.interpreter->AllocateTensors() != kTfLiteOk) {
        return -1;
    }

    g_ctx.input = g_ctx.interpreter->input(0);
    g_ctx.output = LargestSpatialOutput(g_ctx.interpreter);

    return (g_ctx.input && g_ctx.output) ? 0 : -1;
}

extern "C" int tlfm_seg_infer(const uint8_t *pixels, uint8_t *mask)
{
    if (!g_ctx.interpreter || !g_ctx.input || !g_ctx.output) {
        return -1;
    }

    if (FillInputGray(pixels, g_ctx.input) != 0) {
        return -1;
    }

    if (g_ctx.interpreter->Invoke() != kTfLiteOk) {
        return -1;
    }

    return DecodeToMask(g_ctx.output, mask);
}
