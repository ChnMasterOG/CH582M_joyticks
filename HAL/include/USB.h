/********************************** (C) COPYRIGHT *******************************
 * File Name          : USB.h
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2021/11/17
 * Description        : USB驱动头文件
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#ifndef __USB_H
    #define __USB_H

    #include "CH58x_common.h"
    #include "config.h"

    #define DevEP0SIZE      0x40
    #define NumsLockLED     0x01
    #define CapsLockLED     0x02
    #define ScrollLockLED   0x04

    #define POINT_MAX       (127)
    #define POINT_MIN       (-127)
    #define POINT_RANGE     (POINT_MAX-POINT_MIN)

    #define Volume_Play     (1 << 0)
    #define Volume_Next     (1 << 1)
    #define Volume_Prev     (1 << 2)
    #define Volume_Incr     (1 << 3)
    #define Volume_Decr     (1 << 4)
    #define Volume_Mute     (1 << 5)
    #define Volume_Pause    (1 << 6)
    #define Volume_Stop     (1 << 7)

    #define START_USB_EVENT             0x0001
    #define USB_CONNECT_EVENT           0x0010
    #define USB_SEND_JOY_REPORT_EVENT   0x0020
    #define USB_TEST_EVENT              0x1000

    #define USB_ERR_LENGTH              0x01
    #define USB_DAT_INVALID             0x02
    #define USB_ERR_UNKNOWN             0x10

    #define HID_REPORT_GAMEPAD_DESC_SIZE (107)

    extern tmosTaskID usbTaskID;

    void usb_printf(char *pFormat, ...);
    void HAL_USBInit( void );

#endif
