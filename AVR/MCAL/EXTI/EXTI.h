/*
 * EXTI.h
 *
 * Created: 3/28/2025 3:46:12 PM
 *  Author: Abdelrhman Marzoq
 */ 


#ifndef EXTI_H_
#define EXTI_H_


#include "EXTI_reg.h"





typedef enum
{
	EXTI0,
	EXTI1,
	EXTI2
}EXTI_Number_t;

typedef enum
{
	LOW,
	ANY_LOGIC,
	FALLING,
	RISING
}EXTI_Mode_t;

typedef struct  
{
	EXTI_Number_t	Number;
	EXTI_Mode_t		Mode;
	void (* ISR_CallBack)(void);
}EXTI_Config_t;


void EXTI_Enable(EXTI_Config_t *EXTIx);

void EXTI_Disable(EXTI_Config_t *EXTIx);





#endif /* EXTI_H_ */