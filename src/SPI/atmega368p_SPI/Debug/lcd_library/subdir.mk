################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lcd_library/lcd.c \
../lcd_library/test_lcd.c 

OBJS += \
./lcd_library/lcd.o \
./lcd_library/test_lcd.o 

C_DEPS += \
./lcd_library/lcd.d \
./lcd_library/test_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
lcd_library/%.o: ../lcd_library/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


