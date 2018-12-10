/*
 * I2C_comms.h
 *
 *  Created on: Nov 25, 2018
 *      Author: andre
 */

#ifndef I2C_COMMS_H_
#define I2C_COMMS_H_

#include "avr/io.h"

#define START 0xED      			 // start condition for MASTER-TRANSMITTER
#define SLAVEADDR 0x001    // address of slave


/* Define the functions  */
uint8_t i2c_start(void);
uint8_t SendData(char data);
void  i2c_stop(void);

#endif /* I2C_COMMS_H_ */
