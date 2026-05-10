/**
 ******************************************************************************
 * @file    mobilenetv2_fp32.c
 * @author  AST Embedded Analytics Research Platform
 * @date    2026-04-11T13:25:10+0200
 * @brief   AI Tool Automatic Code Generator for Embedded NN computing
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 ******************************************************************************
 */


#include "mobilenetv2_fp32.h"

#include "ai_math_helpers.h"
#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "core_common.h"
#include "core_convert.h"
#include "layers.h"
#include "mobilenetv2_fp32_data.h"


#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_mobilenetv2_fp32

#undef AI_MOBILENETV2_FP32_MODEL_SIGNATURE
#define AI_MOBILENETV2_FP32_MODEL_SIGNATURE "0x11d6302553732961a463c8612a443ef4"

#ifndef AI_TOOLS_REVISION_ID
    #define AI_TOOLS_REVISION_ID ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME "2026-04-11T13:25:10+0200"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME __DATE__ " " __TIME__

#undef AI_MOBILENETV2_FP32_N_BATCHES
#define AI_MOBILENETV2_FP32_N_BATCHES (1)

static ai_ptr g_mobilenetv2_fp32_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_mobilenetv2_fp32_weights_map[1] = AI_C_ARRAY_INIT;


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(serving_default_input_layer0_output_array,
                     AI_ARRAY_FORMAT_FLOAT | AI_FMT_FLAG_IS_IO,
                     NULL,
                     NULL,
                     16384,
                     AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(conv2d_0_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 45056, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(nl_0_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 45056, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(conv2d_1_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 45056, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(nl_1_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 45056, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(conv2d_2_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 20480, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 122880, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(nl_3_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 122880, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(conv2d_4_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 30720, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(nl_4_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 30720, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(conv2d_5_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8192, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 49152, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(nl_6_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 49152, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(conv2d_7_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 49152, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(nl_7_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 49152, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(conv2d_8_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8192, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(eltwise_9_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8192, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 49152, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(nl_10_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 49152, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(conv2d_11_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 12288, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(nl_11_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 12288, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2816, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(conv2d_13_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 16896, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(nl_13_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 16896, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(conv2d_14_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 16896, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(nl_14_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 16896, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(conv2d_15_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2816, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(eltwise_16_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2816, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(conv2d_17_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 16896, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(nl_17_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 16896, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(conv2d_18_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 4224, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(nl_18_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 4224, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(conv2d_19_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 1408, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(conv2d_20_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8448, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(nl_20_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8448, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(conv2d_21_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8448, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(nl_21_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8448, AI_STATIC)

/* Array#37 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 1408, AI_STATIC)

/* Array#38 */
AI_ARRAY_OBJ_DECLARE(eltwise_23_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 1408, AI_STATIC)

/* Array#39 */
AI_ARRAY_OBJ_DECLARE(conv2d_27_upsample_output_array,
                     AI_ARRAY_FORMAT_FLOAT,
                     NULL,
                     NULL,
                     4950,
                     AI_STATIC)

/* Array#40 */
AI_ARRAY_OBJ_DECLARE(conv2d_27_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2816, AI_STATIC)

/* Array#41 */
AI_ARRAY_OBJ_DECLARE(concat_28_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 5632, AI_STATIC)

/* Array#42 */
AI_ARRAY_OBJ_DECLARE(conv2d_29_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2816, AI_STATIC)

/* Array#43 */
AI_ARRAY_OBJ_DECLARE(nl_29_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2816, AI_STATIC)

/* Array#44 */
AI_ARRAY_OBJ_DECLARE(conv2d_33_upsample_output_array,
                     AI_ARRAY_FORMAT_FLOAT,
                     NULL,
                     NULL,
                     10571,
                     AI_STATIC)

/* Array#45 */
AI_ARRAY_OBJ_DECLARE(conv2d_33_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8192, AI_STATIC)

/* Array#46 */
AI_ARRAY_OBJ_DECLARE(concat_34_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 16384, AI_STATIC)

/* Array#47 */
AI_ARRAY_OBJ_DECLARE(conv2d_35_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8192, AI_STATIC)

/* Array#48 */
AI_ARRAY_OBJ_DECLARE(nl_35_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8192, AI_STATIC)

/* Array#49 */
AI_ARRAY_OBJ_DECLARE(conv2d_39_upsample_output_array,
                     AI_ARRAY_FORMAT_FLOAT,
                     NULL,
                     NULL,
                     31752,
                     AI_STATIC)

/* Array#50 */
AI_ARRAY_OBJ_DECLARE(conv2d_39_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 20480, AI_STATIC)

/* Array#51 */
AI_ARRAY_OBJ_DECLARE(concat_40_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 40960, AI_STATIC)

/* Array#52 */
AI_ARRAY_OBJ_DECLARE(conv2d_41_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 20480, AI_STATIC)

/* Array#53 */
AI_ARRAY_OBJ_DECLARE(nl_41_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 20480, AI_STATIC)

/* Array#54 */
AI_ARRAY_OBJ_DECLARE(conv2d_45_upsample_output_array,
                     AI_ARRAY_FORMAT_FLOAT,
                     NULL,
                     NULL,
                     80645,
                     AI_STATIC)

/* Array#55 */
AI_ARRAY_OBJ_DECLARE(conv2d_45_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 81920, AI_STATIC)

/* Array#56 */
AI_ARRAY_OBJ_DECLARE(conv2d_46_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 81920, AI_STATIC)

/* Array#57 */
AI_ARRAY_OBJ_DECLARE(nl_46_nl_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 81920, AI_STATIC)

/* Array#58 */
AI_ARRAY_OBJ_DECLARE(conv2d_47_output_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 32768, AI_STATIC)

/* Array#59 */
AI_ARRAY_OBJ_DECLARE(nl_48_output_array,
                     AI_ARRAY_FORMAT_FLOAT | AI_FMT_FLAG_IS_IO,
                     NULL,
                     NULL,
                     32768,
                     AI_STATIC)

/* Array#60 */
AI_ARRAY_OBJ_DECLARE(conv2d_0_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 99, AI_STATIC)

/* Array#61 */
AI_ARRAY_OBJ_DECLARE(conv2d_0_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#62 */
AI_ARRAY_OBJ_DECLARE(conv2d_1_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 99, AI_STATIC)

/* Array#63 */
AI_ARRAY_OBJ_DECLARE(conv2d_1_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#64 */
AI_ARRAY_OBJ_DECLARE(conv2d_2_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 55, AI_STATIC)

/* Array#65 */
AI_ARRAY_OBJ_DECLARE(conv2d_2_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 5, AI_STATIC)

/* Array#66 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 150, AI_STATIC)

/* Array#67 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 30, AI_STATIC)

/* Array#68 */
AI_ARRAY_OBJ_DECLARE(conv2d_4_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 270, AI_STATIC)

/* Array#69 */
AI_ARRAY_OBJ_DECLARE(conv2d_4_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 30, AI_STATIC)

/* Array#70 */
AI_ARRAY_OBJ_DECLARE(conv2d_5_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 240, AI_STATIC)

/* Array#71 */
AI_ARRAY_OBJ_DECLARE(conv2d_5_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8, AI_STATIC)

/* Array#72 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 384, AI_STATIC)

/* Array#73 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 48, AI_STATIC)

/* Array#74 */
AI_ARRAY_OBJ_DECLARE(conv2d_7_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 432, AI_STATIC)

/* Array#75 */
AI_ARRAY_OBJ_DECLARE(conv2d_7_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 48, AI_STATIC)

/* Array#76 */
AI_ARRAY_OBJ_DECLARE(conv2d_8_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 384, AI_STATIC)

/* Array#77 */
AI_ARRAY_OBJ_DECLARE(conv2d_8_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8, AI_STATIC)

/* Array#78 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 384, AI_STATIC)

/* Array#79 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 48, AI_STATIC)

/* Array#80 */
AI_ARRAY_OBJ_DECLARE(conv2d_11_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 432, AI_STATIC)

/* Array#81 */
AI_ARRAY_OBJ_DECLARE(conv2d_11_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 48, AI_STATIC)

/* Array#82 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 528, AI_STATIC)

/* Array#83 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#84 */
AI_ARRAY_OBJ_DECLARE(conv2d_13_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 726, AI_STATIC)

/* Array#85 */
AI_ARRAY_OBJ_DECLARE(conv2d_13_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 66, AI_STATIC)

/* Array#86 */
AI_ARRAY_OBJ_DECLARE(conv2d_14_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 594, AI_STATIC)

/* Array#87 */
AI_ARRAY_OBJ_DECLARE(conv2d_14_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 66, AI_STATIC)

/* Array#88 */
AI_ARRAY_OBJ_DECLARE(conv2d_15_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 726, AI_STATIC)

/* Array#89 */
AI_ARRAY_OBJ_DECLARE(conv2d_15_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#90 */
AI_ARRAY_OBJ_DECLARE(conv2d_17_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 726, AI_STATIC)

/* Array#91 */
AI_ARRAY_OBJ_DECLARE(conv2d_17_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 66, AI_STATIC)

/* Array#92 */
AI_ARRAY_OBJ_DECLARE(conv2d_18_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 594, AI_STATIC)

/* Array#93 */
AI_ARRAY_OBJ_DECLARE(conv2d_18_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 66, AI_STATIC)

/* Array#94 */
AI_ARRAY_OBJ_DECLARE(conv2d_19_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 1452, AI_STATIC)

/* Array#95 */
AI_ARRAY_OBJ_DECLARE(conv2d_19_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 22, AI_STATIC)

/* Array#96 */
AI_ARRAY_OBJ_DECLARE(conv2d_20_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2904, AI_STATIC)

/* Array#97 */
AI_ARRAY_OBJ_DECLARE(conv2d_20_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 132, AI_STATIC)

/* Array#98 */
AI_ARRAY_OBJ_DECLARE(conv2d_21_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 1188, AI_STATIC)

/* Array#99 */
AI_ARRAY_OBJ_DECLARE(conv2d_21_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 132, AI_STATIC)

/* Array#100 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2904, AI_STATIC)

/* Array#101 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 22, AI_STATIC)

/* Array#102 */
AI_ARRAY_OBJ_DECLARE(conv2d_27_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 968, AI_STATIC)

/* Array#103 */
AI_ARRAY_OBJ_DECLARE(conv2d_27_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#104 */
AI_ARRAY_OBJ_DECLARE(conv2d_29_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2178, AI_STATIC)

/* Array#105 */
AI_ARRAY_OBJ_DECLARE(conv2d_29_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#106 */
AI_ARRAY_OBJ_DECLARE(conv2d_33_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 352, AI_STATIC)

/* Array#107 */
AI_ARRAY_OBJ_DECLARE(conv2d_33_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8, AI_STATIC)

/* Array#108 */
AI_ARRAY_OBJ_DECLARE(conv2d_35_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 1152, AI_STATIC)

/* Array#109 */
AI_ARRAY_OBJ_DECLARE(conv2d_35_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8, AI_STATIC)

/* Array#110 */
AI_ARRAY_OBJ_DECLARE(conv2d_39_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 160, AI_STATIC)

/* Array#111 */
AI_ARRAY_OBJ_DECLARE(conv2d_39_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 5, AI_STATIC)

/* Array#112 */
AI_ARRAY_OBJ_DECLARE(conv2d_41_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 450, AI_STATIC)

/* Array#113 */
AI_ARRAY_OBJ_DECLARE(conv2d_41_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 5, AI_STATIC)

/* Array#114 */
AI_ARRAY_OBJ_DECLARE(conv2d_45_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 100, AI_STATIC)

/* Array#115 */
AI_ARRAY_OBJ_DECLARE(conv2d_45_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 5, AI_STATIC)

/* Array#116 */
AI_ARRAY_OBJ_DECLARE(conv2d_46_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 225, AI_STATIC)

/* Array#117 */
AI_ARRAY_OBJ_DECLARE(conv2d_46_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 5, AI_STATIC)

/* Array#118 */
AI_ARRAY_OBJ_DECLARE(conv2d_47_weights_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 10, AI_STATIC)

/* Array#119 */
AI_ARRAY_OBJ_DECLARE(conv2d_47_bias_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 2, AI_STATIC)

/* Array#120 */
AI_ARRAY_OBJ_DECLARE(conv2d_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 9, AI_STATIC)

/* Array#121 */
AI_ARRAY_OBJ_DECLARE(conv2d_2_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#122 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 5, AI_STATIC)

/* Array#123 */
AI_ARRAY_OBJ_DECLARE(conv2d_5_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 30, AI_STATIC)

/* Array#124 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8, AI_STATIC)

/* Array#125 */
AI_ARRAY_OBJ_DECLARE(conv2d_8_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 48, AI_STATIC)

/* Array#126 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 8, AI_STATIC)

/* Array#127 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 48, AI_STATIC)

/* Array#128 */
AI_ARRAY_OBJ_DECLARE(conv2d_13_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#129 */
AI_ARRAY_OBJ_DECLARE(conv2d_15_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 66, AI_STATIC)

/* Array#130 */
AI_ARRAY_OBJ_DECLARE(conv2d_17_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 11, AI_STATIC)

/* Array#131 */
AI_ARRAY_OBJ_DECLARE(conv2d_19_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 66, AI_STATIC)

/* Array#132 */
AI_ARRAY_OBJ_DECLARE(conv2d_20_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 22, AI_STATIC)

/* Array#133 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 132, AI_STATIC)

/* Array#134 */
AI_ARRAY_OBJ_DECLARE(conv2d_27_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 88, AI_STATIC)

/* Array#135 */
AI_ARRAY_OBJ_DECLARE(conv2d_29_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 198, AI_STATIC)

/* Array#136 */
AI_ARRAY_OBJ_DECLARE(conv2d_33_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 44, AI_STATIC)

/* Array#137 */
AI_ARRAY_OBJ_DECLARE(conv2d_35_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 144, AI_STATIC)

/* Array#138 */
AI_ARRAY_OBJ_DECLARE(conv2d_39_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 32, AI_STATIC)

/* Array#139 */
AI_ARRAY_OBJ_DECLARE(conv2d_41_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 90, AI_STATIC)

/* Array#140 */
AI_ARRAY_OBJ_DECLARE(conv2d_45_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 20, AI_STATIC)

/* Array#141 */
AI_ARRAY_OBJ_DECLARE(conv2d_46_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 45, AI_STATIC)

/* Array#142 */
AI_ARRAY_OBJ_DECLARE(conv2d_47_scratch0_array, AI_ARRAY_FORMAT_FLOAT, NULL, NULL, 5, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(concat_28_output,
                      AI_STATIC,
                      0,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 88, 1408),
                      1,
                      &concat_28_output_array,
                      NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(concat_34_output,
                      AI_STATIC,
                      1,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 16, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 64, 2048),
                      1,
                      &concat_34_output_array,
                      NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(concat_40_output,
                      AI_STATIC,
                      2,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 10, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 40, 2560),
                      1,
                      &concat_40_output_array,
                      NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(conv2d_0_bias,
                      AI_STATIC,
                      3,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_0_bias_array,
                      NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(conv2d_0_output,
                      AI_STATIC,
                      4,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 44, 2816),
                      1,
                      &conv2d_0_output_array,
                      NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(conv2d_0_scratch0,
                      AI_STATIC,
                      5,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 1, 3, 3),
                      AI_STRIDE_INIT(4, 4, 4, 4, 12),
                      1,
                      &conv2d_0_scratch0_array,
                      NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(conv2d_0_weights,
                      AI_STATIC,
                      6,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 3, 3, 11),
                      AI_STRIDE_INIT(4, 4, 4, 44, 132),
                      1,
                      &conv2d_0_weights_array,
                      NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_bias,
                      AI_STATIC,
                      7,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 192, 192),
                      1,
                      &conv2d_10_bias_array,
                      NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_output,
                      AI_STATIC,
                      8,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 192, 6144),
                      1,
                      &conv2d_10_output_array,
                      NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_scratch0,
                      AI_STATIC,
                      9,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 32, 32),
                      1,
                      &conv2d_10_scratch0_array,
                      NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_weights,
                      AI_STATIC,
                      10,
                      0x0,
                      AI_SHAPE_INIT(4, 8, 1, 1, 48),
                      AI_STRIDE_INIT(4, 4, 32, 1536, 1536),
                      1,
                      &conv2d_10_weights_array,
                      NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(conv2d_11_bias,
                      AI_STATIC,
                      11,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 192, 192),
                      1,
                      &conv2d_11_bias_array,
                      NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(conv2d_11_output,
                      AI_STATIC,
                      12,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 192, 3072),
                      1,
                      &conv2d_11_output_array,
                      NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(conv2d_11_weights,
                      AI_STATIC,
                      13,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 3, 3, 48),
                      AI_STRIDE_INIT(4, 1, 48, 48, 48),
                      1,
                      &conv2d_11_weights_array,
                      NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_bias,
                      AI_STATIC,
                      14,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_12_bias_array,
                      NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_output,
                      AI_STATIC,
                      15,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 44, 704),
                      1,
                      &conv2d_12_output_array,
                      NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_scratch0,
                      AI_STATIC,
                      16,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 192, 192),
                      1,
                      &conv2d_12_scratch0_array,
                      NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_weights,
                      AI_STATIC,
                      17,
                      0x0,
                      AI_SHAPE_INIT(4, 48, 1, 1, 11),
                      AI_STRIDE_INIT(4, 4, 192, 2112, 2112),
                      1,
                      &conv2d_12_weights_array,
                      NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(conv2d_13_bias,
                      AI_STATIC,
                      18,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 264, 264),
                      1,
                      &conv2d_13_bias_array,
                      NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(conv2d_13_output,
                      AI_STATIC,
                      19,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 264, 4224),
                      1,
                      &conv2d_13_output_array,
                      NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(conv2d_13_scratch0,
                      AI_STATIC,
                      20,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_13_scratch0_array,
                      NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(conv2d_13_weights,
                      AI_STATIC,
                      21,
                      0x0,
                      AI_SHAPE_INIT(4, 11, 1, 1, 66),
                      AI_STRIDE_INIT(4, 4, 44, 2904, 2904),
                      1,
                      &conv2d_13_weights_array,
                      NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(conv2d_14_bias,
                      AI_STATIC,
                      22,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 264, 264),
                      1,
                      &conv2d_14_bias_array,
                      NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(conv2d_14_output,
                      AI_STATIC,
                      23,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 264, 4224),
                      1,
                      &conv2d_14_output_array,
                      NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(conv2d_14_weights,
                      AI_STATIC,
                      24,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 3, 3, 66),
                      AI_STRIDE_INIT(4, 1, 66, 66, 66),
                      1,
                      &conv2d_14_weights_array,
                      NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(conv2d_15_bias,
                      AI_STATIC,
                      25,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_15_bias_array,
                      NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(conv2d_15_output,
                      AI_STATIC,
                      26,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 44, 704),
                      1,
                      &conv2d_15_output_array,
                      NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(conv2d_15_scratch0,
                      AI_STATIC,
                      27,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 264, 264),
                      1,
                      &conv2d_15_scratch0_array,
                      NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(conv2d_15_weights,
                      AI_STATIC,
                      28,
                      0x0,
                      AI_SHAPE_INIT(4, 66, 1, 1, 11),
                      AI_STRIDE_INIT(4, 4, 264, 2904, 2904),
                      1,
                      &conv2d_15_weights_array,
                      NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(conv2d_17_bias,
                      AI_STATIC,
                      29,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 264, 264),
                      1,
                      &conv2d_17_bias_array,
                      NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(conv2d_17_output,
                      AI_STATIC,
                      30,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 264, 4224),
                      1,
                      &conv2d_17_output_array,
                      NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(conv2d_17_scratch0,
                      AI_STATIC,
                      31,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_17_scratch0_array,
                      NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(conv2d_17_weights,
                      AI_STATIC,
                      32,
                      0x0,
                      AI_SHAPE_INIT(4, 11, 1, 1, 66),
                      AI_STRIDE_INIT(4, 4, 44, 2904, 2904),
                      1,
                      &conv2d_17_weights_array,
                      NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(conv2d_18_bias,
                      AI_STATIC,
                      33,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 264, 264),
                      1,
                      &conv2d_18_bias_array,
                      NULL)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(conv2d_18_output,
                      AI_STATIC,
                      34,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 264, 2112),
                      1,
                      &conv2d_18_output_array,
                      NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(conv2d_18_weights,
                      AI_STATIC,
                      35,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 3, 3, 66),
                      AI_STRIDE_INIT(4, 1, 66, 66, 66),
                      1,
                      &conv2d_18_weights_array,
                      NULL)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(conv2d_19_bias,
                      AI_STATIC,
                      36,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 88, 88),
                      1,
                      &conv2d_19_bias_array,
                      NULL)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(conv2d_19_output,
                      AI_STATIC,
                      37,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 88, 704),
                      1,
                      &conv2d_19_output_array,
                      NULL)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(conv2d_19_scratch0,
                      AI_STATIC,
                      38,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 264, 264),
                      1,
                      &conv2d_19_scratch0_array,
                      NULL)

/* Tensor #39 */
AI_TENSOR_OBJ_DECLARE(conv2d_19_weights,
                      AI_STATIC,
                      39,
                      0x0,
                      AI_SHAPE_INIT(4, 66, 1, 1, 22),
                      AI_STRIDE_INIT(4, 4, 264, 5808, 5808),
                      1,
                      &conv2d_19_weights_array,
                      NULL)

/* Tensor #40 */
AI_TENSOR_OBJ_DECLARE(conv2d_1_bias,
                      AI_STATIC,
                      40,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_1_bias_array,
                      NULL)

/* Tensor #41 */
AI_TENSOR_OBJ_DECLARE(conv2d_1_output,
                      AI_STATIC,
                      41,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 44, 2816),
                      1,
                      &conv2d_1_output_array,
                      NULL)

/* Tensor #42 */
AI_TENSOR_OBJ_DECLARE(conv2d_1_weights,
                      AI_STATIC,
                      42,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 3, 3, 11),
                      AI_STRIDE_INIT(4, 1, 11, 11, 11),
                      1,
                      &conv2d_1_weights_array,
                      NULL)

/* Tensor #43 */
AI_TENSOR_OBJ_DECLARE(conv2d_20_bias,
                      AI_STATIC,
                      43,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 132, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 528, 528),
                      1,
                      &conv2d_20_bias_array,
                      NULL)

/* Tensor #44 */
AI_TENSOR_OBJ_DECLARE(conv2d_20_output,
                      AI_STATIC,
                      44,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 132, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 528, 4224),
                      1,
                      &conv2d_20_output_array,
                      NULL)

/* Tensor #45 */
AI_TENSOR_OBJ_DECLARE(conv2d_20_scratch0,
                      AI_STATIC,
                      45,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 88, 88),
                      1,
                      &conv2d_20_scratch0_array,
                      NULL)

/* Tensor #46 */
AI_TENSOR_OBJ_DECLARE(conv2d_20_weights,
                      AI_STATIC,
                      46,
                      0x0,
                      AI_SHAPE_INIT(4, 22, 1, 1, 132),
                      AI_STRIDE_INIT(4, 4, 88, 11616, 11616),
                      1,
                      &conv2d_20_weights_array,
                      NULL)

/* Tensor #47 */
AI_TENSOR_OBJ_DECLARE(conv2d_21_bias,
                      AI_STATIC,
                      47,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 132, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 528, 528),
                      1,
                      &conv2d_21_bias_array,
                      NULL)

/* Tensor #48 */
AI_TENSOR_OBJ_DECLARE(conv2d_21_output,
                      AI_STATIC,
                      48,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 132, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 528, 4224),
                      1,
                      &conv2d_21_output_array,
                      NULL)

/* Tensor #49 */
AI_TENSOR_OBJ_DECLARE(conv2d_21_weights,
                      AI_STATIC,
                      49,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 3, 3, 132),
                      AI_STRIDE_INIT(4, 1, 132, 132, 132),
                      1,
                      &conv2d_21_weights_array,
                      NULL)

/* Tensor #50 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_bias,
                      AI_STATIC,
                      50,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 88, 88),
                      1,
                      &conv2d_22_bias_array,
                      NULL)

/* Tensor #51 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_output,
                      AI_STATIC,
                      51,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 88, 704),
                      1,
                      &conv2d_22_output_array,
                      NULL)

/* Tensor #52 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_scratch0,
                      AI_STATIC,
                      52,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 132, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 528, 528),
                      1,
                      &conv2d_22_scratch0_array,
                      NULL)

/* Tensor #53 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_weights,
                      AI_STATIC,
                      53,
                      0x0,
                      AI_SHAPE_INIT(4, 132, 1, 1, 22),
                      AI_STRIDE_INIT(4, 4, 528, 11616, 11616),
                      1,
                      &conv2d_22_weights_array,
                      NULL)

/* Tensor #54 */
AI_TENSOR_OBJ_DECLARE(conv2d_27_bias,
                      AI_STATIC,
                      54,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_27_bias_array,
                      NULL)

/* Tensor #55 */
AI_TENSOR_OBJ_DECLARE(conv2d_27_output,
                      AI_STATIC,
                      55,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 44, 704),
                      1,
                      &conv2d_27_output_array,
                      NULL)

/* Tensor #56 */
AI_TENSOR_OBJ_DECLARE(conv2d_27_scratch0,
                      AI_STATIC,
                      56,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 2, 2),
                      AI_STRIDE_INIT(4, 4, 4, 88, 176),
                      1,
                      &conv2d_27_scratch0_array,
                      NULL)

/* Tensor #57 */
AI_TENSOR_OBJ_DECLARE(conv2d_27_upsample_output,
                      AI_STATIC,
                      57,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 15, 15),
                      AI_STRIDE_INIT(4, 4, 4, 88, 1320),
                      1,
                      &conv2d_27_upsample_output_array,
                      NULL)

/* Tensor #58 */
AI_TENSOR_OBJ_DECLARE(conv2d_27_weights,
                      AI_STATIC,
                      58,
                      0x0,
                      AI_SHAPE_INIT(4, 22, 2, 2, 11),
                      AI_STRIDE_INIT(4, 4, 88, 968, 1936),
                      1,
                      &conv2d_27_weights_array,
                      NULL)

/* Tensor #59 */
AI_TENSOR_OBJ_DECLARE(conv2d_29_bias,
                      AI_STATIC,
                      59,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_29_bias_array,
                      NULL)

/* Tensor #60 */
AI_TENSOR_OBJ_DECLARE(conv2d_29_output,
                      AI_STATIC,
                      60,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 44, 704),
                      1,
                      &conv2d_29_output_array,
                      NULL)

/* Tensor #61 */
AI_TENSOR_OBJ_DECLARE(conv2d_29_scratch0,
                      AI_STATIC,
                      61,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 3, 3),
                      AI_STRIDE_INIT(4, 4, 4, 88, 264),
                      1,
                      &conv2d_29_scratch0_array,
                      NULL)

/* Tensor #62 */
AI_TENSOR_OBJ_DECLARE(conv2d_29_weights,
                      AI_STATIC,
                      62,
                      0x0,
                      AI_SHAPE_INIT(4, 22, 3, 3, 11),
                      AI_STRIDE_INIT(4, 4, 88, 968, 2904),
                      1,
                      &conv2d_29_weights_array,
                      NULL)

/* Tensor #63 */
AI_TENSOR_OBJ_DECLARE(conv2d_2_bias,
                      AI_STATIC,
                      63,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 20, 20),
                      1,
                      &conv2d_2_bias_array,
                      NULL)

/* Tensor #64 */
AI_TENSOR_OBJ_DECLARE(conv2d_2_output,
                      AI_STATIC,
                      64,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 20, 1280),
                      1,
                      &conv2d_2_output_array,
                      NULL)

/* Tensor #65 */
AI_TENSOR_OBJ_DECLARE(conv2d_2_scratch0,
                      AI_STATIC,
                      65,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 44, 44),
                      1,
                      &conv2d_2_scratch0_array,
                      NULL)

/* Tensor #66 */
AI_TENSOR_OBJ_DECLARE(conv2d_2_weights,
                      AI_STATIC,
                      66,
                      0x0,
                      AI_SHAPE_INIT(4, 11, 1, 1, 5),
                      AI_STRIDE_INIT(4, 4, 44, 220, 220),
                      1,
                      &conv2d_2_weights_array,
                      NULL)

/* Tensor #67 */
AI_TENSOR_OBJ_DECLARE(conv2d_33_bias,
                      AI_STATIC,
                      67,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 32, 32),
                      1,
                      &conv2d_33_bias_array,
                      NULL)

/* Tensor #68 */
AI_TENSOR_OBJ_DECLARE(conv2d_33_output,
                      AI_STATIC,
                      68,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 32, 1024),
                      1,
                      &conv2d_33_output_array,
                      NULL)

/* Tensor #69 */
AI_TENSOR_OBJ_DECLARE(conv2d_33_scratch0,
                      AI_STATIC,
                      69,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 2, 2),
                      AI_STRIDE_INIT(4, 4, 4, 44, 88),
                      1,
                      &conv2d_33_scratch0_array,
                      NULL)

/* Tensor #70 */
AI_TENSOR_OBJ_DECLARE(conv2d_33_upsample_output,
                      AI_STATIC,
                      70,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 31, 31),
                      AI_STRIDE_INIT(4, 4, 4, 44, 1364),
                      1,
                      &conv2d_33_upsample_output_array,
                      NULL)

/* Tensor #71 */
AI_TENSOR_OBJ_DECLARE(conv2d_33_weights,
                      AI_STATIC,
                      71,
                      0x0,
                      AI_SHAPE_INIT(4, 11, 2, 2, 8),
                      AI_STRIDE_INIT(4, 4, 44, 352, 704),
                      1,
                      &conv2d_33_weights_array,
                      NULL)

/* Tensor #72 */
AI_TENSOR_OBJ_DECLARE(conv2d_35_bias,
                      AI_STATIC,
                      72,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 32, 32),
                      1,
                      &conv2d_35_bias_array,
                      NULL)

/* Tensor #73 */
AI_TENSOR_OBJ_DECLARE(conv2d_35_output,
                      AI_STATIC,
                      73,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 32, 1024),
                      1,
                      &conv2d_35_output_array,
                      NULL)

/* Tensor #74 */
AI_TENSOR_OBJ_DECLARE(conv2d_35_scratch0,
                      AI_STATIC,
                      74,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 16, 3, 3),
                      AI_STRIDE_INIT(4, 4, 4, 64, 192),
                      1,
                      &conv2d_35_scratch0_array,
                      NULL)

/* Tensor #75 */
AI_TENSOR_OBJ_DECLARE(conv2d_35_weights,
                      AI_STATIC,
                      75,
                      0x0,
                      AI_SHAPE_INIT(4, 16, 3, 3, 8),
                      AI_STRIDE_INIT(4, 4, 64, 512, 1536),
                      1,
                      &conv2d_35_weights_array,
                      NULL)

/* Tensor #76 */
AI_TENSOR_OBJ_DECLARE(conv2d_39_bias,
                      AI_STATIC,
                      76,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 20, 20),
                      1,
                      &conv2d_39_bias_array,
                      NULL)

/* Tensor #77 */
AI_TENSOR_OBJ_DECLARE(conv2d_39_output,
                      AI_STATIC,
                      77,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 20, 1280),
                      1,
                      &conv2d_39_output_array,
                      NULL)

/* Tensor #78 */
AI_TENSOR_OBJ_DECLARE(conv2d_39_scratch0,
                      AI_STATIC,
                      78,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 2, 2),
                      AI_STRIDE_INIT(4, 4, 4, 32, 64),
                      1,
                      &conv2d_39_scratch0_array,
                      NULL)

/* Tensor #79 */
AI_TENSOR_OBJ_DECLARE(conv2d_39_upsample_output,
                      AI_STATIC,
                      79,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 63, 63),
                      AI_STRIDE_INIT(4, 4, 4, 32, 2016),
                      1,
                      &conv2d_39_upsample_output_array,
                      NULL)

/* Tensor #80 */
AI_TENSOR_OBJ_DECLARE(conv2d_39_weights,
                      AI_STATIC,
                      80,
                      0x0,
                      AI_SHAPE_INIT(4, 8, 2, 2, 5),
                      AI_STRIDE_INIT(4, 4, 32, 160, 320),
                      1,
                      &conv2d_39_weights_array,
                      NULL)

/* Tensor #81 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_bias,
                      AI_STATIC,
                      81,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 30, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 120, 120),
                      1,
                      &conv2d_3_bias_array,
                      NULL)

/* Tensor #82 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_output,
                      AI_STATIC,
                      82,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 30, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 120, 7680),
                      1,
                      &conv2d_3_output_array,
                      NULL)

/* Tensor #83 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_scratch0,
                      AI_STATIC,
                      83,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 20, 20),
                      1,
                      &conv2d_3_scratch0_array,
                      NULL)

/* Tensor #84 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_weights,
                      AI_STATIC,
                      84,
                      0x0,
                      AI_SHAPE_INIT(4, 5, 1, 1, 30),
                      AI_STRIDE_INIT(4, 4, 20, 600, 600),
                      1,
                      &conv2d_3_weights_array,
                      NULL)

/* Tensor #85 */
AI_TENSOR_OBJ_DECLARE(conv2d_41_bias,
                      AI_STATIC,
                      85,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 20, 20),
                      1,
                      &conv2d_41_bias_array,
                      NULL)

/* Tensor #86 */
AI_TENSOR_OBJ_DECLARE(conv2d_41_output,
                      AI_STATIC,
                      86,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 20, 1280),
                      1,
                      &conv2d_41_output_array,
                      NULL)

/* Tensor #87 */
AI_TENSOR_OBJ_DECLARE(conv2d_41_scratch0,
                      AI_STATIC,
                      87,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 10, 3, 3),
                      AI_STRIDE_INIT(4, 4, 4, 40, 120),
                      1,
                      &conv2d_41_scratch0_array,
                      NULL)

/* Tensor #88 */
AI_TENSOR_OBJ_DECLARE(conv2d_41_weights,
                      AI_STATIC,
                      88,
                      0x0,
                      AI_SHAPE_INIT(4, 10, 3, 3, 5),
                      AI_STRIDE_INIT(4, 4, 40, 200, 600),
                      1,
                      &conv2d_41_weights_array,
                      NULL)

/* Tensor #89 */
AI_TENSOR_OBJ_DECLARE(conv2d_45_bias,
                      AI_STATIC,
                      89,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 20, 20),
                      1,
                      &conv2d_45_bias_array,
                      NULL)

/* Tensor #90 */
AI_TENSOR_OBJ_DECLARE(conv2d_45_output,
                      AI_STATIC,
                      90,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 128, 128),
                      AI_STRIDE_INIT(4, 4, 4, 20, 2560),
                      1,
                      &conv2d_45_output_array,
                      NULL)

/* Tensor #91 */
AI_TENSOR_OBJ_DECLARE(conv2d_45_scratch0,
                      AI_STATIC,
                      91,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 2, 2),
                      AI_STRIDE_INIT(4, 4, 4, 20, 40),
                      1,
                      &conv2d_45_scratch0_array,
                      NULL)

/* Tensor #92 */
AI_TENSOR_OBJ_DECLARE(conv2d_45_upsample_output,
                      AI_STATIC,
                      92,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 127, 127),
                      AI_STRIDE_INIT(4, 4, 4, 20, 2540),
                      1,
                      &conv2d_45_upsample_output_array,
                      NULL)

/* Tensor #93 */
AI_TENSOR_OBJ_DECLARE(conv2d_45_weights,
                      AI_STATIC,
                      93,
                      0x0,
                      AI_SHAPE_INIT(4, 5, 2, 2, 5),
                      AI_STRIDE_INIT(4, 4, 20, 100, 200),
                      1,
                      &conv2d_45_weights_array,
                      NULL)

/* Tensor #94 */
AI_TENSOR_OBJ_DECLARE(conv2d_46_bias,
                      AI_STATIC,
                      94,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 20, 20),
                      1,
                      &conv2d_46_bias_array,
                      NULL)

/* Tensor #95 */
AI_TENSOR_OBJ_DECLARE(conv2d_46_output,
                      AI_STATIC,
                      95,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 128, 128),
                      AI_STRIDE_INIT(4, 4, 4, 20, 2560),
                      1,
                      &conv2d_46_output_array,
                      NULL)

/* Tensor #96 */
AI_TENSOR_OBJ_DECLARE(conv2d_46_scratch0,
                      AI_STATIC,
                      96,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 3, 3),
                      AI_STRIDE_INIT(4, 4, 4, 20, 60),
                      1,
                      &conv2d_46_scratch0_array,
                      NULL)

