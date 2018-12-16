/*
 * flash.c
 *
 *  Created on: Dec 15, 2018
 *      Author: andre
 */

#include "flash.h"


// stores the variable in the eeprom

uint16_t EEMEM eptr_eeprom_code_hash = 10;

/*
uint8_t  flash_teste(void){
	// Hash of the flash
	uint16_t hash = flash_test_calculate_xor();

	// Previously written value
	uint16_t true_hash = eeprom_read_word(&eptr_eeprom_code_hash);
	return ( hash == true_hash) ? 0: 1;
}

uint16_t flash_test_calculate_xor(void) {
    uint16_t hash = 0;

    for (uint16_t k = 0; k < BYTES_FLASH - 1; k += 2) {
        uint16_t value = pgm_read_word_near(k);
        hash ^= value;
    }

    return hash;
}

*/
