/*
 * SPI_comms.c
 *
 *  Created on: Nov 24, 2018
 *      Author: joaorodrigues
 */

#include <SPI_comms.h>

void SPI_MasterInit(void) {
	/* Set MOSI and SCK output, all others input */
	DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);

	DDR_SPI &= ~(1<<DD_MISO);

	PORTB |= (1<<DD_SS);

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR0)|(1<<SPR1);

	SPSR &= ~(1<<SPI2X);
}

void SPI_MasterTransmit(char cData) {
	char flush_buffer;

	/* Start transmission */
	SPDR = cData|(1<<EN);
	/* Wait for transmission complete */
	while (!(SPSR & (1<<SPIF)));

	for (int i = 0; i < 9; i++) {
		PORTB |= (1<<DD_SS);
		_delay_us(1);
		PORTB &= ~(1<<DD_SS);
	}

	_delay_us(1);

	/* Start transmission */
	SPDR = cData&(~(1<<EN));
	/* Wait for transmission complete */
	while (!(SPSR & (1<<SPIF)));

	for (int i = 0; i < 9; i++) {
		PORTB |= (1<<DD_SS);
		_delay_us(1);
		PORTB &= ~(1<<DD_SS);
	}

	_delay_us(1);

	flush_buffer = SPDR;
}
