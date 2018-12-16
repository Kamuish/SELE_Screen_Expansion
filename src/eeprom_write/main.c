/*
 * main.c
 *
 *  Created on: Dec 16, 2018
 *      Author: andre
 */

#include <avr/eeprom.h>
uint16_t  eeprom_addr = 8056U;
int main(void)
{
	uint8_t word[] = "4751";
	eeprom_write_word(word,eeprom_addr);
}
