/************************************************************************
 *																		*
 *		FILE NAME: SRAM.c											*
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

static uint8_t classb_buffer[CLASSB_SEC_SIZE + CLASSB_OVERLAP_SIZE] __attribute__((section(".classb_sram_buffer")));

bool SRAMTest(void)  {
    register bool has_errors = 0;

    for (register uint8_t i = 0; i < CLASSB_NSEC_TOTAL - 1; i++) {
        if (SRAMTestSection(i)) {
            has_errors = 1;
            break;
        }
    }

    return has_errors;
}

bool SRAMTestSection(register uint8_t current_section) {
    register uint8_t error = 0;

    switch (current_section) {
    case 0:
        /* Test the buffer */
        error = MarchCTest((uint8_t *)INTERNAL_SRAM_START, classb_buffer, CLASSB_SEC_SIZE + CLASSB_OVERLAP_SIZE);
        break;
    case 1:
        /* Test the first section. */
        error = MarchCTest((uint8_t *)INTERNAL_SRAM_START + CLASSB_SEC_SIZE, classb_buffer, CLASSB_SEC_SIZE);
        break;
    case CLASSB_NSECS:
        /* Test the last section. */
        error = MarchCTest((uint8_t *)INTERNAL_SRAM_START + CLASSB_NSECS * CLASSB_SEC_SIZE - CLASSB_OVERLAP_SIZE, classb_buffer, CLASSB_SEC_REM + CLASSB_OVERLAP_SIZE);
        break;
    default:
        /* Sections in the middle */
        error = MarchCTest((uint8_t *)INTERNAL_SRAM_START + current_section * CLASSB_SEC_SIZE - CLASSB_OVERLAP_SIZE, classb_buffer, CLASSB_SEC_SIZE + CLASSB_OVERLAP_SIZE);
        break;
    }

    return error;
}

bool MarchCTest(register volatile uint8_t p_sram[], register volatile uint8_t p_buffer[], register uint16_t size) {
	/* Applies the March C test to the SRAM contents */

	register uint16_t i = 0;
	register uint8_t error = 0;

	/* Save to buffer unless buffer is being tested */
	if (p_buffer != p_sram) {
		for (i = 0; i < size; i++) {
			p_buffer[i] = p_sram[i];
		}
	}

	/* M0 - Increasing address, write 0 */
	for (i = 0; i < size; i++) {
		p_sram[i] = 0x00;
	}

	/* M1 - Increasing address, read 0, write 1 */
	for (i = 0; i < size; i++) {
		if (p_sram[i] != 0x00) error = 1;
		p_sram[i] = 0xFF;
	}

	/* M2 - Increasing address, read 1, write 0 */
	for (i = 0; i < size; i++) {
		if (p_sram[i] != 0xFF) error = 1;
		p_sram[i] = 0x00;
	}

	/* M3 - Decreasing address, read 0, write 1 */
	for (i = size - 1; i > 0; i--) {
		if (p_sram[i] != 0x00) error = 1;
		p_sram[i] = 0xFF;
	}

	/* M4 - Decreasing address, read 1, write 0 */
	for (i = size - 1; i > 0; i--) {
		if (p_sram[i] != 0xFF) error = 1;
		p_sram[i] = 0x00;
	}

	/* M5 - Decreasing address, read 0 */
	for (i = size - 1; i > 0; i--) {
		if (p_sram[i] != 0x00) error = 1;
	}

	/* Restore from buffer, unless buffer is being checked */
	if (p_buffer != p_sram) {
		for (i = 0; i < size; i++) {
			p_sram[i] = p_buffer[i];
		}
	}

	return error;
}
