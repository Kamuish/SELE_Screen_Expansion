/*
 * SPI_comms.c
 *
 *  Created on: Dec 11, 2018
 *      Author: joaorodrigues
 */

#include <SPI_comms.h>

void SPIMasterInit(void) {
	/* Set up SPI Master
	 * Returns: void.
	 */

	/* Set MOSI, SCK and SS output, MISO as input */
	DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);

	DDR_SPI &= ~(1<<DD_MISO);

	PORTB |= (1<<DD_SS);

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR0)|(1<<SPR1);

	SPSR &= ~(1<<SPI2X);
}

void SPIMasterTransmit(uint8_t data) {
	/* Transmits the data through SPI
	 * uint8_t data - data to be transmitted
	 * Returns: void.
	 */

	uint8_t flush_buffer; /* Buffer to flush the existent data on the SPI register */

	/* Start transmission */
	SPDR = data;

	/* Wait for transmission complete */
	while (!(SPSR & (1<<SPIF)));

	FlushShiftRegister(); 	/* Flush the shift register to put the byte into the screen */

	flush_buffer = SPDR;	/* Flush the SPI register */
}

void FlushShiftRegister(void) {
	/* Flushes the shift register by switching the latch the appropriate number of times
	 * Returns: void
	 */

	uint8_t NO_OF_BITS = 8; /* Number of bits of the shift register */

	for (int i = 0; i < NO_OF_BITS + 1; i++) {	/* Iterate through the number of bits of the register */
		PORTB |= (1<<DD_SS);	/* Drive the latch to high */
		_delay_us(1);			/* Latch hold time */
		PORTB &= ~(1<<DD_SS);	/* Drive the latch to low */
	}

	_delay_us(1);
}
