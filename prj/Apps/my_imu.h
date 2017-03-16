/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#ifndef _MY_IMU_H_
#define _MY_IMU_H_
#include "stm32f4xx.h"
#include "mpu9250_driver.h"

typedef struct IMU_data
{
	float rol;
	float pitch;
	float yaw;
}IMU_data_t;

extern IMU_data_t             IMU_data;  // 姿态解算出的数据

void get_pit_rol_yaw();

#endif