/*
 * main.c
 *
 *  Created on: Dec 11, 2018
 *      Author: andre
 */

#include "../Screen/LCD.h"

int main(void){

	screen_init(0X40, I2C);
	_delay_ms(10);
	uint8_t command;

	// Display ON
	command = 0x00;
	send_4_bit_command(command,  I2C);

	_delay_ms(1);
	command = 0x70;
	send_4_bit_command(command,  I2C);
	_delay_ms(10);


	uint8_t string[] = "Adeus";
	put_string(string, sizeof(string) -1, I2C);

	return 0;
}
