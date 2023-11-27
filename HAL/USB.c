/********************************** (C) COPYRIGHT *******************************
 * File Name          : USB.c
 * Author             : ChnMasterOG, sakumisu
 * Version            : V2.0
 * Date               : 2023/5/6
 * Description        : CherryUSB驱动
 * Copyright (c) 2023 ChnMasterOG
 * Copyright (c) 2022, sakumisu
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "usbd_core.h"
#include "usbd_hid.h"
#include "usbd_msc.h"
#include "usbd_cdc.h"

#ifndef WBVAL
#define WBVAL(x) (unsigned char)((x) & 0xFF), (unsigned char)(((x) >> 8) & 0xFF)
#endif

/*!< USBD CONFIG */
#define USBD_VERSION 0x0110
#define USBD_PRODUCT_VERSION 0x0001
#define USBD_VID 0x0418
#define USBD_PID 0x78A0
#define USBD_MAX_POWER 0xfa
#define USBD_LANGID_STRING 1033
#define USBD_CONFIG_DESCRIPTOR_SIZE 139

/*!< USBD ENDPOINT CONFIG */
#define USBD_IF0_AL0_EP0_ADDR 0x81
#define USBD_IF0_AL0_EP0_SIZE 0x40
#define USBD_IF0_AL0_EP0_INTERVAL 0x01

#define USBD_IF0_AL0_EP1_ADDR 0x01
#define USBD_IF0_AL0_EP1_SIZE 0x40
#define USBD_IF0_AL0_EP1_INTERVAL 0x01

#define USBD_IF1_AL0_EP0_ADDR 0x82
#define USBD_IF1_AL0_EP0_SIZE 0x20
#define USBD_IF1_AL0_EP0_INTERVAL 0x01

#define USBD_IF1_AL0_EP1_ADDR 0x02
#define USBD_IF1_AL0_EP1_SIZE 0x20
#define USBD_IF1_AL0_EP1_INTERVAL 0x01

#define USBD_IF2_AL0_EP0_ADDR 0x83
#define USBD_IF2_AL0_EP0_SIZE 0x40
#define USBD_IF2_AL0_EP0_INTERVAL 0x01

#define USBD_IF3_AL0_EP0_ADDR 0x84
#define USBD_IF3_AL0_EP0_SIZE 0x40
#define USBD_IF3_AL0_EP0_INTERVAL 0x00

#define USBD_IF3_AL0_EP1_ADDR 0x04
#define USBD_IF3_AL0_EP1_SIZE 0x40
#define USBD_IF3_AL0_EP1_INTERVAL 0x00

/*!< USBD HID CONFIG */
#define USBD_HID_VERSION 0x0111
#define USBD_HID_COUNTRY_CODE 0
#define HID_REPORT_KEYBOARD_DESC_SIZE 63
#define HID_REPORT_MOUSE_DESC_SIZE 74
#define HID_REPORT_VOL_DESC_SIZE 33
#define HID_REPORT_RAW_DESC_SIZE 34
#define HID_REPORT_GAMEPAD_DESC_SIZE 46//52

