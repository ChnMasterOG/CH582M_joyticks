/********************************** (C) COPYRIGHT *******************************
 * File Name          : HAL.h
 * Author             : ChnMasterOG, WCH
 * Version            : V1.1
 * Date               : 2022/11/13
 * Description        : HAL层通用头文件
 * Copyright (c) 2023 ChnMasterOG
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

/******************************************************************************/
#ifndef __HAL_H
#define __HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "CH58x_common.h"
#include "config.h"
#include "tp78_joyticks_via.h"
#include "RTC.h"
#include "SLEEP.h"
#include "LED.h"
#include "KEY.h"
#include "BLE.h"
#include "SWITCH.h"
#include "CORE.h"
#include "BATTERY.h"
#include "WS2812.h"
#include "USB.h"
#include "ICM20602.h"
#include "HW_I2C.h"

/* hal task Event */
#define HAL_KEY_EVENT           0x0001
#define BATTERY_EVENT           0x0002
#define ICM_EVENT               0x0004
#define WS2812_EVENT            0x0008
#define SWITCH_EVENT            0x0010
#define SEND_REPORT_EVENT       0x1000
#define HAL_REG_INIT_EVENT      0x2000

/*********************************************************************
 * GLOBAL VARIABLES
 */

extern tmosTaskID halTaskID;
extern uint8_t joy_hid_buffer[4];
extern uint8_t gyro_enable;

/*********************************************************************
 * GLOBAL FUNCTIONS
 */

extern void HAL_Init( );
extern tmosEvents HAL_ProcessEvent( tmosTaskID task_id, tmosEvents events );
extern void CH58X_BLEInit( void );
extern uint16 HAL_GetInterTempValue( void );
extern void Lib_Calibration_LSI( void );

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
