/*
 * I2C_prog.c
 *
 * Created: 4/30/2025 5:48:32 PM
 *  Author: Abdelrhman
 */ 


#include "I2C_interface.h"
#include "../../Lib/BIT_MATH.h"
#include "avr/interrupt.h"


#define Status				(TWCR & 0xF8)
#define ENABLE_I2C			SET_BIT(TWCR, 2)
#define START				SET_BIT(TWCR,5)
#define Polling_on_Event	while(!GET_BIT(TWCR,7))
#define Enable_Ack_Bit		SET_BIT(TWCR,6)

#define Disble_Ack_Bit		CLR_BIT(TWCR,6)


void I2C_INIT(unsigned int SCL_Speed, uint8 SLA_Address)
{
	// Set SDA Pin
	DIO_u8SetPinDirection(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PINVALUE_LOW);
	// Set SCL Pin
	DIO_u8SetPinDirection(DIO_u8PORTC, DIO_u8PIN1, DIO_u8PIN_OUTPUT);	
	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN1, DIO_u8PINVALUE_LOW);	
	
	// Init Clock Speed
	CLR_BIT(TWSR,0);
	CLR_BIT(TWSR,1);
	TWBR = ((F_CPU/(2*SCL_Speed)) - 8);
	ENABLE_I2C;
	
	// Init Slave Address for the master
	TWAR = ((SLA_Address & 0x7F)  << 1);
	
	CLR_BIT(TWAR,0);

}

void I2C_Master_Write(uint8 DevAddress, uint8 *Data, uint8 Lenght, uint8 STOP_State, uint8 START_State)
{
	int x = 5;
	START;
	Polling_on_Event;
	if (START_State == START && Status != START_Status) 
	{
		while(x == 5)
		{
			x++;	
		}
	}
	else if (START_State == Repeated_START && Status != REP_START_Status) 	{
		while(x == 5)
		{
			x++;
		}
	}	
//	SET_BIT(TWCR,7);
//	(((DevAddress & 0x7F) << 1) | 0); 
	TWDR = 0x04; 
	SET_BIT(TWCR,7);
	Polling_on_Event;
	if (Status != MT_SLA_ACK_Status) 
	{
		while(x == 5)
		{
			x++;
		}
	}  // Get Ack
	
	for (unsigned int Counter = 0; Counter < Lenght; Counter++)
	{
		TWDR = Data[Counter];
		SET_BIT(TWCR,7);
		Polling_on_Event;
		if (Status != MT_DATA_ACK_Status){
			while(x == 5)
			{
				x++;
			}
			}  // Get Ack
		
	}
	SET_BIT(TWCR,7);
	if (STOP_State = WITH_STOP)
	{
		SET_BIT(TWCR,4);
	}
}

void I2C_Master_Read(uint8 DevAddress, uint8 *Data, uint8 Lenght, uint8 STOP_State, uint8 START_State)
{
	Enable_Ack_Bit;
	START;
	Polling_on_Event;
	if (START_State = START && Status != START_Status) while(1);
	SET_BIT(TWCR,7);
	
	TWDR = ((DevAddress << 1) | 1); 
	Polling_on_Event;
	if (Status != MR_SLA_ACK_Status) while(1);  // Get Ack
	SET_BIT(TWCR,7);
	
	for (unsigned int Counter = 0; Counter < Lenght; Counter++)
	{
		Polling_on_Event;
		if (Status != MR_DATA_ACK_Status) while(1);  // Get Ack
		SET_BIT(TWCR,7);
		Data[Counter] = TWDR;
	}
	
	Disble_Ack_Bit;
	
	Polling_on_Event;
	if (Status != MR_DATA_NACK_Status) while(1);  // Get Ack
	
	SET_BIT(TWCR,4);
}