/* Tensor #97 */
AI_TENSOR_OBJ_DECLARE(conv2d_46_weights,
                      AI_STATIC,
                      97,
                      0x0,
                      AI_SHAPE_INIT(4, 5, 3, 3, 5),
                      AI_STRIDE_INIT(4, 4, 20, 100, 300),
                      1,
                      &conv2d_46_weights_array,
                      NULL)

/* Tensor #98 */
AI_TENSOR_OBJ_DECLARE(conv2d_47_bias,
                      AI_STATIC,
                      98,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 2, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 8, 8),
                      1,
                      &conv2d_47_bias_array,
                      NULL)

/* Tensor #99 */
AI_TENSOR_OBJ_DECLARE(conv2d_47_output,
                      AI_STATIC,
                      99,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 2, 128, 128),
                      AI_STRIDE_INIT(4, 4, 4, 8, 1024),
                      1,
                      &conv2d_47_output_array,
                      NULL)

/* Tensor #100 */
AI_TENSOR_OBJ_DECLARE(conv2d_47_scratch0,
                      AI_STATIC,
                      100,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 20, 20),
                      1,
                      &conv2d_47_scratch0_array,
                      NULL)

/* Tensor #101 */
AI_TENSOR_OBJ_DECLARE(conv2d_47_weights,
                      AI_STATIC,
                      101,
                      0x0,
                      AI_SHAPE_INIT(4, 5, 1, 1, 2),
                      AI_STRIDE_INIT(4, 4, 20, 40, 40),
                      1,
                      &conv2d_47_weights_array,
                      NULL)

