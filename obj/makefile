################################################################################
# MRS Version: 1.9.0
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include Profile/subdir.mk
-include HAL/subdir.mk
-include CherryUSB/core/subdir.mk
-include CherryUSB/class/msc/subdir.mk
-include CherryUSB/class/hid/subdir.mk
-include CherryUSB/class/cdc/subdir.mk
-include CherryUSB/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
tp78_joyticks.hex \

SECONDARY_LIST += \
tp78_joyticks.lst \

SECONDARY_SIZE += \
tp78_joyticks.siz \


# All Target
all: tp78_joyticks.elf secondary-outputs

# Tool invocations
tp78_joyticks.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "E:\Project\CH582M_joyticks\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"../StdPeriphDriver" -L"E:\Project\CH582M_joyticks\LIB" -Xlinker --print-memory-usage -Wl,-Map,"tp78_joyticks.map" --specs=nano.specs --specs=nosys.specs -o "tp78_joyticks.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
tp78_joyticks.hex: tp78_joyticks.elf
	@	riscv-none-embed-objcopy -O ihex "tp78_joyticks.elf"  "tp78_joyticks.hex"
	@	@
tp78_joyticks.lst: tp78_joyticks.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "tp78_joyticks.elf" > "tp78_joyticks.lst"
	@	@
tp78_joyticks.siz: tp78_joyticks.elf
	@	riscv-none-embed-size --format=berkeley "tp78_joyticks.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) tp78_joyticks.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
