/********************************** (C) COPYRIGHT *******************************
 * File Name          : SWITCH.h
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/11/15
 * Description        : Ò¡¸ËADCÇý¶¯
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#ifndef __SWITCH_H
#define __SWITCH_H

#include "HAL.h"

#define SWITCH_L_PIN_1          GPIO_Pin_3
#define SWITCH_L_PIN_2          GPIO_Pin_2
#define SWITCH_R_PIN_1          GPIO_Pin_0
#define SWITCH_R_PIN_2          GPIO_Pin_1

#define SWITCH_L_Y_IDX          0
#define SWITCH_L_X_IDX          1
#define SWITCH_R_Y_IDX          2
#define SWITCH_R_X_IDX          3

#define SWITCH_DEFAULT_MAX      3100
#define SWITCH_DEFAULT_MIN      1600
#define SWITCH_DEFAULT_THR_L    (SWITCH_DEFAULT_MIN + (SWITCH_DEFAULT_MAX - SWITCH_DEFAULT_MIN) / 4)
#define SWITCH_DEFAULT_THR_H    (SWITCH_DEFAULT_MAX - (SWITCH_DEFAULT_MAX - SWITCH_DEFAULT_MIN) / 4)

typedef struct {
    uint16_t adc_data;
    uint16_t adc_thr_l;
    uint16_t adc_thr_h;
}switch_data_t;

extern switch_data_t switch_data[4];

void SWITCH_data_deinit( void );
void SWITCH_Init( void );
void SWITCH_ADC_ENABLE( uint8_t index );

#endif