/* Tensor #102 */
AI_TENSOR_OBJ_DECLARE(conv2d_4_bias,
                      AI_STATIC,
                      102,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 30, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 120, 120),
                      1,
                      &conv2d_4_bias_array,
                      NULL)

/* Tensor #103 */
AI_TENSOR_OBJ_DECLARE(conv2d_4_output,
                      AI_STATIC,
                      103,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 30, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 120, 3840),
                      1,
                      &conv2d_4_output_array,
                      NULL)

/* Tensor #104 */
AI_TENSOR_OBJ_DECLARE(conv2d_4_weights,
                      AI_STATIC,
                      104,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 3, 3, 30),
                      AI_STRIDE_INIT(4, 1, 30, 30, 30),
                      1,
                      &conv2d_4_weights_array,
                      NULL)

/* Tensor #105 */
AI_TENSOR_OBJ_DECLARE(conv2d_5_bias,
                      AI_STATIC,
                      105,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 32, 32),
                      1,
                      &conv2d_5_bias_array,
                      NULL)

/* Tensor #106 */
AI_TENSOR_OBJ_DECLARE(conv2d_5_output,
                      AI_STATIC,
                      106,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 32, 1024),
                      1,
                      &conv2d_5_output_array,
                      NULL)

/* Tensor #107 */
AI_TENSOR_OBJ_DECLARE(conv2d_5_scratch0,
                      AI_STATIC,
                      107,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 30, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 120, 120),
                      1,
                      &conv2d_5_scratch0_array,
                      NULL)

