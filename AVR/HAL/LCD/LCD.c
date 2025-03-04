/*
 * LCD.c
 *
 * Created: 3/4/2025 3:54:17 PM
 *  Author: Abdelrhman Marzoq
 */ 



#include "LCD.h"

static void myWait(volatile int ms);

#ifdef _LCD_4BIT_MODE

uint8 AddressDD = 0;


static void Send_4bit(LCD_4bit_t *LCD_t, uint8 Bits);

void LCD_4bit_init(LCD_4bit_t *LCD_t)
{
	/* Init Pins And Ports For LCD */
	DIO_u8SetPinDirection(LCD_t->RS.PORTx, LCD_t->RS.PINx, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinValue(LCD_t->RS.PORTx, LCD_t->RS.PINx, DIO_u8PINVALUE_LOW);
	
	DIO_u8SetPinDirection( LCD_t->EN.PORTx, LCD_t->EN.PINx, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinValue(LCD_t->EN.PORTx, LCD_t->EN.PINx, DIO_u8PINVALUE_LOW);
	
	for (char i = 0; i < 4 ; i++)
	{
		DIO_u8SetPinDirection(LCD_t->Data[(int)i].PORTx, LCD_t->Data[(int)i].PINx , DIO_u8PIN_OUTPUT);
		DIO_u8SetPinValue(LCD_t->Data[(int)i].PORTx, LCD_t->Data[(int)i].PINx , DIO_u8PINVALUE_LOW);
	}
	
	// Following init from DataSheet

	LCD_4bit_Command(LCD_t, _LCD_RETURN_HOME); // Must Be First Command in 4bit mode
	LCD_4bit_Command(LCD_t, _LCD_4BIT_MODE);
	LCD_4bit_Command(LCD_t, _LCD_4BIT_MODE | _LCD_2LINE | _LCD_DOT_MATRIX_7);
	
	// Send command to clear Screen
	LCD_4bit_Command(LCD_t, _LCD_CLEAR);
	// Send command to Display on and Blink cursor on
	LCD_4bit_Command(LCD_t, _LCD_DISPLAY_ON | _LCD_UNDERLINE_CURSOR_ON);
	// Send command to set cursor increamenet toward right after writing without shift display
	LCD_4bit_Command(LCD_t, _LCD_INC_CURSOR_SHIFT_OFF);
	// Send command that i ready to recieve data so i make the AC (Address counter) to First address in DDRAM
	LCD_4bit_Command(LCD_t, _LCD_DDRAM_START);
}

void LCD_4bit_Print_Char(LCD_4bit_t *LCD_t, uint8 Data)
{
	
	
	if (AddressDD == 16) LCD_4bit_Set_Cursor(LCD_t, 2, 1);
	else if (AddressDD == 32)
	{
		LCD_4bit_Set_Cursor(LCD_t, 1, 1);
		AddressDD = 0;
	}
	AddressDD++;
	
	// Select Register Send Command RS = HIGH
	DIO_u8SetPinValue(LCD_t->RS.PORTx, LCD_t->RS.PINx, DIO_u8PINVALUE_HIGH);	
	
	Send_4bit(LCD_t, ((Data>>4) & 0x0F));
	Send_4bit(LCD_t, (Data & 0x0F));
}

void LCD_4bit_Print_String(LCD_4bit_t *LCD_t, uint8 *Data)
{
	// Select Register Send Command RS = HIGH
	while (*Data) LCD_4bit_Print_Char(LCD_t, *Data++);
}

void LCD_4bit_Command(LCD_4bit_t *LCD_t, uint8 COMMAND)
{
	// Select Register Send Command RS = LOW
	DIO_u8SetPinValue(LCD_t->RS.PORTx, LCD_t->RS.PINx, DIO_u8PINVALUE_LOW);
	
	Send_4bit(LCD_t, ((COMMAND>>4) & 0x0F));
	Send_4bit(LCD_t, (COMMAND & 0x0F));
}

void LCD_4bit_Set_Cursor(LCD_4bit_t *LCD_t, uint8 ROW, uint8 COLUMN)
{
	if ( (ROW == 2 || ROW == 1) && ((COLUMN > 0) && (COLUMN <= 16)) )
	{
		switch (ROW)
		{
			case 1 : 
				// Send command to Make AC (Address counter) point to The target column in row 1
				LCD_4bit_Command(LCD_t, (_LCD_ROW1_START + --COLUMN)); 
				AddressDD = COLUMN;
				break;
			case 2 :	
				// Send command to Make AC (Address counter) point to The target column in row 2
				LCD_4bit_Command(LCD_t, (_LCD_ROW2_START + --COLUMN)); 
				AddressDD = 16 + COLUMN;
				break;
		}
	}
}

void LCD_4bit_Print_Number(LCD_4bit_t *LCD_t, int value)
{
	uint8_t str[13] = {0};
	sprintf(str,"%d",value);
	int length = strlen(str);
	if (value < 0) str[length + 1] = '-';
	LCD_4bit_Print_String(LCD_t, str);
}

void LCD_4bit_Display_ON(LCD_4bit_t *LCD)
{
	// To Make Display ON on LDC
	LCD_4bit_Command(LCD, _LCD_DISPLAY_ON);
}

void LCD_4bit_Display_OFF(LCD_4bit_t *LCD)
{
	// To Make Display OFF Without losing DDRAM Content on LDC
	LCD_4bit_Command(LCD, _LCD_DISPLAY_OFF);
}

void LCD_4bit_Clear(LCD_4bit_t *LCD)
{
	// To Clear LCD & DDRAM Memory
	LCD_4bit_Command(LCD, _LCD_CLEAR);
	LCD_4bit_Set_Cursor(LCD, 1, 1);
}

static void Send_4bit(LCD_4bit_t *LCD_t, uint8 Bits)
{
	// Data on D4 -> D7
	for (uint8 i = 0; i < 4; i++)
	{
		DIO_u8SetPinValue(LCD_t->Data[(int)i].PORTx, LCD_t->Data[(int)i].PINx, ((Bits>>(int)i) & 0x01));
	}
	// Enable Signal to Recieve Data or Command
	DIO_u8SetPinValue(LCD_t->EN.PORTx, LCD_t->EN.PINx, DIO_u8PINVALUE_HIGH);
	_delay_ms(7);
	DIO_u8SetPinValue(LCD_t->EN.PORTx, LCD_t->EN.PINx, DIO_u8PINVALUE_LOW);
	_delay_ms(7);
}

#endif

