/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#ifndef _I2C_DRIVER_H_
#define _I2C_DRIVER_H_

#include "stm32f4xx.h"

void I2C1_Init();

void I2C2_Init();

unsigned char I2C1_ByteWrite( unsigned char slave_address,unsigned char data_to_write_in);
unsigned char I2C1_ByteWrite_Reg( unsigned char slave_address,unsigned char reg_address,unsigned char data_to_write_in);

unsigned char I2C1_ByteRead(unsigned char slave_address);
unsigned char I2C1_ByteRead_Reg(unsigned char slave_address,unsigned char reg_address);


unsigned char I2C2_ByteWrite( unsigned char slave_address,unsigned char data_to_write_in);
unsigned char I2C2_ByteWrite_Reg( unsigned char slave_address,unsigned char reg_address,unsigned char data_to_write_in);

unsigned char I2C2_ByteRead(unsigned char slave_address);
unsigned char I2C2_ByteRead_Reg(unsigned char slave_address,unsigned char reg_address);

#endif