/*
 * USART_comms.h
 *
 *  Created on: Dec 2, 2018
 *      Author: joaorodrigues
 */

#ifndef USART_COMMS_H_
#define USART_COMMS_H_

#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000UL
#define BAUD 9600

#include <util/setbaud.h>

void uart_init(void);
void uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);

FILE uart_input;
FILE uart_output;

FILE uart_io;



#endif /* USART_COMMS_H_ */