const unsigned char usbd_descriptor[] = {
/********************************************** Device Descriptor */
    0x12,                                       /*!< bLength */
    0x01,                                       /*!< bDescriptorType */
    WBVAL(USBD_VERSION),                        /*!< bcdUSB */
    0x00,                                       /*!< bDeviceClass */
    0x00,                                       /*!< bDeviceSubClass */
    0x00,                                       /*!< bDeviceProtocol */
    0x40,                                       /*!< bMaxPacketSize */
    WBVAL(USBD_VID),                            /*!< idVendor */
    WBVAL(USBD_PID),                            /*!< idProduct */
    WBVAL(USBD_PRODUCT_VERSION),                /*!< bcdDevice */
    0x01,                                       /*!< iManufacturer */
    0x02,                                       /*!< iProduct */
    0x03,                                       /*!< iSerial */
    0x01,                                       /*!< bNumConfigurations */
/********************************************** Config Descriptor */
    0x09,                                       /*!< bLength */
    0x02,                                       /*!< bDescriptorType */
    WBVAL(USBD_CONFIG_DESCRIPTOR_SIZE),         /*!< wTotalLength */
    0x04,                                       /*!< bNumInterfaces */
    0x01,                                       /*!< bConfigurationValue */
    0x00,                                       /*!< iConfiguration */
    0xa0,                                       /*!< bmAttributes */
    USBD_MAX_POWER,                             /*!< bMaxPower */
/********************************************** Interface 0 Alternate 0 Descriptor */
    0x09,                                       /*!< bLength */
    0x04,                                       /*!< bDescriptorType */
    0x00,                                       /*!< bInterfaceNumber */
    0x00,                                       /*!< bAlternateSetting */
    0x02,                                       /*!< bNumEndpoints */
    0x03,                                       /*!< bInterfaceClass */
    0x00,                                       /*!< bInterfaceSubClass */
    0x00,                                       /*!< bInterfaceProtocol */
    0x00,                                       /*!< iInterface */
/********************************************** Class Specific Descriptor of HID */
    0x09,                                       /*!< bLength */
    0x21,                                       /*!< bDescriptorType */
    WBVAL(USBD_HID_VERSION),                    /*!< bcdHID */
    USBD_HID_COUNTRY_CODE,                      /*!< bCountryCode */
    0x01,                                       /*!< bNumDescriptors */
    0x22,                                       /*!< bDescriptorType */
    WBVAL(HID_REPORT_GAMEPAD_DESC_SIZE),        /*!< wItemLength */
/********************************************** Endpoint 0 Descriptor */
    0x07,                                       /*!< bLength */
    0x05,                                       /*!< bDescriptorType */
    USBD_IF0_AL0_EP0_ADDR,                      /*!< bEndpointAddress */
    0x03,                                       /*!< bmAttributes */
    WBVAL(USBD_IF0_AL0_EP0_SIZE),               /*!< wMaxPacketSize */
    USBD_IF0_AL0_EP0_INTERVAL,                  /*!< bInterval */
/********************************************** Endpoint 1 Descriptor */
    0x07,                                       /*!< bLength */
    0x05,                                       /*!< bDescriptorType */
    USBD_IF0_AL0_EP1_ADDR,                      /*!< bEndpointAddress */
    0x03,                                       /*!< bmAttributes */
    WBVAL(USBD_IF0_AL0_EP1_SIZE),               /*!< wMaxPacketSize */
    USBD_IF0_AL0_EP1_INTERVAL,                  /*!< bInterval */
/********************************************** Interface 1 Alternate 0 Descriptor */
    0x09,                                       /*!< bLength */
    0x04,                                       /*!< bDescriptorType */
    0x01,                                       /*!< bInterfaceNumber */
    0x00,                                       /*!< bAlternateSetting */
    0x02,                                       /*!< bNumEndpoints */
    0x03,                                       /*!< bInterfaceClass */
    0x00,                                       /*!< bInterfaceSubClass */
    0x00,                                       /*!< bInterfaceProtocol */
    0x00,                                       /*!< iInterface */
/********************************************** Class Specific Descriptor of HID */
    0x09,                                       /*!< bLength */
    0x21,                                       /*!< bDescriptorType */
    WBVAL(USBD_HID_VERSION),                    /*!< bcdHID */
    USBD_HID_COUNTRY_CODE,                      /*!< bCountryCode */
    0x01,                                       /*!< bNumDescriptors */
    0x22,                                       /*!< bDescriptorType */
    WBVAL(HID_REPORT_RAW_DESC_SIZE),            /*!< wItemLength */
/********************************************** Endpoint 0 Descriptor */
    0x07,                                       /*!< bLength */
    0x05,                                       /*!< bDescriptorType */
    USBD_IF1_AL0_EP0_ADDR,                      /*!< bEndpointAddress */
    0x03,                                       /*!< bmAttributes */
    WBVAL(USBD_IF1_AL0_EP0_SIZE),               /*!< wMaxPacketSize */
    USBD_IF1_AL0_EP0_INTERVAL,                  /*!< bInterval */
/********************************************** Endpoint 1 Descriptor */
    0x07,                                       /*!< bLength */
    0x05,                                       /*!< bDescriptorType */
    USBD_IF1_AL0_EP1_ADDR,                      /*!< bEndpointAddress */
    0x03,                                       /*!< bmAttributes */
    WBVAL(USBD_IF1_AL0_EP1_SIZE),               /*!< wMaxPacketSize */
    USBD_IF1_AL0_EP1_INTERVAL,                  /*!< bInterval */
/********************************************** Interface Associate Descriptor */
    0x08,                                       /*!< bLength */
    0x0b,                                       /*!< bDescriptorType */
    0x02,                                       /*!< bFirstInterface */
    0x02,                                       /*!< bInterfaceCount */
    0x02,                                       /*!< bFunctionClass */
    0x02,                                       /*!< bFunctionSubClass */
    0x01,                                       /*!< bFunctionProtocol */
    0x00,                                       /*!< iFunction */
/********************************************** Interface 2 Alternate 0 Descriptor */
    0x09,                                       /*!< bLength */
    0x04,                                       /*!< bDescriptorType */
    0x02,                                       /*!< bInterfaceNumber */
    0x00,                                       /*!< bAlternateSetting */
    0x01,                                       /*!< bNumEndpoints */
    0x02,                                       /*!< bInterfaceClass */
    0x02,                                       /*!< bInterfaceSubClass */
    0x01,                                       /*!< bInterfaceProtocol */
    0x00,                                       /*!< iInterface */
/********************************************** Class Specific Descriptor of CDC ACM Control */
    0x05,                                       /*!< bLength */
    0x24,                                       /*!< bDescriptorType */
    0x00,                                       /*!< bDescriptorSubtype */
    WBVAL(0x0110),                              /*!< bcdCDC */
    0x05,                                       /*!< bLength */
    0x24,                                       /*!< bDescriptorType */
    0x01,                                       /*!< bDescriptorSubtype */
    0x02,                                       /*!< bmCapabilities */
    0x03,                                       /*!< bDataInterface */
    0x04,                                       /*!< bLength */
    0x24,                                       /*!< bDescriptorType */
    0x02,                                       /*!< bDescriptorSubtype */
    0x02,                                       /*!< bmCapabilities */
    0x05,                                       /*!< bLength */
    0x24,                                       /*!< bDescriptorType */
    0x06,                                       /*!< bDescriptorSubtype */
    0x02,                                       /*!< bMasterInterface */
    0x03,                                       /*!< bSlaveInterface0 */
/********************************************** Endpoint 0 Descriptor */
    0x07,                                       /*!< bLength */
    0x05,                                       /*!< bDescriptorType */
    USBD_IF2_AL0_EP0_ADDR,                      /*!< bEndpointAddress */
    0x03,                                       /*!< bmAttributes */
    WBVAL(USBD_IF2_AL0_EP0_SIZE),               /*!< wMaxPacketSize */
    USBD_IF2_AL0_EP0_INTERVAL,                  /*!< bInterval */
/********************************************** Interface 3 Alternate 0 Descriptor */
    0x09,                                       /*!< bLength */
    0x04,                                       /*!< bDescriptorType */
    0x03,                                       /*!< bInterfaceNumber */
    0x00,                                       /*!< bAlternateSetting */
    0x02,                                       /*!< bNumEndpoints */
    0x0a,                                       /*!< bInterfaceClass */
    0x00,                                       /*!< bInterfaceSubClass */
    0x00,                                       /*!< bInterfaceProtocol */
    0x00,                                       /*!< iInterface */
/********************************************** Class Specific Descriptor of CDC ACM Data */
/********************************************** Endpoint 0 Descriptor */
    0x07,                                       /*!< bLength */
    0x05,                                       /*!< bDescriptorType */
    USBD_IF3_AL0_EP0_ADDR,                      /*!< bEndpointAddress */
    0x02,                                       /*!< bmAttributes */
    WBVAL(USBD_IF3_AL0_EP0_SIZE),               /*!< wMaxPacketSize */
    USBD_IF3_AL0_EP0_INTERVAL,                  /*!< bInterval */
/********************************************** Endpoint 1 Descriptor */
    0x07,                                       /*!< bLength */
    0x05,                                       /*!< bDescriptorType */
    USBD_IF3_AL0_EP1_ADDR,                      /*!< bEndpointAddress */
    0x02,                                       /*!< bmAttributes */
    WBVAL(USBD_IF3_AL0_EP1_SIZE),               /*!< wMaxPacketSize */
    USBD_IF3_AL0_EP1_INTERVAL,                  /*!< bInterval */
/********************************************** Language ID String Descriptor */
    0x04,                                       /*!< bLength */
    0x03,                                       /*!< bDescriptorType */
    WBVAL(USBD_LANGID_STRING),                  /*!< wLangID0 */
/********************************************** String 1 Descriptor */
/* CL_novel */
    0x12,                                       /*!< bLength */
    0x03,                                       /*!< bDescriptorType */
    0x43, 0x00,                                 /*!< 'C' wcChar0 */
    0x4c, 0x00,                                 /*!< 'L' wcChar1 */
    0x5f, 0x00,                                 /*!< '_' wcChar2 */
    0x6e, 0x00,                                 /*!< 'n' wcChar3 */
    0x6f, 0x00,                                 /*!< 'o' wcChar4 */
    0x76, 0x00,                                 /*!< 'v' wcChar5 */
    0x65, 0x00,                                 /*!< 'e' wcChar6 */
    0x6c, 0x00,                                 /*!< 'l' wcChar7 */
/********************************************** String 2 Descriptor */
/* TP78 */
    0x0a,                                       /*!< bLength */
    0x03,                                       /*!< bDescriptorType */
    0x54, 0x00,                                 /*!< 'T' wcChar0 */
    0x50, 0x00,                                 /*!< 'P' wcChar1 */
    0x37, 0x00,                                 /*!< '7' wcChar2 */
    0x38, 0x00,                                 /*!< '8' wcChar3 */
/********************************************** String 3 Descriptor */
/* Joyticks */
    0x12,                                       /*!< bLength */
    0x03,                                       /*!< bDescriptorType */
    0x4a, 0x00,                                 /*!< 'J' wcChar0 */
    0x6f, 0x00,                                 /*!< 'o' wcChar1 */
    0x79, 0x00,                                 /*!< 'y' wcChar2 */
    0x74, 0x00,                                 /*!< 't' wcChar3 */
    0x69, 0x00,                                 /*!< 'i' wcChar4 */
    0x63, 0x00,                                 /*!< 'c' wcChar5 */
    0x6b, 0x00,                                 /*!< 'k' wcChar6 */
    0x73, 0x00,                                 /*!< 's' wcChar7 */
    0x00
};

