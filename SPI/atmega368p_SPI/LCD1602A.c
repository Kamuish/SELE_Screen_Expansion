/*
 * LCD1604.c
 *
 *  Created on: Dec 7, 2018
 *      Author: joaorodrigues
 */

#include <LCD1602A.h>

void screen_init(void) {
	/* Function Set */

	//screen_instruction(LCD_FUNCTION_4BIT_2LINES);

	/* Display OFF */

	//screen_instruction(LCD_DISP_OFF);

	/* Display Clear */

	//screen_instruction(0x01);

	/* Mode Set */

	//screen_instruction(LCD_MODE_DEFAULT);

	uint8_t command;

	command = 0x60;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	_delay_ms(41);
	command = 0x60;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	_delay_ms(1);
	command = 0x60;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	_delay_ms(1);
	command = 0x20;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	_delay_ms(10);

	/* Function Set */

	command = 0x20;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);

	_delay_ms(10);

	command = 0x08;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);

	_delay_ms(10);

	/* Display OFF */

	command = 0x00;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);

	_delay_ms(10);

	command = 0x48;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);

	_delay_ms(10);

	/* Display Clear */

	command = 0x00;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);

	_delay_ms(10);

	command = 0x40;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);

	_delay_ms(10);

	/* Mode Set */

	command = 0x00;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);

	_delay_ms(10);

	command = 0x30;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPI_MasterTransmit(command);

	_delay_ms(10);
}

void screen_instruction(uint8_t instruction) {
	uint8_t high_nibble = (instruction)&0xF0;
	uint8_t low_nibble  = (instruction)&0x0F;

	//high_nibble = reverse_nibble(high_nibble)<<4;
	//low_nibble 	= reverse_nibble(low_nibble)>>4;

	/* High nibble */

	uint8_t send_instruction;
	send_instruction = high_nibble>>1;
	send_instruction |= (1<<EN);
	send_instruction &= ~(1<<RS);

	SPI_MasterTransmit(send_instruction);

	send_instruction = high_nibble>>1;
	send_instruction &= ~(1<<EN);
	send_instruction &= ~(1<<RS);

	SPI_MasterTransmit(send_instruction);

	_delay_ms(10);

	/* Low nibble */

	send_instruction = low_nibble<<3;
	send_instruction |= (1<<EN);
	send_instruction &= ~(1<<RS);

	SPI_MasterTransmit(send_instruction);

	send_instruction = low_nibble<<3;
	send_instruction &= ~(1<<EN);
	send_instruction &= ~(1<<RS);

	SPI_MasterTransmit(send_instruction);

	_delay_ms(10);
}

void screen_data(uint8_t data) {
	uint8_t high_nibble = (data)&0xF0;
	uint8_t low_nibble  = (data)&0x0F;

	/* High nibble */

	uint8_t send_data;
	send_data = high_nibble>>1;
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);

	SPI_MasterTransmit(send_data);

	send_data = high_nibble>>1;
	send_data |= (1<<RS)|(1<<BKL);
	send_data &= ~(1<<EN);

	SPI_MasterTransmit(send_data);

	_delay_ms(10);

	/* Low nibble */

	send_data = low_nibble<<3;
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);

	SPI_MasterTransmit(send_data);

	send_data = low_nibble<<3;
	send_data |= (1<<RS)|(1<<BKL);
	send_data &= ~(1<<EN);

	SPI_MasterTransmit(send_data);

	_delay_ms(10);

}

void put_char(uint8_t character){
	uint8_t high_nibble = (character)&0xF0;
	uint8_t low_nibble = (character)&0x0F;

	uint8_t rev_high_nibble = reverse_nibble(high_nibble);
	uint8_t rev_low_nibble = reverse_nibble(low_nibble);

	uint8_t reverse_character = (rev_high_nibble<<4)|(rev_low_nibble>>4);

	screen_data(reverse_character);
}

uint8_t reverse_nibble(uint8_t nibble) {
	uint8_t NO_OF_BITS = sizeof(nibble)*8;
	uint8_t rev_nibble = 0;

	for (int i = 0; i < NO_OF_BITS; i++) {
		if((nibble & (1 << i)))
		   rev_nibble |= 1 << ((NO_OF_BITS - 1) - i);
	}

	return rev_nibble;
}

void put_string(uint8_t string[], uint16_t length) {
	uint8_t NO_OF_CHARS = length / sizeof(uint8_t);

	for (int i = 0; i < NO_OF_CHARS; i++) {
		uint8_t character = string[i];
		put_char(character);
	}
}
