/************************************************************************
 *																		*
 *		FILE NAME: SPI_comms.c											*
 *		PURPOSE:									7
 *			Implementation of the SPI protocol using the ATMEGA328P					*
 *		FILE REFERENCES:												*
 *																		*
 *		Name			I/O			Description							*
 *		----			---			-----------							*
 *																		*
 *		EXTERNAL VARIABLES:												*
 *																		*
 *		Name	Type	I/O			Description							*
 *		----	----	---			----------- 						*
 *																		*
 *		EXTERNAL REFERENCES:											*
 *																		*
 *		Name						Description							*
 *		----						-----------							*
 *																		*
 * 		ABNORMAL TERMINATION CONDITIONS, ERROR AND WARNING MESSAGES: 	*
 *																		*
 * 		ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS:							*
 *																		*
 *		NOTES:															*
 *																		*
 * 		REQUIREMENTS/FUNCTIONAL SPECIFICATIONS REFERENCES:				*
 *																		*
 * 		DEVELOPMENT HISTORY:											*
 *																		*
 *		Date	Author	Change ID	Release		Description of change	*
 *		Dec 11, 2018	joaorodrigues													*
 *																		*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include "SPI_comms.h"

void SPI_MasterInit(void) {
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

void SPI_MasterTransmit(uint8_t data) {
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
	/* Flushes the shift register by switching the latch
	 * Returns: void
	 */

	PORTB |= (1<<DD_SS);	/* Drive the latch to high */
	_delay_us(1);			/* Latch hold time */
	PORTB &= ~(1<<DD_SS);	/* Drive the latch to low */

	_delay_us(1);
}

