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
 *		Dec 11, 2018 	joaorodrigues													*
 *		Dec 13, 2018 	André Silva                  State machine																*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include <SPI_comms.h>
#include <I2C_comms.h>
#include <LCD1602A.h>
#include <UART_comms.h>
#include <util/delay.h>
#include <Shift_Strings.h>

#define F_CPU 16000000UL

#define LEFT 0
#define RIGHT 1
#define MIDDLE 2
#define END 3

int main(void) {
	ScreenInit(SPI);
	_delay_ms(1);
	ScreenInit(I2C);
	_delay_ms(1);

	uint8_t command;

	command = LCD_DISP_ON;
	_delay_ms(1);
	ScreenInstruction(command, I2C);
	_delay_ms(1);
	ScreenInstruction(command, SPI);
	_delay_ms(1);

	/* String to put on the screens */
	uint8_t string[] = "123456789";
	uint8_t size = sizeof(string);

	/*  TODO: comply with JPL rule 15, 16, 25 */

	uint8_t lcd_count  = LCD_SIZE - (size/sizeof(string[0])-1);

	/* index of the first letter to change screens*/
	uint8_t string_count = (size/sizeof(string[0])-1);

	/* Flag for the M and S state*/
	PutString(string, size - 1, SPI);
	_delay_ms(10);

	ScreenInstruction(LCD_MOVE_CURSOR_HOME,SPI);
	_delay_ms(10);

	uint8_t state = LEFT;

	while (1) {

		/* Choose state */
		switch (state) {
			case LEFT:
				if (0 == lcd_count) {
					ScreenInstruction(LCD_DISP_CLEAR,I2C);
					_delay_ms(1);

					/* Change state to middle */
					state = MIDDLE;

					/* reset the counter */
					lcd_count = LCD_SIZE - ( size / sizeof(string[0] ) -1);
				}
				break;
			case MIDDLE:
				if (0 == string_count) {
					state = RIGHT;

					/* reset the counter */
					string_count = (size/sizeof(string[0])-1);
				}
				break;
			case RIGHT:
				if (0 == lcd_count) {
					ScreenInstruction(LCD_DISP_CLEAR, SPI);
					_delay_ms(1);

					/* Change state to middle */
					state = END;
					/* reset the counter */
					lcd_count = LCD_SIZE - ( size / sizeof(string[0] ) -1);
				}
				break;
			case END:
				if (0 == string_count) {
					state = LEFT;

					/* reset the counter */
					string_count = (size/sizeof(string[0])-1);
				}
				break;
				break;
		}

		/* Operate on state */
		switch (state) {
			case LEFT:
				StringOnLeftScreen();

				lcd_count--;
				break;
			case MIDDLE:
				StringOnMiddleLeft(string, string_count);

				string_count--;
				break;
			case RIGHT:
				StringOnRightScreen();

				lcd_count--;
				break;
				break;
			case END:
				StringOnMiddleRight(string, string_count);

				string_count--;
				break;
		}

		_delay_ms(100);

	}


	return 0;
}
