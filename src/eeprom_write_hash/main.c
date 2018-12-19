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
 *		Dec 19, 2018	joaorodrigues													*
 *																		*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include <avr/eeprom.h>
#include <stdint.h>

#define eeprom_addr 70

int main(void)
{
	uint16_t word = 55199;
	eeprom_write_word((uint16_t *)eeprom_addr, (uint16_t)word);
}
