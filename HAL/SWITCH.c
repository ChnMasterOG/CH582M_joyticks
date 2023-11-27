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

switch_data_t switch_data[4];

/*******************************************************************************
 * Function Name  : SWITCH_data_deinit
 * Description    : SWITCH摇杆参数默认值
 * Input          : None
 * Return         : None
 *******************************************************************************/
void SWITCH_data_deinit( void )
{
    uint8_t i;

    for (i = 0; i < 4; i++) {
        switch_data[i].adc_thr_h = SWITCH_DEFAULT_THR_H;
        switch_data[i].adc_thr_l = SWITCH_DEFAULT_THR_L;
    }
}

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
    uint16_t adc_data;
    uint8_t chn;
    uint8_t idx_hid = index >= 2 ? index - 2 : index;
    uint8_t region;

    switch (index) {
        case 0:
            chn = 7;
            break;
        case 1:
            chn = 6;
            break;
        case 2:
            chn = 8;
            break;
        case 3:
            chn = 9;
            break;
        default:
            return;
    }
    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_1_4);
    ADC_ChannelCfg( chn );
    adc_data = ADC_ExcutSingleConver();
    if (idx_hid == 0) {
        if (adc_data < SWITCH_DEFAULT_THR_L && switch_data[index].adc_data >= SWITCH_DEFAULT_THR_L)
            joy_hid_buffer[idx_hid] = 1;
        else if (adc_data > SWITCH_DEFAULT_THR_H && switch_data[index].adc_data <= SWITCH_DEFAULT_THR_H)
            joy_hid_buffer[idx_hid] = -1;
        else if (adc_data <= SWITCH_DEFAULT_THR_H && adc_data >= SWITCH_DEFAULT_THR_L &&
                 (switch_data[index].adc_data > SWITCH_DEFAULT_THR_H || switch_data[index].adc_data < SWITCH_DEFAULT_THR_L))
            joy_hid_buffer[idx_hid] = 0;
        else {
            switch_data[index].adc_data = adc_data;
            return;
        }
    } else {
        if (adc_data < SWITCH_DEFAULT_THR_L && switch_data[index].adc_data >= SWITCH_DEFAULT_THR_L)
            joy_hid_buffer[idx_hid] = -1;
        else if (adc_data > SWITCH_DEFAULT_THR_H && switch_data[index].adc_data <= SWITCH_DEFAULT_THR_H)
            joy_hid_buffer[idx_hid] = 1;
        else if (adc_data <= SWITCH_DEFAULT_THR_H && adc_data >= SWITCH_DEFAULT_THR_L &&
                 (switch_data[index].adc_data > SWITCH_DEFAULT_THR_H || switch_data[index].adc_data < SWITCH_DEFAULT_THR_L))
            joy_hid_buffer[idx_hid] = 0;
        else {
            switch_data[index].adc_data = adc_data;
            return;
        }
    }
    switch_data[index].adc_data = adc_data;
    tmos_set_event(usbTaskID, USB_SEND_JOY_REPORT_EVENT);
    tmos_set_event(hidEmuTaskId, BLE_SEND_JOY_REPORT_EVENT);
}
