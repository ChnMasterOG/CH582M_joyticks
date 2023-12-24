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
uint32_t adc_calibration_cnt = 0;
uint32_t adc_calibration_val[4] = { 0 };

static uint8_t switch_hid_buffer[4];

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
        switch_data[i].adc_deadzone_l = (SWITCH_DEFAULT_MIN + SWITCH_DEFAULT_MAX) / 2 - SWITCH_DEFAULT_DEADZONE_VAL / 2;
        switch_data[i].adc_deadzone_h = (SWITCH_DEFAULT_MIN + SWITCH_DEFAULT_MAX) / 2 + SWITCH_DEFAULT_DEADZONE_VAL / 2;
        switch_data[i].adc_max_val = SWITCH_DEFAULT_MAX;
        switch_data[i].adc_min_val = SWITCH_DEFAULT_MIN;
        switch_data[i].adc_data_mid = (SWITCH_DEFAULT_MIN + SWITCH_DEFAULT_MAX) / 2;
    }
}

/*******************************************************************************
 * Function Name  : SWITCH_data_reset
 * Description    : SWITCH摇杆参数复位
 * Input          : None
 * Return         : None
 *******************************************************************************/
void SWITCH_data_reset( void )
{
    uint8_t i;

    for (i = 0; i < 4; i++) {
        switch_data[i].adc_deadzone_l = 0;
        switch_data[i].adc_deadzone_h = 0;
        switch_data[i].adc_max_val = 0;
        switch_data[i].adc_min_val = 0xFFFF;
        switch_data[i].adc_data_mid = 0;
    }
}

/*******************************************************************************
 * Function Name  : SWITCH_data_read_fromVIA
 * Description    : 从via读取SWITCH参数
 * Input          : None
 * Return         : None
 *******************************************************************************/
void SWITCH_data_read_fromVIA( void )
{
    uint8_t i;

    for (i = 0; i < 4; i++) {
        switch_data[i].adc_deadzone_l = via_config.adc_deadzone_l[i];
        switch_data[i].adc_deadzone_h = via_config.adc_deadzone_h[i];
        switch_data[i].adc_max_val = via_config.adc_max_val[i];
        switch_data[i].adc_min_val = via_config.adc_min_val[i];
    }
}

/*******************************************************************************
 * Function Name  : SWITCH_data_sync_toVIA
 * Description    : 同步SWITCH参数给via
 * Input          : None
 * Return         : None
 *******************************************************************************/
