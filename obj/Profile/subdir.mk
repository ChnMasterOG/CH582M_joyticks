################################################################################
# MRS Version: 1.9.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Profile/battservice.c \
../Profile/devinfoservice.c \
../Profile/hiddev.c \
../Profile/hidjoytickservice.c \
../Profile/scanparamservice.c 

OBJS += \
./Profile/battservice.o \
./Profile/devinfoservice.o \
./Profile/hiddev.o \
./Profile/hidjoytickservice.o \
./Profile/scanparamservice.o 

C_DEPS += \
./Profile/battservice.d \
./Profile/devinfoservice.d \
./Profile/hiddev.d \
./Profile/hidjoytickservice.d \
./Profile/scanparamservice.d 


# Each subdirectory must supply rules for building sources it contributes
Profile/%.o: ../Profile/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCLK_OSC32K=2 -I"E:\Project\CH582M_joyticks\HAL\include" -I"E:\Project\CH582M_joyticks\CherryUSB" -I"E:\Project\CH582M_joyticks\LIB" -I"E:\Project\CH582M_joyticks\Profile\include" -I"E:\Project\CH582M_joyticks\RVMSIS" -I"E:\Project\CH582M_joyticks\APP" -I"E:\Project\CH582M_joyticks\CherryUSB\class\hid" -I"E:\Project\CH582M_joyticks\CherryUSB\class\cdc" -I"E:\Project\CH582M_joyticks\CherryUSB\class\msc" -I"E:\Project\CH582M_joyticks\CherryUSB\common" -I"E:\Project\CH582M_joyticks\CherryUSB\core" -I"E:\Project\CH582M_joyticks\Startup" -I"E:\Project\CH582M_joyticks\StdPeriphDriver\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

