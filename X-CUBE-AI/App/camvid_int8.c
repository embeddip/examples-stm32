/**
 ******************************************************************************
 * @file    camvid_int8.c
 * @author  AST Embedded Analytics Research Platform
 * @date    2026-04-11T13:50:16+0200
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


#include "camvid_int8.h"

#include "ai_math_helpers.h"
#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "camvid_int8_data.h"
#include "core_common.h"
#include "core_convert.h"
#include "layers.h"


#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_camvid_int8

#undef AI_CAMVID_INT8_MODEL_SIGNATURE
#define AI_CAMVID_INT8_MODEL_SIGNATURE "0x4375eb8b4d8e863f14386681c3ef14b4"

#ifndef AI_TOOLS_REVISION_ID
    #define AI_TOOLS_REVISION_ID ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME "2026-04-11T13:50:16+0200"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME __DATE__ " " __TIME__

#undef AI_CAMVID_INT8_N_BATCHES
#define AI_CAMVID_INT8_N_BATCHES (1)

static ai_ptr g_camvid_int8_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_camvid_int8_weights_map[1] = AI_C_ARRAY_INIT;


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(serving_default_keras_tensor0_output_array,
                     AI_ARRAY_FORMAT_S8 | AI_FMT_FLAG_IS_IO,
                     NULL,
                     NULL,
                     49153,
                     AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(conv2d_0_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 65536, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(conv2d_1_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     69696,
                     AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(conv2d_1_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 65536, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(pool_2_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 16384, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     18496,
                     AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 32768, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(conv2d_4_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     36992,
                     AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(conv2d_4_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 32768, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(pool_5_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 8192, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     10368,
                     AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 16384, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_upsample_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     61504,
                     AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     69696,
                     AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 32768, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(eltwise_11_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 32768, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     36992,
                     AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 32768, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(conv2d_16_upsample_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     127008,
                     AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(conv2d_16_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     135200,
                     AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(conv2d_16_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 65536, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(eltwise_17_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 65536, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(conv2d_18_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     69696,
                     AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(conv2d_18_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 65536, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_upsample_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     258064,
                     AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_pad_before_output_array,
                     AI_ARRAY_FORMAT_S8,
                     NULL,
                     NULL,
                     266256,
                     AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 262144, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(conv2d_23_output_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 65536, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(nl_24_output_array,
                     AI_ARRAY_FORMAT_S8 | AI_FMT_FLAG_IS_IO,
                     NULL,
                     NULL,
                     65536,
                     AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(conv2d_0_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 432, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(conv2d_0_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 16, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(conv2d_1_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 2304, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(conv2d_1_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 16, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 4608, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 32, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(conv2d_4_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 9216, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(conv2d_4_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 32, AI_STATIC)

/* Array#37 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 18432, AI_STATIC)

/* Array#38 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 64, AI_STATIC)

/* Array#39 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 8192, AI_STATIC)

/* Array#40 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 32, AI_STATIC)

/* Array#41 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 9216, AI_STATIC)

/* Array#42 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 32, AI_STATIC)

/* Array#43 */
AI_ARRAY_OBJ_DECLARE(conv2d_16_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 2048, AI_STATIC)

/* Array#44 */
AI_ARRAY_OBJ_DECLARE(conv2d_16_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 16, AI_STATIC)

/* Array#45 */
AI_ARRAY_OBJ_DECLARE(conv2d_18_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 2304, AI_STATIC)

/* Array#46 */
AI_ARRAY_OBJ_DECLARE(conv2d_18_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 16, AI_STATIC)

/* Array#47 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 1024, AI_STATIC)

/* Array#48 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 16, AI_STATIC)

/* Array#49 */
AI_ARRAY_OBJ_DECLARE(conv2d_23_weights_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 64, AI_STATIC)

/* Array#50 */
AI_ARRAY_OBJ_DECLARE(conv2d_23_bias_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 4, AI_STATIC)

/* Array#51 */
AI_ARRAY_OBJ_DECLARE(conv2d_0_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 1196, AI_STATIC)

/* Array#52 */
AI_ARRAY_OBJ_DECLARE(conv2d_1_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 5408, AI_STATIC)

/* Array#53 */
AI_ARRAY_OBJ_DECLARE(conv2d_3_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 6144, AI_STATIC)

/* Array#54 */
AI_ARRAY_OBJ_DECLARE(conv2d_4_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 6720, AI_STATIC)

/* Array#55 */
AI_ARRAY_OBJ_DECLARE(conv2d_6_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 7168, AI_STATIC)

/* Array#56 */
AI_ARRAY_OBJ_DECLARE(conv2d_10_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 6592, AI_STATIC)

/* Array#57 */
AI_ARRAY_OBJ_DECLARE(conv2d_12_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 6720, AI_STATIC)

/* Array#58 */
AI_ARRAY_OBJ_DECLARE(conv2d_16_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 4832, AI_STATIC)

/* Array#59 */
AI_ARRAY_OBJ_DECLARE(conv2d_18_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 5408, AI_STATIC)

/* Array#60 */
AI_ARRAY_OBJ_DECLARE(conv2d_22_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 2528, AI_STATIC)

/* Array#61 */
AI_ARRAY_OBJ_DECLARE(conv2d_23_scratch0_array, AI_ARRAY_FORMAT_S8, NULL, NULL, 104, AI_STATIC)

