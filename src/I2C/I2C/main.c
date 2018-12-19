/*
 * main.c
 *
 *  Created on: Dec 19, 2018
 *      Author: andre
 */


#include "I2C_comms.h"

uint8_t main(void){
	I2C_Start(I2C_ADDR);

	uint8_t message = 0x00;

	I2C_Write(message);
	_delay_ms(1000);
	I2C_Stop();

	return 0;

}
