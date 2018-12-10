/*
 * LCD.c
 *
 *  Created on: Dec 8, 2018
 *      Author: andre
 */


#include "i2cmaster.h"
#include "LCD.h"



uint8_t reverse_nibble(uint8_t nibble) {

		uint8_t NO_OF_BITS = sizeof(nibble)*8;
		uint8_t rev_nibble = 0;

		for (int i = 0; i < NO_OF_BITS; i++) {
			if((nibble & (1 << i)))
			   rev_nibble |= 1 << ((NO_OF_BITS - 1) - i);
		}

		return rev_nibble;
	}


void screen_init(void) {
	uint8_t command;

	command = 0x18;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(41);

	command = 0x18;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(1);

	command = 0x18;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(1);

	command = 0x10;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(10);


	//  Function set
	command = 0x10;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(10);

	command = 0x60;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(10);


	// Disp off
	command = 0x00;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);


	command = 0x40;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(10);

	// DIsp clear
	command = 0x00;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);

	command = 0x08;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(10);

	// Mode set
	command = 0x00;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);

	command = 0x30;
	command |= (1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	i2c_write(command);
	_delay_ms(10);
}



void screen_instruction(uint8_t instruction) {
	uint8_t high_nibble = (instruction)&0xF0;
	uint8_t low_nibble  = (instruction)&0x0F;

	high_nibble = high_nibble<<4;
	low_nibble 	=  low_nibble  >>4;

	/* High nibble */

	uint8_t send_instruction;
	send_instruction = high_nibble>>1;
	send_instruction |= (1<<EN);
	send_instruction &= ~(1<<RS);

	i2c_write(send_instruction);

	send_instruction &= ~(1<<EN);

	i2c_write(send_instruction);

	_delay_ms(10);

	/* Low nibble */

	send_instruction = low_nibble<<3;
	send_instruction |= (1<<EN);
	send_instruction &= ~(1<<RS);

	i2c_write(send_instruction);

	send_instruction &= ~(1<<EN);
	send_instruction |= (1<<BKL);

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

	i2c_write(send_data);

	_delay_ms(10);

	/* Low nibble */

	send_data = low_nibble<<3;
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);

	i2c_write(send_data);

	send_data &= ~(1<<EN);

	i2c_write(send_data);

	_delay_ms(10);

}

void put_char(uint8_t character){
	uint8_t high_nibble = (character)&0xF0;
	uint8_t low_nibble = (character)&0x0F;

	high_nibble = reverse_nibble(high_nibble);
		low_nibble = reverse_nibble(low_nibble);


	character = (high_nibble<<4)|(low_nibble>>4);

	screen_data(character);
}


void put_string(uint8_t string[], uint16_t length) {
	uint8_t NO_OF_CHARS = length / sizeof(uint8_t);

	for (int i = 0; i < NO_OF_CHARS; i++) {
		uint8_t character = string[i];
		put_char(character);
	}
}