/* Array#62 */
AI_ARRAY_OBJ_DECLARE(nl_24_scratch0_array, AI_ARRAY_FORMAT_S32, NULL, NULL, 124, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_0_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.036280326545238495f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(
    conv2d_0_weights_array_intq,
    AI_STATIC_CONST,
    AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
    16,
    AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.005558939650654793f,
                                         0.010115649551153183f,
                                         0.02640589512884617f,
                                         0.010466468520462513f,
                                         0.025120072066783905f,
                                         0.013804455287754536f,
                                         0.0222946684807539f,
                                         0.022646591067314148f,
                                         0.00874160137027502f,
                                         0.021404212340712547f,
                                         0.03064459003508091f,
                                         0.02163059264421463f,
                                         0.025102274492383003f,
                                         0.013432241976261139f,
                                         0.032578982412815094f,
                                         0.012468730099499226f),
                      AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_10_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.03443612530827522f),
                                                AI_PACK_INTQ_ZP(-15)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_10_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.02283763699233532f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_10_upsample_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.02283763699233532f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_10_weights_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              32,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.001785764005035162f,
                                                                   0.001716341357678175f,
                                                                   0.0023362927604466677f,
                                                                   0.002581062028184533f,
                                                                   0.0017877265345305204f,
                                                                   0.0018928177887573838f,
                                                                   0.001879503601230681f,
                                                                   0.0016822462202981114f,
                                                                   0.0025567826814949512f,
                                                                   0.0028372269589453936f,
                                                                   0.0020154661033302546f,
                                                                   0.0020343908108770847f,
                                                                   0.002143061952665448f,
                                                                   0.0023505650460720062f,
                                                                   0.0022027369122952223f,
                                                                   0.0017501345137134194f,
                                                                   0.001701753819361329f,
                                                                   0.0019008931703865528f,
                                                                   0.0019219683017581701f,
                                                                   0.0018678440246731043f,
                                                                   0.0017219692235812545f,
                                                                   0.0018338531954213977f,
                                                                   0.0020654438994824886f,
                                                                   0.0026621026918292046f,
                                                                   0.001814114162698388f,
                                                                   0.002524623880162835f,
                                                                   0.0015864802990108728f,
                                                                   0.0016388626536354423f,
                                                                   0.0017494328785687685f,
                                                                   0.0016892767744138837f,
                                                                   0.0018978589214384556f,
                                                                   0.0016943139489740133f),
                                                AI_PACK_INTQ_ZP(0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_12_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.025397557765245438f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_12_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.04063061252236366f),
                                                AI_PACK_INTQ_ZP(-36)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_12_weights_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              32,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.0010913924779742956f,
                                                                   0.0018508895300328732f,
                                                                   0.0015523146139457822f,
                                                                   0.0014296126319095492f,
                                                                   0.0010120404185727239f,
                                                                   0.0017431086162105203f,
                                                                   0.0012021864531561732f,
                                                                   0.000640696962364018f,
                                                                   0.0018752524629235268f,
                                                                   0.0012632556026801467f,
                                                                   0.000822419417090714f,
                                                                   0.0008585265604779124f,
                                                                   0.0007127488497644663f,
                                                                   0.0010214170906692743f,
                                                                   0.0012505098711699247f,
                                                                   0.0014040411915630102f,
                                                                   0.00126944319345057f,
                                                                   0.0011772337602451444f,
                                                                   0.0010908730328083038f,
                                                                   0.0007264386513270438f,
                                                                   0.0015718629583716393f,
                                                                   0.0007587922154925764f,
                                                                   0.0011070455657318234f,
                                                                   0.0015961964381858706f,
                                                                   0.0012226499384269118f,
                                                                   0.0009403920848853886f,
                                                                   0.0013886532979086041f,
                                                                   0.0010772532550618052f,
                                                                   0.0010597638320177794f,
                                                                   0.0010573359904810786f,
                                                                   0.0013381001772359014f,
                                                                   0.001716713304631412f),
                                                AI_PACK_INTQ_ZP(0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.05343711003661156f),
                                                AI_PACK_INTQ_ZP(6)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.025397557765245438f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_upsample_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.025397557765245438f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(
    conv2d_16_weights_array_intq,
    AI_STATIC_CONST,
    AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
    16,
    AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.0030159265734255314f,
                                         0.0024482831358909607f,
                                         0.002159229014068842f,
                                         0.002520972862839699f,
                                         0.0021804601419717073f,
                                         0.0024578638840466738f,
                                         0.0025401313323527575f,
                                         0.0027478078845888376f,
                                         0.0026568712200969458f,
                                         0.002297703642398119f,
                                         0.0036050055641680956f,
                                         0.0022753519006073475f,
                                         0.0023815096355974674f,
                                         0.0023587362375110388f,
                                         0.0022478869650512934f,
                                         0.0030328198336064816f),
                      AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_18_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.02652130089700222f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_18_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.06340210884809494f),
                                                AI_PACK_INTQ_ZP(-17)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(
    conv2d_18_weights_array_intq,
    AI_STATIC_CONST,
    AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
    16,
    AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.0007480093045160174f,
                                         0.0006644044769927859f,
                                         0.00091381068341434f,
                                         0.000523967610206455f,
                                         0.0009086686768569052f,
                                         0.0013100208016112447f,
                                         0.0014880973612889647f,
                                         0.0005080029368400574f,
                                         0.0007018555188551545f,
                                         0.0008377967751584947f,
                                         0.0006490034284070134f,
                                         0.0012514401460066438f,
                                         0.0010490476852282882f,
                                         0.0007706971373409033f,
                                         0.0011922193225473166f,
                                         0.0005298051401041448f),
                      AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.030355963855981827f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.036280326545238495f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(
    conv2d_1_weights_array_intq,
    AI_STATIC_CONST,
    AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
    16,
    AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.002156284637749195f,
                                         0.0020491343457251787f,
                                         0.0023995123337954283f,
                                         0.0016888788668438792f,
                                         0.002396967960521579f,
                                         0.0023147198371589184f,
                                         0.002206164412200451f,
                                         0.004953513387590647f,
                                         0.002785120392218232f,
                                         0.0025951878633350134f,
                                         0.0030033958610147238f,
                                         0.0032433427404612303f,
                                         0.001561024459078908f,
                                         0.0033396147191524506f,
                                         0.002635434502735734f,
                                         0.001753640128299594f),
                      AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_22_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.04542669281363487f),
                                                AI_PACK_INTQ_ZP(3)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_22_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.02652130089700222f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_22_upsample_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.02652130089700222f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(
    conv2d_22_weights_array_intq,
    AI_STATIC_CONST,
    AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
    16,
    AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.0028246615547686815f,
                                         0.0029241505544632673f,
                                         0.0028657831717282534f,
                                         0.0029778999742120504f,
                                         0.002594070741906762f,
                                         0.0031037244480103254f,
                                         0.0023274447303265333f,
                                         0.0032833851873874664f,
                                         0.0035732181277126074f,
                                         0.002828156342729926f,
                                         0.0029221754521131516f,
                                         0.0028412076644599438f,
                                         0.0048393490724265575f,
                                         0.0031969482079148293f,
                                         0.0031282794661819935f,
                                         0.0028073161374777555f),
                      AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_23_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.14739879965782166f),
                                                AI_PACK_INTQ_ZP(-23)))

