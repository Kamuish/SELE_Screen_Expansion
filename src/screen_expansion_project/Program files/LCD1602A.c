/************************************************************************
 *																		*
 *		FILE NAME: LCD1602A.c											*
 *		PURPOSE:
 *			LIbrary for the LCD1602A, for both SPI and I2C communication protocols.
 *			We defined functions for initializing the screens, sending instructions and displaying
 *			data. Almost all functions expect a parameter to choose the SPI or the I2C communication
 *			protocol.
 *							*
 *		FILE REFERENCES:												*
 *																		*
 *		Name			I/O			Description							*
 *		----			---			-----------							*
 *																		*
 *		EXTERNAL VARIABLES:												*
 *																		*
 *		Name	Type	I/O			Description							*
 *		----	----	---			----------- 						*
 *																		*
 *		EXTERNAL REFERENCES:											*
 *																		*
 *		Name						Description							*
 *		----						-----------							*
 *																		*
 * 		ABNORMAL TERMINATION CONDITIONS, ERROR AND WARNING MESSAGES: 	*
 *																		*
 * 		ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS:							*
 *																		*
 *		NOTES:															*
 *																		*
 * 		REQUIREMENTS/FUNCTIONAL SPECIFICATIONS REFERENCES:				*
 *																		*
 * 		DEVELOPMENT HISTORY:											*
 *																		*
 *		Date	Author	Change ID	Release		Description of change	*
 *		Dec 11, 2018	joaorodrigues					SPI implementation				*
 *		Dec 14, 2018	Andre silva					I2C implementation
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include <LCD1602A.h>

void ScreenInit(uint8_t protocol_flag) {
	/* Initializes the screen according to the datasheet.
	 * uint8_t protocol_flag : Allows to choose the protocol to use for the communication
	 */

	/* Initial commands */

	(I2C == protocol_flag) ? I2C_InitScreen(): SPI_InitScreen();

	/* Function Set */

	ScreenInstruction(LCD_FUNCTION_4BIT_1LINE, protocol_flag);	/* 4Bit mode with 2Lines interface */

	/* Display OFF */

	ScreenInstruction(LCD_DISP_OFF, protocol_flag);

	/* Display Clear */

	ScreenInstruction(LCD_DISP_CLEAR, protocol_flag);

	/* Mode Set */

	ScreenInstruction(LCD_MODE_DEFAULT, protocol_flag);			/* Default entry mode. Shifts to the right */

	/* Turn the display ON */
	ScreenInstruction(LCD_DISP_ON, protocol_flag);
}

void I2C_InitScreen(void){
	/* Initializes the I2C interface and sends the necessary commands to initialize the MCP23008
	 * on the backpack and, afterwards, initializes the screen.
	 */
	I2C_Init();
	_delay_ms(100);

	uint8_t command;

	/* Initialize backpack */

	_delay_ms(100);
	
	I2C_Start(I2C_ADDR); /* COnfigures all  the pins as outputs*/
	_delay_ms(1);
	I2C_Write(0x00); /* register I2C_ADDR */
	_delay_ms(1);
	I2C_Write(0x00); /* clear all bits */
	I2C_Stop();
	_delay_ms(100);
	
	I2C_Start(I2C_ADDR);  /* set up internal register for continuous write to address */
	_delay_ms(100);
	I2C_Write(0x05);
	_delay_ms(10);
	I2C_Write(0x20);
	I2C_Stop();

	
	I2C_Start(I2C_ADDR); /* Prepares to write on the GPIO registers*/
	_delay_ms(100);
	I2C_Write(0x09); /* gpio register */
	_delay_ms(10);

	/* Screen init */
	command = 0x18;
	Send4BitCommand(command, I2C);
	_delay_ms(41);

	command = 0x18;
	Send4BitCommand(command, I2C);
	_delay_ms(1);

	command = 0x18;
	Send4BitCommand(command, I2C);
	_delay_ms(1);

	command = 0x10;
	Send4BitCommand(command, I2C);
	_delay_ms(10);
}

void SPI_InitScreen(void){
	/* Initializes the SPI interface and sends the necessary commands to initialize the screen (accordingly to
	 * the datasheet).
	 */
	SPI_MasterInit();
	_delay_ms(400);

	uint8_t command;

	command = 0x60;
	Send4BitCommand(command, SPI);
	_delay_ms(41);

	command = 0x60;
	Send4BitCommand(command, SPI);
	_delay_ms(1);

	command = 0x60;
	Send4BitCommand(command, SPI);
	_delay_ms(1);

	command = 0x20;
	Send4BitCommand(command, SPI);
	_delay_ms(10);
}