/*!< USBD HID REPORT Descriptor - Keyboard */
const unsigned char usbd_hid_report_keyboard_descriptor[HID_REPORT_KEYBOARD_DESC_SIZE] = {
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x06, // USAGE (Keyboard)
        0xa1, 0x01, // COLLECTION (Application)
        0x05, 0x07, // USAGE_PAGE (Keyboard)
        0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00, // LOGICAL_MINIMUM (0)
        0x25, 0x01, // LOGICAL_MAXIMUM (1)
        0x75, 0x01, // REPORT_SIZE (1)
        0x95, 0x08, // REPORT_COUNT (8)
        0x81, 0x02, // INPUT (Data,Var,Abs)
        0x95, 0x01, // REPORT_COUNT (1)
        0x75, 0x08, // REPORT_SIZE (8)
        0x81, 0x03, // INPUT (Cnst,Var,Abs)
        0x95, 0x05, // REPORT_COUNT (5)
        0x75, 0x01, // REPORT_SIZE (1)
        0x05, 0x08, // USAGE_PAGE (LEDs)
        0x19, 0x01, // USAGE_MINIMUM (Num Lock)
        0x29, 0x05, // USAGE_MAXIMUM (Kana)
        0x91, 0x02, // OUTPUT (Data,Var,Abs)
        0x95, 0x01, // REPORT_COUNT (1)
        0x75, 0x03, // REPORT_SIZE (3)
        0x91, 0x03, // OUTPUT (Cnst,Var,Abs)
        0x95, 0x06, // REPORT_COUNT (6)
        0x75, 0x08, // REPORT_SIZE (8)
        0x15, 0x00, // LOGICAL_MINIMUM (0)
        0x25, 0xFF, // LOGICAL_MAXIMUM (255)
        0x05, 0x07, // USAGE_PAGE (Keyboard)
        0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65, // USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00, // INPUT (Data,Ary,Abs)
        0xc0        // END_COLLECTION
};

