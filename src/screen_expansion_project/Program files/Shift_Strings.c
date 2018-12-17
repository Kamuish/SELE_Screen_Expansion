/*
 * Shift_Strings.c
 *
 *  Created on: Dec 12, 2018
 *      Author: andre
 */

#include <Shift_Strings.h>

void StringOnLeftScreen() {
	ScreenInstruction(LCD_MOVE_DISP_RIGHT, LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);

	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);
}

void StringOnMiddleLeft(uint8_t *string, uint8_t string_count) {
	ScreenInstruction(LCD_MOVE_DISP_RIGHT,I2C);
	_delay_ms(1);
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT,I2C);
	_delay_ms(1);

	/* Put character on the right screen */
	PutChar(string[string_count-1],I2C);
	_delay_ms(1);

	ScreenInstruction(LCD_MOVE_CURSOR_LEFT,I2C);
	_delay_ms(1);

	ScreenInstruction(LCD_MOVE_DISP_RIGHT,SPI);
	_delay_ms(1);
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);
	_delay_ms(1);
}

void StringOnRightScreen(void) {
	ScreenInstruction(LCD_MOVE_DISP_RIGHT, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);

	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);
}

void StringOnMiddleRight(uint8_t *string, uint8_t string_count) {
	ScreenInstruction(LCD_MOVE_DISP_RIGHT, SPI);
	_delay_ms(1);
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);
	_delay_ms(1);

	/* Put character on the right screen */
	PutChar(string[string_count-1], SPI);
	_delay_ms(1);

	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, SPI);
	_delay_ms(1);

	ScreenInstruction(LCD_MOVE_DISP_RIGHT, I2C);
	_delay_ms(1);
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, I2C);
	_delay_ms(1);
}