/* Tensor #108 */
AI_TENSOR_OBJ_DECLARE(conv2d_5_weights,
                      AI_STATIC,
                      108,
                      0x0,
                      AI_SHAPE_INIT(4, 30, 1, 1, 8),
                      AI_STRIDE_INIT(4, 4, 120, 960, 960),
                      1,
                      &conv2d_5_weights_array,
                      NULL)

/* Tensor #109 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_bias,
                      AI_STATIC,
                      109,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 192, 192),
                      1,
                      &conv2d_6_bias_array,
                      NULL)

/* Tensor #110 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_output,
                      AI_STATIC,
                      110,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 192, 6144),
                      1,
                      &conv2d_6_output_array,
                      NULL)

/* Tensor #111 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_scratch0,
                      AI_STATIC,
                      111,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 32, 32),
                      1,
                      &conv2d_6_scratch0_array,
                      NULL)

/* Tensor #112 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_weights,
                      AI_STATIC,
                      112,
                      0x0,
                      AI_SHAPE_INIT(4, 8, 1, 1, 48),
                      AI_STRIDE_INIT(4, 4, 32, 1536, 1536),
                      1,
                      &conv2d_6_weights_array,
                      NULL)

/* Tensor #113 */
AI_TENSOR_OBJ_DECLARE(conv2d_7_bias,
                      AI_STATIC,
                      113,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 192, 192),
                      1,
                      &conv2d_7_bias_array,
                      NULL)

/* Tensor #114 */
AI_TENSOR_OBJ_DECLARE(conv2d_7_output,
                      AI_STATIC,
                      114,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 192, 6144),
                      1,
                      &conv2d_7_output_array,
                      NULL)

/* Tensor #115 */
AI_TENSOR_OBJ_DECLARE(conv2d_7_weights,
                      AI_STATIC,
                      115,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 3, 3, 48),
                      AI_STRIDE_INIT(4, 1, 48, 48, 48),
                      1,
                      &conv2d_7_weights_array,
                      NULL)

/* Tensor #116 */
AI_TENSOR_OBJ_DECLARE(conv2d_8_bias,
                      AI_STATIC,
                      116,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 32, 32),
                      1,
                      &conv2d_8_bias_array,
                      NULL)

/* Tensor #117 */
AI_TENSOR_OBJ_DECLARE(conv2d_8_output,
                      AI_STATIC,
                      117,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 32, 1024),
                      1,
                      &conv2d_8_output_array,
                      NULL)

