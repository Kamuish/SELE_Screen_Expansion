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
#include <stdbool.h>

#define BYTES_FLASH 660U
#define EEPROM_ADDR 0x22

/* Define the functions */

bool  FLASH_Test(void);   // compares the eeprom hash with the real one
uint16_t FLASH_CalculateHashXOR(void); // calculates the real hash on the MCU flash memory
#endif /* FLASH_H_ */
