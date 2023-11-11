################################################################################
# MRS Version: 1.9.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/BATTERY.c \
../HAL/CORE.c \
../HAL/HW_I2C.c \
../HAL/ICM20602.c \
../HAL/MCU.c \
../HAL/RTC.c \
../HAL/SLEEP.c \
../HAL/USB.c \
../HAL/WS2812.c \
../HAL/hidmouse.c 

OBJS += \
./HAL/BATTERY.o \
./HAL/CORE.o \
./HAL/HW_I2C.o \
./HAL/ICM20602.o \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o \
./HAL/USB.o \
./HAL/WS2812.o \
./HAL/hidmouse.o 

C_DEPS += \
./HAL/BATTERY.d \
./HAL/CORE.d \
./HAL/HW_I2C.d \
./HAL/ICM20602.d \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d \
./HAL/USB.d \
./HAL/WS2812.d \
./HAL/hidmouse.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCLK_OSC32K=2 -I"E:\Project\CH582M_joyticks\HAL\include" -I"E:\Project\CH582M_joyticks\CherryUSB" -I"E:\Project\CH582M_joyticks\LIB" -I"E:\Project\CH582M_joyticks\Profile\include" -I"E:\Project\CH582M_joyticks\RVMSIS" -I"E:\Project\CH582M_joyticks\APP" -I"E:\Project\CH582M_joyticks\CherryUSB\class\hid" -I"E:\Project\CH582M_joyticks\CherryUSB\class\cdc" -I"E:\Project\CH582M_joyticks\CherryUSB\class\msc" -I"E:\Project\CH582M_joyticks\CherryUSB\common" -I"E:\Project\CH582M_joyticks\CherryUSB\core" -I"E:\Project\CH582M_joyticks\Startup" -I"E:\Project\CH582M_joyticks\StdPeriphDriver\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

