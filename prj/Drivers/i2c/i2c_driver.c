/***********************************************

	Fly2017  < 2017-1-13 >
  I2C 驱动程序 库函数版本
	
************************************************/

#include "i2c_driver.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"



/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: void
	output: void
	description: STM32f407 I2C1 初始化

 *=================================================*/
void I2C1_Init()
{
	I2C_InitTypeDef I2C1_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	/*   GPIOB 6,7 Config  */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_I2C1);
	
	I2C1_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C1_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C1_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C1_InitStruct.I2C_ClockSpeed = 50000;
	I2C_Init(I2C1,&I2C1_InitStruct);
	I2C_Cmd(I2C1,ENABLE);
	I2C_AcknowledgeConfig(I2C1,ENABLE);
	
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: void
	output: void
	description: stm32f407 I2C2 初始化

 *=================================================*/
void I2C2_Init()
{
	I2C_InitTypeDef I2C2_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	/*   GPIOB 10,11 Config  */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_I2C1);
	
	I2C2_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C2_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C2_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C2_InitStruct.I2C_ClockSpeed = 50000;
	I2C_Init(I2C2,&I2C2_InitStruct);
	I2C_Cmd(I2C1,ENABLE);
	I2C_AcknowledgeConfig(I2C2,ENABLE);
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 写一个字节到 slave_address 指向的芯片里

 *=================================================*/
unsigned char I2C1_ByteWrite(unsigned char slave_address,unsigned char data_to_write_in)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Transmitter);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1,data_to_write_in);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	return 1;
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 写一个字节到芯片的内部寄存器里，芯片由 slave_address 指向，内部寄存器由 reg_address 指向

 *=================================================*/
unsigned char I2C1_ByteWrite_Reg( unsigned char slave_address,unsigned char reg_address,unsigned char data_to_write_in)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Transmitter);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1,reg_address);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C1,data_to_write_in);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	return 1;
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
unsigned char I2C2_ByteWrite(unsigned char slave_address,unsigned char data_to_write_in)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Transmitter);              
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2,data_to_write_in);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	return 1;
}

unsigned char I2C2_ByteWrite_Reg( unsigned char slave_address,unsigned char reg_address,unsigned char data_to_write_in)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Transmitter);              
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2,reg_address);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C2,data_to_write_in);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	return 1;
}


/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 从 slave_address 指向的芯片读取一个字节

 *=================================================*/
unsigned char I2C1_ByteRead(unsigned char slave_address)
{
	unsigned char data_read;
	
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Receiver);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_AcknowledgeConfig(I2C1,DISABLE);
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	data_read = I2C_ReceiveData(I2C1);
	
	return data_read; 

}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 从slave_address 指向的芯片内部的寄存器（reg_address 指向）中读取一个字节

 *=================================================*/
unsigned char I2C1_ByteRead_Reg(unsigned char slave_address,unsigned char reg_address)
{
	unsigned char data_read;
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Transmitter);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_Cmd(I2C1,ENABLE);
	
	I2C_SendData(I2C1,reg_address);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
//--------------------------------------//
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1,slave_address,I2C_Direction_Receiver);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_AcknowledgeConfig(I2C1,DISABLE);
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	data_read = I2C_ReceiveData(I2C1);
	
	return data_read;
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
unsigned char I2C2_ByteRead(unsigned char slave_address)
{
	unsigned char data_read;
	
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Receiver);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	data_read = I2C_ReceiveData(I2C2);
	
	return data_read; 

}

unsigned char I2C2_ByteRead_Reg(unsigned char slave_address,unsigned char reg_address)
{
	unsigned char data_read;
	
	while(I2C_GetFlagStatus(I2C2,I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Transmitter);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_Cmd(I2C2,ENABLE);
	
	I2C_SendData(I2C2,reg_address);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
//--------------------------------------//
	I2C_GenerateSTART(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2,slave_address,I2C_Direction_Receiver);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	data_read = I2C_ReceiveData(I2C2);
	
	return data_read;
}