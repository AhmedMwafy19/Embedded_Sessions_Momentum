/*
 * EXTI.c
 *
 * Created: 3/28/2025 3:45:49 PM
 *  Author: Abdelrhman Marzoq
 */ 


#include "EXTI.h"
#include "../DIO/DIO_interface.h"
#include "../../lib/BIT_MATH.h"


void (*PTR_ISR[3])(void);


void EXTI_Enable(EXTI_Config_t *EXTIx)
{
	if (EXTIx->Number == EXTI0)
	{
		PTR_ISR[0] = EXTIx->ISR_CallBack;
		SET_BIT(GICR, IRQ0_BIT_EN);
		DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PIN_INPUT);
		if (EXTIx->Mode == LOW)
		{
			CLR_BIT(MCUCR, ISC01_BIT);
			CLR_BIT(MCUCR, ISC00_BIT);
		}
		else if (EXTIx->Mode == ANY_LOGIC)
		{
			CLR_BIT(MCUCR, ISC01_BIT);
			SET_BIT(MCUCR, ISC00_BIT);
		}
		else if (EXTIx->Mode == FALLING)
		{
			SET_BIT(MCUCR, ISC01_BIT);
			CLR_BIT(MCUCR, ISC00_BIT);	
		}		
		else if (EXTIx->Mode == RISING)
		{
			SET_BIT(MCUCR, ISC01_BIT);
			SET_BIT(MCUCR, ISC00_BIT);
		}
	}
	else if (EXTIx->Number == EXTI1)
	{
		
		PTR_ISR[1] = EXTIx->ISR_CallBack;
		DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN3, DIO_u8PIN_INPUT);
		SET_BIT(GICR, IRQ1_BIT_EN);
		if (EXTIx->Mode == LOW)
		{
			CLR_BIT(MCUCR, ISC11_BIT);
			CLR_BIT(MCUCR, ISC10_BIT);
			
		}
		else if (EXTIx->Mode == ANY_LOGIC)
		{
			CLR_BIT(MCUCR, ISC11_BIT);
			SET_BIT(MCUCR, ISC10_BIT);
		}
		else if (EXTIx->Mode == FALLING)
		{
			SET_BIT(MCUCR, ISC11_BIT);
			CLR_BIT(MCUCR, ISC10_BIT);
		}
		else if (EXTIx->Mode == RISING)
		{
			SET_BIT(MCUCR, ISC11_BIT);
			SET_BIT(MCUCR, ISC10_BIT);
		}
		
	}
	else if (EXTIx->Number == EXTI2)
	{
		
		PTR_ISR[2] = EXTIx->ISR_CallBack;
		DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN2, DIO_u8PIN_INPUT);
		SET_BIT(GICR, IRQ2_BIT_EN);
		
		if (EXTIx->Mode == FALLING)
		{
			CLR_BIT(MCUCSR, ISC2_BIT);
		}
		else if (EXTIx->Mode == RISING)
		{
			SET_BIT(MCUCSR, ISC2_BIT);
		}
	}
	SET_BIT(SREG, I_BIT);
}

void EXTI_Disable(EXTI_Config_t *EXTIx)
{
	
	if (EXTIx->Number == EXTI0)
	{
		CLR_BIT(GICR, IRQ0_BIT_EN);
	}
	else if (EXTIx->Number == EXTI1)
	{
		CLR_BIT(GICR, IRQ1_BIT_EN);
	}
	else if (EXTIx->Number == EXTI2)
	{
		CLR_BIT(GICR, IRQ2_BIT_EN);
	}
	
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	// Clear Flag
	CLR_BIT(GIFR, INTF0_BIT);
	
	PTR_ISR[0]();
}
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	// Clear Flag
	CLR_BIT(GIFR, INTF1_BIT);
	
	PTR_ISR[1]();
}
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	// Clear Flag
	CLR_BIT(GIFR, INTF2_BIT);
	
	PTR_ISR[2]();
}