/* Tensor #118 */
AI_TENSOR_OBJ_DECLARE(conv2d_8_scratch0,
                      AI_STATIC,
                      118,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 192, 192),
                      1,
                      &conv2d_8_scratch0_array,
                      NULL)

/* Tensor #119 */
AI_TENSOR_OBJ_DECLARE(conv2d_8_weights,
                      AI_STATIC,
                      119,
                      0x0,
                      AI_SHAPE_INIT(4, 48, 1, 1, 8),
                      AI_STRIDE_INIT(4, 4, 192, 1536, 1536),
                      1,
                      &conv2d_8_weights_array,
                      NULL)

/* Tensor #120 */
AI_TENSOR_OBJ_DECLARE(eltwise_16_output,
                      AI_STATIC,
                      120,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 44, 704),
                      1,
                      &eltwise_16_output_array,
                      NULL)

/* Tensor #121 */
AI_TENSOR_OBJ_DECLARE(eltwise_23_output,
                      AI_STATIC,
                      121,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 22, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 88, 704),
                      1,
                      &eltwise_23_output_array,
                      NULL)

/* Tensor #122 */
AI_TENSOR_OBJ_DECLARE(eltwise_9_output,
                      AI_STATIC,
                      122,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 32, 1024),
                      1,
                      &eltwise_9_output_array,
                      NULL)

/* Tensor #123 */
AI_TENSOR_OBJ_DECLARE(nl_0_nl_output,
                      AI_STATIC,
                      123,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 44, 2816),
                      1,
                      &nl_0_nl_output_array,
                      NULL)

/* Tensor #124 */
AI_TENSOR_OBJ_DECLARE(nl_10_nl_output,
                      AI_STATIC,
                      124,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 192, 6144),
                      1,
                      &nl_10_nl_output_array,
                      NULL)

/* Tensor #125 */
AI_TENSOR_OBJ_DECLARE(nl_11_nl_output,
                      AI_STATIC,
                      125,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 192, 3072),
                      1,
                      &nl_11_nl_output_array,
                      NULL)

/* Tensor #126 */
AI_TENSOR_OBJ_DECLARE(nl_13_nl_output,
                      AI_STATIC,
                      126,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 264, 4224),
                      1,
                      &nl_13_nl_output_array,
                      NULL)

/* Tensor #127 */
AI_TENSOR_OBJ_DECLARE(nl_14_nl_output,
                      AI_STATIC,
                      127,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 264, 4224),
                      1,
                      &nl_14_nl_output_array,
                      NULL)

/* Tensor #128 */
AI_TENSOR_OBJ_DECLARE(nl_17_nl_output,
                      AI_STATIC,
                      128,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 264, 4224),
                      1,
                      &nl_17_nl_output_array,
                      NULL)

/* Tensor #129 */
AI_TENSOR_OBJ_DECLARE(nl_18_nl_output,
                      AI_STATIC,
                      129,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 66, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 264, 2112),
                      1,
                      &nl_18_nl_output_array,
                      NULL)

/* Tensor #130 */
AI_TENSOR_OBJ_DECLARE(nl_1_nl_output,
                      AI_STATIC,
                      130,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 44, 2816),
                      1,
                      &nl_1_nl_output_array,
                      NULL)

/* Tensor #131 */
AI_TENSOR_OBJ_DECLARE(nl_20_nl_output,
                      AI_STATIC,
                      131,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 132, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 528, 4224),
                      1,
                      &nl_20_nl_output_array,
                      NULL)

/* Tensor #132 */
AI_TENSOR_OBJ_DECLARE(nl_21_nl_output,
                      AI_STATIC,
                      132,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 132, 8, 8),
                      AI_STRIDE_INIT(4, 4, 4, 528, 4224),
                      1,
                      &nl_21_nl_output_array,
                      NULL)

/* Tensor #133 */
AI_TENSOR_OBJ_DECLARE(nl_29_nl_output,
                      AI_STATIC,
                      133,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 11, 16, 16),
                      AI_STRIDE_INIT(4, 4, 4, 44, 704),
                      1,
                      &nl_29_nl_output_array,
                      NULL)

/* Tensor #134 */
AI_TENSOR_OBJ_DECLARE(nl_35_nl_output,
                      AI_STATIC,
                      134,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 8, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 32, 1024),
                      1,
                      &nl_35_nl_output_array,
                      NULL)

/* Tensor #135 */
AI_TENSOR_OBJ_DECLARE(nl_3_nl_output,
                      AI_STATIC,
                      135,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 30, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 120, 7680),
                      1,
                      &nl_3_nl_output_array,
                      NULL)

/* Tensor #136 */
AI_TENSOR_OBJ_DECLARE(nl_41_nl_output,
                      AI_STATIC,
                      136,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 64, 64),
                      AI_STRIDE_INIT(4, 4, 4, 20, 1280),
                      1,
                      &nl_41_nl_output_array,
                      NULL)

/* Tensor #137 */
AI_TENSOR_OBJ_DECLARE(nl_46_nl_output,
                      AI_STATIC,
                      137,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5, 128, 128),
                      AI_STRIDE_INIT(4, 4, 4, 20, 2560),
                      1,
                      &nl_46_nl_output_array,
                      NULL)

/* Tensor #138 */
AI_TENSOR_OBJ_DECLARE(nl_48_output,
                      AI_STATIC,
                      138,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 2, 128, 128),
                      AI_STRIDE_INIT(4, 4, 4, 8, 1024),
                      1,
                      &nl_48_output_array,
                      NULL)

/* Tensor #139 */
AI_TENSOR_OBJ_DECLARE(nl_4_nl_output,
                      AI_STATIC,
                      139,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 30, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 120, 3840),
                      1,
                      &nl_4_nl_output_array,
                      NULL)

/* Tensor #140 */
AI_TENSOR_OBJ_DECLARE(nl_6_nl_output,
                      AI_STATIC,
                      140,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 192, 6144),
                      1,
                      &nl_6_nl_output_array,
                      NULL)

/* Tensor #141 */
AI_TENSOR_OBJ_DECLARE(nl_7_nl_output,
                      AI_STATIC,
                      141,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 48, 32, 32),
                      AI_STRIDE_INIT(4, 4, 4, 192, 6144),
                      1,
                      &nl_7_nl_output_array,
                      NULL)

/* Tensor #142 */
AI_TENSOR_OBJ_DECLARE(serving_default_input_layer0_output,
                      AI_STATIC,
                      142,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 1, 128, 128),
                      AI_STRIDE_INIT(4, 4, 4, 4, 512),
                      1,
                      &serving_default_input_layer0_output_array,
                      NULL)


