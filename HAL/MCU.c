/********************************** (C) COPYRIGHT *******************************
 * File Name          : MCU.c
 * Author             : ChnMasterOG, WCH
 * Version            : V1.0
 * Date               : 2023/9/2
 * Description        : 硬件任务处理函数及BLE和硬件初始化
 * Copyright (c) 2023 ChnMasterOG
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"

tmosTaskID halTaskID = INVALID_TASK_ID;
__attribute__((aligned(4))) uint8_t joy_hid_buffer[9] = { 0 };  // X_data, Y_data, Z_data, RZ_data, RX_data, RY_data, D_pad  button_L, button_H
uint8_t switch_calibration = FALSE;
uint8_t gyro_enable = FALSE;
uint8_t button_use_layer2 = FALSE;

/*******************************************************************************
 * @fn          Lib_Calibration_LSI
 *
 * @brief       内部32k校准
 *
 * input parameters
 *
 * @param       None.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
void Lib_Calibration_LSI( void )
{
  Calibration_LSI( Level_64 );
}

#if (defined (BLE_SNV)) && (BLE_SNV == TRUE)
/*******************************************************************************
 * @fn          Lib_Read_Flash
 *
 * @brief       Lib 操作Flash回调
 *
 * input parameters
 *
 * @param       addr.
 * @param       num.
 * @param       pBuf.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
u32 Lib_Read_Flash( u32 addr, u32 num, u32 *pBuf )
{
    EEPROM_READ(addr, pBuf, num * 4);
    return 0;
}

/*******************************************************************************
 * @fn          Lib_Write_Flash
 *
 * @brief       Lib 操作Flash回调
 *
 * input parameters
 *
 * @param       addr.
 * @param       num.
 * @param       pBuf.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
u32 Lib_Write_Flash( u32 addr, u32 num, u32 *pBuf )
{
    EEPROM_ERASE(addr, num * 4);
    EEPROM_WRITE(addr, pBuf, num * 4);
    return 0;
}
#endif

/*******************************************************************************
 * @fn          CH58X_BLEInit
 *
 * @brief       BLE 库初始化
 *
 * input parameters
 *
 * @param       None.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
void CH58X_BLEInit(void)
{
    uint8_t     i;
    bleConfig_t cfg;
    if(tmos_memcmp(VER_LIB, VER_FILE, strlen(VER_FILE)) == FALSE)
    {
        PRINT("head file error...\n");
        while(1);
    }
    SysTick_Config(SysTick_LOAD_RELOAD_Msk);
    PFIC_DisableIRQ(SysTick_IRQn);

    tmos_memset(&cfg, 0, sizeof(bleConfig_t));
    cfg.MEMAddr = (uint32_t)MEM_BUF;
    cfg.MEMLen = (uint32_t)BLE_MEMHEAP_SIZE;
    cfg.BufMaxLen = (uint32_t)BLE_BUFF_MAX_LEN;
    cfg.BufNumber = (uint32_t)BLE_BUFF_NUM;
    cfg.TxNumEvent = (uint32_t)BLE_TX_NUM_EVENT;
    cfg.TxPower = (uint32_t)BLE_TX_POWER;
#if(defined(BLE_SNV)) && (BLE_SNV == TRUE)
    cfg.SNVAddr = (uint32_t)BLE_SNV_ADDR;
    cfg.readFlashCB = Lib_Read_Flash;
    cfg.writeFlashCB = Lib_Write_Flash;
#endif
#if(CLK_OSC32K)
    cfg.SelRTCClock = (uint32_t)CLK_OSC32K;
#endif
    cfg.ConnectNumber = (PERIPHERAL_MAX_CONNECTION & 3) | (CENTRAL_MAX_CONNECTION << 2);
    cfg.srandCB = SYS_GetSysTickCnt;
#if(defined TEM_SAMPLE) && (TEM_SAMPLE == TRUE)
    cfg.tsCB = HAL_GetInterTempValue; // 根据温度变化校准RF和内部RC( 大于7摄氏度 )
  #if(CLK_OSC32K)
    cfg.rcCB = Lib_Calibration_LSI; // 内部32K时钟校准
  #endif
#endif
#if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    cfg.WakeUpTime = WAKE_UP_RTC_MAX_TIME;
    cfg.sleepCB = CH58X_LowPower; // 启用睡眠
#endif
#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
    for(i = 0; i < 6; i++)
    {
        cfg.MacAddr[i] = MacAddr[5 - i];
    }
#else
    {
        uint8_t MacAddr[6];
        GetMACAddress(MacAddr);
        for(i = 0; i < 6; i++)
        {
            cfg.MacAddr[i] = MacAddr[i]; // 使用芯片mac地址
        }
    }
#endif
    if(!cfg.MEMAddr || cfg.MEMLen < 4 * 1024)
    {
        while(1);
    }
    i = BLE_LibInit(&cfg);
    if(i)
    {
        PRINT("LIB init error code: %x ...\n", i);
        while(1);
    }
}

/*******************************************************************************
 * @fn          HAL_ProcessEvent
 *
 * @brief       硬件层事务处理
 *
 * input parameters
 *
 * @param       task_id.
 * @param       events.
 *
 * output parameters
 *
 * @param       events.
 *
 * @return      None.
 */
