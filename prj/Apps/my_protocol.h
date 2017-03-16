#ifndef _MY_PROTOCOL_H_
#define _MY_PROTOCOL_H_
#include "stm32f4xx.h"

#define CLEAR_SD 		0x00
#define OFFSET   		0x01

#define WRITE_PID_ROL 	0x31
#define WRITE_PID_PIT 	0x32
#define WRITE_PID_YAW 	0x33

#define THRO_CRTL  	0x03
#define LEFT      	0x04
#define RIGHT     	0x05
#define FRONT     	0x06
#define BACK      	0x07
#define HOLD_HEIGHT 0x08
#define AUTO_DOWN   0x09
#define FLY_START   0x0A

#define SAFE_STOP   0x11
#define CONNECT_TIP 0x22
////////////////////////////////////////////////////
typedef struct data_to_master
{
	u8 GPS_data[4];
	u8 Height[2];
	u8 order[9]; // ÓÍÃÅ ×óÓÒÆ«ÒÆ Ç°ºóÆ«ÒÆ
	
}data_to_master_t;

typedef struct data_from_master
{
	u8 yaw_pit_rol[3];
	u8 pwm1234[8];
	u8 pid12[6];
	u8 mag;
	u8 bmp;
	u8 err;
	
}data_from_master_t;
//-----------------------------------+
typedef struct data_to_slave
{
	data_from_master_t data;
}data_to_slave_t;

typedef struct data_from_slave
{
	data_to_master_t data;
}data_from_slave_t;

/////////////////////////////////////////

u8 send_to_slave(data_to_slave_t data);

u8 rec_from_slave(data_from_slave_t *data);

void rc_data_anl();

#endif