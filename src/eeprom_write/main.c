/*
 * main.c
 *
 *  Created on: Dec 16, 2018
 *      Author: andre
 */

#include <avr/eeprom.h>
#include <stdint.h>

uint16_t  eeprom_addr = 0x22U;
int main(void)
{
	uint8_t word[] = "56794";
	eeprom_write_word(word,eeprom_addr);
}
