################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Program\ files/EEPROM_test.c \
../Program\ files/FLASH_test.c \
../Program\ files/I2C_comms.c \
../Program\ files/LCD1602A.c \
../Program\ files/SPI_comms.c \
../Program\ files/SRAM_test.c \
../Program\ files/Shift_Strings.c \
../Program\ files/main.c 

OBJS += \
./Program\ files/EEPROM_test.o \
./Program\ files/FLASH_test.o \
./Program\ files/I2C_comms.o \
./Program\ files/LCD1602A.o \
./Program\ files/SPI_comms.o \
./Program\ files/SRAM_test.o \
./Program\ files/Shift_Strings.o \
./Program\ files/main.o 

C_DEPS += \
./Program\ files/EEPROM_test.d \
./Program\ files/FLASH_test.d \
./Program\ files/I2C_comms.d \
./Program\ files/LCD1602A.d \
./Program\ files/SPI_comms.d \
./Program\ files/SRAM_test.d \
./Program\ files/Shift_Strings.d \
./Program\ files/main.d 


# Each subdirectory must supply rules for building sources it contributes
Program\ files/EEPROM_test.o: ../Program\ files/EEPROM_test.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"Program files/EEPROM_test.d" -MT"Program\ files/EEPROM_test.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/FLASH_test.o: ../Program\ files/FLASH_test.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"Program files/FLASH_test.d" -MT"Program\ files/FLASH_test.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/I2C_comms.o: ../Program\ files/I2C_comms.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"Program files/I2C_comms.d" -MT"Program\ files/I2C_comms.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/LCD1602A.o: ../Program\ files/LCD1602A.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"Program files/LCD1602A.d" -MT"Program\ files/LCD1602A.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/SPI_comms.o: ../Program\ files/SPI_comms.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"Program files/SPI_comms.d" -MT"Program\ files/SPI_comms.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/SRAM_test.o: ../Program\ files/SRAM_test.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"Program files/SRAM_test.d" -MT"Program\ files/SRAM_test.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/Shift_Strings.o: ../Program\ files/Shift_Strings.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"Program files/Shift_Strings.d" -MT"Program\ files/Shift_Strings.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/main.o: ../Program\ files/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"Program files/main.d" -MT"Program\ files/main.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


