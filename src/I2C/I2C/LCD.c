/*
 * LCD.c
 *
 *  Created on: Dec 8, 2018
 *      Author: andre
 */


#include "I2C_comms.h"
#include "LCD.h"


void screen_init(void) {
	uint8_t command;

	command = 0x18;
	send_4_bit_command(command);
	_delay_ms(41);

	command = 0x18;
	send_4_bit_command(command);
	_delay_ms(1);

	command = 0x18;
	send_4_bit_command(command);
	_delay_ms(1);

	command = 0x10;
	send_4_bit_command(command);
	_delay_ms(10);


	//  Function set
	screen_instruction(LCD_FUNCTION_4BIT_2LINES);

	// Disp off

	screen_instruction(LCD_DISP_OFF);

	// Disp clear
	screen_instruction(LCD_DISP_CLEAR);


	// Mode set
	screen_instruction(LCD_ENTRY_INC_);

}



void screen_instruction(uint8_t instruction) {
	uint8_t high_nibble = (instruction)&0xF0;
	uint8_t low_nibble  = (instruction)&0x0F;

	/* High nibble */

	uint8_t send_instruction;
	send_instruction = high_nibble>>1;
	send_instruction |= (1<<EN);
	send_instruction |= (1<<BKL);
	send_instruction &= ~(1<<RS);

	i2c_write(send_instruction);

	send_instruction &= ~(1<<EN);
	_delay_ms(1);
	i2c_write(send_instruction);

	_delay_ms(10);

	/* Low nibble */

	send_instruction = low_nibble<<3;
	send_instruction |= (1<<EN);
	send_instruction &= ~(1<<RS);

	i2c_write(send_instruction);

	send_instruction &= ~(1<<EN);
	send_instruction |= (1<<BKL);
	_delay_ms(1);
	i2c_write(send_instruction);

	_delay_ms(10);
}


void screen_data(uint8_t data) {
	uint8_t high_nibble = (data)&0xF0;
	uint8_t low_nibble  = (data)&0x0F;

	/* High nibble */

	uint8_t send_data;
	send_data = high_nibble>>1;
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);

	i2c_write(send_data);

	send_data &= ~(1<<EN);
	_delay_ms(1);

	i2c_write(send_data);

	_delay_ms(10);

	/* Low nibble */

	send_data = low_nibble<<3;
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);

	i2c_write(send_data);

	send_data &= ~(1<<EN);
	_delay_ms(1);

	i2c_write(send_data);

	_delay_ms(10);

}

void send_4_bit_command(uint8_t command){
		/*
		 *  Sends a 4 bit command to the screen, using the I2C protocol.
		 *  The input is 2 bytes, in hex,, in the following order : BLK DB7 DB6 DB5 DB4 E RS x
		 */

		command |= (1<<EN);
		command &= ~(1<<RS);
		i2c_write(command);
		command &= ~(1<<EN);
		command &= ~(1<<RS);
		i2c_write(command);
}


void put_string(uint8_t string[], uint16_t length) {
	uint8_t NO_OF_CHARS = length / sizeof(uint8_t);

	for (int i = 0; i < NO_OF_CHARS; i++) {
		uint8_t character = string[i];
		screen_data(character);
	}
}


