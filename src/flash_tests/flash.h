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
//For the crc16 self test for the flash

#include "UART_comms.h"

#define BYTES_FLASH (660U)

/* Define the functions */

uint8_t flash_teste(void);   // compares the eeprom hash with the real one
uint16_t flash_test_calculate_xor(void);
#endif /* FLASH_H_ */
