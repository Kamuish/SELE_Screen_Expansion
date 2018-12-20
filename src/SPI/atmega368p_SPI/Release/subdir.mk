################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../I2C_comms.c \
../LCD1602A.c \
../SPI_comms.c \
../main.c 

OBJS += \
./I2C_comms.o \
./LCD1602A.o \
./SPI_comms.o \
./main.o 

C_DEPS += \
./I2C_comms.d \
./LCD1602A.d \
./SPI_comms.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/joaorodrigues/Desktop/SELE/project_ICARUS/src/SPI/atmega368p_SPI" -Wall -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=14745600UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


