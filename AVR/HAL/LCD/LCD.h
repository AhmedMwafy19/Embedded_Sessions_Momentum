/*
 * LCD.h
 *
 * Created: 3/4/2025 3:54:30 PM
 *  Author: Abdelrhman Marzoq
 */ 


#include "../../MCAL/DIO/DIO_interface.h"
#include "../../Lib/BIT_MATH.h"
#include "../../Lib/STD_TYPES.h"
#include <util/delay.h>


#ifndef LCD_H_
#define LCD_H_



//@ref INSTRUCTIONS
#define _LCD_CLEAR						0x01					//The LCD Will clear and DDRAM Will clear

#define _LCD_RETURN_HOME				0x02					//Cursor return row 0 column 0

//Entry Mode
#define _LCD_DEC_CURSOR_SHIFT_OFF		0x04					//when write character the cursor will shift to left
#define _LCD_DEC_CURSOR_SHIFT_ON		0x05					//when write character the display will shift to right
#define _LCD_INC_CURSOR_SHIFT_OFF		0x06					//when write character the cursor will shift to right
#define _LCD_INC_CURSOR_SHIFT_ON		0x07					//when write character the display will shift to left

//
#define _LCD_CURSOR_DISPLAY_OFF			0x08					//The cursor will off and lcd will clear without clearing DDRAM
#define _LCD_CURSOR_OFF					_LCD_CURSOR_DISPLAY_OFF | _LCD_DISPLAY_ON
#define _LCD_CURSOR_ON					0x09 | _LCD_DISPLAY_ON	//Cursor will ON
#define _LCD_UNDERLINE_CURSOR_OFF		_LCD_CURSOR_DISPLAY_OFF | _LCD_DISPLAY_ON
#define _LCD_UNDERLINE_CURSOR_ON		0x0A | _LCD_DISPLAY_ON	//UnderLined Cursor will on
#define _LCD_DISPLAY_OFF				_LCD_CURSOR_DISPLAY_OFF
#define _LCD_DISPLAY_ON					0x0C					//Display char will on

//
#define _LCD_MOVE_CURSOR_SHIFT_LEFT		0x10					//Cursor will point to last pos
#define _LCD_MOVE_CURSOR_SHIFT_RIGHT	0x14					//Cursor will point to next pos
#define _LCD_MOVE_DISPLAY_SHIFT_LEFT	0x18					//LCD Will shift to left
#define _LCD_MOVE_DISPLAY_SHIFT_RIGHT	0x1C					//LCD Will shift to right

//
#define _LCD_CGRAM_START				0x40					//Start Address of CGRAM
#define _LCD_DDRAM_START				0x80					//Start Address of DDRAM

#define _LCD_ROW1_START					_LCD_DDRAM_START		//Start Address of Row 1 in LCD 2*16
#define _LCD_ROW2_START					0xC0					//Start Address of Row 2 in LCD 2*16

//Function Set
// Here You must use | operator with either Feature you need to init it (4bit or 8bit) with (2line or 1line) with (5*7 or 5*10) (Recommended)
#define _LCD_4BIT_1LINE_7				0x20
#define _LCD_4BIT_MODE					_LCD_4BIT_1LINE_7	//LCD 4 Data width				  	(Recommended)
//#define _LCD_8BIT_MODE					0x30					//LCD 8 Data width
#define _LCD_1LINE						_LCD_4BIT_1LINE_7		//One line
#define _LCD_2LINE						0x28					//Two lines        				  	(Recommended)
#define _LCD_DOT_MATRIX_7				_LCD_4BIT_1LINE_7		//Custom char will be 5*7	CGRAM 	(Recommended)
#define _LCD_DOT_MATRIX_10				0X24					//Custom char will be 5*10  CGRAM


#ifdef _LCD_4BIT_MODE

typedef struct 
{
	uint8 PINx;
	
	uint8 PORTx;	
}Pin_Config;

typedef struct  
{
	Pin_Config RS;
	
	Pin_Config EN;
	
	Pin_Config Data[4];
}LCD_4bit_t;


/**================================================================
 * @Fn                 	- LCD_4bit_init
 * @brief				- Init the LCD
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						            Configuration for RS and EN and Data Wires.
 * @retval				- NONE
 * Note					- Must call before use LCD
*/
void LCD_4bit_init(LCD_4bit_t *LCD_t);

