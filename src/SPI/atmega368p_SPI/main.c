/*
 * main.c
 *
 *  Created on: Nov 24, 2018
 *      Author: joaorodrigues
 */

#include <util/delay.h>
#include <SPI_comms.h>
#include <LCD1602A.h>

int main(void) {

	/*
	SPI_MasterInit();

	uint8_t command = 0x55;
	SPI_MasterTransmit(command);
	*/

	ScreenInit(SPI);
	_delay_ms(100);
	ScreenInit(I2C);
	_delay_ms(100);

	uint8_t string[] = "aaaaaaaa";
	uint8_t string1[] = "bbbbbbbb";

	PutString(string, sizeof(string) - 1, SPI);
	_delay_ms(100);
	PutString(string, sizeof(string) - 1, I2C);
	_delay_ms(100);

	_delay_ms(1000);

	while (1) {
		ScreenInstruction(LCD_DISP_CLEAR, SPI);
		_delay_ms(10);

		PutString(string1, sizeof(string) - 1, SPI);
		_delay_ms(100);

		ScreenInstruction(LCD_DISP_CLEAR, I2C);
		_delay_ms(10);

		PutString(string1, sizeof(string) - 1, I2C);

		_delay_ms(1000);

		ScreenInstruction(LCD_DISP_CLEAR, SPI);
		_delay_ms(10);

		PutString(string, sizeof(string) - 1, SPI);
		_delay_ms(100);

		ScreenInstruction(LCD_DISP_CLEAR, I2C);
		_delay_ms(10);

		PutString(string, sizeof(string) - 1, I2C);

		_delay_ms(1000);
	}


	return 0;
}
