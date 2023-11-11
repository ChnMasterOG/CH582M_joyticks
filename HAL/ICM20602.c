/********************************** (C) COPYRIGHT *******************************
 * File Name          : ICM20602.c
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/09/29
 * Description        : ICM20602 sensor driver for CH582M
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL 3.0
 *******************************************************************************/

#include <math.h>
#include "ICM20602.h"

#ifndef PI
#define PI          3.1415927
#endif
#define delta_T     0.001f  // sample rate: 1kHz

float I_ex, I_ey, I_ez; // error integral
quater_param_t Q_info = {1, 0, 0, 0};   // quater number
euler_param_t eulerAngle;   // euler angle
icm20602_param_t icm20602_data;
float icm_kp= 0.17; // convergence rate proportional gain of accelerometer
float icm_ki= 0.004;    // Integral gain of gyroscope convergence rate

static float MySqrt(float number)
{
    long i;
    float x, y;
    const float f = 1.5F;
    x = number * 0.5F;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );
    y = * ( float * ) &i;
    y = y * ( f - ( x * y * y ) );
    y = y * ( f - ( x * y * y ) );
    return number * y;
}

static float InvSqrt(float number)
{
    return 1.0f / MySqrt(number);
}

void ICM20602_write_byte(uint8_t reg, uint8_t val)
{
    ICM20602_CS_L();
    SPI0_MasterSendByte( reg );
    SPI0_MasterSendByte( val );
    ICM20602_CS_H();
}

uint8_t ICM20602_read_byte(uint8_t reg)
{
    uint8_t dat;

    ICM20602_CS_L();
    SPI0_MasterSendByte( reg | ICM20602_SPI_R );
    dat = SPI0_MasterRecvByte();
    ICM20602_CS_H();

    return dat;
}

void ICM20602_read_bytes(uint8_t reg, uint8_t *val, uint32_t len)
{
    ICM20602_CS_L();
    SPI0_MasterSendByte( reg | ICM20602_SPI_R );
    while (len--)
        *val++ = SPI0_MasterRecvByte();
    ICM20602_CS_H();
}

void ICM20602_get_acc(void)
{
    uint8_t dat[6];

    ICM20602_read_bytes(ICM20602_ACCEL_XOUT_H, dat, 6);
    icm20602_data.raw_acc_x = (short)((uint16_t)dat[0] << 8 | dat[1]);
    icm20602_data.raw_acc_y = (short)((uint16_t)dat[2] << 8 | dat[3]);
    icm20602_data.raw_acc_z = (short)((uint16_t)dat[4] << 8 | dat[5]);
}

void ICM20602_get_gyro(void)
{
    uint8_t dat[6];

    ICM20602_read_bytes(ICM20602_GYRO_XOUT_H, dat, 6);
    icm20602_data.raw_gyro_x = (short)((uint16_t)dat[0] << 8 | dat[1]);
    icm20602_data.raw_gyro_y = (short)((uint16_t)dat[2] << 8 | dat[3]);
    icm20602_data.raw_gyro_z = (short)((uint16_t)dat[4] << 8 | dat[5]);
}

void ICM20602_gyro_offset_init(void)
{
    int dat[3] = { 0 };
    uint32_t i;

    for (i = 0; i < 100; i++) {
        ICM20602_get_gyro();
        dat[0] += icm20602_data.raw_gyro_x;
        dat[1] += icm20602_data.raw_gyro_y;
        dat[2] += icm20602_data.raw_gyro_z;
        DelayMs(5);
    }
    icm20602_data.raw_gyro_x_offset = dat[0] / 100;
    icm20602_data.raw_gyro_y_offset = dat[1] / 100;
    icm20602_data.raw_gyro_z_offset = dat[2] / 100;
}

void ICM20602_get_orign_data(void)
{
    const float alpha = 0.3;    // low pass filter alpha

    /* unit: g */
    icm20602_data.acc_x = (((float)icm20602_data.raw_acc_x) * alpha) / 4096 + icm20602_data.acc_x * (1 - alpha);
    icm20602_data.acc_y = (((float)icm20602_data.raw_acc_y) * alpha) / 4096 + icm20602_data.acc_y * (1 - alpha);
    icm20602_data.acc_z = (((float)icm20602_data.raw_acc_z) * alpha) / 4096 + icm20602_data.acc_z * (1 - alpha);

    /* unit: rad/s */
    icm20602_data.gyro_x = (float)(icm20602_data.raw_gyro_x - icm20602_data.raw_gyro_x_offset) * PI / 180 / 16.4f;
    icm20602_data.gyro_y = (float)(icm20602_data.raw_gyro_y - icm20602_data.raw_gyro_y_offset) * PI / 180 / 16.4f;
    icm20602_data.gyro_z = (float)(icm20602_data.raw_gyro_z - icm20602_data.raw_gyro_z_offset) * PI / 180 / 16.4f;
}

