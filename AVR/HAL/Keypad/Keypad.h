/*
 * Keypad.h
 *
 *  Created on: Jul 26, 2024
 *      Author: Abdelrhman Marzoq
 */

/**
 * To Customize This Driver for your Keypad i*j Just Justify these Macros
 * Define KEYPAD_ROW_ i
 * Define KEYPAD_COL_ j
 *
 * Must Take Object from struct -> (Keypad_t)
 * Implement it By your target Pin and Port
 *
 * You should first Call Funtion (Key_Init) before Calling any Function
 */



#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

							/*************************************/
							/*          Include Section          */
							/*************************************/
#include "../STM32F103C6_MCAL_Drivers/GPIO/STM32F103C6_GPIO_Driver.h"

							/*************************************/
							/*          Macros Section           */
							/*************************************/

#define KEYPAD_ROW_    	4
#define KEYPAD_COL_		4

							/*************************************/
							/*         Typedef Section           */
							/*************************************/


typedef struct
{
	GPIO_PinConfig_t ROW[KEYPAD_ROW_];        // Just Init it with Pin and Port
	GPIO_PinConfig_t COL[KEYPAD_COL_];	  // Just Init it with Pin and Port
}Keypad_t;




							/*************************************/
							/*       Function Declaration        */
							/*************************************/

/**================================================================
 * @Fn                 	- Key_Init
 * @brief				- Init Pins for Keypad
 * @param [in]			- Keypad : pointer to a GPIO_PinConfig_t structure that contatin
 * 						  		   the configuration information for the specified PORT & PIN.
 * @retval				- NONE
 * Note					- NONE
*/
void Key_Init(Keypad_t *Keypad, const uint8_t D_char[KEYPAD_ROW_][KEYPAD_COL_]);

/**================================================================
 * @Fn                 	- Key_get
 * @brief				- Get the Pressed Key
 * @param [in]			- Keypad : pointer to a GPIO_PinConfig_t structure that contatin
 * 						  		  the configuration information for the specified PORT & PIN.
 * @retval				- return Char the you pressed on Keypad
 * Note					- NONE
*/
uint8_t Key_get(Keypad_t *Keypad);


#endif /* KEYPAD_KEYPAD_H_ */
