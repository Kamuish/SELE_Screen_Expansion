/*
 * Eeprom_test.h
 *
 *  Created on: Dec 18, 2018
 *      Author: andre
 */

#ifndef HEADER_FILES_EEPROM_TEST_HJ_
#define HEADER_FILES_EEPROM_TEST_HJ_

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdbool.h>

#define N_BYTES_EEPROM 	2	  /* Eeprom memory size */
#define USED_ADDR 	   	69	  /* Address used in the EEPROM memory */

/* Function definition */
bool EEPROM_Test(void);


#endif /* HEADER_FILES_EEPROM_TEST_HJ_ */