/*!< USBD HID REPORT Descriptor - Mouse */
const unsigned char usbd_hid_report_mouse_descriptor[HID_REPORT_MOUSE_DESC_SIZE] = {
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x02, // USAGE (Mouse)
        0xA1, 0x01, // COLLECTION (Application)
        0x09, 0x01, // USAGE (Pointer)

        0xA1, 0x00, // COLLECTION (Physical)
        0x05, 0x09, // USAGE_PAGE (Button)
        0x19, 0x01, // USAGE_MINIMUM (Button 1)
        0x29, 0x03, // USAGE_MAXIMUM (Button 3)

        0x15, 0x00, // LOGICAL_MINIMUM (0)
        0x25, 0x01, // LOGICAL_MAXIMUM (1)
        0x95, 0x03, // REPORT_COUNT (3)
        0x75, 0x01, // REPORT_SIZE (1)

        0x81, 0x02, // INPUT (Data,Var,Abs)
        0x95, 0x01, // REPORT_COUNT (1)
        0x75, 0x05, // REPORT_SIZE (5)
        0x81, 0x01, // INPUT (Cnst,Var,Abs)

        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x30, // USAGE (X)
        0x09, 0x31, // USAGE (Y)
        0x09, 0x38,

        0x15, 0x81, // LOGICAL_MINIMUM (-127)
        0x25, 0x7F, // LOGICAL_MAXIMUM (127)
        0x75, 0x08, // REPORT_SIZE (8)
        0x95, 0x03, // REPORT_COUNT (2)

        0x81, 0x06, // INPUT (Data,Var,Rel)
        0xC0, 0x09,
        0x3c, 0x05,
        0xff, 0x09,

        0x01, 0x15,
        0x00, 0x25,
        0x01, 0x75,
        0x01, 0x95,

        0x02, 0xb1,
        0x22, 0x75,
        0x06, 0x95,
        0x01, 0xb1,

        0x01, 0xc0 //   END_COLLECTION
};

