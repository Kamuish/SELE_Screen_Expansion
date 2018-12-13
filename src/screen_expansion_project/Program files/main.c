/************************************************************************
 *																		*
 *		FILE NAME: main.c											*
 *		PURPOSE:														*
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
 *		Dec 11, 2018	joaorodrigues													*
 *																		*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include <SPI_comms.h>
#include <I2C_comms.h>
#include <LCD1602A.h>

//#define F_CPU 1600000UL

int main(void) {
	ScreenInit(SPI);

	/* Display ON, Cursor Blink */

	uint8_t command;

	command = LCD_DISP_ON_BLINK;
	ScreenInstruction(command, SPI);

	/* Print a string */

	uint8_t string[] = "ABCDEFGHIJKLMNO";
	PutString(string, sizeof(string) - 1, SPI);
	_delay_ms(5000);

	while (1) {
		//ScreenInstruction(LCD_MOVE_DISP_RIGHT, SPI);
		_delay_ms(10000);
	}

	return 0;
}
