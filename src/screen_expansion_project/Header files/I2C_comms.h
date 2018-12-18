/*
 * I2C_comms.h
 *
 *  Created on: Dec 11, 2018
 *      Author: joaorodrigues
 */

#ifndef I2C_COMMS_H_
#define I2C_COMMS_H_

#include <avr/io.h>

/* I2C clock in Hz */
#define SCL_CLOCK  100000UL

#define I2C_ADDR   0x40

/* I2C functions  */
void 	I2C_Init(void);					/* Set up I2C communication */
void 	I2C_Start(unsigned char addr);	/* Starts I2C communication */
uint8_t I2C_Write(unsigned char data_i2c);	/* Writes data through I2C */
void  	I2C_Stop(void);					/* Stops I2C communication */

/* Utility functions */
void I2C_WaitForTwint(void);

#endif /* I2C_COMMS_H_ */
