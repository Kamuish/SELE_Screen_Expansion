/************************************************************************
 *																		                                                                                                *
 *		FILE NAME: main.c																			                                 			*
 *		PURPOSE:
 *				Main program of the project. IMplements a state machine to shift the
 *				string between both screens.
 *				Before executing the code, we test 3 memories: FLASH, EEPROM and
 *				SRAM. If either one of these tests fails, a message is displayed and the code
 *				execution is halted.
 *								                                		                                 				*
 *		FILE REFERENCES:																			                                 			*
 *																																		                                *
 *		Name			I/O			Description																		   						*
 *		----			---			-----------																			      					*
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
 *		Dec 13, 2018 	André Silva               State machine			*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include <util/delay.h>

/* Include communication libraries */
#include <SPI_comms.h>
#include <I2C_comms.h>

/* Include screen related libraries */
#include <LCD1602A.h>
#include <Shift_Strings.h>

/* Include testing libraries */
#include <SRAM_test.h>
#include <FLASH_test.h>
#include <EEPROM_test.h>

/* Define clock frequency */
#define F_CPU 14745600UL

/* Define State Machine states */
#define LEFT         0
#define RIGHT        1
#define MIDDLE_LEFT  2
#define MIDDLE_RIGHT 3

int main(void) {

	bool memory_tests_error = 0; /* Global memory tests error flag */

	/* Test the EEPROM */
	bool eeprom_test = EEPROM_Test();

	/* Test the FLASH */
	bool flash_test = FLASH_Test();

	/* Test the SRAM */
	bool sram_test = SRAM_Test();

	eeprom_test = 0;
	flash_test = 0;
	sram_test = 0;

	/* Initialize the screen in SPI mode */
	ScreenInit(SPI);
	_delay_ms(1);

	/* Initialize the screen in I2C mode */
	ScreenInit(I2C);
	_delay_ms(1);

	/* Display the EEPROM test result */
	uint8_t EEPROM_ok[] = "EEPROM OK";
	uint8_t EEPROM_nok[] = "EEPROM NOT OK";

	PutString(eeprom_test ? EEPROM_nok : EEPROM_ok, eeprom_test ? sizeof(EEPROM_nok) - 1 : sizeof(EEPROM_ok) - 1, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1000);
	ScreenInstruction(LCD_DISP_CLEAR, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(10);

	/* Display the FLASH test result */
	uint8_t FLASH_ok[] = "FLASH OK";
	uint8_t FLASH_nok[] = "FLASH NOT OK";

	PutString(flash_test ? FLASH_nok : FLASH_ok, flash_test ? sizeof(FLASH_nok) - 1 : sizeof(FLASH_ok) - 1, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1000);
	ScreenInstruction(LCD_DISP_CLEAR, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(10);

	/* Display the SRAM test result */
	uint8_t SRAM_ok[] = "SRAM OK";
	uint8_t SRAM_nok[] = "SRAM NOT OK";

	PutString(sram_test ? SRAM_nok : SRAM_ok, sram_test ? sizeof(SRAM_nok) - 1 : sizeof(SRAM_ok) - 1, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1000);
	ScreenInstruction(LCD_DISP_CLEAR, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(10);

	memory_tests_error |= (sram_test)|(flash_test)|(eeprom_test);

	/* If one of the tests did not pass, return */
	if (memory_tests_error)
	{
		uint8_t mem_test_error_msg[] = "MEM ERROR. EXIT.";
		PutString(mem_test_error_msg, sizeof(mem_test_error_msg) - 1, RIGHT_SCREEN_PROTOCOL);
		_delay_ms(1000);

		return 1;
	}

	/* String to put on the screens */
	uint8_t string[] = "0123456789";
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
		_delay_ms(250);

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
				
			default:
				/* The state machine should never reach this case */
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

			default:
				/* The state machine should never reach this case */
				break;
		}

	}


	return 0;
}
