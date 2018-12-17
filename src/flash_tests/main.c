/*
 * main.c
 *
 *  Created on: Dec 15, 2018
 *      Author: andre
 */


#include "main.h"

int main(void){
	uart_init();
	stdout = &uart_output;

	uint8_t result = 0;
	//result = flash_teste();

	while(1){
		puts("aaa");
		_delay_ms(2000);
	}

	return 0;
}
