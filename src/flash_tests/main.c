/*
 * main.c
 *
 *  Created on: Dec 15, 2018
 *      Author: andre
 */


#include "main.h"



int main(void){

	_delay_ms(1000);
	puts("Starting flash test");
	uint8_t result = flash_teste();

	uint16_t hash = flash_test_calculate_xor();



	while(1)
	{
		_delay_ms(1000);
	}
	return 0;
}