/*!< USBD HID REPORT Descriptor - Vol */
const unsigned char usbd_hid_report_vol_descriptor[HID_REPORT_VOL_DESC_SIZE] = {
        0x05, 0x0C,
        0x09, 0x01,
        0xA1, 0x01,

        0x09, 0xB0,
        0x09, 0xB5,
        0x09, 0xB6,
        0x09, 0xE9,
        0x09, 0xEA,
        0x09, 0xE2,
        0x09, 0xB1,
        0x09, 0xB7,

        0x15, 0x00,
        0x25, 0x01,
        0x95, 0x08,
        0x75, 0x01,
        0x81, 0x02,
        0xC0
};

/*!< USBD RAW HID REPORT Descriptor - Raw */
const unsigned char usbd_hid_report_raw_descriptor[HID_REPORT_RAW_DESC_SIZE] = {
        0x06, 0x60, 0xFF, // Vendor Defined
        0x09, 0x61, // Vendor Defined
        0xA1, 0x01, // Application

        0x09, 0x62,
        0x15, 0x00, // LOGICAL_MINIMUM (0)
        0x26, 0xFF, 0x00, // LOGICAL_MAXIMUM (0xFF)
        0x95, 0x20, // REPORT_COUNT(RAW_EPSIZE = 32)
        0x75, 0x08, // REPORT_SIZE
        0x81, 0x02,

        0x09, 0x63,
        0x15, 0x00, // LOGICAL_MINIMUM (0)
        0x26, 0xFF, 0x00, // LOGICAL_MAXIMUM (0xFF)
        0x95, 0x20, // REPORT_COUNT(RAW_EPSIZE = 32)
        0x75, 0x08, // REPORT_SIZE
        0x91, 0x02,

        0xC0
};

#if 0
/*!< USBD HID REPORT Descriptor - GamePad */
const unsigned char usbd_hid_report_gamepad_descriptor_backup[52] = {
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x05, // USAGE (Game Pad)
        0xA1, 0x01, // COLLECTION (Application)

        0x09, 0x01, // USAGE (Pointer)
        0xA1, 0x00, // COLLECTION (Physical)
        0x09, 0x30, // USAGE (X)
        0x09, 0x31, // USAGE (Y)
        0x15, 0xFF, // LOGICAL_MINIMUM (-1)
        0x25, 0x01, // LOGICAL_MAXIMUM (1)
        0x95, 0x02, // REPORT_COUNT (2) - count 2
        0x75, 0x02, // REPORT_SIZE (2) - 2 bit
        0x81, 0x02, // INPUT (Data, Var, Abs)
        0xC0,

        0x95, 0x04, // REPORT_COUNT (4) - 填充8bit
        0x75, 0x01, // REPORT_SIZE (1)
        0x81, 0x43, // INPUT (Cnst, Var, Abs, Null)

        0x05, 0x09, // USAGE_PAGE (Button)
        0x19, 0x01, // USAGE_MINIMUM (number 1)
        0x29, 0x06, // USAGE_MAXIMUM (number 6)
        0x15, 0x00, // USAGE_MINIMUM (value 0)
        0x25, 0x01, // USAGE_MAXIMUM (value 1)
        0x95, 0x06, // REPORT_COUNT (6) - count 6
        0x75, 0x01, // REPORT_SIZE (1) - 1 bit
        0x81, 0x42, // INPUT (Data, Var, Abs)

        0x95, 0x02, // REPORT_COUNT (2) - 填充8bit
        0x81, 0x43, // INPUT (Cnst, Var, Abs, Null)
        0xC0,
};
#endif