/* Int quant #24 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_23_weights_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              4,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.006599232088774443f,
                                                                   0.006161902099847794f,
                                                                   0.0067821708507835865f,
                                                                   0.005704679060727358f),
                                                AI_PACK_INTQ_ZP(0, 0, 0, 0)))

/* Int quant #25 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.033347249031066895f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #26 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.030355963855981827f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #27 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              32,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.0026146122254431248f,
                                                                   0.002903599990531802f,
                                                                   0.002029192866757512f,
                                                                   0.0022371094673871994f,
                                                                   0.0021461243741214275f,
                                                                   0.002050102688372135f,
                                                                   0.0026621499564498663f,
                                                                   0.002630258444696665f,
                                                                   0.002504941774532199f,
                                                                   0.0023944417480379343f,
                                                                   0.003027290804311633f,
                                                                   0.0020440889056771994f,
                                                                   0.002681490033864975f,
                                                                   0.0012422448489814997f,
                                                                   0.002025122754275799f,
                                                                   0.0027833078056573868f,
                                                                   0.002155543537810445f,
                                                                   0.00252232002094388f,
                                                                   0.0023387917317450047f,
                                                                   0.001698940061032772f,
                                                                   0.0021957268472760916f,
                                                                   0.002523961244150996f,
                                                                   0.0024255914613604546f,
                                                                   0.002699502743780613f,
                                                                   0.0020065950229763985f,
                                                                   0.0018547773361206055f,
                                                                   0.0018008742481470108f,
                                                                   0.00345163163729012f,
                                                                   0.0034322072751820087f,
                                                                   0.00185198534745723f,
                                                                   0.0024208424147218466f,
                                                                   0.001811221824027598f),
                                                AI_PACK_INTQ_ZP(0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0)))

/* Int quant #28 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_4_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.023102065548300743f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #29 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_4_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.033347249031066895f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #30 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_4_weights_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              32,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.0019606987480074167f,
                                                                   0.0014742149505764246f,
                                                                   0.0024573607370257378f,
                                                                   0.0018438497791066766f,
                                                                   0.0018344750860705972f,
                                                                   0.0013550291769206524f,
                                                                   0.0013421919429674745f,
                                                                   0.0010954778408631682f,
                                                                   0.0017772662686184049f,
                                                                   0.001983245834708214f,
                                                                   0.0016293006483465433f,
                                                                   0.0011057804804295301f,
                                                                   0.0018137444276362658f,
                                                                   0.0012331659672781825f,
                                                                   0.0015185436932370067f,
                                                                   0.001061302493326366f,
                                                                   0.0015701425727456808f,
                                                                   0.001561029814183712f,
                                                                   0.001927275792695582f,
                                                                   0.0021653533913195133f,
                                                                   0.0011661244789138436f,
                                                                   0.0010846602963283658f,
                                                                   0.0028212901670485735f,
                                                                   0.001951101585291326f,
                                                                   0.0015620077028870583f,
                                                                   0.002095133066177368f,
                                                                   0.0016738164704293013f,
                                                                   0.0012181566562503576f,
                                                                   0.002013567602261901f,
                                                                   0.0013152455212548375f,
                                                                   0.0014048513257876039f,
                                                                   0.0015343395061790943f),
                                                AI_PACK_INTQ_ZP(0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0)))

/* Int quant #31 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_6_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.02283763699233532f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #32 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_6_pad_before_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.023102065548300743f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #33 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_6_weights_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              64,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.001634789165109396f,
                                                                   0.001934074331074953f,
                                                                   0.002018228406086564f,
                                                                   0.0020395454484969378f,
                                                                   0.002337038516998291f,
                                                                   0.0028271342162042856f,
                                                                   0.0011397514026612043f,
                                                                   0.0022995788604021072f,
                                                                   0.002411426045000553f,
                                                                   0.00213824026286602f,
                                                                   0.0015910690417513251f,
                                                                   0.0017825408140197396f,
                                                                   0.00224226713180542f,
                                                                   0.002317334059625864f,
                                                                   0.0018970042001456022f,
                                                                   0.0014445992419496179f,
                                                                   0.001845026039518416f,
                                                                   0.002346477936953306f,
                                                                   0.0022598502691835165f,
                                                                   0.002297626808285713f,
                                                                   0.002256552455946803f,
                                                                   0.002273443853482604f,
                                                                   0.0019585092086344957f,
                                                                   0.0015844464069232345f,
                                                                   0.001876426744274795f,
                                                                   0.0012561313342303038f,
                                                                   0.0020991587080061436f,
                                                                   0.0017032752512022853f,
                                                                   0.0021169560495764017f,
                                                                   0.0017690138192847371f,
                                                                   0.0015449722995981574f,
                                                                   0.0012312316102907062f,
                                                                   0.0016842064214870334f,
                                                                   0.001593253924511373f,
                                                                   0.001336124143563211f,
                                                                   0.0017119499389082193f,
                                                                   0.0014429910806939006f,
                                                                   0.0013993852771818638f,
                                                                   0.0014957274543121457f,
                                                                   0.002131897257640958f,
                                                                   0.002692742506042123f,
                                                                   0.002377432072535157f,
                                                                   0.0013704128796234727f,
                                                                   0.0021858529653400183f,
                                                                   0.003059024689719081f,
                                                                   0.0023878486827015877f,
                                                                   0.001415525795891881f,
                                                                   0.002130580600351095f,
                                                                   0.001485514105297625f,
                                                                   0.0012816815869882703f,
                                                                   0.002413351321592927f,
                                                                   0.0017738071037456393f,
                                                                   0.002068517031148076f,
                                                                   0.0013001058250665665f,
                                                                   0.0016847205115482211f,
                                                                   0.0013760020956397057f,
                                                                   0.0013428585371002555f,
                                                                   0.0023492039181292057f,
                                                                   0.00225761323235929f,
                                                                   0.0016534479800611734f,
                                                                   0.0018420473206788301f,
                                                                   0.001521918224170804f,
                                                                   0.0027116143610328436f,
                                                                   0.0011395519832149148f),
                                                AI_PACK_INTQ_ZP(0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                0)))

/* Int quant #34 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_11_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.04063061252236366f),
                                                AI_PACK_INTQ_ZP(-36)))

/* Int quant #35 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_17_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.06340210884809494f),
                                                AI_PACK_INTQ_ZP(-17)))

/* Int quant #36 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_24_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.00390625f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #37 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_2_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.030355963855981827f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #38 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_5_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.023102065548300743f),
                                                AI_PACK_INTQ_ZP(-128)))

/* Int quant #39 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_keras_tensor0_output_array_intq,
                              AI_STATIC_CONST,
                              AI_BUFFER_META_FLAG_SCALE_FLOAT | AI_BUFFER_META_FLAG_ZEROPOINT_S8,
                              1,
                              AI_PACK_INTQ_INFO(AI_PACK_INTQ_SCALE(0.003921568859368563f),
                                                AI_PACK_INTQ_ZP(-128)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(conv2d_0_bias,
                      AI_STATIC,
                      0,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 16, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 64, 64),
                      1,
                      &conv2d_0_bias_array,
                      NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(conv2d_0_output,
                      AI_STATIC,
                      1,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 64, 64),
                      AI_STRIDE_INIT(4, 1, 1, 16, 1024),
                      1,
                      &conv2d_0_output_array,
                      &conv2d_0_output_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(conv2d_0_scratch0,
                      AI_STATIC,
                      2,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 1196, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 1196, 1196),
                      1,
                      &conv2d_0_scratch0_array,
                      NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(conv2d_0_weights,
                      AI_STATIC,
                      3,
                      0x1,
                      AI_SHAPE_INIT(4, 3, 3, 3, 16),
                      AI_STRIDE_INIT(4, 1, 3, 48, 144),
                      1,
                      &conv2d_0_weights_array,
                      &conv2d_0_weights_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_bias,
                      AI_STATIC,
                      4,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 32, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 128, 128),
                      1,
                      &conv2d_10_bias_array,
                      NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_output,
                      AI_STATIC,
                      5,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 32, 32),
                      AI_STRIDE_INIT(4, 1, 1, 32, 1024),
                      1,
                      &conv2d_10_output_array,
                      &conv2d_10_output_array_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_pad_before_output,
                      AI_STATIC,
                      6,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 64, 33, 33),
                      AI_STRIDE_INIT(4, 1, 1, 64, 2112),
                      1,
                      &conv2d_10_pad_before_output_array,
                      &conv2d_10_pad_before_output_array_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_scratch0,
                      AI_STATIC,
                      7,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 6592, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 6592, 6592),
                      1,
                      &conv2d_10_scratch0_array,
                      NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_upsample_output,
                      AI_STATIC,
                      8,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 64, 31, 31),
                      AI_STRIDE_INIT(4, 1, 1, 64, 1984),
                      1,
                      &conv2d_10_upsample_output_array,
                      &conv2d_10_upsample_output_array_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(conv2d_10_weights,
                      AI_STATIC,
                      9,
                      0x1,
                      AI_SHAPE_INIT(4, 64, 2, 2, 32),
                      AI_STRIDE_INIT(4, 1, 64, 2048, 4096),
                      1,
                      &conv2d_10_weights_array,
                      &conv2d_10_weights_array_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_bias,
                      AI_STATIC,
                      10,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 32, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 128, 128),
                      1,
                      &conv2d_12_bias_array,
                      NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_output,
                      AI_STATIC,
                      11,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 32, 32),
                      AI_STRIDE_INIT(4, 1, 1, 32, 1024),
                      1,
                      &conv2d_12_output_array,
                      &conv2d_12_output_array_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_pad_before_output,
                      AI_STATIC,
                      12,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 34, 34),
                      AI_STRIDE_INIT(4, 1, 1, 32, 1088),
                      1,
                      &conv2d_12_pad_before_output_array,
                      &conv2d_12_pad_before_output_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_scratch0,
                      AI_STATIC,
                      13,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 6720, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 6720, 6720),
                      1,
                      &conv2d_12_scratch0_array,
                      NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(conv2d_12_weights,
                      AI_STATIC,
                      14,
                      0x1,
                      AI_SHAPE_INIT(4, 32, 3, 3, 32),
                      AI_STRIDE_INIT(4, 1, 32, 1024, 3072),
                      1,
                      &conv2d_12_weights_array,
                      &conv2d_12_weights_array_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(conv2d_16_bias,
                      AI_STATIC,
                      15,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 16, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 64, 64),
                      1,
                      &conv2d_16_bias_array,
                      NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(conv2d_16_output,
                      AI_STATIC,
                      16,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 64, 64),
                      AI_STRIDE_INIT(4, 1, 1, 16, 1024),
                      1,
                      &conv2d_16_output_array,
                      &conv2d_16_output_array_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(conv2d_16_pad_before_output,
                      AI_STATIC,
                      17,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 65, 65),
                      AI_STRIDE_INIT(4, 1, 1, 32, 2080),
                      1,
                      &conv2d_16_pad_before_output_array,
                      &conv2d_16_pad_before_output_array_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(conv2d_16_scratch0,
                      AI_STATIC,
                      18,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 4832, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 4832, 4832),
                      1,
                      &conv2d_16_scratch0_array,
                      NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(conv2d_16_upsample_output,
                      AI_STATIC,
                      19,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 63, 63),
                      AI_STRIDE_INIT(4, 1, 1, 32, 2016),
                      1,
                      &conv2d_16_upsample_output_array,
                      &conv2d_16_upsample_output_array_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(conv2d_16_weights,
                      AI_STATIC,
                      20,
                      0x1,
                      AI_SHAPE_INIT(4, 32, 2, 2, 16),
                      AI_STRIDE_INIT(4, 1, 32, 512, 1024),
                      1,
                      &conv2d_16_weights_array,
                      &conv2d_16_weights_array_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(conv2d_18_bias,
                      AI_STATIC,
                      21,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 16, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 64, 64),
                      1,
                      &conv2d_18_bias_array,
                      NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(conv2d_18_output,
                      AI_STATIC,
                      22,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 64, 64),
                      AI_STRIDE_INIT(4, 1, 1, 16, 1024),
                      1,
                      &conv2d_18_output_array,
                      &conv2d_18_output_array_intq)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(conv2d_18_pad_before_output,
                      AI_STATIC,
                      23,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 66, 66),
                      AI_STRIDE_INIT(4, 1, 1, 16, 1056),
                      1,
                      &conv2d_18_pad_before_output_array,
                      &conv2d_18_pad_before_output_array_intq)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(conv2d_18_scratch0,
                      AI_STATIC,
                      24,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5408, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 5408, 5408),
                      1,
                      &conv2d_18_scratch0_array,
                      NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(conv2d_18_weights,
                      AI_STATIC,
                      25,
                      0x1,
                      AI_SHAPE_INIT(4, 16, 3, 3, 16),
                      AI_STRIDE_INIT(4, 1, 16, 256, 768),
                      1,
                      &conv2d_18_weights_array,
                      &conv2d_18_weights_array_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(conv2d_1_bias,
                      AI_STATIC,
                      26,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 16, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 64, 64),
                      1,
                      &conv2d_1_bias_array,
                      NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(conv2d_1_output,
                      AI_STATIC,
                      27,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 64, 64),
                      AI_STRIDE_INIT(4, 1, 1, 16, 1024),
                      1,
                      &conv2d_1_output_array,
                      &conv2d_1_output_array_intq)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(conv2d_1_pad_before_output,
                      AI_STATIC,
                      28,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 66, 66),
                      AI_STRIDE_INIT(4, 1, 1, 16, 1056),
                      1,
                      &conv2d_1_pad_before_output_array,
                      &conv2d_1_pad_before_output_array_intq)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(conv2d_1_scratch0,
                      AI_STATIC,
                      29,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 5408, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 5408, 5408),
                      1,
                      &conv2d_1_scratch0_array,
                      NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(conv2d_1_weights,
                      AI_STATIC,
                      30,
                      0x1,
                      AI_SHAPE_INIT(4, 16, 3, 3, 16),
                      AI_STRIDE_INIT(4, 1, 16, 256, 768),
                      1,
                      &conv2d_1_weights_array,
                      &conv2d_1_weights_array_intq)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_bias,
                      AI_STATIC,
                      31,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 16, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 64, 64),
                      1,
                      &conv2d_22_bias_array,
                      NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_output,
                      AI_STATIC,
                      32,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 128, 128),
                      AI_STRIDE_INIT(4, 1, 1, 16, 2048),
                      1,
                      &conv2d_22_output_array,
                      &conv2d_22_output_array_intq)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_pad_before_output,
                      AI_STATIC,
                      33,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 129, 129),
                      AI_STRIDE_INIT(4, 1, 1, 16, 2064),
                      1,
                      &conv2d_22_pad_before_output_array,
                      &conv2d_22_pad_before_output_array_intq)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_scratch0,
                      AI_STATIC,
                      34,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 2528, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 2528, 2528),
                      1,
                      &conv2d_22_scratch0_array,
                      NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_upsample_output,
                      AI_STATIC,
                      35,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 127, 127),
                      AI_STRIDE_INIT(4, 1, 1, 16, 2032),
                      1,
                      &conv2d_22_upsample_output_array,
                      &conv2d_22_upsample_output_array_intq)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(conv2d_22_weights,
                      AI_STATIC,
                      36,
                      0x1,
                      AI_SHAPE_INIT(4, 16, 2, 2, 16),
                      AI_STRIDE_INIT(4, 1, 16, 256, 512),
                      1,
                      &conv2d_22_weights_array,
                      &conv2d_22_weights_array_intq)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(conv2d_23_bias,
                      AI_STATIC,
                      37,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 4, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 16, 16),
                      1,
                      &conv2d_23_bias_array,
                      NULL)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(conv2d_23_output,
                      AI_STATIC,
                      38,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 4, 128, 128),
                      AI_STRIDE_INIT(4, 1, 1, 4, 512),
                      1,
                      &conv2d_23_output_array,
                      &conv2d_23_output_array_intq)

/* Tensor #39 */
AI_TENSOR_OBJ_DECLARE(conv2d_23_scratch0,
                      AI_STATIC,
                      39,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 104, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 104, 104),
                      1,
                      &conv2d_23_scratch0_array,
                      NULL)

