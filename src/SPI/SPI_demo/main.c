/*
 * main.c
 *
 *  Created on: Dec 20, 2018
 *      Author: andre
 */

#include <SPI_comms.h>
uint8_t main(void){
	SPI_MasterInit();
	uint8_t data = 0x00;
	SPI_MasterTransmit(data);

}
