/*
 * main.c
 *
 *  Created on: Nov 25, 2018
 *      Author: andre
 */

#include "util/delay.h"
#include "I2C_comms.h"
#include "../../Screen/LCD.h"


int main(){

	i2c_init();                                // init I2C interface();

	_delay_ms(1);


	uint8_t command;

	screen_init(0X40, I2C);
	_delay_ms(10);


	// Display ON
	command = 0x00;
	send_4_bit_command(command,  I2C);

	_delay_ms(1);

	command = 0x70;
	send_4_bit_command(command,  I2C);
	_delay_ms(10);


	uint8_t string[] = "ASDSADSAD";
	put_string(string, sizeof(string) -1, I2C);


	while (1) {
		screen_instruction(LCD_DISP_ON_CURSOR_BLINK, I2C);

				_delay_ms(1000);

	}

	i2c_stop();

	return 0;
}



