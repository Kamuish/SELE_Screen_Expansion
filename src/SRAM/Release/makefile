################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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
LSS += \
SRAM.lss \

FLASH_IMAGE += \
SRAM.hex \

EEPROM_IMAGE += \
SRAM.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: SRAM.elf secondary-outputs

dependents:
	-cd /home/joaorodrigues/Desktop/SELE/project_ICARUS/src/UART/Release && $(MAKE) all

# Tool invocations
SRAM.elf: $(OBJS) $(USER_OBJS) /home/joaorodrigues/Desktop/SELE/project_ICARUS/src/UART/Release/UART.elf
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SRAM.map -Wl,--section-start=.classb_sram_buffer=0x800100,--section-start=.data=0x800240 -mmcu=atmega328p -o "SRAM.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SRAM.lss: SRAM.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SRAM.elf  >"SRAM.lss"
	@echo 'Finished building: $@'
	@echo ' '

SRAM.hex: SRAM.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -R .classb_sram_buffer -O ihex SRAM.elf  "SRAM.hex"
	@echo 'Finished building: $@'
	@echo ' '

SRAM.eep: SRAM.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SRAM.elf  "SRAM.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SRAM.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p SRAM.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SRAM.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/UART/Release/UART.elf:

-include ../makefile.targets