/**================================================================
 * @Fn                 	- LCD_4bit_Print_Char
 * @brief				- Print 1 Char on LCD
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						  			Configuration for RS and EN and Data Wires.
 * @param [in]			- Data    : is the char need to print
 * @retval				- NONE
 * Note					- NONE
*/
void LCD_4bit_Print_Char(LCD_4bit_t *LCD_t, uint8 Data);

/**================================================================
 * @Fn                 	- LCD_4bit_Print_String
 * @brief				- Print Any string on LCD
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						  			Configuration for RS and EN and Data Wires.
 * @param [in]			- Data    : is the string need to print
 * @retval				- NONE
 * Note					- NONE
*/
void LCD_4bit_Print_String(LCD_4bit_t *LCD_t, uint8 *Data);

/**================================================================
 * @Fn                 	- LCD_4bit_Print_Number
 * @brief				- Print Integer Number
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						  			Configuration for RS and EN and Data Wires.
 * @param [in]			- value   : is the value that need to print on LCD
 * @retval				- NONE
 * Note					- NONE
*/
void LCD_8bit_Print_Number(LCD_8bit_t *LCD_t, int value);

/**================================================================
 * @Fn                 	- LCD_4bit_Set_Cursor
 * @brief				- Set the cursor at specific pos in LDC
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						            Configuration for RS and EN and Data Wires.
 * @param [in]			- row     : The row you need to set cursor
 * @param [in]			- column  :	The column you need to set cursor on row
 * @retval				- NONE
 * Note					- row 1:2    column 1:16
*/
void LCD_4bit_Set_Cursor(LCD_4bit_t *LCD_t, uint8 ROW, uint8 COLUMN);

/**================================================================
 * @Fn                 	- LCD_4bit_Command
 * @brief				-
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						            Configuration for RS and EN and Data Wires.
 * @param [in]			- Command : is commands from @ref INSTRUCTIONS
 * @retval				- NONE
 * Note					- NONE
*/
void LCD_4bit_Command(LCD_4bit_t *LCD_t, uint8 COMMAND);

/**================================================================
 * @Fn                 	- LCD_4bit_Display_ON
 * @brief				- Display ON Content of LCD
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						  			Configuration for RS and EN and Data Wires.
 * @retval				- NONE
 * Note					- NONE
*/
void LCD_4bit_Display_ON(LCD_4bit_t *LCD);

/**================================================================
 * @Fn                 	- LCD_4bit_Display_OFF
 * @brief				- Display OFF to Content of LCD Without losing it on DDRAM
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						  			Configuration for RS and EN and Data Wires.
 * @retval				- NONE
 * Note					- NONE
*/
void LCD_4bit_Display_OFF(LCD_4bit_t *LCD);

/**================================================================
 * @Fn                 	- LCD_4bit_Clear
 * @brief				- Clear All Content on LCD and Losing this data from DDRAM
 * @param [in]			- LCD     : pointer to LCD_4bit_t structure that Contain
 * 						  			Configuration for RS and EN and Data Wires.
 * @retval				- NONE
 * Note					- NONE
*/
void LCD_4bit_Clear(LCD_4bit_t *LCD);

	

#endif








#ifdef _LCD_8BIT_MODE

typedef struct
{
	uint8 PINx;
	
	uint8 PORTx;
}Pin_Config;

typedef struct
{
	Pin_Config RS;
	
	Pin_Config E;
	
	Pin_Config Data[8];
}LCD_8bit_t;


void LCD_8bit_init(LCD_8bit_t *LCD_t);

void LCD_8bit_Print_Char(LCD_8bit_t *LCD_t, uint8 *Data);

void LCD_8bit_Print_String(LCD_8bit_t *LCD_t, uint8 *Data);

void LCD_8bit_Print_Number(LCD_8bit_t *LCD_t, int value);

void LCD_8bit_Clear(LCD_8bit_t *LCD);

void LCD_8bit_Display_OFF(LCD_8bit_t *LCD);

void LCD_8bit_Display_ON(LCD_8bit_t *LCD);

void LCD_8bit_Print_Number(LCD_8bit_t *LCD_t, int value);




#endif



#endif /* LCD_H_ */