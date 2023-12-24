/********************************** (C) COPYRIGHT *******************************
 * File Name          : tp78_via.c
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/4/28
 * Description        : TP78的VIA支持库
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GNU GENERAL PUBLIC LICENSE v2.0 or later
 *******************************************************************************/

#include "tp78_joyticks_via.h"
#include "HAL.h"

__attribute__((aligned(EEPROM_BLOCK_SIZE))) flash_data_t via_config = {
        .pitch_sensitivity = 1.0,
        .roll_sensitivity = 1.0,
        .roll_mid = 180.0,
        .sw_l_x_settings = { .mirror_settings = TRUE, .mapping_settings = MAP_TO_X_AXIS },
        .sw_l_y_settings = { .mapping_settings = MAP_TO_Y_AXIS },
        .sw_r_x_settings = { .mirror_settings = TRUE, .mapping_settings = MAP_TO_Z_AXIS },
        .sw_r_y_settings = { .mapping_settings = MAP_TO_RZ_AXIS },
        .sw_l_x_settings_L2 = { .mirror_settings = TRUE, .mapping_settings = MAP_TO_X_AXIS },
        .sw_l_y_settings_L2 = { .mapping_settings = MAP_TO_Y_AXIS },
        .sw_r_x_settings_L2 = { .mirror_settings = TRUE, .mapping_settings = MAP_TO_Z_AXIS },
        .sw_r_y_settings_L2 = { .mapping_settings = MAP_TO_RZ_AXIS },
        .gyro_trigger_key = HAL_KEY_SW_MR,
        .gyro_key_enable = TRUE,
        .gyro_x_settings = { .mapping_settings = MAP_TO_Z_AXIS },
        .gyro_y_settings = { .mapping_settings = MAP_TO_RZ_AXIS },
        .select_layer_key = HAL_KEY_SW_ML,
        .button_settings[0] = { .mapping_settings = MAP_TO_BUTTON_SW_1 },
        .button_settings[1] = { .mapping_settings = MAP_TO_BUTTON_SW_2 },
        .button_settings[2] = { .mapping_settings = MAP_TO_BUTTON_SW_3 },
        .button_settings[3] = { .mapping_settings = MAP_TO_BUTTON_SW_4 },
        .button_settings[4] = { .mapping_settings = MAP_TO_BUTTON_SW_L },
        .button_settings[5] = { .mapping_settings = MAP_TO_BUTTON_SW_R },
        .button_settings[6] = { .mapping_settings = MAP_TO_BUTTON_SW_ZL },
        .button_settings[7] = { .mapping_settings = MAP_TO_BUTTON_SW_ZR },
        .button_settings[8] = { .mapping_settings = MAP_TO_BUTTON_SW_ML },
        .button_settings[9] = { .mapping_settings = MAP_TO_BUTTON_SW_MR },
        .button_settings_L2[0] = { .mapping_settings = MAP_TO_D_PAD_1 },
        .button_settings_L2[1] = { .mapping_settings = MAP_TO_D_PAD_2 },
        .button_settings_L2[2] = { .mapping_settings = MAP_TO_D_PAD_3 },
        .button_settings_L2[3] = { .mapping_settings = MAP_TO_D_PAD_4 },
};

/*******************************************************************************
 * Function Name  : via_set_default_config
 * Description    : via设置默认配置
 * Input          : None
 * Return         : None
 *******************************************************************************/
