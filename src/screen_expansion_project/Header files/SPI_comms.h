/*
 * SPI_comms.h
 *
 *  Created on: Dec 11, 2018
 *      Author: joaorodrigues
 */

#ifndef SPI_COMMS_H_
#define SPI_COMMS_H_

#include <avr/io.h>
#include <util/delay.h>

/* Define SPI Data Direction Register and Bits */

#define DDR_SPI DDRB	/* SPI Data Direction Register */
#define DD_SS PB2		/* Slave Select bit - Shift register latch */
#define DD_MOSI PB3		/* SPI MOSI */
#define DD_MISO PB4		/* SPI MISO */
#define DD_SCK PB5		/* SPI Clock */

/* SPI functions */

void SPIMasterInit(void);				/* Initializes SPI Master */
void SPIMasterTransmit(uint8_t cData);	/* Transmits data through SPI */

/* Utility functions */

void FlushShiftRegister(void);			/* Flushes the shift register */

#endif /* SPI_COMMS_H_ */
