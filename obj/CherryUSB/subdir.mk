################################################################################
# MRS Version: 1.9.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CherryUSB/usb_ch58x_dc_usbfs.c 

OBJS += \
./CherryUSB/usb_ch58x_dc_usbfs.o 

C_DEPS += \
./CherryUSB/usb_ch58x_dc_usbfs.d 


# Each subdirectory must supply rules for building sources it contributes
CherryUSB/%.o: ../CherryUSB/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCLK_OSC32K=2 -I"E:\Project\CH582M_joyticks\HAL\include" -I"E:\Project\CH582M_joyticks\CherryUSB" -I"E:\Project\CH582M_joyticks\LIB" -I"E:\Project\CH582M_joyticks\Profile\include" -I"E:\Project\CH582M_joyticks\RVMSIS" -I"E:\Project\CH582M_joyticks\APP" -I"E:\Project\CH582M_joyticks\CherryUSB\class\hid" -I"E:\Project\CH582M_joyticks\CherryUSB\class\cdc" -I"E:\Project\CH582M_joyticks\CherryUSB\class\msc" -I"E:\Project\CH582M_joyticks\CherryUSB\common" -I"E:\Project\CH582M_joyticks\CherryUSB\core" -I"E:\Project\CH582M_joyticks\Startup" -I"E:\Project\CH582M_joyticks\StdPeriphDriver\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

