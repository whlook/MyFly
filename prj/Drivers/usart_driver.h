/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#ifndef _USART_DRIVER_H_
#define _USART_DRIVER_H_

#include "stm32f4xx.h"
#include "stdio.h"

void USART1_Init(int baud); // PA9,10  TX,RX
void USART2_Init(int baud); // PA2,3   TX,RX

void USART1_sendData(unsigned char * tx_data_buf,unsigned char length);
unsigned char USART1_recData(unsigned char *get_buf);

void USART2_sendData(unsigned char * tx_data_buf,unsigned char length);
unsigned char USART2_recData(unsigned char *get_buf);






#endif