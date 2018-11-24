/*
 * SPI_comms.h
 *
 *  Created on: Nov 24, 2018
 *      Author: joaorodrigues
 */

#ifndef SPI_COMMS_H_
#define SPI_COMMS_H_

#include <avr/io.h>

/* Define SPI Data Direction Register and Bits */

#define DDR_SPI DDRB
#define DD_SS PB2
#define DD_MOSI PB3
#define DD_MISO PB4
#define DD_SCK PB5

/* Define SPI_comms.c functions */

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);

#endif /* SPI_COMMS_H_ */
