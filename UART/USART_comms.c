/*
 * USART_comms.c
 *
 *  Created on: Dec 2, 2018
 *      Author: joaorodrigues
 */

#ifndef USART_COMMS_C_
#define USART_COMMS_C_

#include <USART_comms.h>

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

FILE uart_io = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

void uart_init(void) {

	/* Set baud rate */
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif

	/* Enable receiver and transmitter */
	UCSR0B = _BV(RXEN0)|_BV(TXEN0);

	/* Set frame format: 8data, 2stop bit */
	UCSR0C = _BV(UCSZ01)|_BV(UCSZ00);
}

void uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

char uart_getchar(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}
#endif /* USART_COMMS_C_ */
