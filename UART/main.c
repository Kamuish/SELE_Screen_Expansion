/*
 * main.c
 *
 *  Created on: Dec 2, 2018
 *      Author: joaorodrigues
 */

#include <USART_comms.h>
#include <util/delay.h>

int main(void) {

    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;

    while(1) {
        puts("asdadsasd!");
        _delay_ms(2000);
    }

    return 0;
}
