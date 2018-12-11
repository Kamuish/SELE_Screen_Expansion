################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Program\ files/I2C_comms.c \
../Program\ files/LCD1602A.c \
../Program\ files/SPI_comms.c \
../Program\ files/main.c 

OBJS += \
./Program\ files/I2C_comms.o \
./Program\ files/LCD1602A.o \
./Program\ files/SPI_comms.o \
./Program\ files/main.o 

C_DEPS += \
./Program\ files/I2C_comms.d \
./Program\ files/LCD1602A.d \
./Program\ files/SPI_comms.d \
./Program\ files/main.d 


# Each subdirectory must supply rules for building sources it contributes
Program\ files/I2C_comms.o: ../Program\ files/I2C_comms.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"Program files/I2C_comms.d" -MT"Program\ files/I2C_comms.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/LCD1602A.o: ../Program\ files/LCD1602A.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"Program files/LCD1602A.d" -MT"Program\ files/LCD1602A.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/SPI_comms.o: ../Program\ files/SPI_comms.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"Program files/SPI_comms.d" -MT"Program\ files/SPI_comms.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Program\ files/main.o: ../Program\ files/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/screen_expansion_project/Header files" -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"Program files/main.d" -MT"Program\ files/main.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