void via_set_default_config(void)
{
    memset(&via_config, 0, sizeof(via_config));
    via_config.pitch_sensitivity = 1.0;
    via_config.roll_sensitivity = 1.0;
    via_config.roll_mid = 180.0;
    via_config.sw_l_x_settings.mirror_settings = TRUE;
    via_config.sw_l_x_settings.mapping_settings = MAP_TO_X_AXIS;
    via_config.sw_l_y_settings.mapping_settings = MAP_TO_Y_AXIS;
    via_config.sw_r_x_settings.mirror_settings = TRUE;
    via_config.sw_r_x_settings.mapping_settings = MAP_TO_Z_AXIS;
    via_config.sw_r_y_settings.mapping_settings = MAP_TO_RZ_AXIS;
    via_config.sw_l_x_settings_L2.mirror_settings = TRUE;
    via_config.sw_l_x_settings_L2.mapping_settings = MAP_TO_X_AXIS;
    via_config.sw_l_y_settings_L2.mapping_settings = MAP_TO_Y_AXIS;
    via_config.sw_r_x_settings_L2.mirror_settings = TRUE;
    via_config.sw_r_x_settings_L2.mapping_settings = MAP_TO_Z_AXIS;
    via_config.sw_r_y_settings_L2.mapping_settings = MAP_TO_RZ_AXIS;
    via_config.gyro_trigger_key = HAL_KEY_SW_MR;
    via_config.gyro_key_enable = TRUE;
    via_config.gyro_x_settings.mapping_settings = MAP_TO_Z_AXIS;
    via_config.gyro_y_settings.mapping_settings = MAP_TO_RZ_AXIS;
    via_config.select_layer_key = HAL_KEY_SW_ML;
    via_config.button_settings[0].mapping_settings = MAP_TO_BUTTON_SW_1;
    via_config.button_settings[1].mapping_settings = MAP_TO_BUTTON_SW_2;
    via_config.button_settings[2].mapping_settings = MAP_TO_BUTTON_SW_3;
    via_config.button_settings[3].mapping_settings = MAP_TO_BUTTON_SW_4;
    via_config.button_settings[4].mapping_settings = MAP_TO_BUTTON_SW_L;
    via_config.button_settings[5].mapping_settings = MAP_TO_BUTTON_SW_R;
    via_config.button_settings[6].mapping_settings = MAP_TO_BUTTON_SW_ZL;
    via_config.button_settings[7].mapping_settings = MAP_TO_BUTTON_SW_ZR;
    via_config.button_settings[8].mapping_settings = MAP_TO_BUTTON_SW_ML;
    via_config.button_settings[9].mapping_settings = MAP_TO_BUTTON_SW_MR;
    via_config.button_settings_L2[0].mapping_settings = MAP_TO_D_PAD_1;
    via_config.button_settings_L2[1].mapping_settings = MAP_TO_D_PAD_2;
    via_config.button_settings_L2[2].mapping_settings = MAP_TO_D_PAD_3;
    via_config.button_settings_L2[3].mapping_settings = MAP_TO_D_PAD_4;
}

/*******************************************************************************
 * Function Name  : via_custom_value_command
 * Description    : via客制化命令
 * Input          : *data - raw data, len - 数据长度
 * Return         : None
 *******************************************************************************/
