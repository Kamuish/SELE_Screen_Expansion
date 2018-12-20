/*
 * main.c
 *
 *  Created on: Dec 20, 2018
 *      Author: andre
 */

#include "SPI_comms.h"
uint8_t main(void){

	SPI_MasterInit();
	uint8_t data = 0xF0;
	SPI_MasterTransmit(data);
	data = 0x2A;
	SPI_MasterTransmit(data);
	data = 0xFF;
	SPI_MasterTransmit(data);
	uint8_t aaa = 'A';
	SPI_MasterTransmit(aaa);

	return 0;
}
