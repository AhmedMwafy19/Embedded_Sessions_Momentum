/*
 * I2C_interface.h
 *
 * Created: 4/30/2025 5:48:59 PM
 *  Author: Abdelrhman
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include "I2C_reg.h"
#include "I2C_cfg.h"
#include "../DIO/DIO_interface.h"
#include "../../Lib/STD_TYPES.h"


// Status
#define START_Status				0x08
#define REP_START_Status			0x10
#define MT_SLA_ACK_Status			0x18
#define MT_SLA_NACK_Status			0x20
#define MT_DATA_ACK_Status			0x28
#define MT_DATA_NACK_Status			0x30
#define MR_SLA_ACK_Status			0x40
#define MR_SLA_NACK_Status			0x48
#define MR_DATA_ACK_Status			0x50
#define MR_DATA_NACK_Status			0x58
#define SR_SLA_ACK_Status			0x60
#define SR_DATA_ACK_Status			0x80
#define ST_SLA_ACK_Status			0xA8
#define ST_DATA_ACK_Status			0xB8
#define ST_DATA_NACK_Status			0xC0



// Stop Cond
#define WITHOUT_STOP				0
#define WITH_STOP					1

// Start Cond
#define START						0
#define Repeated_START				1



void I2C_INIT(unsigned int SCL_Speed, uint8 SLA_Address);

void I2C_Master_Write(uint8 DevAddress, uint8 *Data, uint8 Lenght, uint8 STOP_State, uint8 START_State);

void I2C_Master_Read(uint8 DevAddress, uint8 *Data, uint8 Lenght, uint8 STOP_State, uint8 START_State);

#endif /* I2C_INTERFACE_H_ */