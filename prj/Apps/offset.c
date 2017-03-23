/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#include "offset.h"
#include "stm32f4xx.h"
#include "mpu9250_driver.h"
#include "my_imu.h"
#include "flash_driver.h"

/* Externs */


extern IMU_data_t             IMU_data;  // 姿态解算出的数据
extern MPU9250_read_data_t    MPU_data;  // mpu9250的数据

//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////
u8 GYRO_OFFSET_OK = 0;

u8 ACC_OFFSET_OK = 0;

offset_data_t offset_data;

void offset()
{
	if(!GYRO_OFFSET_OK)
	{
		static int32_t	tempgx=0,tempgy=0,tempgz=0;
		static int cnt_g=0;

		if(cnt_g==0)
		{
			offset_data.gyro_offset_x=0;
			offset_data.gyro_offset_y=0;
			offset_data.gyro_offset_z=0;
			tempgx = 0;
			tempgy = 0;
			tempgz = 0;
			cnt_g = 1;
			return;
		}
		tempgx+= MPU_data.gyro_x;
		tempgy+= MPU_data.gyro_y;
		tempgz+= MPU_data.gyro_z;
		if(cnt_g==2000)
		{
			offset_data.gyro_offset_x=tempgx/cnt_g;
			offset_data.gyro_offset_y=tempgy/cnt_g;
			offset_data.gyro_offset_z=tempgz/cnt_g;
			cnt_g = 0;
			GYRO_OFFSET_OK = 1;
			return;
		}
		cnt_g++;
	}
	if(!ACC_OFFSET_OK)
	{
		static int32_t	tempax=0,tempay=0,tempaz=0;
		static int  cnt_a=0;

		if(cnt_a==0)
		{
			offset_data.acc_offset_x = 0;
			offset_data.acc_offset_y= 0;
			offset_data.acc_offset_z = 0;
			tempax = 0;
			tempay = 0;
			tempaz = 0;
			cnt_a = 1;
			return;
		}
		tempax+= MPU_data.acc_x;
		tempay+= MPU_data.acc_y;
		tempaz+= MPU_data.acc_z;
		
		if(cnt_a==2000)
		{
			offset_data.acc_offset_x=tempax/cnt_a;
			offset_data.acc_offset_y=tempay/cnt_a;
			offset_data.acc_offset_z=tempaz/cnt_a;
			cnt_a = 0;
			
			ACC_OFFSET_OK = 1;
			return;
		}
		cnt_a++;		
	}
}

void read_offset() // acc xyz  gyro xyz
{
	u16 data_buf[6];
	flash_read(data_buf,6);
	
	offset_data.acc_offset_x = data_buf[0];
	offset_data.acc_offset_y = data_buf[1];
	offset_data.acc_offset_z = data_buf[2];
	
	offset_data.gyro_offset_x = data_buf[3];
	offset_data.gyro_offset_y = data_buf[4];
	offset_data.gyro_offset_z = data_buf[5];
	
}