/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(nl_48_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_47_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_48_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_48_layer,
                     48,
                     SM_TYPE,
                     0x0,
                     NULL,
                     sm,
                     forward_sm,
                     &nl_48_chain,
                     NULL,
                     &nl_48_layer,
                     AI_STATIC,
                     .nl_params = NULL,
                     .axis = AI_SHAPE_CHANNEL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_47_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_46_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_47_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_47_weights, &conv2d_47_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_47_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_47_layer,
                     47,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_47_chain,
                     NULL,
                     &nl_48_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(nl_46_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_46_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_46_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_46_nl_layer,
                     46,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_relu,
                     &nl_46_nl_chain,
                     NULL,
                     &conv2d_47_layer,
                     AI_STATIC,
                     .nl_params = NULL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_46_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_45_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_46_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_46_weights, &conv2d_46_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_46_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_46_layer,
                     46,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_46_chain,
                     NULL,
                     &nl_46_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_45_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_45_upsample_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_45_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_45_weights, &conv2d_45_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_45_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_45_layer,
                     45,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_45_chain,
                     NULL,
                     &conv2d_46_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float conv2d_45_upsample_scales_data[] = {2, 2, 1.0, 1.0};
AI_ARRAY_OBJ_DECLARE(conv2d_45_upsample_scales,
                     AI_ARRAY_FORMAT_FLOAT,
                     conv2d_45_upsample_scales_data,
                     conv2d_45_upsample_scales_data,
                     4,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_45_upsample_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_41_nl_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_45_upsample_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_45_upsample_layer,
                     45,
                     UPSAMPLE_TYPE,
                     0x0,
                     NULL,
                     upsample,
                     forward_upsample_zeros,
                     &conv2d_45_upsample_chain,
                     NULL,
                     &conv2d_45_layer,
                     AI_STATIC,
                     .scales = &conv2d_45_upsample_scales,
                     .center = false,
                     .mode = AI_UPSAMPLE_ZEROS,
                     .nearest_mode = AI_ROUND_PREFER_CEIL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(nl_41_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_41_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_41_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_41_nl_layer,
                     41,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_relu,
                     &nl_41_nl_chain,
                     NULL,
                     &conv2d_45_upsample_layer,
                     AI_STATIC,
                     .nl_params = NULL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_41_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &concat_40_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_41_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_41_weights, &conv2d_41_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_41_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_41_layer,
                     41,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_41_chain,
                     NULL,
                     &nl_41_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    concat_40_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_39_output, &conv2d_2_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &concat_40_output),
    AI_TENSOR_LIST_OBJ_EMPTY,
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(concat_40_layer,
                     40,
                     CONCAT_TYPE,
                     0x0,
                     NULL,
                     concat,
                     forward_concat,
                     &concat_40_chain,
                     NULL,
                     &conv2d_41_layer,
                     AI_STATIC,
                     .axis = AI_SHAPE_CHANNEL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_39_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_39_upsample_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_39_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_39_weights, &conv2d_39_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_39_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_39_layer,
                     39,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_39_chain,
                     NULL,
                     &concat_40_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float conv2d_39_upsample_scales_data[] = {2, 2, 1.0, 1.0};
AI_ARRAY_OBJ_DECLARE(conv2d_39_upsample_scales,
                     AI_ARRAY_FORMAT_FLOAT,
                     conv2d_39_upsample_scales_data,
                     conv2d_39_upsample_scales_data,
                     4,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_39_upsample_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_35_nl_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_39_upsample_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_39_upsample_layer,
                     39,
                     UPSAMPLE_TYPE,
                     0x0,
                     NULL,
                     upsample,
                     forward_upsample_zeros,
                     &conv2d_39_upsample_chain,
                     NULL,
                     &conv2d_39_layer,
                     AI_STATIC,
                     .scales = &conv2d_39_upsample_scales,
                     .center = false,
                     .mode = AI_UPSAMPLE_ZEROS,
                     .nearest_mode = AI_ROUND_PREFER_CEIL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(nl_35_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_35_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_35_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_35_nl_layer,
                     35,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_relu,
                     &nl_35_nl_chain,
                     NULL,
                     &conv2d_39_upsample_layer,
                     AI_STATIC,
                     .nl_params = NULL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_35_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &concat_34_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_35_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_35_weights, &conv2d_35_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_35_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_35_layer,
                     35,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_35_chain,
                     NULL,
                     &nl_35_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    concat_34_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_33_output, &eltwise_9_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &concat_34_output),
    AI_TENSOR_LIST_OBJ_EMPTY,
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(concat_34_layer,
                     34,
                     CONCAT_TYPE,
                     0x0,
                     NULL,
                     concat,
                     forward_concat,
                     &concat_34_chain,
                     NULL,
                     &conv2d_35_layer,
                     AI_STATIC,
                     .axis = AI_SHAPE_CHANNEL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_33_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_33_upsample_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_33_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_33_weights, &conv2d_33_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_33_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_33_layer,
                     33,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_33_chain,
                     NULL,
                     &concat_34_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float conv2d_33_upsample_scales_data[] = {2, 2, 1.0, 1.0};
AI_ARRAY_OBJ_DECLARE(conv2d_33_upsample_scales,
                     AI_ARRAY_FORMAT_FLOAT,
                     conv2d_33_upsample_scales_data,
                     conv2d_33_upsample_scales_data,
                     4,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_33_upsample_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_29_nl_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_33_upsample_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_33_upsample_layer,
                     33,
                     UPSAMPLE_TYPE,
                     0x0,
                     NULL,
                     upsample,
                     forward_upsample_zeros,
                     &conv2d_33_upsample_chain,
                     NULL,
                     &conv2d_33_layer,
                     AI_STATIC,
                     .scales = &conv2d_33_upsample_scales,
                     .center = false,
                     .mode = AI_UPSAMPLE_ZEROS,
                     .nearest_mode = AI_ROUND_PREFER_CEIL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(nl_29_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_29_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_29_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_29_nl_layer,
                     29,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_relu,
                     &nl_29_nl_chain,
                     NULL,
                     &conv2d_33_upsample_layer,
                     AI_STATIC,
                     .nl_params = NULL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_29_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &concat_28_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_29_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_29_weights, &conv2d_29_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_29_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_29_layer,
                     29,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_29_chain,
                     NULL,
                     &nl_29_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    concat_28_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_27_output, &eltwise_16_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &concat_28_output),
    AI_TENSOR_LIST_OBJ_EMPTY,
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(concat_28_layer,
                     28,
                     CONCAT_TYPE,
                     0x0,
                     NULL,
                     concat,
                     forward_concat,
                     &concat_28_chain,
                     NULL,
                     &conv2d_29_layer,
                     AI_STATIC,
                     .axis = AI_SHAPE_CHANNEL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_27_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_27_upsample_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_27_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_27_weights, &conv2d_27_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_27_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_27_layer,
                     27,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_27_chain,
                     NULL,
                     &concat_28_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float conv2d_27_upsample_scales_data[] = {2, 2, 1.0, 1.0};
AI_ARRAY_OBJ_DECLARE(conv2d_27_upsample_scales,
                     AI_ARRAY_FORMAT_FLOAT,
                     conv2d_27_upsample_scales_data,
                     conv2d_27_upsample_scales_data,
                     4,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_27_upsample_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_23_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_27_upsample_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_27_upsample_layer,
                     27,
                     UPSAMPLE_TYPE,
                     0x0,
                     NULL,
                     upsample,
                     forward_upsample_zeros,
                     &conv2d_27_upsample_chain,
                     NULL,
                     &conv2d_27_layer,
                     AI_STATIC,
                     .scales = &conv2d_27_upsample_scales,
                     .center = false,
                     .mode = AI_UPSAMPLE_ZEROS,
                     .nearest_mode = AI_ROUND_PREFER_CEIL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    eltwise_23_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_19_output, &conv2d_22_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_23_output),
    AI_TENSOR_LIST_OBJ_EMPTY,
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(eltwise_23_layer,
                     23,
                     ELTWISE_TYPE,
                     0x0,
                     NULL,
                     eltwise,
                     forward_eltwise,
                     &eltwise_23_chain,
                     NULL,
                     &conv2d_27_upsample_layer,
                     AI_STATIC,
                     .operation = ai_sum_f32,
                     .buffer_operation = ai_sum_buffer_f32, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_22_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_21_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_22_weights, &conv2d_22_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_22_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_22_layer,
                     22,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_22_chain,
                     NULL,
                     &eltwise_23_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_21_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_21_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_21_nl_nl_params_data,
                     nl_21_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_21_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_21_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_21_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_21_nl_layer,
                     21,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_21_nl_chain,
                     NULL,
                     &conv2d_22_layer,
                     AI_STATIC,
                     .nl_params = &nl_21_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_21_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_20_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_21_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_21_weights, &conv2d_21_bias, NULL),
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_21_layer,
                     21,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_dw_if32of32wf32,
                     &conv2d_21_chain,
                     NULL,
                     &nl_21_nl_layer,
                     AI_STATIC,
                     .groups = 132,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_20_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_20_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_20_nl_nl_params_data,
                     nl_20_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_20_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_20_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_20_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_20_nl_layer,
                     20,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_20_nl_chain,
                     NULL,
                     &conv2d_21_layer,
                     AI_STATIC,
                     .nl_params = &nl_20_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_20_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_19_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_20_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_20_weights, &conv2d_20_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_20_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_20_layer,
                     20,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_20_chain,
                     NULL,
                     &nl_20_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_19_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_18_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_19_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_19_weights, &conv2d_19_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_19_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_19_layer,
                     19,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_19_chain,
                     NULL,
                     &conv2d_20_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_18_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_18_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_18_nl_nl_params_data,
                     nl_18_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_18_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_18_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_18_nl_layer,
                     18,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_18_nl_chain,
                     NULL,
                     &conv2d_19_layer,
                     AI_STATIC,
                     .nl_params = &nl_18_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_18_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_17_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_18_weights, &conv2d_18_bias, NULL),
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_18_layer,
                     18,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_dw_if32of32wf32,
                     &conv2d_18_chain,
                     NULL,
                     &nl_18_nl_layer,
                     AI_STATIC,
                     .groups = 66,
                     .filter_stride = AI_SHAPE_2D_INIT(2, 2),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_17_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_17_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_17_nl_nl_params_data,
                     nl_17_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_17_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_17_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_17_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_17_nl_layer,
                     17,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_17_nl_chain,
                     NULL,
                     &conv2d_18_layer,
                     AI_STATIC,
                     .nl_params = &nl_17_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_17_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_16_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_17_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_17_weights, &conv2d_17_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_17_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_17_layer,
                     17,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_17_chain,
                     NULL,
                     &nl_17_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    eltwise_16_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_12_output, &conv2d_15_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_16_output),
    AI_TENSOR_LIST_OBJ_EMPTY,
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(eltwise_16_layer,
                     16,
                     ELTWISE_TYPE,
                     0x0,
                     NULL,
                     eltwise,
                     forward_eltwise,
                     &eltwise_16_chain,
                     NULL,
                     &conv2d_17_layer,
                     AI_STATIC,
                     .operation = ai_sum_f32,
                     .buffer_operation = ai_sum_buffer_f32, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_15_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_14_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_15_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_15_weights, &conv2d_15_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_15_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_15_layer,
                     15,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_15_chain,
                     NULL,
                     &eltwise_16_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_14_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_14_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_14_nl_nl_params_data,
                     nl_14_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_14_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_14_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_14_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_14_nl_layer,
                     14,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_14_nl_chain,
                     NULL,
                     &conv2d_15_layer,
                     AI_STATIC,
                     .nl_params = &nl_14_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_14_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_13_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_14_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_14_weights, &conv2d_14_bias, NULL),
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_14_layer,
                     14,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_dw_if32of32wf32,
                     &conv2d_14_chain,
                     NULL,
                     &nl_14_nl_layer,
                     AI_STATIC,
                     .groups = 66,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_13_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_13_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_13_nl_nl_params_data,
                     nl_13_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_13_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_13_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_13_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_13_nl_layer,
                     13,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_13_nl_chain,
                     NULL,
                     &conv2d_14_layer,
                     AI_STATIC,
                     .nl_params = &nl_13_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_13_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_13_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_13_weights, &conv2d_13_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_13_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_13_layer,
                     13,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_13_chain,
                     NULL,
                     &nl_13_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_12_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_11_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_12_weights, &conv2d_12_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_12_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_12_layer,
                     12,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_12_chain,
                     NULL,
                     &conv2d_13_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_11_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_11_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_11_nl_nl_params_data,
                     nl_11_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_11_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_11_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_11_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_11_nl_layer,
                     11,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_11_nl_chain,
                     NULL,
                     &conv2d_12_layer,
                     AI_STATIC,
                     .nl_params = &nl_11_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_11_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_10_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_11_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_11_weights, &conv2d_11_bias, NULL),
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_11_layer,
                     11,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_dw_if32of32wf32,
                     &conv2d_11_chain,
                     NULL,
                     &nl_11_nl_layer,
                     AI_STATIC,
                     .groups = 48,
                     .filter_stride = AI_SHAPE_2D_INIT(2, 2),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_10_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_10_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_10_nl_nl_params_data,
                     nl_10_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_10_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_10_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_10_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_10_nl_layer,
                     10,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_10_nl_chain,
                     NULL,
                     &conv2d_11_layer,
                     AI_STATIC,
                     .nl_params = &nl_10_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_10_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_9_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_10_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_10_weights, &conv2d_10_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_10_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_10_layer,
                     10,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_10_chain,
                     NULL,
                     &nl_10_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    eltwise_9_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_5_output, &conv2d_8_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_9_output),
    AI_TENSOR_LIST_OBJ_EMPTY,
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(eltwise_9_layer,
                     9,
                     ELTWISE_TYPE,
                     0x0,
                     NULL,
                     eltwise,
                     forward_eltwise,
                     &eltwise_9_chain,
                     NULL,
                     &conv2d_10_layer,
                     AI_STATIC,
                     .operation = ai_sum_f32,
                     .buffer_operation = ai_sum_buffer_f32, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_8_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_7_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_8_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_8_weights, &conv2d_8_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_8_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_8_layer,
                     8,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_8_chain,
                     NULL,
                     &eltwise_9_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_7_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_7_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_7_nl_nl_params_data,
                     nl_7_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_7_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_7_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_7_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_7_nl_layer,
                     7,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_7_nl_chain,
                     NULL,
                     &conv2d_8_layer,
                     AI_STATIC,
                     .nl_params = &nl_7_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_7_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_6_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_7_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_7_weights, &conv2d_7_bias, NULL),
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_7_layer,
                     7,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_dw_if32of32wf32,
                     &conv2d_7_chain,
                     NULL,
                     &nl_7_nl_layer,
                     AI_STATIC,
                     .groups = 48,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_6_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_6_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_6_nl_nl_params_data,
                     nl_6_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_6_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_6_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_6_nl_layer,
                     6,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_6_nl_chain,
                     NULL,
                     &conv2d_7_layer,
                     AI_STATIC,
                     .nl_params = &nl_6_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_6_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_6_weights, &conv2d_6_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_6_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_6_layer,
                     6,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_6_chain,
                     NULL,
                     &nl_6_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_5_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_4_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_5_weights, &conv2d_5_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_5_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_5_layer,
                     5,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_5_chain,
                     NULL,
                     &conv2d_6_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_4_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_4_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_4_nl_nl_params_data,
                     nl_4_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_4_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_4_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_4_nl_layer,
                     4,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_4_nl_chain,
                     NULL,
                     &conv2d_5_layer,
                     AI_STATIC,
                     .nl_params = &nl_4_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_4_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_3_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_4_weights, &conv2d_4_bias, NULL),
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_4_layer,
                     4,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_dw_if32of32wf32,
                     &conv2d_4_chain,
                     NULL,
                     &nl_4_nl_layer,
                     AI_STATIC,
                     .groups = 30,
                     .filter_stride = AI_SHAPE_2D_INIT(2, 2),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_3_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_3_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_3_nl_nl_params_data,
                     nl_3_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_3_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_3_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_3_nl_layer,
                     3,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_3_nl_chain,
                     NULL,
                     &conv2d_4_layer,
                     AI_STATIC,
                     .nl_params = &nl_3_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_3_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_3_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_3_layer,
                     3,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_3_chain,
                     NULL,
                     &nl_3_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_2_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_1_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_2_weights, &conv2d_2_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_2_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_2_layer,
                     2,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_2_chain,
                     NULL,
                     &conv2d_3_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_1_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_1_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_1_nl_nl_params_data,
                     nl_1_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_1_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_1_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_1_nl_layer,
                     1,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_1_nl_chain,
                     NULL,
                     &conv2d_2_layer,
                     AI_STATIC,
                     .nl_params = &nl_1_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_1_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_0_nl_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_1_layer,
                     1,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_dw_if32of32wf32,
                     &conv2d_1_chain,
                     NULL,
                     &nl_1_nl_layer,
                     AI_STATIC,
                     .groups = 11,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_float nl_0_nl_nl_params_data[] = {0.0, 6.0};
AI_ARRAY_OBJ_DECLARE(nl_0_nl_nl_params,
                     AI_ARRAY_FORMAT_FLOAT,
                     nl_0_nl_nl_params_data,
                     nl_0_nl_nl_params_data,
                     2,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_0_nl_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_0_nl_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(nl_0_nl_layer,
                     0,
                     NL_TYPE,
                     0x0,
                     NULL,
                     nl,
                     forward_clip,
                     &nl_0_nl_chain,
                     NULL,
                     &conv2d_1_layer,
                     AI_STATIC,
                     .nl_params = &nl_0_nl_nl_params, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_0_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_input_layer0_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_0_weights, &conv2d_0_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_0_scratch0, NULL))

AI_LAYER_OBJ_DECLARE(conv2d_0_layer,
                     0,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_if32of32wf32,
                     &conv2d_0_chain,
                     NULL,
                     &nl_0_nl_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(2, 2),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(AI_NET_OBJ_INSTANCE,
                       AI_STATIC,
                       AI_BUFFER_INIT(AI_FLAG_NONE,
                                      AI_BUFFER_FORMAT_U8,
                                      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 87260, 1, 1),
                                      87260,
                                      NULL,
                                      NULL),
                       AI_BUFFER_INIT(AI_FLAG_NONE,
                                      AI_BUFFER_FORMAT_U8,
                                      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 577420, 1, 1),
                                      577420,
                                      NULL,
                                      NULL),
                       AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE,
                                                  AI_MOBILENETV2_FP32_IN_NUM,
                                                  &serving_default_input_layer0_output),
                       AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE,
                                                  AI_MOBILENETV2_FP32_OUT_NUM,
                                                  &nl_48_output),
                       &conv2d_0_layer,
                       0x533355a4,
                       NULL)