void ICM20602_AHRS_update(icm20602_param_t* icm)
{
    float halfT = 0.5 * delta_T;
    float vx, vy, vz;
    float ex, ey, ez;

    float q0 = Q_info.q0;
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;

    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;

    float norm;

    if (icm->acc_x * icm->acc_y * icm->acc_z == 0)
        return;

    norm = InvSqrt(icm->acc_x * icm->acc_x + icm->acc_y * icm->acc_y + icm->acc_z * icm->acc_z);
    icm->acc_x = icm->acc_x * norm;
    icm->acc_y = icm->acc_y * norm;
    icm->acc_z = icm->acc_z * norm;

    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;

    ex = icm->acc_y * vz - icm->acc_z * vy;
    ey = icm->acc_z * vx - icm->acc_x * vz;
    ez = icm->acc_x * vy - icm->acc_y * vx;

    I_ex += halfT * ex;
    I_ey += halfT * ey;
    I_ez += halfT * ez;

    icm->gyro_x = icm->gyro_x + icm_kp* ex + icm_ki* I_ex;
    icm->gyro_y = icm->gyro_y + icm_kp* ey + icm_ki* I_ey;
    icm->gyro_z = icm->gyro_z + icm_kp* ez + icm_ki* I_ez;

    q0 = q0 + (-q1 * icm->gyro_x - q2 * icm->gyro_y - q3 * icm->gyro_z) * halfT;
    q1 = q1 + (q0 * icm->gyro_x + q2 * icm->gyro_z - q3 * icm->gyro_y) * halfT;
    q2 = q2 + (q0 * icm->gyro_y - q1 * icm->gyro_z + q3 * icm->gyro_x) * halfT;
    q3 = q3 + (q0 * icm->gyro_z + q1 * icm->gyro_y - q2 * icm->gyro_x) * halfT;

    norm = InvSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    Q_info.q0 = q0 * norm;
    Q_info.q1 = q1 * norm;
    Q_info.q2 = q2 * norm;
    Q_info.q3 = q3 * norm;
}

void ICM20602_euler_angle_update(void)
{
    float q0 = Q_info.q0;
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;

    eulerAngle.pitch = asin(2 * q0 * q2 - 2 * q1 * q3) * 180 / PI;
    eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 180 / PI;
    eulerAngle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 180 / PI;
}

void ICM20602_data_update(void)
{
    ICM20602_get_acc();
    ICM20602_get_gyro();
    ICM20602_get_orign_data();
    ICM20602_AHRS_update(&icm20602_data);
    ICM20602_euler_angle_update();
}

void ICM20602_init(void)
{
    uint8_t id;

    GPIOA_SetBits( ICM20602_CS_PIN | ICM20602_SCK_PIN | ICM20602_MOSI_PIN );
    GPIOA_ModeCfg( ICM20602_CS_PIN | ICM20602_SCK_PIN | ICM20602_MOSI_PIN, GPIO_ModeOut_PP_5mA );
    GPIOA_SetBits( ICM20602_MISO_PIN );
    GPIOA_ModeCfg( ICM20602_MISO_PIN, GPIO_ModeIN_PU );
    SPI0_MasterDefInit();

    while (id != 0x12) {
        DelayMs(2);
        id = ICM20602_read_byte(ICM20602_WHO_AM_I);
    }

    /* Reset ICM20602 */
    ICM20602_write_byte(ICM20602_PWR_MGMT_1, 0x80);
    DelayMs(100);
    ICM20602_write_byte(ICM20602_PWR_MGMT_1, 0x00);

    /* Config acc ¡À8g 4096LSB/g; gyro ¡À2000dps 16.4LSB/g */
    ICM20602_write_byte(ICM20602_PWR_MGMT_1, 0x01);  // clock source
    ICM20602_write_byte(ICM20602_PWR_MGMT_2, 0x01);  // open accelerometer and gyro
    ICM20602_write_byte(ICM20602_CONFIG, 0x01);  // gyro 176Hz/177Hz sample rate 1kHz
    ICM20602_write_byte(ICM20602_SMPLRT_DIV, 0x07);  // not divide sample rate
    ICM20602_write_byte(ICM20602_GYRO_CONFIG, 0x18); // ¡À2000 dps
    ICM20602_write_byte(ICM20602_ACCEL_CONFIG, 0x10);    // ¡À8g
    ICM20602_write_byte(ICM20602_ACCEL_CONFIG_2, 0x03);  // accelerometer 44.8Hz/61.5Hz sample rate 1kHz
}

