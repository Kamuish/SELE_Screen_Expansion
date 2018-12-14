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
#include <Shift_Strings.h>

#define F_CPU 16000000UL

int main(void) {
	//ScreenInit(SPI);
	_delay_ms(1);
	ScreenInit(I2C);
	_delay_ms(1);

	_delay_ms(1);
		ScreenInit(SPI);
		_delay_ms(1);

	uint8_t command;

	command = LCD_DISP_ON;
	//ScreenInstruction(command, SPI);
	_delay_ms(1);
	ScreenInstruction(command, I2C);
	_delay_ms(1);
	ScreenInstruction(command, SPI);
	_delay_ms(1);

	/***********************************/
	/* Initializes State machine variables */
	/*                                                                             */
	/***********************************/

	/* String to put on the screens */
	uint8_t string1[] = "CHUPA, NOBREGA";

	uint8_t state = 'L';
	/*number of pixels */
	uint8_t screen_bits = 16 ;
	/* number of allowed shifts won the right and left screen */

	uint8_t count_left = screen_bits - (sizeof(string1)/sizeof(string1[0])-1) + 1 ;
	uint8_t count_right = screen_bits - (sizeof(string1)/sizeof(string1[0])-1) + 1 ;

	/* index of the first letter to change screens*/
	uint8_t shift_middle = (sizeof(string1)/sizeof(string1[0])-1)  - 2;
	uint8_t shift_end = (sizeof(string1)/sizeof(string1[0])-1) - 2 ;

	/* Flag for the M and S state*/
	uint8_t flag = 0;
	PutString(string1, sizeof(string1) - 1, SPI);
	_delay_ms(10);


	int k = 0;
	for (k = 0; k < (sizeof(string1)/sizeof(string1[0])-1) ; k++){
		ScreenInstruction(LCD_MOVE_CURSOR_LEFT,SPI);
		_delay_ms(10);
	}

	/*  TODO: comply with JPL rule 15, 16, 25 */
	/*  TODO: limpar a RAM depois de uma volta completa, se nao vamos ter loop back da mensagem */
	while (1) {
		/* @non-terminating@ */

		_delay_ms(1000);

		#if(DEBUG == 1)
		ScreenInstruction(LCD_DISP_CLEAR,I2C);
		PutChar(state, I2C);
		#endif

        switch(state)
        {
            case 'L':
                /* ALl on left screen*/

            	ScreenInstruction(LCD_MOVE_DISP_RIGHT,SPI);
				_delay_ms(10);

				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);
				_delay_ms(10);

				count_left--;
				if (0 == count_left)
                {
					ScreenInstruction(LCD_DISP_CLEAR,I2C);
					_delay_ms(10);

					/* Change state to middle */
                	state = 'M';
					/* reset the counter */
					count_left = screen_bits - ( sizeof(string1) / sizeof(string1[0] ) -1) + 1 ;

					/* Put character on the right screen */
					PutChar(string1[ (sizeof(string1)/sizeof(string1[0]) - 1) -1 ],I2C);
					_delay_ms(10);
					ScreenInstruction(LCD_MOVE_CURSOR_LEFT,I2C);
                }
                break;

            case 'M':

                /* On the middle*/
                /* Shift of the left screen */

            	ScreenInstruction(LCD_MOVE_DISP_RIGHT,SPI);
				_delay_ms(10);
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);
				_delay_ms(10);

	        	ScreenInstruction(LCD_MOVE_DISP_RIGHT,I2C);
				_delay_ms(10);
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, I2C);
				_delay_ms(10);

                /* Put character on the right screen */
				PutChar(string1[shift_middle],I2C);

				_delay_ms(10);
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT,I2C);

                if (0 == flag)
                {
                	shift_middle--;
 				   if (shift_middle == 0)
 				   {
 							flag = 1;
 				   }
                }
                else
				{
					state = 'R';
					flag = 0;
					/* reset the counter */
					shift_middle = (sizeof(string1)/sizeof(string1[0])-1)  - 2 ;
				}
                break;

            case 'R':
                /* All on the right screen */

            	 ScreenInstruction(LCD_MOVE_DISP_RIGHT,I2C);
				_delay_ms(10);
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, I2C);
				_delay_ms(10);

				count_right--;

				if ( 0 == count_right )
				{
					ScreenInstruction(LCD_DISP_CLEAR, SPI);
					_delay_ms(10);
					state = 'S';
					/* reset the counter */
					count_right = screen_bits - (sizeof(string1)/sizeof(string1[0])-1) + 1 ;

					PutChar(string1[( sizeof(string1) / sizeof(string1[0]) - 1)  - 1 ], SPI);
					_delay_ms(10);
					ScreenInstruction(LCD_MOVE_CURSOR_LEFT,SPI);
				}

				break;

            case 'S':
            	/* Case in which the string is coming out of the right screen and entering the left one */

            	ScreenInstruction(LCD_MOVE_DISP_RIGHT, I2C);
				_delay_ms(10);
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, I2C);

				/* Shift on the right screen*/
				ScreenInstruction(LCD_MOVE_DISP_RIGHT, SPI);
				_delay_ms(10);
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);
				_delay_ms(10);


				PutChar(string1[shift_end], SPI);
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);

				if (0 == flag)
				{
					shift_end--;
				   if ( 0 == shift_end)
				   {
							flag = 1;
				   }
				}
				else
				{
					state = 'I';
					flag = 0;
					// reset the counter
					shift_end =  ( sizeof(string1) / sizeof(string1[0] ) - 1 ) -2  ;
				}
				break;

            case 'I':
            	/* return to initial position */
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);
				ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);

				state = 'L';
        	}

		}


	return 0;
}