#else

AI_NETWORK_OBJ_DECLARE(AI_NET_OBJ_INSTANCE,
                       AI_STATIC,
                       AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
                           AI_FLAG_NONE,
                           1,
                           AI_BUFFER_INIT(AI_FLAG_NONE,
                                          AI_BUFFER_FORMAT_U8,
                                          AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 87260, 1, 1),
                                          87260,
                                          NULL,
                                          NULL)),
                       AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
                           AI_FLAG_NONE,
                           1,
                           AI_BUFFER_INIT(AI_FLAG_NONE,
                                          AI_BUFFER_FORMAT_U8,
                                          AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 577420, 1, 1),
                                          577420,
                                          NULL,
                                          NULL)),
                       AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE,
                                                  AI_MOBILENETV2_FP32_IN_NUM,
                                                  &serving_default_input_layer0_output),
                       AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE,
                                                  AI_MOBILENETV2_FP32_OUT_NUM,
                                                  &nl_48_output),
                       &conv2d_0_layer,
                       0x533355a4,
                       NULL)

#endif /*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool mobilenetv2_fp32_configure_activations(ai_network *net_ctx, const ai_network_params *params)
{
    AI_ASSERT(net_ctx)

    if (ai_platform_get_activations_map(g_mobilenetv2_fp32_activations_map, 1, params)) {
        /* Updating activations (byte) offsets */

        serving_default_input_layer0_output_array.data =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 501220);
        serving_default_input_layer0_output_array.data_start =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 501220);
        conv2d_0_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 566756);
        conv2d_0_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 566756);
        conv2d_0_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 320996);
        conv2d_0_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 320996);
        nl_0_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 320996);
        nl_0_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 320996);
        conv2d_1_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 315232);
        conv2d_1_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 315232);
        nl_1_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 315232);
        nl_1_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 315232);
        conv2d_2_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 495456);
        conv2d_2_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 495456);
        conv2d_2_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 495500);
        conv2d_2_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 495500);
        conv2d_3_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 495480);
        conv2d_3_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 495480);
        conv2d_3_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 3960);
        conv2d_3_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 3960);
        nl_3_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 3960);
        nl_3_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 3960);
        conv2d_4_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_4_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        nl_4_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 122880);
        nl_4_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 122880);
        conv2d_5_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_5_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_5_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 120);
        conv2d_5_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 120);
        conv2d_6_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_6_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_6_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 32888);
        conv2d_6_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 32888);
        nl_6_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 229496);
        nl_6_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 229496);
        conv2d_7_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 32888);
        conv2d_7_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 32888);
        nl_7_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 229496);
        nl_7_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 229496);
        conv2d_8_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 32888);
        conv2d_8_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 32888);
        conv2d_8_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 33080);
        conv2d_8_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 33080);
        eltwise_9_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 65848);
        eltwise_9_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 65848);
        conv2d_10_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_10_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_10_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        conv2d_10_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        nl_10_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 295224);
        nl_10_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 295224);
        conv2d_11_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_11_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        nl_11_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        nl_11_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        conv2d_12_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_12_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_12_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 192);
        conv2d_12_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 192);
        conv2d_13_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_13_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_13_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        conv2d_13_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        nl_13_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 166200);
        nl_13_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 166200);
        conv2d_14_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        conv2d_14_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        nl_14_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 166200);
        nl_14_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 166200);
        conv2d_15_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 11456);
        conv2d_15_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 11456);
        conv2d_15_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 11720);
        conv2d_15_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 11720);
        eltwise_16_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 22984);
        eltwise_16_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 22984);
        conv2d_17_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_17_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_17_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        conv2d_17_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        nl_17_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 166200);
        nl_17_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 166200);
        conv2d_18_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_18_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        nl_18_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 34248);
        nl_18_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 34248);
        conv2d_19_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_19_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_19_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 264);
        conv2d_19_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 264);
        conv2d_20_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_20_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_20_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        conv2d_20_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        nl_20_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 132408);
        nl_20_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 132408);
        conv2d_21_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        conv2d_21_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        nl_21_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 132408);
        nl_21_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 132408);
        conv2d_22_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 5896);
        conv2d_22_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 5896);
        conv2d_22_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 6424);
        conv2d_22_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 6424);
        eltwise_23_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 12056);
        eltwise_23_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 12056);
        conv2d_27_upsample_output_array.data =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 34248);
        conv2d_27_upsample_output_array.data_start =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 34248);
        conv2d_27_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_27_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_27_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 352);
        conv2d_27_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 352);
        concat_28_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 34248);
        concat_28_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 34248);
        conv2d_29_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_29_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_29_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 792);
        conv2d_29_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 792);
        nl_29_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 12056);
        nl_29_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 12056);
        conv2d_33_upsample_output_array.data =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 23320);
        conv2d_33_upsample_output_array.data_start =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 23320);
        conv2d_33_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_33_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_33_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        conv2d_33_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 98616);
        concat_34_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        concat_34_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_35_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 65536);
        conv2d_35_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 65536);
        conv2d_35_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 66112);
        conv2d_35_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 66112);
        nl_35_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        nl_35_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_39_upsample_output_array.data =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 32768);
        conv2d_39_upsample_output_array.data_start =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 32768);
        conv2d_39_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_39_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_39_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 159776);
        conv2d_39_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 159776);
        concat_40_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 241696);
        concat_40_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 241696);
        conv2d_41_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_41_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_41_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 360);
        conv2d_41_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 360);
        nl_41_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 82280);
        nl_41_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 82280);
        conv2d_45_upsample_output_array.data =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 164200);
        conv2d_45_upsample_output_array.data_start =
            AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 164200);
        conv2d_45_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_45_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_45_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 153900);
        conv2d_45_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 153900);
        conv2d_46_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_46_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_46_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 148720);
        conv2d_46_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 148720);
        nl_46_nl_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 148720);
        nl_46_nl_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 148720);
        conv2d_47_scratch0_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_47_scratch0_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 0);
        conv2d_47_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 20);
        conv2d_47_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 20);
        nl_48_output_array.data = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 131092);
        nl_48_output_array.data_start = AI_PTR(g_mobilenetv2_fp32_activations_map[0] + 131092);
        return true;
    }
    AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
    return false;
}


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool mobilenetv2_fp32_configure_weights(ai_network *net_ctx, const ai_network_params *params)
{
    AI_ASSERT(net_ctx)

    if (ai_platform_get_weights_map(g_mobilenetv2_fp32_weights_map, 1, params)) {
        /* Updating weights (byte) offsets */

        conv2d_0_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_0_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 0);
        conv2d_0_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 0);
        conv2d_0_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_0_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 396);
        conv2d_0_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 396);
        conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_1_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 440);
        conv2d_1_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 440);
        conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_1_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 836);
        conv2d_1_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 836);
        conv2d_2_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_2_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 880);
        conv2d_2_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 880);
        conv2d_2_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_2_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 1100);
        conv2d_2_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 1100);
        conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_3_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 1120);
        conv2d_3_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 1120);
        conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_3_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 1720);
        conv2d_3_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 1720);
        conv2d_4_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_4_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 1840);
        conv2d_4_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 1840);
        conv2d_4_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_4_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 2920);
        conv2d_4_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 2920);
        conv2d_5_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_5_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 3040);
        conv2d_5_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 3040);
        conv2d_5_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_5_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 4000);
        conv2d_5_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 4000);
        conv2d_6_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_6_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 4032);
        conv2d_6_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 4032);
        conv2d_6_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_6_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 5568);
        conv2d_6_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 5568);
        conv2d_7_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_7_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 5760);
        conv2d_7_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 5760);
        conv2d_7_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_7_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 7488);
        conv2d_7_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 7488);
        conv2d_8_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_8_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 7680);
        conv2d_8_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 7680);
        conv2d_8_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_8_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 9216);
        conv2d_8_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 9216);
        conv2d_10_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_10_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 9248);
        conv2d_10_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 9248);
        conv2d_10_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_10_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 10784);
        conv2d_10_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 10784);
        conv2d_11_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_11_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 10976);
        conv2d_11_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 10976);
        conv2d_11_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_11_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 12704);
        conv2d_11_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 12704);
        conv2d_12_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_12_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 12896);
        conv2d_12_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 12896);
        conv2d_12_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_12_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 15008);
        conv2d_12_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 15008);
        conv2d_13_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_13_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 15052);
        conv2d_13_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 15052);
        conv2d_13_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_13_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 17956);
        conv2d_13_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 17956);
        conv2d_14_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_14_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 18220);
        conv2d_14_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 18220);
        conv2d_14_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_14_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 20596);
        conv2d_14_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 20596);
        conv2d_15_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_15_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 20860);
        conv2d_15_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 20860);
        conv2d_15_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_15_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 23764);
        conv2d_15_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 23764);
        conv2d_17_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_17_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 23808);
        conv2d_17_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 23808);
        conv2d_17_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_17_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 26712);
        conv2d_17_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 26712);
        conv2d_18_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_18_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 26976);
        conv2d_18_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 26976);
        conv2d_18_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_18_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 29352);
        conv2d_18_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 29352);
        conv2d_19_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_19_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 29616);
        conv2d_19_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 29616);
        conv2d_19_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_19_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 35424);
        conv2d_19_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 35424);
        conv2d_20_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_20_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 35512);
        conv2d_20_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 35512);
        conv2d_20_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_20_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 47128);
        conv2d_20_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 47128);
        conv2d_21_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_21_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 47656);
        conv2d_21_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 47656);
        conv2d_21_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_21_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 52408);
        conv2d_21_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 52408);
        conv2d_22_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_22_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 52936);
        conv2d_22_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 52936);
        conv2d_22_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_22_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 64552);
        conv2d_22_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 64552);
        conv2d_27_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_27_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 64640);
        conv2d_27_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 64640);
        conv2d_27_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_27_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 68512);
        conv2d_27_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 68512);
        conv2d_29_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_29_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 68556);
        conv2d_29_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 68556);
        conv2d_29_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_29_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 77268);
        conv2d_29_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 77268);
        conv2d_33_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_33_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 77312);
        conv2d_33_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 77312);
        conv2d_33_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_33_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 78720);
        conv2d_33_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 78720);
        conv2d_35_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_35_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 78752);
        conv2d_35_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 78752);
        conv2d_35_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_35_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 83360);
        conv2d_35_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 83360);
        conv2d_39_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_39_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 83392);
        conv2d_39_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 83392);
        conv2d_39_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_39_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 84032);
        conv2d_39_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 84032);
        conv2d_41_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_41_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 84052);
        conv2d_41_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 84052);
        conv2d_41_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_41_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 85852);
        conv2d_41_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 85852);
        conv2d_45_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_45_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 85872);
        conv2d_45_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 85872);
        conv2d_45_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_45_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 86272);
        conv2d_45_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 86272);
        conv2d_46_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_46_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 86292);
        conv2d_46_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 86292);
        conv2d_46_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_46_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 87192);
        conv2d_46_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 87192);
        conv2d_47_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_47_weights_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 87212);
        conv2d_47_weights_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 87212);
        conv2d_47_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_47_bias_array.data = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 87252);
        conv2d_47_bias_array.data_start = AI_PTR(g_mobilenetv2_fp32_weights_map[0] + 87252);
        return true;
    }
    AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
    return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_mobilenetv2_fp32_get_info(ai_handle network, ai_network_report *report)
{
    ai_network *net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

    if (report && net_ctx) {
        ai_network_report r = {
            .model_name = AI_MOBILENETV2_FP32_MODEL_NAME,
            .model_signature = AI_MOBILENETV2_FP32_MODEL_SIGNATURE,
            .model_datetime = AI_TOOLS_DATE_TIME,

            .compile_datetime = AI_TOOLS_COMPILE_TIME,

            .runtime_revision = ai_platform_runtime_get_revision(),
            .runtime_version = ai_platform_runtime_get_version(),

            .tool_revision = AI_TOOLS_REVISION_ID,
            .tool_version = {AI_TOOLS_VERSION_MAJOR,
                             AI_TOOLS_VERSION_MINOR,
                             AI_TOOLS_VERSION_MICRO,
                             0x0},
            .tool_api_version = AI_STRUCT_INIT,

            .api_version = ai_platform_api_get_version(),
            .interface_api_version = ai_platform_interface_api_get_version(),

            .n_macc = 17230517,
            .n_inputs = 0,
            .inputs = NULL,
            .n_outputs = 0,
            .outputs = NULL,
            .params = AI_STRUCT_INIT,
            .activations = AI_STRUCT_INIT,
            .n_nodes = 0,
            .signature = 0x533355a4,
        };

        if (!ai_platform_api_get_network_report(network, &r))
            return false;

        *report = r;
        return true;
    }
    return false;
}


