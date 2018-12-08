/*
 * LCD1604.h
 *
 *  Created on: Dec 7, 2018
 *      Author: joaorodrigues
 */

#ifndef LCD1602A_H_
#define LCD1602A_H_

#include <SPI_comms.h>

#define RS 1
#define EN 2
#define BKL 7

void screen_init(void); // Initializes the screen
void screen_instruction(uint8_t instruction); // Sends an 8-bit instruction to the screen
void screen_data(uint8_t data); // Sends an 8-bit data command to the screen

void put_char(uint8_t character); // Puts the character 'character' on the cursor position

#endif /* LCD1602A_H_ */
