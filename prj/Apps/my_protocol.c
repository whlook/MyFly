
/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#include "my_protocol.h"
#include "usart_driver.h"
#include "stm32f4xx_gpio.h"
#include "usart_driver.h"

extern unsigned char usart1_rec_buf[200];

#define LED_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_9)
/* Externs */



//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////
static u8 data_to_send[50];  // 发送数据缓存
static u8 data_to_rec[1000];  // 接收数据缓存

static u8 flag_to_slave = 0;
static u8 flag_from_slave = 0;

static u16 safe_count = 0; // 安全计数器，如果长时间没有从pc接收到有效信息，则触发警报
u8 warning = 0; // 值为1 触发警报

u8 send_to_slave(data_to_slave_t data)
{
	u8 i = 0;
	data_to_send[i++] = 0xAA;
	data_to_send[i++] = 0xAA;
	data_to_send[i++] = flag_to_slave;
	
	flag_to_slave++;
	if(flag_to_slave>250)
		flag_to_slave = 0;
	
	data_to_send[i++] = data.data.yaw_pit_rol[0];
	data_to_send[i++] = data.data.yaw_pit_rol[1];
	data_to_send[i++] = data.data.yaw_pit_rol[2];
	
	data_to_send[i++] = data.data.pwm1234[0];
	data_to_send[i++] = data.data.pwm1234[1];
	data_to_send[i++] = data.data.pwm1234[2];
	data_to_send[i++] = data.data.pwm1234[3];
	data_to_send[i++] = data.data.pwm1234[4];
	data_to_send[i++] = data.data.pwm1234[5];
	data_to_send[i++] = data.data.pwm1234[6];
	data_to_send[i++] = data.data.pwm1234[7];
	
	data_to_send[i++] = data.data.pid12[0];
	data_to_send[i++] = data.data.pid12[1];
	data_to_send[i++] = data.data.pid12[2];
	data_to_send[i++] = data.data.pid12[3];
	data_to_send[i++] = data.data.pid12[4];
	data_to_send[i++] = data.data.pid12[5];
	
	data_to_send[i++] = data.data.mag;
	data_to_send[i++] = data.data.bmp;
	
	data_to_send[i++] = data.data.err;
	
	u8 sum = 0;
	for(u8 j = 0;j<i;j++)
		sum += data_to_send[j];
	data_to_send[i++] = sum;
	
	USART1_sendData(data_to_send,i);
	
	return 1;
	
}

u8 rec_from_slave(data_from_slave_t *data)
{
	
	//USART1_recData(data_to_rec);
	u16 i = 0;
	u16 j = 0;
	for(;j<185;j++)
	{
			if(usart1_rec_buf[j] == 0xAA && usart1_rec_buf[j+1] == 0xAA)
			{
					i = j;
					u8 sum = 0;
					u16 k = i;
	
					
					i++;i++;
					
					flag_from_slave = usart1_rec_buf[i++];	
					
					data->data.GPS_data[0] = usart1_rec_buf[i++];
					data->data.GPS_data[1] = usart1_rec_buf[i++];
					data->data.GPS_data[2] = usart1_rec_buf[i++];
					data->data.GPS_data[3] = usart1_rec_buf[i++];
					
					data->data.Height[0] = usart1_rec_buf[i++];
					data->data.Height[1] = usart1_rec_buf[i++];
					
					data->data.order[0] = usart1_rec_buf[i++];
					data->data.order[1] = usart1_rec_buf[i++];
					data->data.order[2] = usart1_rec_buf[i++];
					data->data.order[3] = usart1_rec_buf[i++];
					data->data.order[4] = usart1_rec_buf[i++];
					data->data.order[5] = usart1_rec_buf[i++];
					data->data.order[6] = usart1_rec_buf[i++];
					data->data.order[7] = usart1_rec_buf[i++];
					data->data.order[8] = usart1_rec_buf[i++];
							
					for(;k<i;k++)
						sum += usart1_rec_buf[k];
					if(sum == usart1_rec_buf[i])
					{
					
						return 1;
					}

				
			}
	}
	return 0;
	

//			i++;
//	if(i>99) i = 0;
//	i++;
//	if(i>99) i = 0;
//		if(data_to_rec[i]==flag_from_slave)
//			return;
//		flag_from_slave = data_to_rec[i++];
//		if(i>99) i = 0;
//		
//		data->data.GPS_data[0] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.GPS_data[1] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.GPS_data[2] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.GPS_data[3] = data_to_rec[i++];
//		if(i>99) i = 0;
//		
//		data->data.Height[0] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.Height[1] = data_to_rec[i++];
//		if(i>99) i = 0;
//		
//		data->data.order[0] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.order[1] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.order[2] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.order[3] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.order[4] = data_to_rec[i++];
//		if(i>99) i = 0;
//		data->data.order[5] = data_to_rec[i++];
//		if(i>99) i = 0;
	
}



void rc_data_anl()  // 遥控数据解析
{
	
}