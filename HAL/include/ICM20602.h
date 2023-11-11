/********************************** (C) COPYRIGHT *******************************
 * File Name          : ICM20602.h
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/09/29
 * Description        : ICM20602 sensor driver for CH582M
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL 3.0
 *******************************************************************************/

#ifndef _ICM_20602_H
#define _ICM_20602_H

#include "CH58x_common.h"

typedef struct {
    float acc_x;
    float acc_y;
    float acc_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    short raw_acc_x;
    short raw_acc_y;
    short raw_acc_z;
    short raw_gyro_x;
    short raw_gyro_y;
    short raw_gyro_z;
    short raw_gyro_x_offset;
    short raw_gyro_y_offset;
    short raw_gyro_z_offset;
}icm20602_param_t;

typedef struct {
    float q0;
    float q1;
    float q2;
    float q3;
}quater_param_t;

typedef struct {
    float pitch;
    float roll;
    float yaw;
}euler_param_t;

#define ICM20602_GPIO_(x)               GPIOA_ ## x
#define ICM20602_CS_PIN                 GPIO_Pin_12
#define ICM20602_SCK_PIN                GPIO_Pin_13
#define ICM20602_MOSI_PIN               GPIO_Pin_14
#define ICM20602_MISO_PIN               GPIO_Pin_15

#define ICM20602_CS_H()                 ICM20602_GPIO_(SetBits)(ICM20602_CS_PIN)
#define ICM20602_CS_L()                 ICM20602_GPIO_(ResetBits)(ICM20602_CS_PIN)

#define ICM20602_SPI_W                  0x00
#define ICM20602_SPI_R                  0x80

#define ICM20602_XG_OFFS_TC_H           0x04
#define ICM20602_XG_OFFS_TC_L           0x05
#define ICM20602_YG_OFFS_TC_H           0x07
#define ICM20602_YG_OFFS_TC_L           0x08
#define ICM20602_ZG_OFFS_TC_H           0x0A
#define ICM20602_ZG_OFFS_TC_L           0x0B
#define ICM20602_SELF_TEST_X_ACCEL      0x0D
#define ICM20602_SELF_TEST_Y_ACCEL      0x0E
#define ICM20602_SELF_TEST_Z_ACCEL      0x0F
#define ICM20602_XG_OFFS_USRH           0x13
#define ICM20602_XG_OFFS_USRL           0x14
#define ICM20602_YG_OFFS_USRH           0x15
#define ICM20602_YG_OFFS_USRL           0x16
#define ICM20602_ZG_OFFS_USRH           0x17
#define ICM20602_ZG_OFFS_USRL           0x18
#define ICM20602_SMPLRT_DIV             0x19
#define ICM20602_CONFIG                 0x1A
#define ICM20602_GYRO_CONFIG            0x1B
#define ICM20602_ACCEL_CONFIG           0x1C
#define ICM20602_ACCEL_CONFIG_2         0x1D
#define ICM20602_LP_MODE_CFG            0x1E
#define ICM20602_ACCEL_WOM_X_THR        0x20
#define ICM20602_ACCEL_WOM_Y_THR        0x21
#define ICM20602_ACCEL_WOM_Z_THR        0x22
#define ICM20602_FIFO_EN                0x23
#define ICM20602_FSYNC_INT              0x36
#define ICM20602_INT_PIN_CFG            0x37
#define ICM20602_INT_ENABLE             0x38
#define ICM20602_FIFO_WM_INT_STATUS     0x39
#define ICM20602_INT_STATUS             0x3A
#define ICM20602_ACCEL_XOUT_H           0x3B
#define ICM20602_ACCEL_XOUT_L           0x3C
#define ICM20602_ACCEL_YOUT_H           0x3D
#define ICM20602_ACCEL_YOUT_L           0x3E
#define ICM20602_ACCEL_ZOUT_H           0x3F
#define ICM20602_ACCEL_ZOUT_L           0x40
#define ICM20602_TEMP_OUT_H             0x41
#define ICM20602_TEMP_OUT_L             0x42
#define ICM20602_GYRO_XOUT_H            0x43
#define ICM20602_GYRO_XOUT_L            0x44
#define ICM20602_GYRO_YOUT_H            0x45
#define ICM20602_GYRO_YOUT_L            0x46
#define ICM20602_GYRO_ZOUT_H            0x47
#define ICM20602_GYRO_ZOUT_L            0x48
#define ICM20602_SELF_TEST_X_GYRO       0x50
#define ICM20602_SELF_TEST_Y_GYRO       0x51
#define ICM20602_SELF_TEST_Z_GYRO       0x52
#define ICM20602_FIFO_WM_TH1            0x60
#define ICM20602_FIFO_WM_TH2            0x61
#define ICM20602_SIGNAL_PATH_RESET      0x68
#define ICM20602_ACCEL_INTEL_CTRL       0x69
#define ICM20602_USER_CTRL              0x6A
#define ICM20602_PWR_MGMT_1             0x6B
#define ICM20602_PWR_MGMT_2             0x6C
#define ICM20602_I2C_IF                 0x70
#define ICM20602_FIFO_COUNTH            0x72
#define ICM20602_FIFO_COUNTL            0x73
#define ICM20602_FIFO_R_W               0x74
#define ICM20602_WHO_AM_I               0x75
#define ICM20602_XA_OFFSET_H            0x77
#define ICM20602_XA_OFFSET_L            0x78
#define ICM20602_YA_OFFSET_H            0x7A
#define ICM20602_YA_OFFSET_L            0x7B
#define ICM20602_ZA_OFFSET_H            0x7D
#define ICM20602_ZA_OFFSET_L            0x7E

extern quater_param_t Q_info;
extern euler_param_t eulerAngle;
extern icm20602_param_t icm20602_data;

void ICM20602_get_acc(void);
void ICM20602_get_gyro(void);
void ICM20602_gyro_offset_init(void);
void ICM20602_get_orign_data(void);
void ICM20602_AHRS_update(icm20602_param_t* icm);
void ICM20602_euler_angle_update(void);
void ICM20602_data_update(void);
void ICM20602_init(void);

#endif
