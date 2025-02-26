#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H
//Ports
#define DIO_u8PORTA 0u
#define DIO_u8PORTB 1u
#define DIO_u8PORTC 2u
#define DIO_u8PORTD 3u
//pin
#define DIO_u8PIN0 0
#define DIO_u8PIN1 1u
#define DIO_u8PIN2 2u
#define DIO_u8PIN3 3u
#define DIO_u8PIN4 4u
#define DIO_u8PIN5 5u
#define DIO_u8PIN6 6u
#define DIO_u8PIN7 7u
//direction
#define DIO_u8PIN_INPUT 0
#define DIO_u8PIN_OUTPUT 1u
//value
#define DIO_u8PINVALUE_HIGH   1u
#define DIO_u8PINVALUE_LOW    0
//portvalue
#define DIO_u8PORT_HIGH 0xff
#define DIO_u8PORT_LOW 0
//portdirection
#define DIO_u8PORT_INPUT  0
#define DIO_u8PORT_OUTPUT  0xff
//functions that deals with each pin
uint8 DIO_u8SetPinDirection(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8 Copy_u8Direction);
uint8 DIO_u8SetPinValue(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8 Copy_u8Value);
uint8 DIO_u8ReadPinValue(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8* Copy_pu8Value);
uint8 DIO_u8TogglePinValue(uint8 Copy_u8Port,uint8 Copy_u8Pin);



//functions that deals with each port
uint8 DIO_u8SetPortDirection(uint8 Copy_u8Port,uint8 Copy_u8Direction);
uint8 DIO_u8SetPortValue(uint8 Copy_u8Port,uint8 Copy_u8Value);


#endif
