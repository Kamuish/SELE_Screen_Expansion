/*
 * main.c
 *
 *  Created on: Nov 25, 2018
 *      Author: andre
 */

#include "I2C_comms.h"

int main(){

	i2c_start();
	char command = 0x00C;

	SendData(command);
	i2c_stop();

	return 0;
}
