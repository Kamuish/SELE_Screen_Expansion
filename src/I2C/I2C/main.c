/*
 * main.c
 *
 *  Created on: Nov 25, 2018
 *      Author: andre
 */

#include "util/delay.h"
#include "i2cmaster.h"
#include "LCD.h"



// CLK -> A5
int main(){

	i2c_init();                                // init I2C interface();

	_delay_ms(1);

	// COnfigures all  the pins as outputs
	i2c_start(0x40);
	_delay_ms(1);
	i2c_write(0x00); // register addr
	_delay_ms(1);
	i2c_write(0x00); // clear all bits
	i2c_stop();
	_delay_ms(100);

	// set up internal register for continuous write to address

	i2c_start(0x40);
	_delay_ms(100);
	i2c_write(0x05);
	_delay_ms(10);
	i2c_write(0x20);
	i2c_stop();

	i2c_start(0x40);
	_delay_ms(100);

	i2c_write(0x09); // gpio register
	_delay_ms(10);


	uint8_t command;

	screen_init();
	_delay_ms(10);


	// Display ON
	command = 0x00;
	send_4_bit_command(command);

	_delay_ms(1);

	command = 0x70;
	send_4_bit_command(command);
	_delay_ms(10);


	uint8_t string[] = "Ola Mundo ad as sa";
	put_string(string, sizeof(string) -1);


	while (1) {
		screen_instruction(LCD_DISP_ON_CURSOR_BLINK);

				_delay_ms(1000);

	}

	i2c_stop();

	return 0;
}



