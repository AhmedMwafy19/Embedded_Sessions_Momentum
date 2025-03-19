/*
 * Calc.c
 *
 *  Created on: Jul 29, 2024
 *      Author: Abdelrhman Marzoq
 */


#include "Calc.h"


// Static Functions Declarations
static void Char_init(Stack_Char *List);
static uint8_t Char_isEmpty (Stack_Char *List);
static uint8_t Char_isFull (Stack_Char *List);
static uint8_t Char_Top (Stack_Char *List);
static void Char_Pop(Stack_Char * List);
static void Char_Push(Stack_Char * List, uint8_t Data);

static void Float_init(Stack_Float *List);
static uint8_t Float_isEmpty (Stack_Float *List);
static uint8_t Float_isFull (Stack_Float *List);
static float Float_Top (Stack_Float *List);
static void Float_Pop(Stack_Float * List);
static void Float_Push(Stack_Float * List, float Data);

static float Calc_res(float Num1, float Num2, uint8_t sympol);

static uint8_t Get_Length(float Number);
static void evaluate(void);



// Var
LCD_4bit_t lcd;
Keypad_t key;
EXIT_t exti;


volatile uint8_t ISR = 1;

uint8_t Operation[60];
static uint8_t Postfix[100];


//Functions Definitions

// Get Precedence of Operators
static uint8_t Precedence(uint8_t Operator)
{
	switch (Operator)
	{
	case '*' :
	case '/' : return 2;
	case '+' :
	case '-' : return 1;
	}
}

// Init Pins for LCD, Keypad and EXTI
void Calc_init(void)
{
	// Enable CLK FOR GPIO B
	RCC_GPIOB_CLK_EN;
	// Enable CLK FOR GPIO A
	RCC_GPIOA_CLK_EN;
	// Enable CLK FOR AFIO
	RCC_AFIO_CLK_EN;

	// Init LCD
	lcd.RS.GPIOx = GPIOA;
	lcd.RS.GPIO_PinNumber = GPIO_PIN15;
	lcd.EN.GPIOx = GPIOA;
	lcd.EN.GPIO_PinNumber = GPIO_PIN12;
	lcd.Data[0].GPIOx = GPIOA;
	lcd.Data[0].GPIO_PinNumber = GPIO_PIN11;
	lcd.Data[1].GPIOx = GPIOA;
	lcd.Data[1].GPIO_PinNumber = GPIO_PIN10;
	lcd.Data[2].GPIOx = GPIOA;
	lcd.Data[2].GPIO_PinNumber = GPIO_PIN9;
	lcd.Data[3].GPIOx = GPIOA;
	lcd.Data[3].GPIO_PinNumber = GPIO_PIN8;
	LCD_4bit_init(&lcd);
	// End

	// Init Keypad
	key.ROW[0].GPIO_PinNumber = GPIO_PIN11;
	key.ROW[0].GPIOx = GPIOB;
	key.ROW[1].GPIO_PinNumber = GPIO_PIN10;
	key.ROW[1].GPIOx = GPIOB;
	key.ROW[2].GPIO_PinNumber = GPIO_PIN1;
	key.ROW[2].GPIOx = GPIOB;
	key.ROW[3].GPIO_PinNumber = GPIO_PIN0;
	key.ROW[3].GPIOx = GPIOB;
	key.COL[0].GPIO_PinNumber = GPIO_PIN4;
	key.COL[0].GPIOx = GPIOA;
	key.COL[1].GPIO_PinNumber = GPIO_PIN3;
	key.COL[1].GPIOx = GPIOA;
	key.COL[2].GPIO_PinNumber = GPIO_PIN2;
	key.COL[2].GPIOx = GPIOA;
	key.COL[3].GPIO_PinNumber = GPIO_PIN1;
	key.COL[3].GPIOx = GPIOA;
	const uint8_t Char[KEYPAD_ROW_][KEYPAD_COL_] = {{'7', '8', '9', '/'},
													{'4', '5', '6', '*'},
													{'1', '2', '3', '-'},
													{'.', '0', '=', '+'}};
	Key_Init(&key, Char);
	// End


	// EXTI Button for Reset CALC

	// Init External Interrupt
	exti.EXTI_PIN = EXTI0PA0;
	exti.Detect_EXTI = FALLING;
	exti.IRQ_EN = EN_EXTI;
	exti.PF_IRQ = Reset;
	EXTI_Init(&exti);
	// End
}


void Calc(uint8_t *Equ)
{
	Stack_Char stack_t;
	Char_init(&stack_t);
	// Local Counters
	int j = 0;
	int i = 0;
	while (Equ[j] != '\0')
	{
		uint8_t Current = Equ[j];
		// Check Digit or not
		if ((Current <= '9' && Current >= '0') || Current == '.' )
		{
			while ((Current <= '9' && Current >= '0') || Current == '.' )
			{
				Postfix[i++] = Current;
				Current = Equ[++j];
			}
			Postfix[i++] = ' ';
		}
		else
		{
			while(!(Char_isEmpty(&stack_t)) && Precedence(Current) <= Precedence(Char_Top(&stack_t)))
			{
				Postfix[i++] = Char_Top(&stack_t);
				Char_Pop(&stack_t);
			}
			if (!Char_isFull(&stack_t))
			{
				Char_Push(&stack_t, Current);
			}
			j++;
		}
	}
	while (!Char_isEmpty(&stack_t))
	{
		Postfix[i++] = Char_Top(&stack_t);
		Char_Pop(&stack_t);
	}
	Postfix[i] = '\0';
	evaluate();
}