/*!< USBD HID REPORT Descriptor - GamePad */
const unsigned char usbd_hid_report_gamepad_descriptor[HID_REPORT_GAMEPAD_DESC_SIZE] = {
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x05, // USAGE (Game Pad)
        0xA1, 0x01, // COLLECTION (Application)

        0x09, 0x01, // USAGE (Pointer)
        0xA1, 0x00, // COLLECTION (Physical)
        0x09, 0x30, // USAGE (X)
        0x09, 0x31, // USAGE (Y)
        0x15, 0xFF, // LOGICAL_MINIMUM (-1)
        0x25, 0x01, // LOGICAL_MAXIMUM (1)
        0x95, 0x02, // REPORT_COUNT (2) - count 2
        0x75, 0x08, // REPORT_SIZE (8) - 8 bit
        0x81, 0x02, // INPUT (Data, Var, Abs)
        0xC0,

        0x05, 0x09, // USAGE_PAGE (Button)
        0x19, 0x01, // USAGE_MINIMUM (number 1)
        0x29, 0x0A, // USAGE_MAXIMUM (number 10)
        0x15, 0x00, // LOGICAL_MINIMUM (value 0)
        0x25, 0x01, // LOGICAL_MAXIMUM (value 1)
        0x95, 0x0A, // REPORT_COUNT (10) - count 10
        0x75, 0x01, // REPORT_SIZE (1) - 1 bit
        0x81, 0x42, // INPUT (Data, Var, Abs)

        0x95, 0x06, // REPORT_COUNT (6) - 填充8bit
        0x81, 0x43, // INPUT (Cnst, Var, Abs, Null)
        0xC0,
};

#include "HAL.h"
#include "tp78_joyticks_via.h"

#define HID_STATE_IDLE 0
#define HID_STATE_BUSY 1

/*!< hid state ! Data can be sent only when state is idle  */
static uint8_t hid_state = HID_STATE_IDLE;
volatile uint8_t cdc_ep_tx_busy_flag = FALSE;

/* function ------------------------------------------------------------------*/
static void usbd_hid_gamepad_in_callback(uint8_t ep, uint32_t nbytes)
{
    hid_state = HID_STATE_IDLE;
}

static void usbd_hid_gamepad_out_callback(uint8_t ep, uint32_t nbytes)
{

}

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t raw_buffer[32] = { 0 };
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t cdc_buffer[0x40];

static void usbd_hid_raw_in_callback(uint8_t ep, uint32_t nbytes)
{

}

/* support via */
static void usbd_hid_raw_out_callback(uint8_t ep, uint32_t nbytes)
{
  via_data_processing(raw_buffer, 32);
  usbd_ep_start_write(USBD_IF1_AL0_EP0_ADDR, raw_buffer, sizeof(raw_buffer));
  usbd_ep_start_read(USBD_IF1_AL0_EP1_ADDR, raw_buffer, sizeof(raw_buffer));
}

/* cdc function */
static void usbd_cdc_acm_bulk_in_callback(uint8_t ep, uint32_t nbytes)
{
    if ((nbytes % 64) == 0 && nbytes) {
        usbd_ep_start_write(USBD_IF3_AL0_EP0_ADDR, NULL, 0);
    } else {
        cdc_ep_tx_busy_flag = FALSE;
    }
}

