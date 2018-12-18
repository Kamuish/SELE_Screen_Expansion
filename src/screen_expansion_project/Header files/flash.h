/*
 * flash.h
 *
 *  Created on: Dec 15, 2018
 *      Author: andre
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#define BYTES_FLASH 660U


/* Define the functions */

uint8_t  flash_teste(void);   // compares the eeprom hash with the real one
uint16_t calculate_hash_xor(void); // calculates the real hash on the MCU flash memory
#endif /* FLASH_H_ */