AI_API_ENTRY
ai_bool ai_mobilenetv2_fp32_get_report(ai_handle network, ai_network_report *report)
{
    ai_network *net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

    if (report && net_ctx) {
        ai_network_report r = {
            .model_name = AI_MOBILENETV2_FP32_MODEL_NAME,
            .model_signature = AI_MOBILENETV2_FP32_MODEL_SIGNATURE,
            .model_datetime = AI_TOOLS_DATE_TIME,

            .compile_datetime = AI_TOOLS_COMPILE_TIME,

            .runtime_revision = ai_platform_runtime_get_revision(),
            .runtime_version = ai_platform_runtime_get_version(),

            .tool_revision = AI_TOOLS_REVISION_ID,
            .tool_version = {AI_TOOLS_VERSION_MAJOR,
                             AI_TOOLS_VERSION_MINOR,
                             AI_TOOLS_VERSION_MICRO,
                             0x0},
            .tool_api_version = AI_STRUCT_INIT,

            .api_version = ai_platform_api_get_version(),
            .interface_api_version = ai_platform_interface_api_get_version(),

            .n_macc = 17230517,
            .n_inputs = 0,
            .inputs = NULL,
            .n_outputs = 0,
            .outputs = NULL,
            .map_signature = AI_MAGIC_SIGNATURE,
            .map_weights = AI_STRUCT_INIT,
            .map_activations = AI_STRUCT_INIT,
            .n_nodes = 0,
            .signature = 0x533355a4,
        };

        if (!ai_platform_api_get_network_report(network, &r))
            return false;

        *report = r;
        return true;
    }
    return false;
}


AI_API_ENTRY
ai_error ai_mobilenetv2_fp32_get_error(ai_handle network)
{
    return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_mobilenetv2_fp32_create(ai_handle *network, const ai_buffer *network_config)
{
    return ai_platform_network_create(network,
                                      network_config,
                                      AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
                                      AI_TOOLS_API_VERSION_MAJOR,
                                      AI_TOOLS_API_VERSION_MINOR,
                                      AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_mobilenetv2_fp32_create_and_init(ai_handle *network,
                                             const ai_handle activations[],
                                             const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_mobilenetv2_fp32_create(network, AI_MOBILENETV2_FP32_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE) {
        return err;
    }

    if (ai_mobilenetv2_fp32_data_params_get(&params) != true) {
        err = ai_mobilenetv2_fp32_get_error(*network);
        return err;
    }
#if defined(AI_MOBILENETV2_FP32_DATA_ACTIVATIONS_COUNT)
    /* set the addresses of the activations buffers */
    for (ai_u16 idx = 0; activations && idx < params.map_activations.size; idx++) {
        AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_MOBILENETV2_FP32_DATA_WEIGHTS_COUNT)
    /* set the addresses of the weight buffers */
    for (ai_u16 idx = 0; weights && idx < params.map_weights.size; idx++) {
        AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_mobilenetv2_fp32_init(*network, &params) != true) {
        err = ai_mobilenetv2_fp32_get_error(*network);
    }
    return err;
}


AI_API_ENTRY
ai_buffer *ai_mobilenetv2_fp32_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
    if (network == AI_HANDLE_NULL) {
        network = (ai_handle)&AI_NET_OBJ_INSTANCE;
        AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
    }
    return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer *ai_mobilenetv2_fp32_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
    if (network == AI_HANDLE_NULL) {
        network = (ai_handle)&AI_NET_OBJ_INSTANCE;
        AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
    }
    return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_mobilenetv2_fp32_destroy(ai_handle network)
{
    return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_mobilenetv2_fp32_init(ai_handle network, const ai_network_params *params)
{
    ai_network *net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
    ai_bool ok = true;

    if (!net_ctx)
        return false;
    ok &= mobilenetv2_fp32_configure_weights(net_ctx, params);
    ok &= mobilenetv2_fp32_configure_activations(net_ctx, params);

    ok &= ai_platform_network_post_init(network);

    return ok;
}


AI_API_ENTRY
ai_i32 ai_mobilenetv2_fp32_run(ai_handle network, const ai_buffer *input, ai_buffer *output)
{
    return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_mobilenetv2_fp32_forward(ai_handle network, const ai_buffer *input)
{
    return ai_platform_network_process(network, input, NULL);
}


#undef AI_MOBILENETV2_FP32_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME
