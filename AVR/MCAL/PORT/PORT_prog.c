#include "STD_TYPES.h"

#include "PORT_prv.h"
#include "PORT_cfg.h"
#include "PORT_interface.h"
#include "PORT_reg.h"

void PORT_voidInit(void)
{
	DDRA = PORTA_DIRECTION;
	DDRB = PORTB_DIRECTION;
	DDRC = PORTC_DIRECTION;
	DDRD = PORTD_DIRECTION;
	
	PORTA = PORTA_INIT_VAL;
	PORTB = PORTB_INIT_VAL;
	PORTC = PORTC_INIT_VAL;
	PORTD = PORTD_INIT_VAL;
}
