/*
 * Shift_Strings.c
 *
 *  Created on: Dec 12, 2018
 *      Author: andre
 */

#include <Shift_Strings.h>

void InitStringLeft(uint8_t *string, uint8_t size) {
	/* Display the string on the left screen */
	PutString(string, size - 1, LEFT_SCREEN_PROTOCOL);
	_delay_ms(10);

	/* Shift cursor back to the start of the left screen */
	ScreenInstruction(LCD_MOVE_CURSOR_HOME, LEFT_SCREEN_PROTOCOL);
	_delay_ms(10);
}

void StringOnLeftScreen(void) {
	/* Shift the left screen to the right */
	ScreenInstruction(LCD_MOVE_DISP_RIGHT, LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift cursor back to the starting position */
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);
}

void StringOnMiddleLeft(uint8_t *string, uint8_t string_count) {
	/* Shift the right screen to the right */
	ScreenInstruction(LCD_MOVE_DISP_RIGHT,RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift cursor back to the starting position */
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT,RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Put character on the right screen */
	PutChar(string[string_count-1],RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift cursor back to the starting position */
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT,RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift the left screen to the right */
	ScreenInstruction(LCD_MOVE_DISP_RIGHT,LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift cursor back to the starting position */
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);
}

void StringOnRightScreen(void) {
	/* Shift the right screen to the right */
	ScreenInstruction(LCD_MOVE_DISP_RIGHT, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift cursor back to the starting position */
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);
}

void StringOnMiddleRight(uint8_t *string, uint8_t string_count) {
	/* Shift left screen to the right */
	ScreenInstruction(LCD_MOVE_DISP_RIGHT, LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift cursor back to the starting position */
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Put character on the right screen */
	PutChar(string[string_count-1], LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift cursor back to the starting position */
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, LEFT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift right screen to the right */
	ScreenInstruction(LCD_MOVE_DISP_RIGHT, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);

	/* Shift cursor back to the starting position */
	ScreenInstruction(LCD_MOVE_CURSOR_LEFT, RIGHT_SCREEN_PROTOCOL);
	_delay_ms(1);
}
