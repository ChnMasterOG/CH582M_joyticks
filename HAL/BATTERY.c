/********************************** (C) COPYRIGHT *******************************
 * File Name          : BATTERY.c
 * Author             : ChnMasterOG
 * Version            : V1.1
 * Date               : 2022/1/26
 * Description        : 电池ADC采样源文件
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"

__attribute__((aligned(2))) UINT16 BAT_abcBuff[ADC_MAXBUFLEN];
UINT32 BAT_adcVal = 0;
UINT32 BAT_adcHistory = 0;
static signed short RoughCalib_Value = 0;

/*******************************************************************************
 * Function Name  : BATTERY_Init
 * Description    : 电池ADC初始化
 * Input          : None
 * Return         : None
 *******************************************************************************/
void BATTERY_Init( void )
{
  uint8_t i;
//  ADC_InterTSSampInit();
//  RoughCalib_Value = ADC_DataCalib_Rough(); // 用于计算ADC内部偏差，记录到变量 RoughCalib_Value中
  // bat charging io
  GPIOB_ModeCfg( BAT_CHRG_PIN, GPIO_ModeIN_PU );
  // control adc enable or disable
  GPIOB_ModeCfg( BAT_COM_PIN, GPIO_ModeOut_PP_5mA );
  GPIOB_ResetBits( BAT_COM_PIN );
  // adc init
  GPIOA_ModeCfg( BAT_ADC_PIN, GPIO_ModeIN_Floating );
  ADC_ExtSingleChSampInit( SampleFreq_3_2, ADC_PGA_0 );
  ADC_ChannelCfg( 12 );
  ADC_StartUp();
  R8_ADC_AUTO_CYCLE = 0;    // ADC自动转换周期：256*16/60000000s = 68us
  BAT_ADC_ENA();
  BATTERY_DMA_ENABLE( );
  tmos_start_task( halTaskID, BATTERY_EVENT, MS1_TO_SYSTEM_TIME(100) );  // 等待稳定：100ms
}

/*******************************************************************************
 * Function Name  : BATTERY_DMA_ENABLE
 * Description    : 电池ADC DMA使能, 将转换结果通过DMA载入BAT_abcBuff中
 * Input          : None
 * Return         : None
 *******************************************************************************/
void BATTERY_DMA_ENABLE( void )
{
  R16_ADC_DMA_BEG = (UINT16) (UINT32) &BAT_abcBuff[0];
  R16_ADC_DMA_END = (UINT16) (UINT32) &BAT_abcBuff[ADC_MAXBUFLEN];
  R8_ADC_CTRL_DMA = RB_ADC_DMA_ENABLE | RB_ADC_AUTO_EN | RB_ADC_CONT_EN; // 定时间隔自动连续ADC采样; ADC连续转换模式; DMA地址循环功能使能
}

/*******************************************************************************
 * Function Name  : BATTERY_ADC_Convert
 * Description    : 电池ADC连续转换读取电压值
 * Input          : None
 * Return         : None
 *******************************************************************************/
void BATTERY_ADC_Convert( void )
{
  uint8_t i;
  for(i = 0; i < ADC_MAXBUFLEN; i++) {
    BAT_abcBuff[i] = ADC_ExcutSingleConver();      // 连续采样ADC_MAXBUFLEN次
  }
  BATTERY_ADC_Calculation( );
//  OLED_PRINT("ADC: %d", BAT_adcVal);
}

/*******************************************************************************
 * Function Name  : BATTERY_ADC_Calculation
 * Description    : 获取电池ADC等级
 * Input          : ADC值
 * Return         : 电量等级
 *******************************************************************************/
void BATTERY_ADC_Calculation( void )
{
  uint8_t i;
  UINT32 BAT_adcVal_tmp = 0;
  for (i = 0; i < ADC_MAXBUFLEN; i++) {
    BAT_adcVal_tmp += BAT_abcBuff[i] + RoughCalib_Value;
  }
  BAT_adcVal_tmp /= ADC_MAXBUFLEN;
  if ( BAT_adcHistory > 4 * BAT_FLOATING_VAL + BAT_adcVal_tmp ) return;  // 突然掉电
  BAT_adcHistory = BAT_adcVal;
  BAT_adcVal = BAT_adcVal_tmp;
}

/*******************************************************************************
 * Function Name  : BATTERY_ADC_GetLevel
 * Description    : 获取电池ADC等级
 * Input          : ADC值
 * Return         : 电量等级
 *******************************************************************************/
static UINT8 BATTERY_ADC_GetLevel( UINT32 adc_val )
{

}

/*******************************************************************************
 * Function Name  : BATTERY_DrawBMP
 * Description    : 绘制电池图案(仅电量等级改变才绘制)
 * Input          : None
 * Return         : None
 *******************************************************************************/
void BATTERY_DrawBMP( void )
{

}
