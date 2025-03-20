/*
 * Keypad.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Abdelrhman Marzoq
 */


#include "Keypad.h"

static uint8_t Btn[KEYPAD_ROW_][KEYPAD_COL_];

void Key_Init(Keypad_t *Keypad, const uint8_t D_char[KEYPAD_ROW_][KEYPAD_COL_])
{
	// Init Rows Wires to be O/P and Logic LOW
	for (int index = 0; index < KEYPAD_ROW_; index++)
	{
		Keypad->ROW[index].GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		Keypad->ROW[index].GPIO_OUTPUT_Speed = GPIO_SPEED_2M;
		GPIO_INIT(&(Keypad->ROW[index]));
		GPIO_WRITE_PIN(&(Keypad->ROW[index]), LOW);
	}

	// Init Columns Wire to be I/P
	for (int index = 0; index < KEYPAD_COL_; index++)
	{
		Keypad->COL[index].GPIO_MODE = GPIO_MODE_INPUT_PD;
		Keypad->COL[index].GPIO_OUTPUT_Speed = GPIO_SPEED_2M;
		GPIO_INIT(&(Keypad->COL[index]));
	}

	// Draw Keypad (2D Array) with Custom char
	for (int row = 0; row < KEYPAD_ROW_; row++)
	{
		for (int col = 0; col < KEYPAD_COL_; col++)
		{
			Btn[row][col] =  D_char[row][col];
		}
	}
}


uint8_t Key_get(Keypad_t *Keypad)
{
	// Select Cell that you pressed on
	for (int row = 0; row < KEYPAD_ROW_; row++)
	{
		GPIO_WRITE_PIN(&(Keypad->ROW[row]), HIGH);
		for (volatile int i = 0; i < 255; i++);
		for (int col = 0; col < KEYPAD_COL_; col++)
		{

			if (GPIO_READ_PIN(&(Keypad->COL[col])) == HIGH)
			{
				// In Future will Write Professional Delay
				for (volatile int i = 0; i < 100000; i++);
				GPIO_WRITE_PIN(&(Keypad->ROW[row]), LOW);
				return Btn[row][col];
			}
		}
		GPIO_WRITE_PIN(&(Keypad->ROW[row]), LOW);
	}

	// In case you didn`t Press any thing
	return (uint8_t)' ';
}
