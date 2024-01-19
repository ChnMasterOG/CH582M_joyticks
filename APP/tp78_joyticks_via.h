/********************************** (C) COPYRIGHT *******************************
 * File Name          : tp78_via.h
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/4/28
 * Description        : TP78的VIA支持库
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GNU GENERAL PUBLIC LICENSE v2.0 or later
 *******************************************************************************/

#ifndef TP78_VIA_H
#define TP78_VIA_H

#include "CH58x_common.h"

#define VIA_FIRMWARE_VERSION        0x00000000  // 4 bytes
#define VIA_PROTOCOL_VERSION        0x000C  // 2 bytes

#define VIA_DATA_FLASH_ADDR         0x0   // dataflash

#define MAP_TO_NONE                 0
#define MAP_TO_X_AXIS               1
#define MAP_TO_Y_AXIS               2
#define MAP_TO_Z_AXIS               3
#define MAP_TO_RZ_AXIS              4
#define MAP_TO_RX_AXIS              5
#define MAP_TO_RY_AXIS              6
#define MAP_TO_D_PAD_1              7
#define MAP_TO_D_PAD_2              8
#define MAP_TO_D_PAD_3              9
#define MAP_TO_D_PAD_4              10
#define MAP_TO_BUTTON_SW_1          11  // square
#define MAP_TO_BUTTON_SW_2          12  // fork
#define MAP_TO_BUTTON_SW_3          13  // circle
#define MAP_TO_BUTTON_SW_4          14  // triangle
#define MAP_TO_BUTTON_SW_L          15
#define MAP_TO_BUTTON_SW_R          16
#define MAP_TO_BUTTON_SW_ZL         17
#define MAP_TO_BUTTON_SW_ZR         18
#define MAP_TO_BUTTON_SW_ML         19
#define MAP_TO_BUTTON_SW_MR         20
#define MAP_TO_BUTTON_SW_EX1        21
#define MAP_TO_BUTTON_SW_EX2        22
#define MAP_TO_BUTTON_SW_EX3        23
#define MAP_TO_BUTTON_SW_EX4        24
#define MAP_TO_BUTTON_SW_EX5        25
#define MAP_TO_BUTTON_SW_EX6        16

#define id_adc_max_value_0          1
#define id_adc_max_value_1          2
#define id_adc_max_value_2          3
#define id_adc_max_value_3          4
#define id_adc_min_value_0          5
#define id_adc_min_value_1          6
#define id_adc_min_value_2          7
#define id_adc_min_value_3          8
#define id_adc_deadzone_h_0         9
#define id_adc_deadzone_h_1         10
#define id_adc_deadzone_h_2         11
#define id_adc_deadzone_h_3         12
#define id_adc_deadzone_l_0         13
#define id_adc_deadzone_l_1         14
#define id_adc_deadzone_l_2         15
#define id_adc_deadzone_l_3         16
#define id_sw_l_x_mirror            17
#define id_sw_l_x_mapping           18
#define id_sw_l_y_mirror            19
#define id_sw_l_y_mapping           20
#define id_sw_r_x_mirror            21
#define id_sw_r_x_mapping           22
#define id_sw_r_y_mirror            23
#define id_sw_r_y_mapping           24
#define id_sw_l_x_mirror_L2         25
#define id_sw_l_x_mapping_L2        26
#define id_sw_l_y_mirror_L2         27
#define id_sw_l_y_mapping_L2        28
#define id_sw_r_x_mirror_L2         29
#define id_sw_r_x_mapping_L2        30
#define id_sw_r_y_mirror_L2         31
#define id_sw_r_y_mapping_L2        32

#define id_pitch_sensitivity        1
#define id_roll_sensitivity         2
#define id_pitch_mid                3
#define id_roll_mid                 4
#define id_gyro_key_enable          5
#define id_gyro_trigger_key         6
#define id_gyro_x_mirror            7
#define id_gyro_x_mapping           8
#define id_gyro_y_mirror            9
#define id_gyro_y_mapping           10

#define id_select_layer_key         1
#define id_first_button_x_mirror    2
#define id_last_button_y_mapping    21
#define id_first_button_x_mirror_L2 22
#define id_last_button_y_mapping_L2 41

#define id_backlight_enable         1