static void usbd_cdc_acm_bulk_out_callback(uint8_t ep, uint32_t nbytes)
{
    uint8_t send_buf[6] = {0};
    /* for debug */
    if (cdc_buffer[0] == 'a') {
        if (cdc_buffer[2] == 'l') {
            if (cdc_buffer[4] >= '0' && cdc_buffer[4] <= '3') {
                send_buf[0] = (cdc_buffer[4] - '0');
                usbd_ep_start_write(USBD_IF0_AL0_EP0_ADDR, send_buf, sizeof(send_buf));
            }
        } else if (cdc_buffer[2] == 'r') {
            if (cdc_buffer[4] >= '0' && cdc_buffer[4] <= '3') {
                send_buf[1] = (cdc_buffer[4] - '0');
                usbd_ep_start_write(USBD_IF0_AL0_EP0_ADDR, send_buf, sizeof(send_buf));
            }
        }
    } else if (cdc_buffer[0] == 'b') {
        if (cdc_buffer[2] >= '0' && cdc_buffer[2] <= '9') {
            send_buf[4] = 1 << (cdc_buffer[2] - '0');
            send_buf[5] = 1 << (cdc_buffer[2] - '8');
            usbd_ep_start_write(USBD_IF0_AL0_EP0_ADDR, send_buf, sizeof(send_buf));
        }
    }
    usbd_ep_start_read(USBD_IF3_AL0_EP1_ADDR, cdc_buffer, 0x40);
}

/*!< endpoint call back */
static struct usbd_endpoint hid_gamepad_in_ep = {
    .ep_cb = usbd_hid_gamepad_in_callback,
    .ep_addr = USBD_IF0_AL0_EP0_ADDR
};

static struct usbd_endpoint hid_gamepad_out_ep = {
    .ep_cb = usbd_hid_gamepad_out_callback,
    .ep_addr = USBD_IF0_AL0_EP1_ADDR
};

static struct usbd_endpoint hid_raw_in_ep = {
    .ep_cb = usbd_hid_raw_in_callback,
    .ep_addr = USBD_IF1_AL0_EP0_ADDR
};

static struct usbd_endpoint hid_raw_out_ep = {
    .ep_cb = usbd_hid_raw_out_callback,
    .ep_addr = USBD_IF1_AL0_EP1_ADDR
};

struct usbd_endpoint cdc_in_ep = {
    .ep_cb = usbd_cdc_acm_bulk_in_callback,
    .ep_addr = USBD_IF3_AL0_EP0_ADDR
};

struct usbd_endpoint cdc_out_ep = {
    .ep_cb = usbd_cdc_acm_bulk_out_callback,
    .ep_addr = USBD_IF3_AL0_EP1_ADDR
};

struct usbd_interface intf0;
struct usbd_interface intf1;
struct usbd_interface intf2;
struct usbd_interface intf3;

static void usb_device_init()
{
    usbd_desc_register(usbd_descriptor);
    usbd_add_interface(usbd_hid_init_intf(&intf0, usbd_hid_report_gamepad_descriptor, HID_REPORT_GAMEPAD_DESC_SIZE));
    usbd_add_endpoint(&hid_gamepad_in_ep);
    usbd_add_endpoint(&hid_gamepad_out_ep);
    usbd_add_interface(usbd_hid_init_intf(&intf1, usbd_hid_report_raw_descriptor, HID_REPORT_RAW_DESC_SIZE));
    usbd_add_endpoint(&hid_raw_in_ep);
    usbd_add_endpoint(&hid_raw_out_ep);
    usbd_add_interface(usbd_cdc_acm_init_intf(&intf2));
    usbd_add_interface(usbd_cdc_acm_init_intf(&intf3));
    usbd_add_endpoint(&cdc_in_ep);
    usbd_add_endpoint(&cdc_out_ep);

    usbd_initialize();
}

// Task id
tmosTaskID usbTaskID = INVALID_TASK_ID;

void usbd_configure_done_callback(void)
{
    usbd_ep_start_read(USBD_IF1_AL0_EP1_ADDR, raw_buffer, sizeof(raw_buffer));
    usbd_ep_start_read(USBD_IF3_AL0_EP1_ADDR, cdc_buffer, sizeof(cdc_buffer));
}

/*--------------------------- define for hid ---------------------------*/

void usbh_hid_set_idle(uint8_t intf, uint8_t report_id, uint8_t duration)
{

}

