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

	_delay_ms(1000);
	puts("Starting flash test");
	uint8_t result = flash_teste();

	if (1 == result){
		puts("flash test passed");
		PORTB = (1<<PB0);

	DDRB = (1<<DDB1)|(1<<DDB0);
	}
	else{
		puts("flash test failed");
		PORTB = (1<<PB1);

			DDRB = (1<<DDB1)|(1<<DDB0);
	}
	while(1){

		_delay_ms(1000);
	}
	return 0;
}
