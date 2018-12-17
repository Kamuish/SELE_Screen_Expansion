/************************************************************************
 *																		*
 *		FILE NAME: Shift_Strings.h											*
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
 *		Dec 13, 2018	joaorodrigues													*
 *																		*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#ifndef HEADER_FILES_SHIFT_STRINGS_H_
#define HEADER_FILES_SHIFT_STRINGS_H_

#include <avr/io.h>
#include <LCD1602A.h>
#include <I2C_comms.h>
#include <SPI_comms.h>
#include <util/delay.h>
#include <UART_comms.h>

/* Define Screen protocol position */
#define LEFT_SCREEN_PROTOCOL SPI
#define RIGHT_SCREEN_PROTOCOL I2C

#define DEBUG 0

void StringOnLeftScreen(void);
void StringOnMiddleLeft(uint8_t *string, uint8_t string_count);
void StringOnRightScreen(void);
void StringOnMiddleRight(uint8_t *string, uint8_t string_count);

#endif /* HEADER_FILES_SHIFT_STRINGS_H_ */
