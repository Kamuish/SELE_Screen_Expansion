/*
 * main.c
 *
 *  Created on: Nov 24, 2018
 *      Author: joaorodrigues
 */

#include <util/delay.h>
#include <SPI_comms.h>
#include <LCD1602A.h>

int main(void) {

	SPI_MasterInit();
	_delay_ms(400);

	uint8_t command;

	screen_init();

	/* Display ON, Cursor Blink */

	command = 0x0B;
	screen_instruction(command);

	/* Print 'O' */

	put_char('A');

	while (1) {
		_delay_ms(100);
	}

	return 0;
}
