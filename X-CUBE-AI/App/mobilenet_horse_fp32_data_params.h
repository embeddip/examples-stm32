/**
  ******************************************************************************
  * @file    mobilenet_horse_fp32_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-04-11T13:37:14+0200
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef MOBILENET_HORSE_FP32_DATA_PARAMS_H
#define MOBILENET_HORSE_FP32_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_MOBILENET_HORSE_FP32_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_mobilenet_horse_fp32_data_weights_params[1]))
*/

#define AI_MOBILENET_HORSE_FP32_DATA_CONFIG               (NULL)


#define AI_MOBILENET_HORSE_FP32_DATA_ACTIVATIONS_SIZES \
  { 577420, }
#define AI_MOBILENET_HORSE_FP32_DATA_ACTIVATIONS_SIZE     (577420)
#define AI_MOBILENET_HORSE_FP32_DATA_ACTIVATIONS_COUNT    (1)
#define AI_MOBILENET_HORSE_FP32_DATA_ACTIVATION_1_SIZE    (577420)



#define AI_MOBILENET_HORSE_FP32_DATA_WEIGHTS_SIZES \
  { 87260, }
#define AI_MOBILENET_HORSE_FP32_DATA_WEIGHTS_SIZE         (87260)
#define AI_MOBILENET_HORSE_FP32_DATA_WEIGHTS_COUNT        (1)
#define AI_MOBILENET_HORSE_FP32_DATA_WEIGHT_1_SIZE        (87260)



#define AI_MOBILENET_HORSE_FP32_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_mobilenet_horse_fp32_activations_table[1])

extern ai_handle g_mobilenet_horse_fp32_activations_table[1 + 2];



#define AI_MOBILENET_HORSE_FP32_DATA_WEIGHTS_TABLE_GET() \
  (&g_mobilenet_horse_fp32_weights_table[1])

extern ai_handle g_mobilenet_horse_fp32_weights_table[1 + 2];


#endif    /* MOBILENET_HORSE_FP32_DATA_PARAMS_H */
