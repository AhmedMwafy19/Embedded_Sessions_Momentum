/*
 * EXTI_reg.h
 *
 * Created: 3/28/2025 3:58:02 PM
 *  Author: Abdelrhman Marzoq
 */ 


#ifndef EXTI_REG_H_
#define EXTI_REG_H_

/** Bit Mask For GICR */

#define IRQ0_BIT_EN     6
#define IRQ1_BIT_EN     7
#define IRQ2_BIT_EN     5

/** Bit Mask For MCUCR */

#define ISC00_BIT		0
#define ISC01_BIT		1
#define ISC10_BIT		2
#define ISC11_BIT		3

/** Bit Mask For MCUCSR */
#define ISC2_BIT		6

/** Bit Mask For SREG */
#define I_BIT			7


/** Bit Mask For GIFR */

#define INTF1_BIT		7
#define INTF0_BIT		6
#define INTF2_BIT		5


#define SREG        (*((volatile unsigned char *)0x5F))


#define MCUCR        (*((volatile unsigned char *)0x55))
#define MCUCSR       (*((volatile unsigned char *)0x54))
#define GICR		 (*((volatile unsigned char *)0x5B))
#define GIFR		 (*((volatile unsigned char *)0x5A))



#endif /* EXTI_REG_H_ */