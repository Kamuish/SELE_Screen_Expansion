/*
 * SPI_comms.c
 *
 *  Created on: Nov 24, 2018
 *      Author: joaorodrigues
 */

#include <SPI_comms.h>

void SPI_MasterInit(void) {
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS)|(0<<DD_MISO);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData) {
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while (!(SPSR & (1<<SPIF)));
}
