/************************************************************************
 *																		*
 *		FILE NAME: SRAM.h											*
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

#ifndef SRAM_H_
#define SRAM_H_

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

#define CLASSB_NSECS         (8U)
#define CLASSB_OVERLAP       (25UL)
#define CLASSB_SEC_SIZE      (INTERNAL_SRAM_SIZE / CLASSB_NSECS)
#define CLASSB_SEC_REM       (INTERNAL_SRAM_SIZE % CLASSB_NSECS)
#define CLASSB_OVERLAP_SIZE  ((CLASSB_SEC_SIZE*CLASSB_OVERLAP)/100)

#if (0 == CLASSB_SEC_REM)
#  define CLASSB_NSEC_TOTAL CLASSB_NSECS
#else
#  define CLASSB_NSEC_TOTAL CLASSB_NSECS + 1
#endif

#define INTERNAL_SRAM_START (0x0100)
#define INTERNAL_SRAM_SIZE  (2048U)

#define SRAM_SIGNAL PB0

bool SRAM_Test(void);
bool SRAM_TestSection(register uint8_t current_section);
bool SRAM_MarchCTest(register volatile uint8_t p_sram[], register volatile uint8_t p_buffer[], register uint16_t size);
void SRAM_OK();
void SRAM_NOK();

#endif /* SRAM_H_ */
