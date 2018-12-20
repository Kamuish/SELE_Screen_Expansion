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
SPI_demo.lss \

FLASH_IMAGE += \
SPI_demo.hex \

EEPROM_IMAGE += \
SPI_demo.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: SPI_demo.elf secondary-outputs

# Tool invocations
SPI_demo.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SPI_demo.map -mmcu=atmega328p -o "SPI_demo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SPI_demo.lss: SPI_demo.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SPI_demo.elf  >"SPI_demo.lss"
	@echo 'Finished building: $@'
	@echo ' '

SPI_demo.hex: SPI_demo.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SPI_demo.elf  "SPI_demo.hex"
	@echo 'Finished building: $@'
	@echo ' '

SPI_demo.eep: SPI_demo.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SPI_demo.elf  "SPI_demo.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SPI_demo.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p SPI_demo.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: SPI_demo.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pm328p -cavrisp -P/dev/ttyACM0 -b19200 -u -Uflash:w:SPI_demo.hex:a -Ueeprom:w:SPI_demo.eep:a -Ulfuse:w:0xf7:m -Uhfuse:w:0xd1:m -Uefuse:w:0xff:m
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SPI_demo.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