tmosEvents HAL_ProcessEvent( tmosTaskID task_id, tmosEvents events )
{
    uint8_t *msgPtr;
    uint8_t i, flag;
    static uint32_t cal_time = 0;
    static uint8_t last_joy_hid_buffer[sizeof(joy_hid_buffer)];

    if (events & SYS_EVENT_MSG)
    { // 处理HAL层消息，调用tmos_msg_receive读取消息，处理完成后删除消息。
        msgPtr = tmos_msg_receive(task_id);
        if(msgPtr)
        {
            /* De-allocate */
            tmos_msg_deallocate(msgPtr);
        }
        return events ^ SYS_EVENT_MSG;
    }

    if (events & HAL_REG_INIT_EVENT)
    {
#if(defined BLE_CALIBRATION_ENABLE) && (BLE_CALIBRATION_ENABLE == TRUE) // 校准任务，单次校准耗时小于10ms
        BLE_RegInit();  // 校准RF
#if(defined CLK_OSC32K && CLK_OSC32K != 0x80)
        Lib_Calibration_LSI(); // 校准内部RC
#endif
        tmos_start_task(halTaskID, HAL_REG_INIT_EVENT, MS1_TO_SYSTEM_TIME(BLE_CALIBRATION_PERIOD));
        return events ^ HAL_REG_INIT_EVENT;
#endif
    }

    if (events & SEND_REPORT_EVENT)
    {
        flag = 0;
        for (i = 0; i < sizeof(joy_hid_buffer); i++) {
            if (last_joy_hid_buffer[i] != joy_hid_buffer[i]) {
                last_joy_hid_buffer[i] = joy_hid_buffer[i];
                flag = 1;
            }
        }
        if (flag == 1) {
            tmos_set_event(usbTaskID, USB_SEND_JOY_REPORT_EVENT);
            tmos_set_event(hidEmuTaskId, BLE_SEND_JOY_REPORT_EVENT);
        }
        return events ^ SEND_REPORT_EVENT;
    }

    if (events & HAL_KEY_EVENT)
    {
#if (defined HAL_KEY) && (HAL_KEY == TRUE)
        HAL_KeyPoll(); /* Check for keys */
        tmos_start_task(halTaskID, HAL_KEY_EVENT, MS1_TO_SYSTEM_TIME(KEY_THREAD_PREIOD));
        return events ^ HAL_KEY_EVENT;
#endif
    }

    if (events & ICM_EVENT)
    {
        ICM20602_data_update();
        if (gyro_enable == TRUE)
            ICM20602_report();
//        usb_printf("pitch: %d, roll: %d\r\n", (int)(eulerAngle.pitch * 1000), (int)(eulerAngle.roll * 1000));
        tmos_start_task(halTaskID, ICM_EVENT, MS1_TO_SYSTEM_TIME(ICM_THREAD_PREIOD));
        return events ^ ICM_EVENT;
    }

    if (events & SWITCH_EVENT)
    {
        if (switch_calibration == FALSE) {
            for (i = 0; i < 4; i++)
                SWITCH_ADC_ENABLE(i, 0);
        } else if (switch_calibration == SWITCH_CAL_STEP1_START) {
            SWITCH_data_reset();
            switch_calibration = SWITCH_CAL_STEP1_SAMPLE;
            SWITCH_Calibration(1, 0);
            cal_time = 0;
        } else if (switch_calibration == SWITCH_CAL_STEP1_SAMPLE) {
            cal_time++;
            SWITCH_Calibration(1, 1);
            if (cal_time >= SWITCH_CAL_TIME * 1000 / SWITCH_THREAD_PREIOD) {
                switch_calibration = SWITCH_CAL_STEP1_STOP;
            }
        } else if (switch_calibration == SWITCH_CAL_STEP1_STOP) {
            switch_calibration = SWITCH_CAL_STEP2_START;
            SWITCH_Calibration(1, 2);
        } else if (switch_calibration == SWITCH_CAL_STEP2_START) {
            switch_calibration = SWITCH_CAL_STEP2_SAMPLE;
            SWITCH_Calibration(2, 0);
            cal_time = 0;
        } else if (switch_calibration == SWITCH_CAL_STEP2_SAMPLE) {
            cal_time++;
            SWITCH_Calibration(2, 1);
            if (cal_time >= SWITCH_CAL_TIME * 1000 / SWITCH_THREAD_PREIOD) {
                switch_calibration = SWITCH_CAL_STEP2_STOP;
            }
        } else if (switch_calibration == SWITCH_CAL_STEP2_STOP) {
            switch_calibration = FALSE;
            SWITCH_Calibration(2, 2);
            SWITCH_data_sync_toVIA();
            via_data_write();
            for (i = 0; i < 4; i++)
                usb_printf("CAL%d: %d %d %d %d \r\n", i, switch_data[i].adc_min_val, switch_data[i].adc_max_val, switch_data[i].adc_deadzone_l, switch_data[i].adc_deadzone_h);
            SoftReset();
        }
//        usb_printf("%d %d %d %d \r\n", switch_data[0].adc_data, switch_data[1].adc_data, switch_data[2].adc_data, switch_data[3].adc_data);
        tmos_start_task(halTaskID, SWITCH_EVENT, MS1_TO_SYSTEM_TIME(SWITCH_THREAD_PREIOD));
        return events ^ SWITCH_EVENT;
    }

    if (events & WS2812_EVENT)
    {
        WS2812_Send();
        tmos_start_task(halTaskID, WS2812_EVENT, MS1_TO_SYSTEM_TIME(WS2812_THREAD_PREIOD));
        return events ^ WS2812_EVENT;
    }

    if (events & BATTERY_EVENT)
    {
        BATTERY_ADC_Convert();
//        usb_printf("%d \r\n", BAT_adcVal);
        tmos_start_task(halTaskID, BATTERY_EVENT, MS1_TO_SYSTEM_TIME(BATTERY_THREAD_PREIOD));
        return events ^ BATTERY_EVENT;
    }

    return 0;
}