/* Tensor #40 */
AI_TENSOR_OBJ_DECLARE(conv2d_23_weights,
                      AI_STATIC,
                      40,
                      0x1,
                      AI_SHAPE_INIT(4, 16, 1, 1, 4),
                      AI_STRIDE_INIT(4, 1, 16, 64, 64),
                      1,
                      &conv2d_23_weights_array,
                      &conv2d_23_weights_array_intq)

/* Tensor #41 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_bias,
                      AI_STATIC,
                      41,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 32, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 128, 128),
                      1,
                      &conv2d_3_bias_array,
                      NULL)

/* Tensor #42 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_output,
                      AI_STATIC,
                      42,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 32, 32),
                      AI_STRIDE_INIT(4, 1, 1, 32, 1024),
                      1,
                      &conv2d_3_output_array,
                      &conv2d_3_output_array_intq)

/* Tensor #43 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_pad_before_output,
                      AI_STATIC,
                      43,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 34, 34),
                      AI_STRIDE_INIT(4, 1, 1, 16, 544),
                      1,
                      &conv2d_3_pad_before_output_array,
                      &conv2d_3_pad_before_output_array_intq)

/* Tensor #44 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_scratch0,
                      AI_STATIC,
                      44,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 6144, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 6144, 6144),
                      1,
                      &conv2d_3_scratch0_array,
                      NULL)

/* Tensor #45 */
AI_TENSOR_OBJ_DECLARE(conv2d_3_weights,
                      AI_STATIC,
                      45,
                      0x1,
                      AI_SHAPE_INIT(4, 16, 3, 3, 32),
                      AI_STRIDE_INIT(4, 1, 16, 512, 1536),
                      1,
                      &conv2d_3_weights_array,
                      &conv2d_3_weights_array_intq)

