/*
 * main.c
 *
 *  Created on: Dec 19, 2018
 *      Author: andre
 */


#include "I2C_comms.h"

uint8_t main(void){
	I2C_Init();

	I2C_Start(I2C_ADDR);

	uint8_t data = 0xF0;

	I2C_Write(data);

	data = 0x2A;

	I2C_Write(data);

	data = 0xFF;

	I2C_Write(data);

	uint8_t aaa = 'A';

	I2C_Write(aaa);

	I2C_Stop();

	return 0;

}
