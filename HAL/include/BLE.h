/********************************** (C) COPYRIGHT *******************************
 * File Name          : BLE.h
 * Author             : ChnMasterOG, WCH
 * Version            : V1.3
 * Date               : 2022/2/26
 * Description        :
 * Copyright (c) 2023 ChnMasterOG
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#ifndef BLE_H
#define BLE_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "CONFIG.h"

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * MACROS
 */
// Task Events
#define START_DEVICE_EVT            0x0001
#define START_REPORT_EVT            0x0002
#define START_PARAM_UPDATE_EVT      0x0004
#define START_PHY_UPDATE_EVT        0x0008

#define BLE_STATUS_UNCONNECTED      0x0
#define BLE_STATUS_CONNECTED        0x1

/*********************************************************************
 * FUNCTIONS
 */
  
/*********************************************************************
 * GLOBAL VARIABLES
 */

/*
 * Task Initialization for the BLE Application
 */
extern void HidEmu_Init( void );

/*
 * Task Event Processor for the BLE Application
 */
extern uint16 HidEmu_ProcessEvent( uint8 task_id, uint16 events );

extern tmosTaskID hidEmuTaskId;
extern uint8_t BLE_status;

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif 