/*******************************************************************************
 * @fn          HAL_Init
 *
 * @brief       硬件初始化
 *
 * input parameters
 *
 * @param       None.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
void HAL_Init()
{
    halTaskID = TMOS_ProcessEventRegister( HAL_ProcessEvent );

    HAL_TimeInit();
    via_data_read();
    ICM20602_init();
    ICM20602_gyro_offset_init();
    BATTERY_Init();
    SWITCH_Init();  // assert adc init
    HAL_KeyInit();
    HAL_USBInit();
    WS2812_PWM_Init();

    if (HAL_PUSH_BUTTON10()) {
        DelayMs(10);
        if (HAL_PUSH_BUTTON10())
            switch_calibration = SWITCH_CAL_STEP1_START;
    }

    /* 初始灯光 */
    if (via_config.backlight_enable == TRUE)
        WS2812_Change_Style_to(button_use_layer2 ? WS2812_Style_Cyan_Breath : WS2812_Style_Purple_Breath);

if (switch_calibration == FALSE) {
    tmos_start_task(halTaskID, ICM_EVENT, MS1_TO_SYSTEM_TIME(1000));
    tmos_start_task(halTaskID, WS2812_EVENT, MS1_TO_SYSTEM_TIME(1000));
}
#if(defined BLE_CALIBRATION_ENABLE) && (BLE_CALIBRATION_ENABLE == TRUE)
    tmos_start_task(halTaskID, HAL_REG_INIT_EVENT, MS1_TO_SYSTEM_TIME(BLE_CALIBRATION_PERIOD)); // 添加校准任务，单次校准耗时小于10ms
#endif
}

/*******************************************************************************
 * @fn      HAL_GetInterTempValue
 *
 * @brief   获取内部温感采样值，如果使用了ADC中断采样，需在此函数中暂时屏蔽中断.
 *
 * @return  内部温感采样值.
 */
uint16_t HAL_GetInterTempValue(void)
{
    uint8_t  sensor, channel, config, tkey_cfg;
    uint16_t adc_data;

    tkey_cfg = R8_TKEY_CFG;
    sensor = R8_TEM_SENSOR;
    channel = R8_ADC_CHANNEL;
    config = R8_ADC_CFG;
    ADC_InterTSSampInit();
    R8_ADC_CONVERT |= RB_ADC_START;
    while(R8_ADC_CONVERT & RB_ADC_START);
    adc_data = R16_ADC_DATA;
    R8_TEM_SENSOR = sensor;
    R8_ADC_CHANNEL = channel;
    R8_ADC_CFG = config;
    R8_TKEY_CFG = tkey_cfg;
    return (adc_data);
}

/******************************** endfile @ mcu ******************************/
