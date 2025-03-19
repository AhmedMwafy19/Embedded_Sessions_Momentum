/*
 * Calc.h
 *
 *  Created on: Jul 29, 2024
 *      Author: Abdelrhman Marzoq
 */

#ifndef CALC_H_
#define CALC_H_

#include "../HAL_Drivers/LCD/LCD.h"
#include "../HAL_Drivers/Keypad/Keypad.h"
#include "../STM32F103C6_MCAL_Drivers/EXTI/EXTI.h"

#define MAX 100

// externed Objects
extern LCD_4bit_t lcd;
extern Keypad_t key;
extern EXIT_t exti;

extern uint8_t i;
extern volatile uint8_t ISR;

extern uint8_t Operation[60];

typedef struct
{
	uint8_t Data[MAX];
	int Top;
}Stack_Char;

typedef struct
{
	float Data[MAX];
	int Top;
}Stack_Float;

void Calc_init(void);


void Reset(void);

#endif /* CALC_H_ */
