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
atmega368p_SPI.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: atmega368p_SPI.elf secondary-outputs

# Tool invocations
atmega368p_SPI.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,atmega368p_SPI.map -mmcu=atmega328p -o "atmega368p_SPI.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

atmega368p_SPI.lss: atmega368p_SPI.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S atmega368p_SPI.elf  >"atmega368p_SPI.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: atmega368p_SPI.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p atmega368p_SPI.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) atmega368p_SPI.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