/* Tensor #46 */
AI_TENSOR_OBJ_DECLARE(conv2d_4_bias,
                      AI_STATIC,
                      46,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 32, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 128, 128),
                      1,
                      &conv2d_4_bias_array,
                      NULL)

/* Tensor #47 */
AI_TENSOR_OBJ_DECLARE(conv2d_4_output,
                      AI_STATIC,
                      47,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 32, 32),
                      AI_STRIDE_INIT(4, 1, 1, 32, 1024),
                      1,
                      &conv2d_4_output_array,
                      &conv2d_4_output_array_intq)

/* Tensor #48 */
AI_TENSOR_OBJ_DECLARE(conv2d_4_pad_before_output,
                      AI_STATIC,
                      48,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 34, 34),
                      AI_STRIDE_INIT(4, 1, 1, 32, 1088),
                      1,
                      &conv2d_4_pad_before_output_array,
                      &conv2d_4_pad_before_output_array_intq)

/* Tensor #49 */
AI_TENSOR_OBJ_DECLARE(conv2d_4_scratch0,
                      AI_STATIC,
                      49,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 6720, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 6720, 6720),
                      1,
                      &conv2d_4_scratch0_array,
                      NULL)

/* Tensor #50 */
AI_TENSOR_OBJ_DECLARE(conv2d_4_weights,
                      AI_STATIC,
                      50,
                      0x1,
                      AI_SHAPE_INIT(4, 32, 3, 3, 32),
                      AI_STRIDE_INIT(4, 1, 32, 1024, 3072),
                      1,
                      &conv2d_4_weights_array,
                      &conv2d_4_weights_array_intq)

/* Tensor #51 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_bias,
                      AI_STATIC,
                      51,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 64, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 256, 256),
                      1,
                      &conv2d_6_bias_array,
                      NULL)

/* Tensor #52 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_output,
                      AI_STATIC,
                      52,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 64, 16, 16),
                      AI_STRIDE_INIT(4, 1, 1, 64, 1024),
                      1,
                      &conv2d_6_output_array,
                      &conv2d_6_output_array_intq)

/* Tensor #53 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_pad_before_output,
                      AI_STATIC,
                      53,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 18, 18),
                      AI_STRIDE_INIT(4, 1, 1, 32, 576),
                      1,
                      &conv2d_6_pad_before_output_array,
                      &conv2d_6_pad_before_output_array_intq)

/* Tensor #54 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_scratch0,
                      AI_STATIC,
                      54,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 7168, 1, 1),
                      AI_STRIDE_INIT(4, 1, 1, 7168, 7168),
                      1,
                      &conv2d_6_scratch0_array,
                      NULL)

/* Tensor #55 */
AI_TENSOR_OBJ_DECLARE(conv2d_6_weights,
                      AI_STATIC,
                      55,
                      0x1,
                      AI_SHAPE_INIT(4, 32, 3, 3, 64),
                      AI_STRIDE_INIT(4, 1, 32, 2048, 6144),
                      1,
                      &conv2d_6_weights_array,
                      &conv2d_6_weights_array_intq)

/* Tensor #56 */
AI_TENSOR_OBJ_DECLARE(eltwise_11_output,
                      AI_STATIC,
                      56,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 32, 32),
                      AI_STRIDE_INIT(4, 1, 1, 32, 1024),
                      1,
                      &eltwise_11_output_array,
                      &eltwise_11_output_array_intq)

/* Tensor #57 */
AI_TENSOR_OBJ_DECLARE(eltwise_17_output,
                      AI_STATIC,
                      57,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 64, 64),
                      AI_STRIDE_INIT(4, 1, 1, 16, 1024),
                      1,
                      &eltwise_17_output_array,
                      &eltwise_17_output_array_intq)

/* Tensor #58 */
AI_TENSOR_OBJ_DECLARE(nl_24_output,
                      AI_STATIC,
                      58,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 4, 128, 128),
                      AI_STRIDE_INIT(4, 1, 1, 4, 512),
                      1,
                      &nl_24_output_array,
                      &nl_24_output_array_intq)

/* Tensor #59 */
AI_TENSOR_OBJ_DECLARE(nl_24_scratch0,
                      AI_STATIC,
                      59,
                      0x0,
                      AI_SHAPE_INIT(4, 1, 124, 1, 1),
                      AI_STRIDE_INIT(4, 4, 4, 496, 496),
                      1,
                      &nl_24_scratch0_array,
                      NULL)

/* Tensor #60 */
AI_TENSOR_OBJ_DECLARE(pool_2_output,
                      AI_STATIC,
                      60,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 16, 32, 32),
                      AI_STRIDE_INIT(4, 1, 1, 16, 512),
                      1,
                      &pool_2_output_array,
                      &pool_2_output_array_intq)

/* Tensor #61 */
AI_TENSOR_OBJ_DECLARE(pool_5_output,
                      AI_STATIC,
                      61,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 32, 16, 16),
                      AI_STRIDE_INIT(4, 1, 1, 32, 512),
                      1,
                      &pool_5_output_array,
                      &pool_5_output_array_intq)

/* Tensor #62 */
AI_TENSOR_OBJ_DECLARE(serving_default_keras_tensor0_output,
                      AI_STATIC,
                      62,
                      0x1,
                      AI_SHAPE_INIT(4, 1, 3, 128, 128),
                      AI_STRIDE_INIT(4, 1, 1, 3, 384),
                      1,
                      &serving_default_keras_tensor0_output_array,
                      &serving_default_keras_tensor0_output_array_intq)


/**  Layer declarations section  **********************************************/


AI_STATIC_CONST ai_i32 nl_24_nl_params_data[] = {1266146048, 24, -124};
AI_ARRAY_OBJ_DECLARE(nl_24_nl_params,
                     AI_ARRAY_FORMAT_S32,
                     nl_24_nl_params_data,
                     nl_24_nl_params_data,
                     3,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(nl_24_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_23_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_24_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_24_scratch0))

