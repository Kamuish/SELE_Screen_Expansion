/*
 * flash.c
 *
 *  Created on: Dec 15, 2018
 *      Author: andre
 */

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


