/*
 * flash.c
 *
 *  Created on: Dec 15, 2018
 *      Author: andre
 */

#include <flash.h>

uint8_t  flash_teste(void){
	/* Compares the XOR hash of the flash memory with the one present on the eeprom memory
	 * on the address 0x22
	 * */

	uint16_t hash = calculate_hash_xor();

	/* Reads previously written hash value */
	uint16_t true_hash = eeprom_read_word ((const uint16_t*)0x22);
	return ( hash == true_hash);
}

uint16_t calculate_hash_xor(void)
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