void usbh_hid_set_protocol(uint8_t intf, uint8_t protocol)
{

}

void usbh_hid_set_report(uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t *report, uint8_t report_len)
{

}

void usb_suspend_wake_up_cb(uint8_t type)
{

}

/*--------------------------- define for cdc ---------------------------*/

#include <stdarg.h>
void usb_printf(char *pFormat, ...)
{
    char pStr[0x40] = {'\0'};
    va_list ap;

    va_start(ap, pFormat);
    vsprintf((char*)pStr, pFormat, ap);
    va_end(ap);

    cdc_ep_tx_busy_flag = TRUE;
    usbd_ep_start_write(USBD_IF3_AL0_EP0_ADDR, pStr, 0x40);
//    while (cdc_ep_tx_busy_flag);
}

/*--------------------------- define for msc ---------------------------*/
#define BLOCK_SIZE    512
#define BLOCK_COUNT   64

void usbd_msc_get_cap(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
    *block_num = BLOCK_COUNT; //Pretend having so many buffer,not has actually.
    *block_size = BLOCK_SIZE;
}

int usbd_msc_sector_read(uint32_t sector, uint8_t *buffer, uint32_t length)
{

    return 0;
}

int usbd_msc_sector_write(uint32_t sector, uint8_t *buffer, uint32_t length)
{

    return 0;
}

/*******************************************************************************
 * Function Name  : USB_ProcessEvent
 * Description    : USB处理事件
 * Input          : task_id： 任务id, events: USB事件
 * Return         : tmosEvents
 *******************************************************************************/
tmosEvents USB_ProcessEvent( tmosTaskID task_id, tmosEvents events )
{
    int ret;

    if ( events & START_USB_EVENT )
    {
        PFIC_EnableIRQ( USB_IRQn );
        return events ^ START_USB_EVENT;
    }

    if ( events & USB_SEND_JOY_REPORT_EVENT )
    {
        usbd_ep_start_write(USBD_IF0_AL0_EP0_ADDR, joy_hid_buffer, 4);
//        hid_state = HID_STATE_BUSY;
//        while (hid_state != HID_STATE_IDLE);
        return events ^ USB_SEND_JOY_REPORT_EVENT;
    }

    if ( events & USB_TEST_EVENT )
    {
#if 0
        hid_keyboard_test();
        hid_mouse_test();
#endif
        tmos_start_task(usbTaskID, USB_TEST_EVENT, MS1_TO_SYSTEM_TIME(500));
        return events ^ USB_TEST_EVENT;
    }

    return 0;
}

/*******************************************************************************
 * Function Name  : HAL_USBInit
 * Description    : USB初始化
 * Input          : None
 * Return         : None
 *******************************************************************************/
void HAL_USBInit( void )
{
    uint16_t Udisk_mode = 0;

    usbTaskID = TMOS_ProcessEventRegister( USB_ProcessEvent );
    /* support to cherry usb */
#if 0
    TMR0_TimerInit(FREQ_SYS / 1000);
    TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END);
    PFIC_EnableIRQ(TMR0_IRQn);
    PFIC_SetPriority(TMR0_IRQn, 20);
#endif
    /* usb device init */
    usb_device_init();
    while (!usb_device_is_configured());
}

void usb_dc_low_level_init(void)
{
    extern void USB_IRQHandler(void);
    PFIC_EnableIRQ(USB_IRQn);
    PFIC_EnableFastINT0(USB_IRQn, (uint32_t)(void *)USB_IRQHandler);
}

void usb_hc_low_level_init(void)
{
//  PFIC_EnableIRQ(USB2_IRQn);
}

#if 0
volatile uint32_t timer_count_user = 0;

__INTERRUPT
__HIGH_CODE
void TMR0_IRQHandler(void)
{
    /*!< Timer 0 IRQ */
    if (TMR0_GetITFlag(TMR0_3_IT_CYC_END)) {
        /*!< Clear Pending flag */
        TMR0_ClearITFlag(TMR0_3_IT_CYC_END);

        /*!< Updata the ms count */
        timer_count_user++;
        /*!< Set timing time 1ms */
        R32_TMR0_CNT_END = GetSysClock() / 1000;
        R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
        R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN;

        /*!< Enable interrupt */
        TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END);
    }
}

uint32_t chey_board_millis(void)
{
    return timer_count_user;
}
#endif
