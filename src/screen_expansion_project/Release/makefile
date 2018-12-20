################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Program\ files/subdir.mk
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
screen_expansion.lss \

FLASH_IMAGE += \
screen_expansion.hex \

EEPROM_IMAGE += \
screen_expansion.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: screen_expansion.elf secondary-outputs

# Tool invocations
screen_expansion.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,screen_expansion.map -Wl,--section-start=.classb_sram_buffer=0x800100,--section-start=.data=0x800240 -mmcu=atmega328p -o "screen_expansion.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

screen_expansion.lss: screen_expansion.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S screen_expansion.elf  >"screen_expansion.lss"
	@echo 'Finished building: $@'
	@echo ' '

screen_expansion.hex: screen_expansion.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -R .classb_sram_buffer -O ihex screen_expansion.elf  "screen_expansion.hex"
	@echo 'Finished building: $@'
	@echo ' '

screen_expansion.eep: screen_expansion.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex screen_expansion.elf  "screen_expansion.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: screen_expansion.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p screen_expansion.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) screen_expansion.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
