/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : ChnMasterOG, WCH
 * Version            : V1.0
 * Date               : 2023/9/2
 * Description        : TP78扩展 Joytick
 * Copyright (c) 2023 ChnMasterOG
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "HAL.h"
#include "CONFIG.h"
#include "CH58x_common.h"
#include "hiddev.h"

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if (defined (BLE_MAC)) && (BLE_MAC == TRUE)
u8C MacAddr[6] = {0x84, 0xC2, 0xE5, 0x78, 0x73, 0x01};
#endif

/*******************************************************************************
* Function Name  : Main_Circulation
* Description    : 主循环
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
__HIGH_CODE
void Main_Circulation()
{
  // 开启TMOS任务调度
  while(1){
    TMOS_SystemProcess( );
  }
}

/*******************************************************************************
* Function Name  : main
* Description    : 主函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main( void )
{
#if (defined (DCDC_ENABLE)) && (DCDC_ENABLE == TRUE)
    PWR_DCDCCfg( ENABLE );
#endif
    SetSysClock( CLK_SOURCE_PLL_60MHz );
#if (defined (HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    GPIOA_ModeCfg( GPIO_Pin_All, GPIO_ModeIN_PU );
    GPIOB_ModeCfg( GPIO_Pin_All, GPIO_ModeIN_PU );
#endif
#ifdef DEBUG
    GPIOA_SetBits(bTXD1);
    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
#endif
    PRINT("%s\n", VER_LIB);
    CH58X_BLEInit();
    HAL_Init();
    GAPRole_PeripheralInit();
    HidDev_Init();
    HidEmu_Init();
    Main_Circulation();
}

/*******************************************************************************
* Function Name  : GPIOA_IRQHandler
* Description    : GPIOA外部中断
* Input          : None
* Return         : None
*******************************************************************************/
__INTERRUPT
__HIGH_CODE
void GPIOA_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : GPIOB_IRQHandler
* Description    : GPIOB外部中断
* Input          : None
* Return         : None
*******************************************************************************/
__INTERRUPT
__HIGH_CODE
void GPIOB_IRQHandler( void )
{

}

/******************************** endfile @ main ******************************/
