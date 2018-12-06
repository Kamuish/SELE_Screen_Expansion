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
	_delay_ms(400);

	char command;

	command = 0x60;
	SPI_MasterTransmit(command);
	_delay_ms(41);

	command = 0x60;
	SPI_MasterTransmit(command);
	_delay_ms(1);

	command = 0x60;
	SPI_MasterTransmit(command);
	_delay_ms(1);

	command = 0x20;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	/* Function Set */

	command = 0x20;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	command = 0x08;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	/* Display OFF */

	command = 0x00;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	command = 0x48;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	/* Display Clear */

	command = 0x00;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	command = 0x40;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	/* Mode Set */

	command = 0x00;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	command = 0x30;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	/* Display ON, Cursor Blink */

	command = 0x00;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	command = 0xD8;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	/* Print 'O' */

	command = 0x92;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	command = 0xFA;
	SPI_MasterTransmit(command);
	_delay_ms(10);

	while (1) {
		_delay_ms(100);
	}

	return 0;
}
