#include "LCD.h"


void screen_init(uint8_t addr, uint8_t comm[]){
	/*
	 *  Initializes the screen, with the I2C interface if the slave address is different than 0xFF. Otherwise,
	 *  it uses the SPI interface.
	 *  It's assumed that the configuration of the interfaces has been already done before invoking this function
	 */

	if ("I2C" == comm){
		// Initialize backpack
	}
	uint8_t command;

	command = 0x18;
	send_4_bit_command(command, comm);
	_delay_ms(41);

	command = 0x18;
	send_4_bit_command(command, comm);
	_delay_ms(1);

	command = 0x18;
	send_4_bit_command(command, comm);
	_delay_ms(1);

	command = 0x10;
	send_4_bit_command(command, comm);
	_delay_ms(10);


	//  Function set
	screen_instruction(LCD_FUNCTION_4BIT_2LINES, comm);

	// Disp off

	screen_instruction(LCD_DISP_OFF, comm);

	// Disp clear
	screen_instruction(LCD_DISP_CLEAR, comm);


	// Mode set
	screen_instruction(LCD_ENTRY_INC_, comm);

}


void screen_instruction(uint8_t instruction, uint8_t comm[] ) {
	uint8_t high_nibble = (instruction)&0xF0;
	uint8_t low_nibble  = (instruction)&0x0F;

	/* High nibble */

	uint8_t send_instruction;
	send_instruction = high_nibble>>1;
	send_instruction |= (1<<EN);
	send_instruction |= (1<<BKL);
	send_instruction &= ~(1<<RS);

	transfer_data(send_instruction,comm);

	send_instruction &= ~(1<<EN);
	_delay_ms(1);
	transfer_data(send_instruction,comm);

	_delay_ms(10);

	/* Low nibble */

	send_instruction = low_nibble<<3;
	send_instruction |= (1<<EN);
	send_instruction &= ~(1<<RS);

	transfer_data(send_instruction,comm);

	send_instruction &= ~(1<<EN);
	send_instruction |= (1<<BKL);
	_delay_ms(1);
	transfer_data(send_instruction,comm);

	_delay_ms(10);
}

void transfer_data(uint8_t data, uint8_t comm[] ){
	if ( "I2C" == comm)
	{
		i2c_write(send_data);
	}
	else
	{
		// SPI
	}
}

void screen_data(uint8_t data, uint8_t comm[] ){
    /*
	 * Sends an 8-bit data command to the screen
	 */

	uint8_t high_nibble = (data)&0xF0;
	uint8_t low_nibble  = (data)&0x0F;

	/* High nibble */

	uint8_t send_data;
	send_data = high_nibble>>1;
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);

	transfer_data(send_data,comm);

	send_data &= ~(1<<EN);
	_delay_ms(1);

	transfer_data(send_data,comm);
	_delay_ms(10);

	/* Low nibble */
	send_data = low_nibble<<3;
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);
	transfer_data(send_data,comm);

	send_data &= ~(1<<EN);
	_delay_ms(1);

	transfer_data(send_data,comm);

	}
}


void put_string(uint8_t string[], uint16_t length) {
	uint8_t NO_OF_CHARS = length / sizeof(uint8_t);

	for (int i = 0; i < NO_OF_CHARS; i++) {
		uint8_t character = string[i];
		screen_data(character);
	}
}

void send_4_bit_command(uint8_t command, uint8_t comm[]){
	// sends a 4 bit command, via I2C or SPI

	command |= (1<<EN);
	command &= ~(1<<RS);
	transfer_data(command,comm);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	transfer_data(command,comm);

}


