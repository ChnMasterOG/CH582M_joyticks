/********************************** (C) COPYRIGHT *******************************
 * File Name          : SWITCH.c
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/11/15
 * Description        : 摇杆ADC驱动
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/
 
#include "HAL.h"

uint16_t switch_data[4] = { 0 };

/*******************************************************************************
 * Function Name  : SWITCH_Init
 * Description    : 初始化SWITCH摇杆
 * Input          : None
 * Return         : None
 *******************************************************************************/
void SWITCH_Init( void )
{
    // adc init
    GPIOA_ModeCfg( SWITCH_L_PIN_1 | SWITCH_L_PIN_2 | SWITCH_R_PIN_1 | SWITCH_R_PIN_2, GPIO_ModeIN_Floating );
    tmos_start_task( halTaskID, SWITCH_EVENT, MS1_TO_SYSTEM_TIME(100) );  // 等待稳定：100ms
}

/*******************************************************************************
 * Function Name  : BATTERY_DMA_ENABLE
 * Description    : 电池ADC DMA使能, 将转换结果通过DMA载入BAT_abcBuff中
 * Input          : index - 0: switch L 1; 1: switch L 2;
 *                          2: switch R 1; 3: switch R 2;
 * Return         : None
 *******************************************************************************/
void SWITCH_ADC_ENABLE( uint8_t index )
{
    uint8_t chn;

    switch (index) {
        case 0:
            chn = 6;
            break;
        case 1:
            chn = 7;
            break;
        case 2:
            chn = 9;
            break;
        case 3:
            chn = 8;
            break;
        default:
            return;
    }
    ADC_ChannelCfg( chn );
    ADC_StartUp();
    while (!(R8_ADC_INT_FLAG & RB_ADC_IF_EOC));
    switch_data[index] = R16_ADC_DATA;
}
