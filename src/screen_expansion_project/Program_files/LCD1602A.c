/*
 * LCD1602A.c
 *
 *  Created on: Dec 11, 2018
 *      Author: joaorodrigues
 */

#include <LCD1602A.h>

/* Low level screen functions */

void ScreenInit(void) {
	/* Initializes the screen according to the datasheet.
	 */
	uint8_t command;

	/* Initial commands */

	command = 0x60;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPIMasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPIMasterTransmit(command);
	_delay_ms(41);
	command = 0x60;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPIMasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPIMasterTransmit(command);
	_delay_ms(1);
	command = 0x60;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPIMasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPIMasterTransmit(command);
	_delay_ms(1);
	command = 0x20;
	command |= (1<<EN);
	command &= ~(1<<RS);
	SPIMasterTransmit(command);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	SPIMasterTransmit(command);
	_delay_ms(10);

	/* Function Set */

	ScreenInstruction(LCD_FUNCTION_4BIT_2LINES);	/* 4Bit mode with 2Lines interface */

	/* Display OFF */

	ScreenInstruction(LCD_DISP_OFF);

	/* Display Clear */

	ScreenInstruction(LCD_DISP_CLEAR);

	/* Mode Set */

	ScreenInstruction(LCD_MODE_DEFAULT);			/* Default entry mode. Shifts to the right */
}

void ScreenInstruction(uint8_t instruction) {
	/* Sends an instruction to the screen
	 * uint8_t instruction - instruction to be sent
	 * Returns: void.
	 */

	uint8_t high_nibble = (instruction)&0xF0;	/* High 4bit nibble of the character */
	uint8_t low_nibble  = (instruction)&0x0F;	/* Low 4bit nibble of the character */

	/* if (SPI) reverse the instruction before sending */

	high_nibble = ReverseNibble(high_nibble)<<4;
	low_nibble 	= ReverseNibble(low_nibble)>>4;

	/* Send high nibble */

	uint8_t send_instruction;				/* Instruction to be sent */
	send_instruction = high_nibble>>1;		/* Shift high nibble to correct position */
	send_instruction |= (1<<EN);			/* Enable pin high */
	send_instruction &= ~(1<<RS);			/* RS pin low for instruction */

	SPIMasterTransmit(send_instruction);	/* Send instruction */

	send_instruction &= ~(1<<EN);			/* Enable pin low */

	SPIMasterTransmit(send_instruction);	/* Send again with EN low */

	_delay_ms(10);							/* Delay between screen writes */

	/* Send low nibble */

	send_instruction = low_nibble<<3;		/* Shift low nibble to correct position */
	send_instruction |= (1<<EN);			/* Same procedure as for high nibble */
	send_instruction &= ~(1<<RS);

	SPIMasterTransmit(send_instruction);

	send_instruction &= ~(1<<EN);
	send_instruction |= (1<<BKL);			/* Backlight pin high to enable baklight */

	SPIMasterTransmit(send_instruction);

	_delay_ms(10);
}

void ScreenData(uint8_t data) {
	/* Sends data to the screen.
	 * uint8_t data - data to be displayed
	 * Returns: void.
	 */

	uint8_t high_nibble = (data)&0xF0;	/* High 4bit nibble of the character */
	uint8_t low_nibble  = (data)&0x0F;	/* Low 4bit nibble of the character */

	/* if (SPI) reverse the data before sending */

	high_nibble = ReverseNibble(high_nibble);	/* Reverse high nibble */
	low_nibble = ReverseNibble(low_nibble);		/* Reverse low nibble */

	/* Send high nibble */

	uint8_t send_data;							/* Data to be sent */
	send_data = high_nibble>>1;					/* Shift high nibble to correct position */
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);		/* RS high for data, EN high, BKL high */

	SPIMasterTransmit(send_data);				/* Send data */

	send_data &= ~(1<<EN);						/* Enable low */

	SPIMasterTransmit(send_data);				/* Send data again with enable low */

	_delay_ms(10);

	/* Send low nibble */

	send_data = low_nibble<<3;					/* Shift low nibble to correct position */
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);		/* Same procedure as for high nibble */

	SPIMasterTransmit(send_data);

	send_data &= ~(1<<EN);

	SPIMasterTransmit(send_data);

	_delay_ms(10);

}

/* Higher level screen functions */

void PutChar(uint8_t character){
	/* Writes a character to the screen on the cursor current position.
	 * uint8_t character - the character to write
	 * Returns: void.
	 */

	ScreenData(character);		/* Send data to screen */
}

void PutString(uint8_t string[], uint16_t length) {
	/* Writes a string to the screen starting on the cursor current position.
	 * uint8_t string[] - character array to write
	 * uint16_t length - size of the character array obtained from sizeof(string)
	 * Returns: void.
	 */
	uint8_t NO_OF_CHARS = length / sizeof(uint8_t);

	for (int i = 0; i < NO_OF_CHARS; i++) { 	/* Iterate through the char array */
		uint8_t character = string[i];
		PutChar(character);						/* Put a char at a time on the screen */
	}
}

/* Utility functions */

uint8_t ReverseNibble(uint8_t nibble) {
	/* Reverses a nibble of data
	 * uint8_t nibble - nibble to reverse
	 * Returns: inverted nibble.
	 */

	uint8_t NO_OF_BITS = sizeof(nibble)*8; 	/* Number of bits the nibble */
	uint8_t rev_nibble = 0;					/* Reversed nibble temporary variable */

	for (int i = 0; i < NO_OF_BITS; i++) {	/* Iterate through the bits */
		if((nibble & (1 << i)))
		   rev_nibble |= 1 << ((NO_OF_BITS - 1) - i);	/* Build reversed nibble */
	}

	return rev_nibble;
}