AI_LAYER_OBJ_DECLARE(nl_24_layer,
                     24,
                     SM_TYPE,
                     0x0,
                     NULL,
                     sm,
                     forward_sm_integer,
                     &nl_24_chain,
                     NULL,
                     &nl_24_layer,
                     AI_STATIC,
                     .nl_params = &nl_24_nl_params,
                     .axis = AI_SHAPE_CHANNEL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_23_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_23_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_23_weights, &conv2d_23_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_23_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_23_layer,
                     23,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_pw_sssa8_ch,
                     &conv2d_23_chain,
                     NULL,
                     &nl_24_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_22_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_22_weights, &conv2d_22_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_22_layer,
                     22,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_sssa8_ch,
                     &conv2d_22_chain,
                     NULL,
                     &conv2d_23_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_22_pad_before_value_data[] = {-128};
AI_ARRAY_OBJ_DECLARE(conv2d_22_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_22_pad_before_value_data,
                     conv2d_22_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_22_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_upsample_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_22_pad_before_layer,
                     22,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_22_pad_before_chain,
                     NULL,
                     &conv2d_22_layer,
                     AI_STATIC,
                     .value = &conv2d_22_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )


AI_STATIC_CONST ai_float conv2d_22_upsample_scales_data[] = {2, 2, 1.0, 1.0};
AI_ARRAY_OBJ_DECLARE(conv2d_22_upsample_scales,
                     AI_ARRAY_FORMAT_FLOAT,
                     conv2d_22_upsample_scales_data,
                     conv2d_22_upsample_scales_data,
                     4,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_22_upsample_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_upsample_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_22_upsample_layer,
                     22,
                     UPSAMPLE_TYPE,
                     0x0,
                     NULL,
                     upsample,
                     forward_upsample_zeros_is8os8,
                     &conv2d_22_upsample_chain,
                     NULL,
                     &conv2d_22_pad_before_layer,
                     AI_STATIC,
                     .scales = &conv2d_22_upsample_scales,
                     .center = false,
                     .mode = AI_UPSAMPLE_ZEROS,
                     .nearest_mode = AI_ROUND_PREFER_CEIL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_18_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_18_weights, &conv2d_18_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_18_layer,
                     18,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_3x3_sssa8_ch,
                     &conv2d_18_chain,
                     NULL,
                     &conv2d_22_upsample_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_18_pad_before_value_data[] = {-17};
AI_ARRAY_OBJ_DECLARE(conv2d_18_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_18_pad_before_value_data,
                     conv2d_18_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_18_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_17_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_18_pad_before_layer,
                     18,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_18_pad_before_chain,
                     NULL,
                     &conv2d_18_layer,
                     AI_STATIC,
                     .value = &conv2d_18_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    eltwise_17_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_16_output, &conv2d_1_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_17_output),
    AI_TENSOR_LIST_OBJ_EMPTY,
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(eltwise_17_layer,
                     17,
                     ELTWISE_INTEGER_TYPE,
                     0x0,
                     NULL,
                     eltwise_integer,
                     forward_eltwise_integer_INT8,
                     &eltwise_17_chain,
                     NULL,
                     &conv2d_18_pad_before_layer,
                     AI_STATIC,
                     .operation = ai_sum_f32,
                     .buffer_operation = ai_sum_buffer_INT8, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_16_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_16_weights, &conv2d_16_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_16_layer,
                     16,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_sssa8_ch,
                     &conv2d_16_chain,
                     NULL,
                     &eltwise_17_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_16_pad_before_value_data[] = {-128};
AI_ARRAY_OBJ_DECLARE(conv2d_16_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_16_pad_before_value_data,
                     conv2d_16_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_16_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_upsample_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_16_pad_before_layer,
                     16,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_16_pad_before_chain,
                     NULL,
                     &conv2d_16_layer,
                     AI_STATIC,
                     .value = &conv2d_16_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )


AI_STATIC_CONST ai_float conv2d_16_upsample_scales_data[] = {2, 2, 1.0, 1.0};
AI_ARRAY_OBJ_DECLARE(conv2d_16_upsample_scales,
                     AI_ARRAY_FORMAT_FLOAT,
                     conv2d_16_upsample_scales_data,
                     conv2d_16_upsample_scales_data,
                     4,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_16_upsample_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_upsample_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_16_upsample_layer,
                     16,
                     UPSAMPLE_TYPE,
                     0x0,
                     NULL,
                     upsample,
                     forward_upsample_zeros_is8os8,
                     &conv2d_16_upsample_chain,
                     NULL,
                     &conv2d_16_pad_before_layer,
                     AI_STATIC,
                     .scales = &conv2d_16_upsample_scales,
                     .center = false,
                     .mode = AI_UPSAMPLE_ZEROS,
                     .nearest_mode = AI_ROUND_PREFER_CEIL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_12_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_12_weights, &conv2d_12_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_12_layer,
                     12,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_3x3_sssa8_ch,
                     &conv2d_12_chain,
                     NULL,
                     &conv2d_16_upsample_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_12_pad_before_value_data[] = {-36};
AI_ARRAY_OBJ_DECLARE(conv2d_12_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_12_pad_before_value_data,
                     conv2d_12_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_12_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_11_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_12_pad_before_layer,
                     12,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_12_pad_before_chain,
                     NULL,
                     &conv2d_12_layer,
                     AI_STATIC,
                     .value = &conv2d_12_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    eltwise_11_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_10_output, &conv2d_4_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_11_output),
    AI_TENSOR_LIST_OBJ_EMPTY,
    AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(eltwise_11_layer,
                     11,
                     ELTWISE_INTEGER_TYPE,
                     0x0,
                     NULL,
                     eltwise_integer,
                     forward_eltwise_integer_INT8,
                     &eltwise_11_chain,
                     NULL,
                     &conv2d_12_pad_before_layer,
                     AI_STATIC,
                     .operation = ai_sum_f32,
                     .buffer_operation = ai_sum_buffer_INT8, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_10_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_10_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_10_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_10_weights, &conv2d_10_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_10_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_10_layer,
                     10,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_sssa8_ch,
                     &conv2d_10_chain,
                     NULL,
                     &eltwise_11_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_10_pad_before_value_data[] = {-128};
AI_ARRAY_OBJ_DECLARE(conv2d_10_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_10_pad_before_value_data,
                     conv2d_10_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_10_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_10_upsample_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_10_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_10_pad_before_layer,
                     10,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_10_pad_before_chain,
                     NULL,
                     &conv2d_10_layer,
                     AI_STATIC,
                     .value = &conv2d_10_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )


AI_STATIC_CONST ai_float conv2d_10_upsample_scales_data[] = {2, 2, 1.0, 1.0};
AI_ARRAY_OBJ_DECLARE(conv2d_10_upsample_scales,
                     AI_ARRAY_FORMAT_FLOAT,
                     conv2d_10_upsample_scales_data,
                     conv2d_10_upsample_scales_data,
                     4,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_10_upsample_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_10_upsample_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_10_upsample_layer,
                     10,
                     UPSAMPLE_TYPE,
                     0x0,
                     NULL,
                     upsample,
                     forward_upsample_zeros_is8os8,
                     &conv2d_10_upsample_chain,
                     NULL,
                     &conv2d_10_pad_before_layer,
                     AI_STATIC,
                     .scales = &conv2d_10_upsample_scales,
                     .center = false,
                     .mode = AI_UPSAMPLE_ZEROS,
                     .nearest_mode = AI_ROUND_PREFER_CEIL, )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_6_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_6_weights, &conv2d_6_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_6_layer,
                     6,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_3x3_sssa8_ch,
                     &conv2d_6_chain,
                     NULL,
                     &conv2d_10_upsample_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_6_pad_before_value_data[] = {-128};
AI_ARRAY_OBJ_DECLARE(conv2d_6_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_6_pad_before_value_data,
                     conv2d_6_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_6_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_5_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_6_pad_before_layer,
                     6,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_6_pad_before_chain,
                     NULL,
                     &conv2d_6_layer,
                     AI_STATIC,
                     .value = &conv2d_6_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )

AI_TENSOR_CHAIN_OBJ_DECLARE(pool_5_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_5_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(pool_5_layer,
                     5,
                     POOL_TYPE,
                     0x0,
                     NULL,
                     pool,
                     forward_mp_integer_INT8,
                     &pool_5_chain,
                     NULL,
                     &conv2d_6_pad_before_layer,
                     AI_STATIC,
                     .pool_size = AI_SHAPE_2D_INIT(2, 2),
                     .pool_stride = AI_SHAPE_2D_INIT(2, 2),
                     .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_4_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_4_weights, &conv2d_4_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_4_layer,
                     4,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_3x3_sssa8_ch,
                     &conv2d_4_chain,
                     NULL,
                     &pool_5_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_4_pad_before_value_data[] = {-128};
AI_ARRAY_OBJ_DECLARE(conv2d_4_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_4_pad_before_value_data,
                     conv2d_4_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_4_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_4_pad_before_layer,
                     4,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_4_pad_before_chain,
                     NULL,
                     &conv2d_4_layer,
                     AI_STATIC,
                     .value = &conv2d_4_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_3_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_3_layer,
                     3,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_3x3_sssa8_ch,
                     &conv2d_3_chain,
                     NULL,
                     &conv2d_4_pad_before_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_3_pad_before_value_data[] = {-128};
AI_ARRAY_OBJ_DECLARE(conv2d_3_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_3_pad_before_value_data,
                     conv2d_3_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_3_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_2_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_3_pad_before_layer,
                     3,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_3_pad_before_chain,
                     NULL,
                     &conv2d_3_layer,
                     AI_STATIC,
                     .value = &conv2d_3_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )

AI_TENSOR_CHAIN_OBJ_DECLARE(pool_2_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_2_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(pool_2_layer,
                     2,
                     POOL_TYPE,
                     0x0,
                     NULL,
                     pool,
                     forward_mp_integer_INT8,
                     &pool_2_chain,
                     NULL,
                     &conv2d_3_pad_before_layer,
                     AI_STATIC,
                     .pool_size = AI_SHAPE_2D_INIT(2, 2),
                     .pool_stride = AI_SHAPE_2D_INIT(2, 2),
                     .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_1_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_pad_before_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_1_layer,
                     1,
                     CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_deep_3x3_sssa8_ch,
                     &conv2d_1_chain,
                     NULL,
                     &pool_2_layer,
                     AI_STATIC,
                     .groups = 1,
                     .filter_stride = AI_SHAPE_2D_INIT(1, 1),
                     .dilation = AI_SHAPE_2D_INIT(1, 1),
                     .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0),
                     .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID,
                     .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, )


AI_STATIC_CONST ai_i8 conv2d_1_pad_before_value_data[] = {-128};
AI_ARRAY_OBJ_DECLARE(conv2d_1_pad_before_value,
                     AI_ARRAY_FORMAT_S8,
                     conv2d_1_pad_before_value_data,
                     conv2d_1_pad_before_value_data,
                     1,
                     AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(conv2d_1_pad_before_chain,
                            AI_STATIC_CONST,
                            4,
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_output),
                            AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_pad_before_output),
                            AI_TENSOR_LIST_OBJ_EMPTY,
                            AI_TENSOR_LIST_OBJ_EMPTY)

AI_LAYER_OBJ_DECLARE(conv2d_1_pad_before_layer,
                     1,
                     PAD_TYPE,
                     0x0,
                     NULL,
                     pad,
                     forward_pad,
                     &conv2d_1_pad_before_chain,
                     NULL,
                     &conv2d_1_layer,
                     AI_STATIC,
                     .value = &conv2d_1_pad_before_value,
                     .mode = AI_PAD_CONSTANT,
                     .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), )

AI_TENSOR_CHAIN_OBJ_DECLARE(
    conv2d_0_chain,
    AI_STATIC_CONST,
    4,
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor0_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_output),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_0_weights, &conv2d_0_bias, NULL),
    AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_scratch0))

AI_LAYER_OBJ_DECLARE(conv2d_0_layer,
                     0,
                     OPTIMIZED_CONV2D_TYPE,
                     0x0,
                     NULL,
                     conv2d,
                     forward_conv2d_rgb_sssa8_ch,
                     &conv2d_0_chain,
                     NULL,
                     &conv2d_1_pad_before_layer,
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
                                      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 58944, 1, 1),
                                      58944,
                                      NULL,
                                      NULL),
                       AI_BUFFER_INIT(AI_FLAG_NONE,
                                      AI_BUFFER_FORMAT_U8,
                                      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 323600, 1, 1),
                                      323600,
                                      NULL,
                                      NULL),
                       AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE,
                                                  AI_CAMVID_INT8_IN_NUM,
                                                  &serving_default_keras_tensor0_output),
                       AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE,
                                                  AI_CAMVID_INT8_OUT_NUM,
                                                  &nl_24_output),
                       &conv2d_0_layer,
                       0x6d3b25ca,
                       NULL)

