/*
 * I2C_comms.h
 *
 *  Created on: Nov 25, 2018
 *      Author: andre
 */

#ifndef I2C_COMMS_H_
#define I2C_COMMS_H_

#include "avr/io.h"

/* define CPU frequency in hz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 1600000UL
#endif

/* I2C clock in Hz */
#define SCL_CLOCK  100000L




/* Define the functions  */
void i2c_init(void);
void i2c_start(unsigned char addr);
uint8_t i2c_write(unsigned char data);
void  i2c_stop(void);

#endif /* I2C_COMMS_H_ */
