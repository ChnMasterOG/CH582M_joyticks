/********************************** (C) COPYRIGHT *******************************
 * File Name          : CORE.c
 * Author             : ChnMasterOG
 * Version            : V1.1
 * Date               : 2022/12/24
 * Description        : 上下电、MCU Sleep相关控制
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"

/*******************************************************************************
 * Function Name  : APPJumpBoot
 * Description    : 跳转到bootloader
 * Input          : 无
 * Return         : 无
 *******************************************************************************/
__HIGH_CODE
void APPJumpBoot(void)   //此段代码必须运行在RAM中
{
  PFIC_DisableIRQ(USB_IRQn);
  PFIC_DisableIRQ(GPIO_A_IRQn);
  PFIC_DisableIRQ(GPIO_B_IRQn);
  PFIC_DisableIRQ(TMR0_IRQn);
  PFIC_DisableIRQ(RTC_IRQn);
  WWDG_ResetCfg(DISABLE);
  while(FLASH_ROM_ERASE(0, EEPROM_BLOCK_SIZE))
  {
    ;//ROM 擦4K1个单位，擦0地址起始
  }
  FLASH_ROM_SW_RESET();
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;  //安全访问模式
  SAFEOPERATE;
  R16_INT32K_TUNE = 0xFFFF;
  R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
  R8_SAFE_ACCESS_SIG = 0;//进入后执行复位，复位类型为上电复位
  while(1);//营造空片的现象，启动时就会停在BOOT，等烧写，超时时间10s
}

/*******************************************************************************
 * Function Name  : SoftReset
 * Description    : 软件复位
 * Input          : 无
 * Return         : 无
 *******************************************************************************/
__HIGH_CODE
void SoftReset(void)   //软件复位
{
  PFIC_DisableIRQ(USB_IRQn);
  PFIC_DisableIRQ(GPIO_A_IRQn);
  PFIC_DisableIRQ(GPIO_B_IRQn);
  PFIC_DisableIRQ(TMR0_IRQn);
  PFIC_DisableIRQ(RTC_IRQn);
  WWDG_ResetCfg(DISABLE);
  FLASH_ROM_SW_RESET();
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;  //安全访问模式
  SAFEOPERATE;
  R16_INT32K_TUNE = 0xFFFF;
  R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
  R8_SAFE_ACCESS_SIG = 0;
  while(1);
}