#else

AI_NETWORK_OBJ_DECLARE(AI_NET_OBJ_INSTANCE,
                       AI_STATIC,
                       AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
                           AI_FLAG_NONE,
                           1,
                           AI_BUFFER_INIT(AI_FLAG_NONE,
                                          AI_BUFFER_FORMAT_U8,
                                          AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 58944, 1, 1),
                                          58944,
                                          NULL,
                                          NULL)),
                       AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
                           AI_FLAG_NONE,
                           1,
                           AI_BUFFER_INIT(AI_FLAG_NONE,
                                          AI_BUFFER_FORMAT_U8,
                                          AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 323600, 1, 1),
                                          323600,
                                          NULL,
                                          NULL)),
                       AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE,
                                                  AI_CAMVID_INT8_IN_NUM,
                                                  &serving_default_keras_tensor0_output),
                       AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE,
                                                  AI_CAMVID_INT8_OUT_NUM,
                                                  &nl_24_output),
                       &conv2d_0_layer,
                       0x6d3b25ca,
                       NULL)

#endif /*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool camvid_int8_configure_activations(ai_network *net_ctx, const ai_network_params *params)
{
    AI_ASSERT(net_ctx)

    if (ai_platform_get_activations_map(g_camvid_int8_activations_map, 1, params)) {
        /* Updating activations (byte) offsets */

        serving_default_keras_tensor0_output_array.data =
            AI_PTR(g_camvid_int8_activations_map[0] + 166160);
        serving_default_keras_tensor0_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 166160);
        conv2d_0_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 215316);
        conv2d_0_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 215316);
        conv2d_0_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 216512);
        conv2d_0_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 216512);
        conv2d_1_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 212352);
        conv2d_1_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 212352);
        conv2d_1_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 166160);
        conv2d_1_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 166160);
        conv2d_1_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 211328);
        conv2d_1_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 211328);
        pool_2_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 166160);
        pool_2_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 166160);
        conv2d_3_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 192832);
        conv2d_3_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 192832);
        conv2d_3_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_3_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_3_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 160064);
        conv2d_3_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 160064);
        conv2d_4_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 155840);
        conv2d_4_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 155840);
        conv2d_4_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_4_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_4_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 154816);
        conv2d_4_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 154816);
        pool_5_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 203136);
        pool_5_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 203136);
        conv2d_6_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 200960);
        conv2d_6_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 200960);
        conv2d_6_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 187584);
        conv2d_6_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 187584);
        conv2d_6_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_6_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_10_upsample_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 93312);
        conv2d_10_upsample_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 93312);
        conv2d_10_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 85120);
        conv2d_10_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 85120);
        conv2d_10_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 187584);
        conv2d_10_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 187584);
        conv2d_10_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 84096);
        conv2d_10_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 84096);
        eltwise_11_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 154816);
        eltwise_11_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 154816);
        conv2d_12_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 150592);
        conv2d_12_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 150592);
        conv2d_12_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 84096);
        conv2d_12_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 84096);
        conv2d_12_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_12_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_16_upsample_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 84320);
        conv2d_16_upsample_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 84320);
        conv2d_16_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 76128);
        conv2d_16_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 76128);
        conv2d_16_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_16_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 276864);
        conv2d_16_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 75104);
        conv2d_16_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 75104);
        eltwise_17_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 75104);
        eltwise_17_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 75104);
        conv2d_18_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 70944);
        conv2d_18_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 70944);
        conv2d_18_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 65536);
        conv2d_18_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 65536);
        conv2d_18_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 0);
        conv2d_18_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 0);
        conv2d_22_upsample_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 65536);
        conv2d_22_upsample_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 65536);
        conv2d_22_pad_before_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 57344);
        conv2d_22_pad_before_output_array.data_start =
            AI_PTR(g_camvid_int8_activations_map[0] + 57344);
        conv2d_22_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 0);
        conv2d_22_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 0);
        conv2d_22_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 55296);
        conv2d_22_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 55296);
        conv2d_23_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 0);
        conv2d_23_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 0);
        conv2d_23_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 54784);
        conv2d_23_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 54784);
        nl_24_scratch0_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 0);
        nl_24_scratch0_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 0);
        nl_24_output_array.data = AI_PTR(g_camvid_int8_activations_map[0] + 120320);
        nl_24_output_array.data_start = AI_PTR(g_camvid_int8_activations_map[0] + 120320);
        return true;
    }
    AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
    return false;
}


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool camvid_int8_configure_weights(ai_network *net_ctx, const ai_network_params *params)
{
    AI_ASSERT(net_ctx)

    if (ai_platform_get_weights_map(g_camvid_int8_weights_map, 1, params)) {
        /* Updating weights (byte) offsets */

        conv2d_0_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_0_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 0);
        conv2d_0_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 0);
        conv2d_0_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_0_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 432);
        conv2d_0_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 432);
        conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_1_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 496);
        conv2d_1_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 496);
        conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_1_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 2800);
        conv2d_1_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 2800);
        conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_3_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 2864);
        conv2d_3_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 2864);
        conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_3_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 7472);
        conv2d_3_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 7472);
        conv2d_4_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_4_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 7600);
        conv2d_4_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 7600);
        conv2d_4_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_4_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 16816);
        conv2d_4_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 16816);
        conv2d_6_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_6_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 16944);
        conv2d_6_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 16944);
        conv2d_6_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_6_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 35376);
        conv2d_6_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 35376);
        conv2d_10_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_10_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 35632);
        conv2d_10_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 35632);
        conv2d_10_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_10_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 43824);
        conv2d_10_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 43824);
        conv2d_12_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_12_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 43952);
        conv2d_12_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 43952);
        conv2d_12_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_12_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 53168);
        conv2d_12_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 53168);
        conv2d_16_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_16_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 53296);
        conv2d_16_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 53296);
        conv2d_16_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_16_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 55344);
        conv2d_16_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 55344);
        conv2d_18_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_18_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 55408);
        conv2d_18_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 55408);
        conv2d_18_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_18_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 57712);
        conv2d_18_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 57712);
        conv2d_22_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_22_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 57776);
        conv2d_22_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 57776);
        conv2d_22_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_22_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 58800);
        conv2d_22_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 58800);
        conv2d_23_weights_array.format |= AI_FMT_FLAG_CONST;
        conv2d_23_weights_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 58864);
        conv2d_23_weights_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 58864);
        conv2d_23_bias_array.format |= AI_FMT_FLAG_CONST;
        conv2d_23_bias_array.data = AI_PTR(g_camvid_int8_weights_map[0] + 58928);
        conv2d_23_bias_array.data_start = AI_PTR(g_camvid_int8_weights_map[0] + 58928);
        return true;
    }
    AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
    return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_camvid_int8_get_info(ai_handle network, ai_network_report *report)
{
    ai_network *net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

    if (report && net_ctx) {
        ai_network_report r = {
            .model_name = AI_CAMVID_INT8_MODEL_NAME,
            .model_signature = AI_CAMVID_INT8_MODEL_SIGNATURE,
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

            .n_macc = 84738324,
            .n_inputs = 0,
            .inputs = NULL,
            .n_outputs = 0,
            .outputs = NULL,
            .params = AI_STRUCT_INIT,
            .activations = AI_STRUCT_INIT,
            .n_nodes = 0,
            .signature = 0x6d3b25ca,
        };

        if (!ai_platform_api_get_network_report(network, &r))
            return false;

        *report = r;
        return true;
    }
    return false;
}


