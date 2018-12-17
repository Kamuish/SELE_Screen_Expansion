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
 *		Dec 15, 2018	joaorodrigues													*
 *																		*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include <SRAM.h>
#include <UART_comms.h>
#include <util/delay.h>
#include <avr/eeprom.h>

int main(void) {

	uart_init();
	stdout = &uart_output;

	puts("UART communication established.");

	_delay_ms(2000);

	puts("Testing SRAM");

	_delay_ms(2000);

	/* Test SRAM */
	bool sram_test = SRAMTest();
	sram_test ? puts("Error in SRAM.") : puts("SRAM OK!");

	_delay_ms(2000);

	puts("Finished testing SRAM");

	_delay_ms(2000);

	return 0;
}
