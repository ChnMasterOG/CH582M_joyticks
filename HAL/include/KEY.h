/********************************** (C) COPYRIGHT *******************************
* File Name          : KEY.h
* Author             : ChnMasterOG
* Version            : V1.0
* Date               : 2023/11/14
* Description        : add joytick support
 * Copyright (c) 2023 ChnMasterOG
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: GPL-3.0
*******************************************************************************/



/******************************************************************************/
#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************************************
 *                                              MACROS
 **************************************************************************************************/

#define HAL_KEY_POLLING_VALUE   	   100

/* Switches (keys) */
#define HAL_KEY_SW_1    0x01    // key left 1
#define HAL_KEY_SW_2    0x02    // key left 2
#define HAL_KEY_SW_3    0x04    // key right 1
#define HAL_KEY_SW_4    0x08    // key right 2
#define HAL_KEY_SW_L    0x10    // key L
#define HAL_KEY_SW_R    0x20    // key R
#define HAL_KEY_SW_ZL   0x40    // key ZL
#define HAL_KEY_SW_ZR   0x80    // key ZR
#define HAL_KEY_SW_ML   0x100   // key ML
#define HAL_KEY_SW_MR   0x200   // key MR

/* 按键定义 */

/* 连接一个按键 */
#define KEY1_BV         BV(16)
#define KEY2_BV         BV(17)
#define KEY3_BV         BV(4)
#define KEY4_BV         BV(5)
#define KEY5_BV         BV(5)
#define KEY6_BV         BV(0)
#define KEY7_BV         BV(6)
#define KEY8_BV         BV(20)
#define KEY9_BV         BV(22)
#define KEY10_BV        BV(1)

#define KEY1_PD        	(R32_PB_PD_DRV |= KEY1_BV)  // 上拉R32_PB_PU
#define KEY2_PD        	(R32_PB_PD_DRV |= KEY2_BV)
#define KEY3_PD        	(R32_PB_PD_DRV |= KEY3_BV)
#define KEY4_PD        	(R32_PB_PD_DRV |= KEY4_BV)
#define KEY5_PD         (R32_PA_PD_DRV |= KEY5_BV)
#define KEY6_PD         (R32_PB_PD_DRV |= KEY6_BV)
#define KEY7_PD         (R32_PA_PD_DRV |= KEY7_BV)
#define KEY8_PD         (R32_PB_PD_DRV |= KEY8_BV)
#define KEY9_PD         (R32_PB_PD_DRV |= KEY9_BV)
#define KEY10_PD        (R32_PB_PD_DRV |= KEY10_BV)

#define KEY1_PU         {R32_PB_PD_DRV &= ~KEY1_BV; R32_PB_PU |= KEY1_BV;}
#define KEY2_PU         {R32_PB_PD_DRV &= ~KEY2_BV; R32_PB_PU |= KEY2_BV;}
#define KEY3_PU         {R32_PB_PD_DRV &= ~KEY3_BV; R32_PB_PU |= KEY3_BV;}
#define KEY4_PU         {R32_PB_PD_DRV &= ~KEY4_BV; R32_PB_PU |= KEY4_BV;}
#define KEY5_PU         {R32_PA_PD_DRV &= ~KEY5_BV; R32_PA_PU |= KEY5_BV;}
#define KEY6_PU         {R32_PB_PD_DRV &= ~KEY6_BV; R32_PB_PU |= KEY6_BV;}
#define KEY7_PU         {R32_PA_PD_DRV &= ~KEY7_BV; R32_PA_PU |= KEY7_BV;}
#define KEY8_PU         {R32_PB_PD_DRV &= ~KEY8_BV; R32_PB_PU |= KEY8_BV;}
#define KEY9_PU         {R32_PB_PD_DRV &= ~KEY9_BV; R32_PB_PU |= KEY9_BV;}
#define KEY10_PU        {R32_PB_PD_DRV &= ~KEY10_BV; R32_PB_PU |= KEY10_BV;}

#define KEY1_DIR       	(R32_PB_DIR &= ~KEY1_BV)
#define KEY2_DIR        (R32_PB_DIR &= ~KEY2_BV)
#define KEY3_DIR        (R32_PB_DIR &= ~KEY3_BV)
#define KEY4_DIR        (R32_PB_DIR &= ~KEY4_BV)
#define KEY5_DIR        (R32_PA_DIR &= ~KEY5_BV)
#define KEY6_DIR        (R32_PB_DIR &= ~KEY6_BV)
#define KEY7_DIR        (R32_PA_DIR &= ~KEY7_BV)
#define KEY8_DIR        (R32_PB_DIR &= ~KEY8_BV)
#define KEY9_DIR        (R32_PB_DIR &= ~KEY9_BV)
#define KEY10_DIR       (R32_PB_DIR &= ~KEY10_BV)

#define KEY1_IN        	(ACTIVE_LOW(R32_PB_PIN&KEY1_BV))
#define KEY2_IN        	(ACTIVE_LOW(R32_PB_PIN&KEY2_BV))
#define KEY3_IN        	(ACTIVE_LOW(R32_PB_PIN&KEY3_BV))
#define KEY4_IN        	(ACTIVE_LOW(R32_PB_PIN&KEY4_BV))
#define KEY5_IN         (ACTIVE_LOW(R32_PA_PIN&KEY5_BV))
#define KEY6_IN         (ACTIVE_LOW(R32_PB_PIN&KEY6_BV))
#define KEY7_IN         (ACTIVE_LOW(R32_PA_PIN&KEY7_BV))
#define KEY8_IN         (ACTIVE_LOW(R32_PB_PIN&KEY8_BV))
#define KEY9_IN         (ACTIVE_LOW(R32_PB_PIN&KEY9_BV))
#define KEY10_IN        (ACTIVE_LOW(R32_PB_PIN&KEY10_BV))

#define HAL_PUSH_BUTTON1()          ( KEY1_IN ) //添加自定义按键
#define HAL_PUSH_BUTTON2()          ( KEY2_IN )
#define HAL_PUSH_BUTTON3()          ( KEY3_IN )
#define HAL_PUSH_BUTTON4()          ( KEY4_IN )
#define HAL_PUSH_BUTTON5()          ( KEY5_IN )
#define HAL_PUSH_BUTTON6()          ( KEY6_IN )
#define HAL_PUSH_BUTTON7()          ( KEY7_IN )
#define HAL_PUSH_BUTTON8()          ( KEY8_IN )
#define HAL_PUSH_BUTTON9()          ( KEY9_IN )
#define HAL_PUSH_BUTTON10()         ( KEY10_IN )

/**************************************************************************************************
 * TYPEDEFS
 **************************************************************************************************/
typedef void (*halKeyCBack_t) (uint16_t keys );

typedef struct
{
  uint16_t  keys;   // keys
} keyChange_t;

/**************************************************************************************************
 *                                             GLOBAL VARIABLES
 **************************************************************************************************/

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Initialize the Key Service
 */
void HAL_KeyInit( void );

/*
 * This is for internal used by hal_driver
 */
void HAL_KeyPoll( void );

/*
 * Configure the Key Service
 */
void HalKeyConfig( const halKeyCBack_t cback);

/*
 * Read the Key callback
 */
void HalKeyCallback ( uint8 keys );

/*
 * Read the Key status
 */
uint16_t HalKeyRead( void);

/**************************************************************************************************
**************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
