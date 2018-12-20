/************************************************************************
 *																		*
 *		FILE NAME: FLASH_test.c										*
 *		PURPOSE:
 *			Implementation of tests for the FLASH memory. To validate this memory we compare
 *			a previously calculated  (with a python script) hash of the .hex file  stored on the EEPROM
 *			memory (a different project was used to write on the EEPROM memory) with a 16 bit XOR hash
 *			calculated on the utilized bytes of the FLASH memory.  					*
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
 *		Dec 11, 2018	André Silva													*
 *																		*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include <FLASH_test.h>

bool  FLASH_Test(void)
{
	/* Compares the XOR hash of the flash memory with the one present on the eeprom memory
	 * on the address 0x22
	 * */

	uint16_t hash = FLASH_CalculateHashXOR();

	/* Reads previously written hash value */
	uint16_t true_hash = eeprom_read_word ((uint16_t *)EEPROM_ADDR);
	return (bool)(hash != true_hash);
}

uint16_t FLASH_CalculateHashXOR(void)
{
	/* 
	 * Calculates 16 bit XOR hash of the utilized flash memory
	 */ 

    uint16_t hash = 0; /* Variable to hold the hash */

    for (uint16_t k = 0; k < BYTES_FLASH - 1; k += 2) {
        uint16_t value = pgm_read_word_near(k);
        hash ^= value;
    }

    return hash;
}


