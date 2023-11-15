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

#define SWITCH_L_PIN_1      GPIO_Pin_3
#define SWITCH_L_PIN_2      GPIO_Pin_2
#define SWITCH_R_PIN_1      GPIO_Pin_0
#define SWITCH_R_PIN_2      GPIO_Pin_1

void SWITCH_Init( void );
void SWITCH_ADC_ENABLE( uint8_t index );

#endif
