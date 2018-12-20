/************************************************************************
 *																		*
 *		FILE NAME: I2C_comms.c											*
 *		PURPOSE:
 *			Implementation of the I2C protocol, using the ATMEGA328P. In this implementation
 *			we have a continuous check of the data present on the status registers. If we detect anomalies
 *			a LED connected to port B0 will be turned on and a STOP condition will be sent.										*
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
 *		Dec 11, 2018	André Silva													*
 *																		*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/

#include <I2C_comms.h>

void I2C_Init(void){
	/* Sets up I2C communication
	 */

	 TWSR = 0;                            /* no prescaler */
	 TWBR = ( (F_CPU/SCL_CLOCK )-16 )/2;  /* must be > 10 for stable operation */
	 DDRB |= (1 <<PB0);
}

void I2C_Start(unsigned char addr){
	/* Send start action  for I2C communication and wait untils the TWINT flag is set.
	 * Also checks TWI status register for correct sending of start signal.
	 * Afterwards chooses the slave, by setting the address to twdr and clearing the TWINT flag
	 */
	PORTB &= ~(1 <<PB0); /* turn off the LED */
	TWCR = ( 1 << TWINT ) | ( 1 << TWSTA)  |  ( 1 << TWEN);

	I2C_WaitForTwint();

	if ( (TWSR & 0xF8)  != TW_START){
		/* Did not receive slave ack*/
		PORTB |= (1 <<PB0);
		I2C_Stop();  /* Does not allow to send more data*/
		return;

	}

	TWDR = addr ;

	TWCR = (1<<TWINT) | (1<<TWEN);
	I2C_WaitForTwint();
	if ( (TWSR & 0xF8)  != TW_MT_SLA_ACK){
		/* Did not receive slave ack*/
		PORTB |= (1 <<PB0);
		I2C_Stop();  /* Does not allow to send more data*/
		return;
	}

}


void I2C_Write( unsigned char data_i2c){
	/* Send command and wait for the flag and ACK
	 */
	TWDR = data_i2c;

	TWCR = (1<<TWINT) | (1<<TWEN);

	I2C_WaitForTwint();

	uint8_t status = (TWSR & 0xF8) ;
	if ( status  != TW_MT_DATA_ACK){
		PORTB |= ( 1 << PB0);
		I2C_Stop();  /* Does not allow to send more data*/
		}
}

void  I2C_Stop(void){
	/* Sends I2C stop action
	 */
	TWCR =  ( 1 << TWINT ) | ( 1 << TWEN ) | (1 << TWSTO ) ;
	while(TWCR & (1<<TWSTO));                                                   // waits for TWSTO to set
}

/* Utility functions */

void I2C_WaitForTwint(void) {
	/*
	 * Waits for the TWINT flag to set
	 */
	while (  ! ( TWCR  &  ( 1 << TWINT )));                                                    // waits for TWINT to set
}