void SWITCH_data_sync_toVIA( void )
{
    uint8_t i;

    for (i = 0; i < 4; i++) {
        via_config.adc_deadzone_l[i] = switch_data[i].adc_deadzone_l;
        via_config.adc_deadzone_h[i] = switch_data[i].adc_deadzone_h;
        via_config.adc_max_val[i] = switch_data[i].adc_max_val;
        via_config.adc_min_val[i] = switch_data[i].adc_min_val;
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
    SWITCH_data_read_fromVIA();
    GPIOA_ModeCfg( SWITCH_L_PIN_1 | SWITCH_L_PIN_2 | SWITCH_R_PIN_1 | SWITCH_R_PIN_2, GPIO_ModeIN_Floating );
    tmos_start_task( halTaskID, SWITCH_EVENT, MS1_TO_SYSTEM_TIME(100) );  // 等待稳定：100ms
}

/*******************************************************************************
 * Function Name  : SWITCH_ADC_ENABLE
 * Description    : SWITCH采集ADC参数
 * Input          : index - 0: switch L 1; 1: switch L 2;
 *                          2: switch R 1; 3: switch R 2;
 *                  mode - 0: normal, 1: calibration step1, 2: calibration step2
 * Return         : None
 *******************************************************************************/
void SWITCH_ADC_ENABLE( uint8_t index, uint8_t mode )
{
    uint16_t adc_data;
    uint8_t chn;
    uint8_t i, region;

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
    if (mode == 0) {
        if (adc_data >= switch_data[index].adc_deadzone_l && adc_data <= switch_data[index].adc_deadzone_h) {
            switch_hid_buffer[index] = 0;
        } else {
            if (adc_data > switch_data[index].adc_max_val)
                adc_data = switch_data[index].adc_max_val;
            else if (adc_data < switch_data[index].adc_min_val)
                adc_data = switch_data[index].adc_min_val;
            switch_hid_buffer[index] = (int)POINT_RANGE * (adc_data - switch_data[index].adc_min_val) /
                                    (switch_data[index].adc_max_val - switch_data[index].adc_min_val) + POINT_MIN;
        }
        if (index == 3) {
            if (button_use_layer2) {
                for (i = 0; i < 4; i++) {
                    if (via_config.sw_settings_L2[i].mirror_settings == TRUE)
                        switch_hid_buffer[i] = -switch_hid_buffer[i];
                    if (via_config.sw_settings_L2[i].mapping_settings != MAP_TO_NONE)
                        joy_hid_buffer[via_config.sw_settings_L2[i].mapping_settings - MAP_TO_X_AXIS] = switch_hid_buffer[i];
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (via_config.sw_settings[i].mirror_settings == TRUE)
                        switch_hid_buffer[i] = -switch_hid_buffer[i];
                    if (via_config.sw_settings[i].mapping_settings != MAP_TO_NONE)
                        joy_hid_buffer[via_config.sw_settings[i].mapping_settings - MAP_TO_X_AXIS] = switch_hid_buffer[i];
                }
            }
            if (gyro_enable == FALSE)
                tmos_start_task(halTaskID, SEND_REPORT_EVENT, MS1_TO_SYSTEM_TIME(2));
        }
    } else if (mode == 1) {     // 校准行程模式
        if (switch_data[index].adc_max_val < adc_data)
            switch_data[index].adc_max_val = adc_data;
        if (switch_data[index].adc_min_val > adc_data)
            switch_data[index].adc_min_val = adc_data;
    } else if (mode == 2) {     // 校准中心模式
        adc_calibration_val[index] += adc_data;
    }
}

/*******************************************************************************
 * Function Name  : SWITCH_Calibration
 * Description    : 校准摇杆
 * Input          : mode - 1: 校准行程模式
 *                         2: 校准中心模式
 *                  ctl - 0: 开始
 *                        1: 采集中
 *                        2: 结束采集
 * Return         : None
 *******************************************************************************/
void SWITCH_Calibration( uint8_t mode, uint8_t ctl )
{
    uint16_t h_tmp, l_tmp;
    uint8_t i;

    if ( mode == 1 ) {
        if ( ctl == 0 ) {   // 绿灯提示
            normal_style_color[GREEN_INDEX] = LED_DEFAULT_BRIGHTNESS;
            normal_style_color[RED_INDEX] = 0;
            normal_style_color[BLUE_INDEX] = 0;
            led_style_func = WS2812_Style_Normal;
            WS2812_Send();
        } else if ( ctl == 1 ) {
            for (i = 0; i < 4; i++)
                SWITCH_ADC_ENABLE(i, 1);
        } else {
            normal_style_color[GREEN_INDEX] = LED_DEFAULT_BRIGHTNESS;
            normal_style_color[RED_INDEX] = LED_DEFAULT_BRIGHTNESS;
            normal_style_color[BLUE_INDEX] = LED_DEFAULT_BRIGHTNESS;
            WS2812_status = WS2812_STATUS_CHANGE_STYLE;
            WS2812_Send();
        }
    } else {
        if ( ctl == 0 ) {   // 蓝灯提示
            normal_style_color[GREEN_INDEX] = 0;
            normal_style_color[RED_INDEX] = 0;
            normal_style_color[BLUE_INDEX] = LED_DEFAULT_BRIGHTNESS;
            led_style_func = WS2812_Style_Normal;
            WS2812_Send();
            for (i = 0; i < 4; i++)
                adc_calibration_val[i] = 0;
            adc_calibration_cnt = 0;
        } else if ( ctl == 1 ) {
            for (i = 0; i < 4; i++)
                SWITCH_ADC_ENABLE(i, 2);
            adc_calibration_cnt++;
        } else {
            for (i = 0; i < 4; i++) {
                switch_data[i].adc_data_mid = adc_calibration_val[i] / adc_calibration_cnt;
                /* 计算deadzone */
                h_tmp = switch_data[i].adc_max_val - switch_data[i].adc_data_mid;
                l_tmp = switch_data[i].adc_data_mid - switch_data[i].adc_min_val;
                if (h_tmp > l_tmp) {
                    switch_data[i].adc_deadzone_h = h_tmp - l_tmp + switch_data[i].adc_data_mid + SWITCH_DEADZONE_MIN / 2;
                    switch_data[i].adc_deadzone_l = switch_data[i].adc_data_mid - SWITCH_DEADZONE_MIN / 2;
                } else {
                    switch_data[i].adc_deadzone_h = switch_data[i].adc_data_mid + SWITCH_DEADZONE_MIN / 2;
                    switch_data[i].adc_deadzone_l = switch_data[i].adc_data_mid - (l_tmp - h_tmp) - SWITCH_DEADZONE_MIN / 2;
                }
            }
            normal_style_color[GREEN_INDEX] = LED_DEFAULT_BRIGHTNESS;
            normal_style_color[RED_INDEX] = LED_DEFAULT_BRIGHTNESS;
            normal_style_color[BLUE_INDEX] = LED_DEFAULT_BRIGHTNESS;
            WS2812_Change_Style_to(WS2812_Style_Off);
        }
    }
}