static void via_custom_value_command(uint8_t *data, uint8_t len)
{
  uint8_t *command_id = &data[0];
  uint8_t *command_channel = &data[1];
  uint8_t *command_value = &data[2];

  switch (*command_channel) {
    case 0: { // switch configs
      switch (*command_value) {
        case id_adc_max_value_0 ... id_adc_max_value_3: { // id_adc_max_value
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.adc_max_val[*command_value - id_adc_max_value_0] = data[4] | (data[3] << 8);
          } else {
              data[4] = via_config.adc_max_val[*command_value - id_adc_max_value_0] & 0xFF;
              data[3] = (via_config.adc_max_val[*command_value - id_adc_max_value_0] >> 8) & 0xFF;
          }
          break;
        }
        case id_adc_min_value_0 ... id_adc_min_value_3: { // id_adc_min_value
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.adc_min_val[*command_value - id_adc_min_value_0] = data[4] | (data[3] << 8);
          } else {
              data[4] = via_config.adc_min_val[*command_value - id_adc_min_value_0] & 0xFF;
              data[3] = (via_config.adc_min_val[*command_value - id_adc_min_value_0] >> 8) & 0xFF;
          }
          break;
        }
        case id_adc_deadzone_h_0 ... id_adc_deadzone_h_3: { // id_adc_deadzone_h
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.adc_deadzone_h[*command_value - id_adc_deadzone_h_0] = data[4] | (data[3] << 8);
          } else {
              data[4] = via_config.adc_deadzone_h[*command_value - id_adc_deadzone_h_0] & 0xFF;
              data[3] = (via_config.adc_deadzone_h[*command_value - id_adc_deadzone_h_0] >> 8) & 0xFF;
          }
          break;
        }
        case id_adc_deadzone_l_0 ... id_adc_deadzone_l_3: { // id_adc_deadzone_l
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.adc_deadzone_l[*command_value - id_adc_deadzone_l_0] = data[4] | (data[3] << 8);
          } else {
              data[4] = via_config.adc_deadzone_l[*command_value - id_adc_deadzone_l_0] & 0xFF;
              data[3] = (via_config.adc_deadzone_l[*command_value - id_adc_deadzone_l_0] >> 8) & 0xFF;
          }
          break;
        }
        case id_sw_l_x_mirror ... id_sw_r_y_mapping: {
          uint8_t dif = *command_value - id_sw_l_x_mirror;
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              if (dif & 1)  // mapping
                  via_config.sw_settings[dif / 2].mapping_settings = data[3];
              else  // mirror
                  via_config.sw_settings[dif / 2].mirror_settings = data[3];
          } else {
              if (dif & 1)  // mapping
                  data[3] = via_config.sw_settings[dif / 2].mapping_settings;
              else  // mirror
                  data[3] = via_config.sw_settings[dif / 2].mirror_settings;
          }
          break;
        }
        case id_sw_l_x_mirror_L2 ... id_sw_r_y_mapping_L2: {
          uint8_t dif = *command_value - id_sw_l_x_mirror_L2;
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              if (dif & 1)  // mapping
                  via_config.sw_settings_L2[dif / 2].mapping_settings = data[3];
              else  // mirror
                  via_config.sw_settings_L2[dif / 2].mirror_settings = data[3];
          } else {
              if (dif & 1)  // mapping
                  data[3] = via_config.sw_settings_L2[dif / 2].mapping_settings;
              else  // mirror
                  data[3] = via_config.sw_settings_L2[dif / 2].mirror_settings;
          }
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    case 1: { // gyro configs
      switch (*command_value) {
        case id_pitch_sensitivity: { // id_pitch_sensitivity
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.pitch_sensitivity = (float)(data[4] | (data[3] << 8)) / 100;
          } else {
              data[4] = (uint16_t)(via_config.pitch_sensitivity * 100) & 0xFF;
              data[3] = ((uint16_t)(via_config.pitch_sensitivity * 100) >> 8) & 0xFF;
          }
          break;
        }
        case id_roll_sensitivity: { // id_roll_sensitivity
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.roll_sensitivity = (float)(data[4] | (data[3] << 8)) / 100;
          } else {
              data[4] = (uint16_t)(via_config.roll_sensitivity * 100) & 0xFF;
              data[3] = ((uint16_t)(via_config.roll_sensitivity * 100) >> 8) & 0xFF;
          }
          break;
        }
        case id_pitch_mid: { // id_pitch_mid
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.pitch_mid = (float)(data[4] | (data[3] << 8)) / 100 - 180.0;
          } else {
              data[4] = (uint16_t)((via_config.pitch_mid + 180.0) * 100) & 0xFF;
              data[3] = ((uint16_t)((via_config.pitch_mid + 180.0) * 100) >> 8) & 0xFF;
          }
          break;
        }
        case id_roll_mid: { // id_roll_mid
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.roll_mid = (float)(data[4] | (data[3] << 8)) / 100 - 180.0;
          } else {
              data[4] = (uint16_t)((via_config.roll_mid + 180.0) * 100) & 0xFF;
              data[3] = ((uint16_t)((via_config.roll_mid + 180.0) * 100) >> 8) & 0xFF;
          }
          break;
        }
        case id_gyro_key_enable: { // id_gyro_key_enable
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.gyro_key_enable = data[3];
          } else {
              data[3] = via_config.gyro_key_enable;
          }
          break;
        }
        case id_gyro_trigger_key: { // id_gyro_trigger_key
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.gyro_trigger_key = (1 << data[3]);
          } else {
              for (uint8_t i = 1; i < 16; i++) {
                  if (via_config.gyro_trigger_key & (1 << i)) {
                      data[3] = i;
                      break;
                  }
              }
          }
          break;
        }
        case id_gyro_x_mirror ... id_gyro_y_mapping: {
          uint8_t dif = *command_value - id_gyro_x_mirror;
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              if (dif & 1)  // mapping
                  via_config.gyro_settings[dif / 2].mapping_settings = data[3];
              else  // mirror
                  via_config.gyro_settings[dif / 2].mirror_settings = data[3];
          } else {
              if (dif & 1)  // mapping
                  data[3] = via_config.gyro_settings[dif / 2].mapping_settings;
              else  // mirror
                  data[3] = via_config.gyro_settings[dif / 2].mirror_settings;
          }
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    case 2: { // button configs
      switch (*command_value) {
        case id_select_layer_key: {
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              via_config.gyro_trigger_key = (1 << data[3]);
          } else {
              for (uint8_t i = 1; i < 16; i++) {
                  if (via_config.gyro_trigger_key & (1 << i)) {
                      data[3] = i;
                      break;
                  }
              }
          }
          break;
        }
        case id_first_button_x_mirror ... id_last_button_y_mapping: {
          uint8_t dif = *command_value - id_first_button_x_mirror;
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              if (dif & 1)  // mapping
                  via_config.button_settings[dif / 2].mapping_settings = data[3];
              else  // mirror
                  via_config.button_settings[dif / 2].mirror_settings = data[3];
          } else {
              if (dif & 1)  // mapping
                  data[3] = via_config.button_settings[dif / 2].mapping_settings;
              else  // mirror
                  data[3] = via_config.button_settings[dif / 2].mirror_settings;
          }
          break;
        }
        case id_first_button_x_mirror_L2 ... id_last_button_y_mapping_L2: {
          uint8_t dif = *command_value - id_first_button_x_mirror_L2;
          if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
              if (dif & 1)  // mapping
                  via_config.button_settings_L2[dif / 2].mapping_settings = data[3];
              else  // mirror
                  via_config.button_settings_L2[dif / 2].mirror_settings = data[3];
          } else {
              if (dif & 1)  // mapping
                  data[3] = via_config.button_settings_L2[dif / 2].mapping_settings;
              else  // mirror
                  data[3] = via_config.button_settings_L2[dif / 2].mirror_settings;
          }
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    default: {
      break;
    }
  }

  if (*command_id == VIA_ID_CUSTOM_SET_VALUE) {
      SWITCH_data_read_fromVIA();
  }
}

