#include "to_pc.h"
#include "includes.h"
/* Externs */


extern IMU_data_t IMU_data;
extern u32 sys_cnt;

//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////

static u8 data_to_send[33];

static void Send_Status()
{
	float roll = IMU_data.rol;
	float pitch = IMU_data.pitch;
	float yaw = IMU_data.yaw;
	
	u8 _cnt = 0;
	u8 sum = 0;
	u8 i;
  volatile short int  _temp;

  data_to_send[_cnt++] = 0xAA;
  data_to_send[_cnt++] = 0xAA;
  data_to_send[_cnt++] = 0x01;
  data_to_send[_cnt++] = 12;

  _temp = (int)(roll * 100);
  data_to_send[_cnt++] = BYTE1(_temp);
  data_to_send[_cnt++] = BYTE0(_temp);
  _temp = (int)(pitch * 100);
  data_to_send[_cnt++] = BYTE1(_temp);
  data_to_send[_cnt++] = BYTE0(_temp);
  _temp =(int)( yaw * 100);
  data_to_send[_cnt++] = BYTE1(_temp);
  data_to_send[_cnt++] = BYTE0(_temp);

  _temp = 2 ;
  data_to_send[_cnt++] = BYTE3(_temp);
  data_to_send[_cnt++] = BYTE2(_temp);
  data_to_send[_cnt++] = BYTE1(_temp);
  data_to_send[_cnt++] = BYTE0(_temp);
  _temp = 2;
  data_to_send[_cnt++] = BYTE0(_temp);
  _temp = 2;
  data_to_send[_cnt++] = BYTE0(_temp);


  for ( i = 0; i < _cnt; i++)
    sum += data_to_send[i];
  data_to_send[_cnt++] = sum;

  USART1_sendData(data_to_send,_cnt);
	
// USART1_Send(data_to_send,_cnt);

	
}

void send_to_pc(void)
{
	Send_Status();
}

