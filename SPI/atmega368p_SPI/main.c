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

	command = LCD_DISP_ON_BLINK;
	screen_instruction(command);

	/* Print 'O' */

	uint8_t string[] = "O Andre e gay!!";
	put_string(string, sizeof(string) -1);

	_delay_ms(5000);

	while (1) {
		screen_instruction(LCD_MOVE_DISP_RIGHT);
		_delay_ms(10000);
	}

	return 0;
}
