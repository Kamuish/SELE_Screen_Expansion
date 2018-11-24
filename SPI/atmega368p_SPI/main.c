/*
 * main.c
 *
 *  Created on: Nov 24, 2018
 *      Author: joaorodrigues
 */

#include <util/delay.h>
#include <SPI_comms.h>

int main(void) {

	SPI_MasterInit();

	char command = 0x01;
	SPI_MasterTransmit(command);

	while (1) {
		PORTB &= ~(1<<PB5);
		_delay_ms(500);
		PORTB |= 1<<PB5;
		_delay_ms(500);
	}
	return 0;
}
