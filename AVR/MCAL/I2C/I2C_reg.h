/*
 * I2C_reg.h
 *
 * Created: 4/30/2025 5:43:24 PM
 *  Author: 2M
 */ 


#ifndef I2C_REG_H_
#define I2C_REG_H_

#define TWCR      	(*((volatile unsigned char *)0x56))
#define TWDR      	(*((volatile unsigned char *)0x23))
#define TWAR      	(*((volatile unsigned char *)0x22))
#define TWSR      	(*((volatile unsigned char *)0x21))
#define TWBR      	(*((volatile unsigned char *)0x20))



#endif /* I2C_REG_H_ */