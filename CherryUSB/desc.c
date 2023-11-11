/**
  *
  * Licensed to the Apache Software Foundation (ASF) under one or more
  * contributor license agreements.  See the NOTICE file distributed with
  * this work for additional information regarding copyright ownership.  The
  * ASF licenses this file to you under the Apache License, Version 2.0 (the
  * "License"); you may not use this file except in compliance with the
  * License.  You may obtain a copy of the License at
  *
  *   http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
  * License for the specific language governing permissions and limitations
  * under the License.
  *
  */


#ifndef WBVAL
#define WBVAL(x) (unsigned char)((x) & 0xFF), (unsigned char)(((x) >> 8) & 0xFF)
#endif




/*!< USBD CONFIG */
#define USBD_VERSION 0x0110
#define USBD_PRODUCT_VERSION 0x0001
#define USBD_VID 0xffff
#define USBD_PID 0xffff
#define USBD_MAX_POWER 0xfa
#define USBD_LANGID_STRING 1033
#define USBD_CONFIG_DESCRIPTOR_SIZE 139




/*!< USBD ENDPOINT CONFIG */

#define USBD_IF0_AL0_EP0_ADDR 0x04
#define USBD_IF0_AL0_EP0_SIZE 0x40
#define USBD_IF0_AL0_EP0_INTERVAL 0x01

#define USBD_IF0_AL0_EP1_ADDR 0x84
#define USBD_IF0_AL0_EP1_SIZE 0x40
#define USBD_IF0_AL0_EP1_INTERVAL 0x01

#define USBD_IF1_AL0_EP0_ADDR 0x03
#define USBD_IF1_AL0_EP0_SIZE 0x20
#define USBD_IF1_AL0_EP0_INTERVAL 0x01

#define USBD_IF1_AL0_EP1_ADDR 0x83
#define USBD_IF1_AL0_EP1_SIZE 0x20
#define USBD_IF1_AL0_EP1_INTERVAL 0x01

#define USBD_IF2_AL0_EP0_ADDR 0x01
#define USBD_IF2_AL0_EP0_SIZE 0x40
#define USBD_IF2_AL0_EP0_INTERVAL 0x01

#define USBD_IF3_AL0_EP0_ADDR 0x02
#define USBD_IF3_AL0_EP0_SIZE 0x40
#define USBD_IF3_AL0_EP0_INTERVAL 0x00

#define USBD_IF3_AL0_EP1_ADDR 0x82
#define USBD_IF3_AL0_EP1_SIZE 0x40
#define USBD_IF3_AL0_EP1_INTERVAL 0x00




/*!< USBD HID CONFIG */
#define USBD_HID_VERSION 0x0111
#define USBD_HID_COUNTRY_CODE 0
#define USBD_IF0_AL0_HID_REPORT_DESC_SIZE 2
#define USBD_IF1_AL0_HID_REPORT_DESC_SIZE 2




/*!< USBD Descriptor */
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
    WBVAL(USBD_IF0_AL0_HID_REPORT_DESC_SIZE),   /*!< wItemLength */
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
    WBVAL(USBD_IF1_AL0_HID_REPORT_DESC_SIZE),   /*!< wItemLength */
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




/*!< USBD HID REPORT 0 Descriptor */
const unsigned char usbd_hid_0_report_descriptor[USBD_IF0_AL0_HID_REPORT_DESC_SIZE] = {
    0x00,
    0xC0    /* END_COLLECTION */
};




/*!< USBD HID REPORT 1 Descriptor */
const unsigned char usbd_hid_1_report_descriptor[USBD_IF1_AL0_HID_REPORT_DESC_SIZE] = {
    0x00,
    0xC0    /* END_COLLECTION */
};



/*******************************************************END OF FILE*************/