typedef enum {
    VIA_ID_GET_PROTOCOL_VERSION = 0x01, // always 0x01
    VIA_ID_GET_KEYBOARD_VALUE = 0x02,
    VIA_ID_SET_KEYBOARD_VALUE = 0x03,
    VIA_ID_DYNAMIC_KEYMAP_GET_KEYCODE = 0x04,
    VIA_ID_DYNAMIC_KEYMAP_SET_KEYCODE = 0x05,
    VIA_ID_DYNAMIC_KEYMAP_RESET = 0x06,
    VIA_ID_CUSTOM_SET_VALUE = 0x07,
    VIA_ID_CUSTOM_GET_VALUE = 0x08,
    VIA_ID_CUSTOM_SAVE = 0x09,
    VIA_ID_EEPROM_RESET = 0x0A,
    VIA_ID_BOOTLOADER_JUMP = 0x0B,
    VIA_ID_DYNAMIC_KEYMAP_MACRO_GET_COUNT = 0x0C,
    VIA_ID_DYNAMIC_KEYMAP_MACRO_GET_BUFFER_SIZE = 0x0D,
    VIA_ID_DYNAMIC_KEYMAP_MACRO_GET_BUFFER = 0x0E,
    VIA_ID_DYNAMIC_KEYMAP_MACRO_SET_BUFFER = 0x0F,
    VIA_ID_DYNAMIC_KEYMAP_MACRO_RESET = 0x10,
    VIA_ID_DYNAMIC_KEYMAP_GET_LAYER_COUNT = 0x11,
    VIA_ID_DYNAMIC_KEYMAP_GET_BUFFER = 0x12,
    VIA_ID_DYNAMIC_KEYMAP_SET_BUFFER = 0x13,
    VIA_ID_DYNAMIC_KEYMAP_GET_ENCODER = 0x14,
    VIA_ID_DYNAMIC_KEYMAP_SET_ENCODER = 0x15,
    VIA_ID_UNHANDLED = 0xFF,
}via_command_id;

typedef enum {
    VIA_ID_UPTIME = 0x01,
    VIA_ID_LAYOUT_OPTIONS = 0x02,
    VIA_ID_SWITCH_MATRIX_STATE = 0x03,
    VIA_ID_FIRMWARE_VERSION = 0x04,
    VIA_ID_DEVICE_INDICATION = 0x05,
}via_keyboard_value_id;

typedef enum {
    VIA_ID_CUSTOM_CHANNEL = 0x00,
    VIA_ID_BACKLIGHT_CHANNEL = 0x01,
    VIA_ID_RGBLIGHT_CHANNEL = 0x02,
    VIA_ID_RGB_MATRIX_CHANNEL = 0x03,
    VIA_ID_AUDIO_CHANNEL = 0x04,
}via_channel_id;

typedef enum {
    VIA_ID_BACKLIGHT_BRIGHTNESS = 0x01,
    VIA_ID_BACKLIGHT_EFFECT = 0x02,
}via_backlight_value;

typedef enum {
    VIA_ID_RGBLIGHT_BRIGHTNESS = 0x01,
    VIA_ID_RGBLIGHT_EFFECT = 0x02,
    VIA_ID_RGBLIGHT_EFFECT_SPEED = 0x03,
    VIA_ID_RGBLIGHT_COLOR = 0x04,
}via_rgblight_value;

typedef enum {
    VIA_ID_RGB_MATRIX_BRIGHTNESS = 0x01,
    VIA_ID_RGB_MATRIX_EFFECT = 0x02,
    VIA_ID_RGB_MATRIX_EFFECT_SPEED = 0x03,
    VIA_ID_RGB_MATRIX_COLOR = 0x04,
}via_rgb_matrix_value;

typedef enum {
    VIA_ID_AUDIO_ENABLE = 0x01,
    VIA_ID_AUDIO_CLICKY_ENABLE = 0x02,
}via_audio_value;

typedef struct {
    uint8_t mapping_settings;
    uint8_t mirror_settings;
}component_settings_t;

typedef struct {
    uint16_t adc_max_val[4];
    uint16_t adc_min_val[4];
    uint16_t adc_deadzone_h[4];
    uint16_t adc_deadzone_l[4];
    union {
        struct {
            component_settings_t sw_l_x_settings;
            component_settings_t sw_l_y_settings;
            component_settings_t sw_r_x_settings;
            component_settings_t sw_r_y_settings;
        };
        component_settings_t sw_settings[4];
    };
    union {
        struct {
            component_settings_t sw_l_x_settings_L2;
            component_settings_t sw_l_y_settings_L2;
            component_settings_t sw_r_x_settings_L2;
            component_settings_t sw_r_y_settings_L2;
        };
        component_settings_t sw_settings_L2[4];
    };
    float pitch_sensitivity;
    float roll_sensitivity;
    float pitch_mid;
    float roll_mid;
    uint8_t gyro_key_enable;
    uint16_t gyro_trigger_key;
    union {
        struct {
            component_settings_t gyro_x_settings;
            component_settings_t gyro_y_settings;
        };
        component_settings_t gyro_settings[4];
    };
    uint16_t select_layer_key;
    component_settings_t button_settings[10];
    component_settings_t button_settings_L2[10];
    uint16_t backlight_enable;
}flash_data_t;

extern flash_data_t via_config;

void via_set_default_config(void);
void via_data_processing(uint8_t *data, uint8_t len);
void via_data_read( void );
void via_data_write( void );

#endif