/*******************************************************************************
 * Function Name  : via_data_processing
 * Description    : 处理USB接收的via raw data
 * Input          : *data - raw data, len - 数据长度
 * Return         : None
 *******************************************************************************/
void via_data_processing(uint8_t *data, uint8_t len)
{
  uint8_t *command_id = &data[0];
  uint8_t *command_data = &data[1];

  /* attention: data is transfered with big end format */
  switch (*command_id) {
    case (uint8_t)VIA_ID_GET_PROTOCOL_VERSION:
        command_data[0] = VIA_PROTOCOL_VERSION >> 8;
        command_data[1] = VIA_PROTOCOL_VERSION & 0xFF;
        break;
    case (uint8_t)VIA_ID_GET_KEYBOARD_VALUE:
        switch (command_data[0]) {
          case (uint8_t)VIA_ID_UPTIME: {
              uint32_t sec2 = R16_RTC_CNT_2S;
              uint16_t t32k = R16_RTC_CNT_32K;
              *(uint32_t*)command_data = (sec2 << 1) + ((t32k < 0x8000) ? 0 : 1);
              break;
          }
          case (uint8_t)VIA_ID_LAYOUT_OPTIONS: {
              /* unsupport this command */
              break;
          }
          case (uint8_t)VIA_ID_SWITCH_MATRIX_STATE: {
              /* report KeyMatrix */
              break;
          }
          case (uint8_t)VIA_ID_FIRMWARE_VERSION: {
              uint32_t value = VIA_FIRMWARE_VERSION;
              command_data[1] = (value >> 24) & 0xFF;
              command_data[2] = (value >> 16) & 0xFF;
              command_data[3] = (value >> 8) & 0xFF;
              command_data[4] = value & 0xFF;
              break;
          }
          default: {
              *command_id = (uint32_t)VIA_ID_UNHANDLED;
              break;
          }
        }
        break;
    case (uint8_t)VIA_ID_SET_KEYBOARD_VALUE:
        switch (command_data[0]) {
          case (uint8_t)VIA_ID_LAYOUT_OPTIONS: {
              // write keyboard layout
              break;
          }
          case (uint8_t)VIA_ID_DEVICE_INDICATION: {
              break;
          }
          default: {
              *command_id = VIA_ID_UNHANDLED;
              break;
          }
        }
        break;
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_GET_KEYCODE: {
        /********* format *********
          command_data[0] = layer
          command_data[1] = row
          command_data[2] = col
        **************************/
        command_data[3] = 0;
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_SET_KEYCODE: {
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_RESET: {
        break;
    }
    case (uint8_t)VIA_ID_CUSTOM_SET_VALUE:
    case (uint8_t)VIA_ID_CUSTOM_GET_VALUE: {
        via_custom_value_command(data, len);
        break;
    }
    case (uint8_t)VIA_ID_CUSTOM_SAVE: {
        via_data_write();
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_MACRO_GET_COUNT: {
        command_data[0] = 0;
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_MACRO_GET_BUFFER_SIZE: {
        command_data[0] = command_data[1] = 0;
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_MACRO_GET_BUFFER: {
        /************* format *************
          command_data[0] = offset HSB
          command_data[1] = offset LSB
          command_data[2] = size
        **********************************/
        /* TP78 unsupport this command */
        command_data[0] = command_data[1] = command_data[2] = 0;
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_MACRO_SET_BUFFER: {
        /************* format *************
          command_data[0] = offset HSB
          command_data[1] = offset LSB
          command_data[2] = size
        **********************************/
        /* TP78 unsupport this command */
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_MACRO_RESET: {
        /* TP78 unsupport this command */
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_GET_LAYER_COUNT: {
        command_data[0] = 1;  // layer
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_GET_BUFFER: {
        /* via is used uint16 to record keymap */
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_SET_BUFFER: {
        /* via is used uint16 to record keymap */
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_GET_ENCODER: {
        break;
    }
    case (uint8_t)VIA_ID_DYNAMIC_KEYMAP_SET_ENCODER: {
        break;
    }
    default: {
        *command_id = VIA_ID_UNHANDLED;
        break;
    }
  }
}

/*******************************************************************************
 * Function Name  : via_data_read
 * Description    : 从flash读取via配置数据
 * Input          : None
 * Return         : None
 *******************************************************************************/
void via_data_read( void )
{
    EEPROM_READ(VIA_DATA_FLASH_ADDR, &via_config, sizeof(via_config));
}

/*******************************************************************************
 * Function Name  : via_data_write
 * Description    : 将via配置数据写入flash
 * Input          : None
 * Return         : None
 *******************************************************************************/
void via_data_write( void )
{
    uint32_t tmp;

    SYS_DisableAllIrq(&tmp);
    EEPROM_ERASE(VIA_DATA_FLASH_ADDR, EEPROM_BLOCK_SIZE);
    EEPROM_WRITE(VIA_DATA_FLASH_ADDR, &via_config, sizeof(via_config));
    SYS_RecoverIrq(tmp);
}
