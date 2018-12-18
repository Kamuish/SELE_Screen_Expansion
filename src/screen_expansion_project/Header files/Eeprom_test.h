/*
 * Eeprom_test.h
 *
 *  Created on: Dec 18, 2018
 *      Author: andre
 */

#ifndef HEADER_FILES_EEPROM_TEST_H_
#define HEADER_FILES_EEPROM_TEST_H_

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define N_BYTES_EEPROM 1024  /* Eeprom memory size */
#define USED_ADDR                0x22   /* Address used in the EEPROM memory */

/* Function definition */
void Eeprom_test(void);


#endif /* HEADER_FILES_EEPROM_TEST_H_ */