static void evaluate(void)
{
	Stack_Float stack_t;
	Float_init(&stack_t);

	int i = 0;
	uint32_t Num = 0;
	uint8_t Sympol = ' ';
	uint8_t Check = 1;
	uint8_t temp = 0;
	float Operand1, Operand2;
	float Res;
	float Float_Num = 0;
	uint8_t Flag_repeat = 1;
	uint8_t Flag_Div_0 = 1;
//	uint8_t Flag_Floating = 0;
	while (Postfix[i] != '\0')
	{
		uint8_t Current = Postfix[i];

		if (Current <= '9' && Current >= '0')
		{
			while (Current <= '9' && Current >= '0')
			{
				Num = (Num * 10) + (int)(Current - '0');
				Current = Postfix[++i];
			}
			if (Current == '.' && Flag_repeat == 1)
			{
				Current = Postfix[++i];
				if (temp != Check)
				{
					float j = 0.1;
					while (Current <= '9' && Current >= '0')
					{
						Float_Num +=  ((Current - '0') * j) ;
						Current = Postfix[++i];
						j *= 0.1;
					}
					temp = Check;
				}
				else {
					Flag_repeat = 0;
					break;
				}
			}
			if (Current == ' ')
			{
				Float_Num += (float)Num;
				Check++;
				Float_Push(&stack_t, Float_Num);
				Num = 0;
				Float_Num = 0;
				i++;
				continue;
			}
		}
		else
		{
			Sympol = Current;
			Operand2 = Float_Top(&stack_t);
			Float_Pop(&stack_t);
			Operand1 = Float_Top(&stack_t);
			Float_Pop(&stack_t);
			if (Sympol == '/' && Operand2 == 0)
			{
				LCD_4bit_Set_Cursor(&lcd, 2, 2);
				LCD_4bit_Print(&lcd, "Error Div by 0");
				Flag_Div_0 = 0;
			}
			else
			{
				Float_Push(&stack_t, Calc_res(Operand1, Operand2, Sympol));
				i++;
			}
			if (!Flag_Div_0) break;
		}
	}
	if (Flag_Div_0 && Flag_repeat)
	{
		Res = Float_Top(&stack_t);
		Float_Pop(&stack_t);
		int length = Get_Length(Res);
		LCD_4bit_Set_Cursor(&lcd, 2, 16-(length + 2));
		LCD_4bit_Print_Fl_Number(&lcd, Res, 2);
	}
	while(ISR);
	ISR = 1;
}

// Calculate Res and printing on LCD
static float Calc_res(float Num1, float Num2, uint8_t sympol)
{
	switch(sympol)
	{
	case '+':
		return Num1 + Num2;
		break;
	case '-':
		return Num1 - Num2;
		break;
	case '*':
		return Num1 * Num2;
		break;
	case '/':
		return Num1 / Num2;
	default : break;
	}
}

static uint8_t Get_Length(float Number)
{
	uint8_t str[10] = {0};
	int Decimal;
	Decimal = (int)Number;
	sprintf(str, "%d", Decimal);
	volatile uint8_t length = 0;
	while(str[length++] != '\0');
	return length;
}


/*  Helper Stack Functions For Char Stack */
static void Char_init(Stack_Char *List)
{
	List->Top = 0;
}

static uint8_t Char_isEmpty (Stack_Char *List)
{
	return List->Top == 0;
}

static uint8_t Char_isFull (Stack_Char *List)
{
	return List->Top >= MAX;
}

static void Char_Push(Stack_Char * List, uint8_t Data)
{
	List->Data[(List->Top)++] = Data;
}

static void Char_Pop(Stack_Char * List)
{
	(List->Top)--;
}

static uint8_t Char_Top(Stack_Char *List)
{
	return (List->Data[List->Top - 1]);
}
//    END

/*  Helper Stack Functions For Float Stack */
static void Float_init(Stack_Float *List)
{
	List->Top = 0;
}

static uint8_t Float_isEmpty (Stack_Float *List)
{
	return List->Top == 0;
}

static uint8_t Float_isFull (Stack_Float *List)
{
	return List->Top >= MAX;
}

static void Float_Push(Stack_Float * List, float Data)
{
	List->Data[(List->Top)++] = Data;
}

static void Float_Pop(Stack_Float * List)
{
	(List->Top)--;
}

static float Float_Top(Stack_Float *List)
{
	return (List->Data[List->Top - 1]);
}
//       END

// Reset All Var I Used
void Reset(void)
{
	LCD_4bit_Clear(&lcd);
	LCD_4bit_Command(&lcd, _LCD_RETURN_HOME);
	ISR = 0;
	for (int i = 0; i < 16; i++) Operation[i] = '\0';
	for (int i = 0; i < 100; i++) Postfix[i] = '\0';
}
