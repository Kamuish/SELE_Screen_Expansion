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

uint8_t i2c_start(void){
	/*
	 * Send start action  for I2C communication and wait untils the TWINT flag is set.
	 *Also checks TWI status register for correct sending of start signal.
	 * Afterwards chooses the slave, by setting the address to twdr and clearing the TWINT flag
	 *
	 */
	TWCR = ( 1 << TWINT ) | ( 1 << TWSTA)  |  ( 1 << TWEN);

	WaitForTwint();

	if  (( TWSR  &  0xF8)  !=  START)														     // CHECKS TWI STATUS REGISTER
			return -1;

	TWDR = SLAVEADDR ;
	TWCR = (1<<TWINT) | (1<<TWEN);
	WaitForTwint();

	if ((TWSR & 0xF8) != SLAVEADDR)
		return -1;
	return 0;
}




uint8_t SendData(char data){
	/*
	 * Send command and waits for the flag and ACK
	 */
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	WaitForTwint();
	if  ((TWSR & 0xF8) != data)
		return -1;
	return 0;
}


void  i2c_stop(void){
	/*
	 * Sends I2C stop action
	 *
	 */

	TWCR =  ( 1 << TWINT ) | ( 1 << TWEN ) | (1 << TWSTO ) ;

}

















