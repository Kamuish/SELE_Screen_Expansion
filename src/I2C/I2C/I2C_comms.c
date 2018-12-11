/*
 * I2C_coms.c
 *
 *  Created on: Nov 25, 2018
 *      Author: andre
 */

#include "I2C_comms.h"


void WaitForTwint(void){
	/*
	 * Waits for the TWINT flag to set
	 */
	while (  ! ( TWCR  &  ( 1 << TWINT )));                                                    // waits for TWINT to set
}

void i2c_init(void){
	/*
	 * Setps up the SCL freq
	 *
	 */

	 TWSR = 0;                         /* no prescaler */
	 TWBR = ( (F_CPU/SCL_CLOCK )-16 )/2;  /* must be > 10 for stable operation */

}



void i2c_start(unsigned char addr){
	/*
	 * Send start action  for I2C communication and wait untils the TWINT flag is set.
	 *Also checks TWI status register for correct sending of start signal.
	 * Afterwards chooses the slave, by setting the address to twdr and clearing the TWINT flag
	 */
	TWCR = ( 1 << TWINT ) | ( 1 << TWSTA)  |  ( 1 << TWEN);

	WaitForTwint();

	TWDR = addr ;

	TWCR = (1<<TWINT) | (1<<TWEN);
	WaitForTwint();


}


uint8_t i2c_write( unsigned char data){
	/*
	 * Send command and waits for the flag and ACK
	 */
	TWDR = data;

	TWCR = (1<<TWINT) | (1<<TWEN);

	WaitForTwint();

	return 0;
}



void  i2c_stop(void){
	/*
	 * Sends I2C stop action
	 *
	 */
	TWCR =  ( 1 << TWINT ) | ( 1 << TWEN ) | (1 << TWSTO ) ;
	while(TWCR & (1<<TWSTO));                                                   // waits for TWSTO to set
}

















