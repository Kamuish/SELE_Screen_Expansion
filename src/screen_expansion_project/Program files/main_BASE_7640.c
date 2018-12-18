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
 *		Dec 17, 2018 	joaorodrigues			State Machine improvements *
 *		Dec 13, 2018 	André Silva             State machine			*
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
#define MIDDLE_LEFT 2
#define MIDDLE_RIGHT 3

int main(void) {

	/* TODO:
	 * - comply with JPL rule 15, 16, 25
	 * - Maybe initialize SPI/I2C here, instead of in the ScreenInit(...) function */

	/* Initialize the screen in SPI mode */
	ScreenInit(SPI);
	_delay_ms(1);

	/* Initialize the screen in I2C mode */
	ScreenInit(I2C);
	_delay_ms(1);

	/* String to put on the screens */
	uint8_t string[] = "123456789";
	uint8_t size = sizeof(string);		/* Size of the string */

	/* Display the string on the left screen */
	InitStringLeft(string, size);

	/* Initialize state machine on the LEFT state
	 * (since string is fully  on the left screen)
	 */
	uint8_t state = LEFT;
	uint8_t lcd_count = LCD_SIZE - ( size / sizeof(string[0] ) -1);
	uint8_t string_count = (size/sizeof(string[0])-1);

	while (1) {
		/* Delay between shifts */
		_delay_ms(1000);

		/* Choose state */
		switch (state) {
			case LEFT:
				/* String is completely on the left screen */

				/* if lcd_count == 0, the string has reached the end of the left screen */
				if (0 == lcd_count) {
					/* Clear screen on the right */
					ScreenInstruction(LCD_DISP_CLEAR, RIGHT_SCREEN_PROTOCOL);
					_delay_ms(1);

					/* Change state to MIDDLE_LEFT */
					state = MIDDLE_LEFT;

					/* Reset screen counter */
					lcd_count = LCD_SIZE - ( size / sizeof(string[0] ) -1);
				}

				break;
			case MIDDLE_LEFT:
				/* String is leaving the left screen and entering the right one */

				/* if string_count == 0, the string has completely left the left screen */
				if (0 == string_count) {
					/* Change state to RIGHT */
					state = RIGHT;

					/* Reset string counter */
					string_count = (size/sizeof(string[0])-1);
				}

				break;
			case RIGHT:
				/* String is completely on the right screen */

				/* if lcd_count == 0, the string has reached the end of the right screen */
				if (0 == lcd_count) {
					/* Clear screen on the left */
					ScreenInstruction(LCD_DISP_CLEAR, LEFT_SCREEN_PROTOCOL);
					_delay_ms(1);

					/* Change state to MIDDLE_RIGHT */
					state = MIDDLE_RIGHT;

					/* Reset screen counter */
					lcd_count = LCD_SIZE - ( size / sizeof(string[0] ) -1);
				}

				break;
			case MIDDLE_RIGHT:
				/* String is leaving the right screen and entering the left one */

				/* if string_count == 0, the string has completely left the right screen */
				if (0 == string_count) {
					/* Change state to LEFT */
					state = LEFT;

					/* Reset string counter */
					string_count = (size/sizeof(string[0])-1);
				}
				break;
		}

		/* Operate on state */
		switch (state) {
			case LEFT:
				/* String is completely on the left screen */
				StringOnLeftScreen();
				lcd_count--;			/* Decrease lcd_count */
				break;
			case MIDDLE_LEFT:
				/* String is leaving the left screen and entering the right one */
				StringOnMiddleLeft(string, string_count);
				string_count--;			/* Decrease string_count */
				break;
			case RIGHT:
				/* String is completely on the right screen */
				StringOnRightScreen();
				lcd_count--;			/* Decrease lcd_count */
				break;
			case MIDDLE_RIGHT:
				/* String is leaving the right screen and entering the left one */
				StringOnMiddleRight(string, string_count);
				string_count--;			/* Decrease string_count */
				break;
		}

	}


	return 0;
}