void ScreenInstruction(uint8_t instruction, uint8_t protocol_flag) {
	/* Sends an instruction to the screen
	 * uint8_t instruction - instruction to be sent
	 * Returns: void.
	 */

	uint8_t high_nibble = (instruction)&0xF0;	/* High 4bit nibble of the character */
	uint8_t low_nibble  = (instruction)&0x0F;	/* Low 4bit nibble of the character */

	/* if (SPI) reverse the instruction before sending */
	if (SPI == protocol_flag) {
		high_nibble = ReverseNibble(high_nibble)<<4;
		low_nibble 	= ReverseNibble(low_nibble)>>4;
	}

	/* Send high nibble */

	uint8_t send_instruction;				/* Instruction to be sent */
	send_instruction  = high_nibble>>1;		/* Shift high nibble to correct position */
	send_instruction |= (1<<BKL);			/* Backlight pin high to enable baklight */
	send_instruction |= (1<<EN);			/* Enable pin high */
	send_instruction &= ~(1<<RS);			/* RS pin low for instruction */

	TransferData(send_instruction, protocol_flag);	/* Send instruction */

	send_instruction &= ~(1<<EN);			/* Enable pin low */

	TransferData(send_instruction, protocol_flag);	/* Send again with EN low */

	_delay_ms(10);							/* Delay between screen writes */

	/* Send low nibble */

	send_instruction = low_nibble<<3;		/* Shift low nibble to correct position */
	send_instruction |= (1<<BKL);			/* Backlight pin high to enable baklight */
	send_instruction |= (1<<EN);			/* Same procedure as for high nibble */
	send_instruction &= ~(1<<RS);

	TransferData(send_instruction, protocol_flag);

	send_instruction &= ~(1<<EN);


	TransferData(send_instruction, protocol_flag);

	_delay_ms(10);
}

void ScreenData(uint8_t data, uint8_t protocol_flag) {
	/* Sends data to the screen.
	 * uint8_t data - data to be displayed
	 * Returns: void.
	 */

	uint8_t high_nibble = (data) & 0xF0;	/* High 4bit nibble of the character */
	uint8_t low_nibble  = (data) & 0x0F;	/* Low 4bit nibble of the character */

	/* Send high nibble */

	uint8_t send_data;							/* Data to be sent */
	send_data = high_nibble>>1;					/* Shift high nibble to correct position */
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);		/* RS high for data, EN high, BKL high */

	TransferData(send_data, protocol_flag);	/* Send data */

	send_data &= ~(1<<EN);						/* Enable low */

	TransferData(send_data, protocol_flag);	/* Send data again with enable low */

	_delay_ms(10);

	/* Send low nibble */

	send_data = low_nibble<<3;					/* Shift low nibble to correct position */
	send_data |= (1<<RS)|(1<<EN)|(1<<BKL);		/* Same procedure as for high nibble */

	TransferData(send_data, protocol_flag);

	send_data &= ~(1<<EN);

	TransferData(send_data, protocol_flag);

	_delay_ms(10);
}

/* Higher level screen functions */

void PutChar(uint8_t character, uint8_t protocol_flag){
	/* Writes a character to the screen on the cursor current position.
	 * uint8_t character - the character to write
	 * Returns: void.
	 */

	/* if (SPI) reverse the data before sending */
	if (SPI == protocol_flag){
		uint8_t high_nibble = (character)&0xF0;
		uint8_t low_nibble = (character)&0x0F;

		high_nibble = ReverseNibble(high_nibble);
		low_nibble = ReverseNibble(low_nibble);

		character = (high_nibble<<4)|(low_nibble>>4);

	}

	ScreenData(character, protocol_flag);		/* Send data to screen */
}

void PutString(uint8_t string[], uint16_t length, uint8_t protocol_flag) {
	/* Writes a string to the screen starting on the cursor current position.
	 * uint8_t string[] - character array to write
	 * uint16_t length - size of the character array obtained from sizeof(string)
	 * Returns: void.
	 */
	uint8_t NO_OF_CHARS = length / sizeof(uint8_t);

	for (uint8_t i = 0; i < NO_OF_CHARS; i++) { 	/* Iterate through the char array */
		uint8_t character = string[i];
		PutChar(character, protocol_flag);						/* Put a char at a time on the screen */
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

	for (uint8_t i = 0; i < NO_OF_BITS; i++) {	/* Iterate through the bits */
		if((nibble & (1 << i)))
		   rev_nibble |= 1 << ((NO_OF_BITS - 1) - i);	/* Build reversed nibble */
	}

	return rev_nibble;
}

void TransferData(uint8_t data, uint8_t protocol_flag){
	/* Uses the I2C protocol or the SPI, depending on the passed flag
	 * uint8_t data - data to send
	 * uint8_t protocol_flag - Chooses the protocol to use. Can be SPI or I2C
	 * Returns: void
	 */

    I2C == protocol_flag ? I2C_Write(data): SPI_MasterTransmit(data);
}

void Send4BitCommand(uint8_t command, uint8_t protocol_flag){
	/* Uses the I2C protocol or the SPI, depending on the passed flag, to pass a 4 bit command.
	 * 	Sends a command with the Enable bit set  and RS clear and, afterwards, sends the same command
	 * 	with the Enable bit clear.
	 * uint8_t command - command to send
	 * uint8_t protocol_flag - Chooses the protocol to use. Can be SPI or I2C
	 * Returns: void
	 */

	command |= (1<<EN);
	command &= ~(1<<RS);
	TransferData(command, protocol_flag);
	command &= ~(1<<EN);
	command &= ~(1<<RS);
	TransferData(command, protocol_flag);

}
