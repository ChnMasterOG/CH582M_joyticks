/********************************** (C) COPYRIGHT *******************************
* File Name          : KEY.c
* Author             : ChnMasterOG, WCH
* Version            : V2.0
* Date               : 2023/11/14
* Description        : add joytick support
* Copyright (c) 2023 ChnMasterOG
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: GPL-3.0
*******************************************************************************/



/******************************************************************************/
/* 头文件包含 */
#include "CH58x_common.h"
#include "HAL.h"


/**************************************************************************************************
 *                                        GLOBAL VARIABLES
 **************************************************************************************************/

static uint16 halKeySavedKeys;     /* 保留按键最后的状态，用于查询是否有键值变化 */


/**************************************************************************************************
 *                                        FUNCTIONS - Local
 **************************************************************************************************/
static halKeyCBack_t pHalKeyProcessFunction;	    /* callback function */


/**************************************************************************************************
 * @fn      HAL_key_callback
 *
 * @brief   按键回调函数
 *
 * @param   none
 *
 * @return  None
 **************************************************************************************************/
void HAL_key_callback( uint16_t keys )
{
    joy_hid_buffer[4] = keys & 0xFF;
    joy_hid_buffer[5] = (keys >> 8) & 0x3;
    tmos_set_event(usbTaskID, USB_SEND_JOY_REPORT_EVENT);
}

/**************************************************************************************************
 * @fn      HAL_KeyInit
 *
 * @brief   Initilize Key Service
 *
 * @param   none
 *
 * @return  None
 **************************************************************************************************/
void HAL_KeyInit( void )
{
    /* Initialize previous key to 0 */
    halKeySavedKeys = 0;
    /* Initialize callback function */
    pHalKeyProcessFunction  = NULL;
    KEY1_DIR; KEY2_DIR; KEY3_DIR; KEY4_DIR;
    KEY5_DIR; KEY6_DIR; KEY7_DIR; KEY8_DIR;
    KEY9_DIR; KEY10_DIR;
    KEY1_PD; KEY2_PD; KEY3_PD; KEY4_PD;
    KEY5_PD; KEY6_PD; KEY7_PD; KEY8_PD;
    KEY9_PD; KEY10_PD;
    HalKeyConfig( HAL_key_callback );
}

/**************************************************************************************************
 * @fn      HalKeyConfig
 *
 * @brief   Configure the Key serivce
 *
 * @param   interruptEnable - TRUE/FALSE, enable/disable interrupt
 *          cback - pointer to the CallBack function
 *
 * @return  None
 **************************************************************************************************/
void HalKeyConfig ( halKeyCBack_t cback)
{
    /* Register the callback fucntion */
    pHalKeyProcessFunction = cback;
#if (defined HAL_KEY) && (HAL_KEY == TRUE)
	tmos_start_task( halTaskID, HAL_KEY_EVENT, HAL_KEY_POLLING_VALUE);    /* Kick off polling */
#endif
}

/**************************************************************************************************
 * @fn      HalKeyRead
 *
 * @brief   Read the current value of a key
 *
 * @param   None
 *
 * @return  keys - current keys status
 **************************************************************************************************/
uint16_t HalKeyRead( void )
{
    uint16_t keys = 0;

    if (HAL_PUSH_BUTTON1())
        keys |= HAL_KEY_SW_1;
    if (HAL_PUSH_BUTTON2())
        keys |= HAL_KEY_SW_2;
    if (HAL_PUSH_BUTTON3())
        keys |= HAL_KEY_SW_3;
    if (HAL_PUSH_BUTTON4())
        keys |= HAL_KEY_SW_4;
    if (HAL_PUSH_BUTTON5())
        keys |= HAL_KEY_SW_L;
    if (HAL_PUSH_BUTTON6())
        keys |= HAL_KEY_SW_R;
    if (HAL_PUSH_BUTTON7())
        keys |= HAL_KEY_SW_ZL;
    if (HAL_PUSH_BUTTON8())
        keys |= HAL_KEY_SW_ZR;
    if (HAL_PUSH_BUTTON9())
        keys |= HAL_KEY_SW_ML;
    if (HAL_PUSH_BUTTON10())
        keys |= HAL_KEY_SW_MR;

    return keys;
}


/**************************************************************************************************
 * @fn      HAL_KeyPoll
 *
 * @brief   Called by hal_driver to poll the keys
 *
 * @param   None
 *
 * @return  None
 **************************************************************************************************/
void HAL_KeyPoll(void)
{
    uint16_t keys = 0;

    if (HAL_PUSH_BUTTON1())
        keys |= HAL_KEY_SW_1;
    if (HAL_PUSH_BUTTON2())
        keys |= HAL_KEY_SW_2;
    if (HAL_PUSH_BUTTON3())
        keys |= HAL_KEY_SW_3;
    if (HAL_PUSH_BUTTON4())
        keys |= HAL_KEY_SW_4;
    if (HAL_PUSH_BUTTON5())
        keys |= HAL_KEY_SW_L;
    if (HAL_PUSH_BUTTON6())
        keys |= HAL_KEY_SW_R;
    if (HAL_PUSH_BUTTON7())
        keys |= HAL_KEY_SW_ZL;
    if (HAL_PUSH_BUTTON8())
        keys |= HAL_KEY_SW_ZR;
    if (HAL_PUSH_BUTTON9())
        keys |= HAL_KEY_SW_ML;
    if (HAL_PUSH_BUTTON10())
        keys |= HAL_KEY_SW_MR;

	if (keys == halKeySavedKeys)    /* Exit - since no keys have changed */
		return;

	halKeySavedKeys = keys;	       /* Store the current keys for comparation next time */

    /* Invoke Callback if new keys were depressed */
    if (keys && (pHalKeyProcessFunction))
        (pHalKeyProcessFunction) (keys);
}


/******************************** endfile @ key ******************************/