AI_API_ENTRY
ai_bool ai_camvid_int8_get_report(ai_handle network, ai_network_report *report)
{
    ai_network *net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

    if (report && net_ctx) {
        ai_network_report r = {
            .model_name = AI_CAMVID_INT8_MODEL_NAME,
            .model_signature = AI_CAMVID_INT8_MODEL_SIGNATURE,
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

            .n_macc = 84738324,
            .n_inputs = 0,
            .inputs = NULL,
            .n_outputs = 0,
            .outputs = NULL,
            .map_signature = AI_MAGIC_SIGNATURE,
            .map_weights = AI_STRUCT_INIT,
            .map_activations = AI_STRUCT_INIT,
            .n_nodes = 0,
            .signature = 0x6d3b25ca,
        };

        if (!ai_platform_api_get_network_report(network, &r))
            return false;

        *report = r;
        return true;
    }
    return false;
}


AI_API_ENTRY
ai_error ai_camvid_int8_get_error(ai_handle network)
{
    return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_camvid_int8_create(ai_handle *network, const ai_buffer *network_config)
{
    return ai_platform_network_create(network,
                                      network_config,
                                      AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
                                      AI_TOOLS_API_VERSION_MAJOR,
                                      AI_TOOLS_API_VERSION_MINOR,
                                      AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_camvid_int8_create_and_init(ai_handle *network,
                                        const ai_handle activations[],
                                        const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_camvid_int8_create(network, AI_CAMVID_INT8_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE) {
        return err;
    }

    if (ai_camvid_int8_data_params_get(&params) != true) {
        err = ai_camvid_int8_get_error(*network);
        return err;
    }
#if defined(AI_CAMVID_INT8_DATA_ACTIVATIONS_COUNT)
    /* set the addresses of the activations buffers */
    for (ai_u16 idx = 0; activations && idx < params.map_activations.size; idx++) {
        AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_CAMVID_INT8_DATA_WEIGHTS_COUNT)
    /* set the addresses of the weight buffers */
    for (ai_u16 idx = 0; weights && idx < params.map_weights.size; idx++) {
        AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_camvid_int8_init(*network, &params) != true) {
        err = ai_camvid_int8_get_error(*network);
    }
    return err;
}


AI_API_ENTRY
ai_buffer *ai_camvid_int8_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
    if (network == AI_HANDLE_NULL) {
        network = (ai_handle)&AI_NET_OBJ_INSTANCE;
        AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
    }
    return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer *ai_camvid_int8_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
    if (network == AI_HANDLE_NULL) {
        network = (ai_handle)&AI_NET_OBJ_INSTANCE;
        AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
    }
    return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_camvid_int8_destroy(ai_handle network)
{
    return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_camvid_int8_init(ai_handle network, const ai_network_params *params)
{
    ai_network *net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
    ai_bool ok = true;

    if (!net_ctx)
        return false;
    ok &= camvid_int8_configure_weights(net_ctx, params);
    ok &= camvid_int8_configure_activations(net_ctx, params);

    ok &= ai_platform_network_post_init(network);

    return ok;
}


AI_API_ENTRY
ai_i32 ai_camvid_int8_run(ai_handle network, const ai_buffer *input, ai_buffer *output)
{
    return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_camvid_int8_forward(ai_handle network, const ai_buffer *input)
{
    return ai_platform_network_process(network, input, NULL);
}


#undef AI_CAMVID_INT8_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME
