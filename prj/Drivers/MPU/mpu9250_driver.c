/***********************************************

	Fly2017  < 2017-1-13 >
	MPU9250 驱动程序 库函数版本

************************************************/
#include "mpu9250_driver.h"
#include "i2c_driver.h"
#include "stm32f4xx_gpio.h"
#include "offset.h"

/* Externs */

 MPU9250_read_data_t    MPU_data;  // mpu9250的数据


//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
static short int GetData(unsigned char slave_address,unsigned char REG_Address)
{
	short int H,L;
	
	H=I2C1_ByteRead_Reg(slave_address,REG_Address);
	L=I2C1_ByteRead_Reg(slave_address,REG_Address+1);
	
	return ((H<<8)+L);
	
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
static short int GetData_L(unsigned char slave_address,unsigned char REG_Address)
{
	short int H,L;
	
	L=I2C1_ByteRead_Reg(slave_address,REG_Address);
	H=I2C1_ByteRead_Reg(slave_address,REG_Address+1);
	
	return ((H<<8)+L);
}

// delay ms // 
static void delay_ms(u16 nms)
{	
	
	uint16_t i,j;
	
	for(i=0;i<nms;i++)
		for(j=0;j<8500;j++);
	
} 

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
void MPU9250_init(void)
{

	I2C1_ByteWrite_Reg(0xd0,MPU6500_PWR_MGMT_1,0x00);  		 // wake up mpu6500
	delay_ms(50);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_PWR_MGMT_1,0x03);  		 // setClockSource
	delay_ms(50);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_SMPLRT_DIV,1);      // setDiv //  1000/(0+1) = 1000Hz
	delay_ms(50);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_CONFIG,0x04);          // gyro low pass 20Hz
	delay_ms(50);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_GYRO_CONFIG,0x18);     // +-2000 dps
	delay_ms(50);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_ACCEL_CONFIG,0x10);    // +-8g
	delay_ms(50);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_ACCEL_CONFIG_2,0x04);  // acc low pass 20Hz
	delay_ms(50);
//+----------------------------------------------------+
	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x00);       //  disable master , if open ,0x20
	delay_ms(50);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x02);     // open passby
	delay_ms(50);
//+----------------------+
	I2C1_ByteWrite_Reg(0x18,0x0a,0x06);                    // open ak's read
	delay_ms(50);
//+----------------------+
	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x20);       //
	delay_ms(50);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x00);     //
	delay_ms(50);
	
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/

#define CONSTANTS_ONE_G			  9.7950f		/* m/s^2 */
#define PI                    3.141592654
#define SENSOR_MAX_G          8.0f        // g
#define SENSOR_MAX_W          2000.0f     // deg/s
#define ACC_SCALE             (SENSOR_MAX_G/32768.0f)  // turn to g
#define GYRO_SCALE            (SENSOR_MAX_W/32768.0f)  // turn to deg

void   MPU9250_get_data(void)
{
	
	/****  data  ****/
	MPU_data.acc_x = (float)GetData(0xd0,MPU6500_ACCEL_XOUT_H)*ACC_SCALE*CONSTANTS_ONE_G - offset_data.acc_offset_x; // g
	MPU_data.acc_y = (float)GetData(0xd0,MPU6500_ACCEL_YOUT_H)*ACC_SCALE*CONSTANTS_ONE_G - offset_data.acc_offset_y;
	MPU_data.acc_z = (float)GetData(0xd0,MPU6500_ACCEL_ZOUT_H)*ACC_SCALE*CONSTANTS_ONE_G - offset_data.acc_offset_z;
	
	MPU_data.gyro_x = (float)GetData(0xd0,MPU6500_GYRO_XOUT_H)*GYRO_SCALE*180.f/PI - offset_data.gyro_offset_x; // deg/s
	MPU_data.gyro_y = (float)GetData(0xd0,MPU6500_GYRO_YOUT_H)*GYRO_SCALE*180.f/PI - offset_data.gyro_offset_y;
	MPU_data.gyro_z = (float)GetData(0xd0,MPU6500_GYRO_ZOUT_H)*GYRO_SCALE*180.f/PI - offset_data.gyro_offset_z;
	
	MPU_data.temperature =(float)GetData(0xd0,MPU6500_TEMP_OUT_H)/340 + 36.53; // ℃
	
	/****  turn to physical  ****/
//	MPU_data.acc_x = (float)MPU_data.acc_x*ACC_SCALE*CONSTANTS_ONE_G;  //g  
//	MPU_data.acc_y = (float)MPU_data.acc_y*ACC_SCALE*CONSTANTS_ONE_G;
//	MPU_data.acc_z = (float)MPU_data.acc_z*ACC_SCALE*CONSTANTS_ONE_G;
//	
//	
//	MPU_data.gyro_x = (float)MPU_data.gyro_x*GYRO_SCALE*180.f/PI;      // deg/s   
//	MPU_data.gyro_y = (float)MPU_data.gyro_y*GYRO_SCALE*180.f/PI;
//	MPU_data.gyro_z = (float)MPU_data.gyro_z*GYRO_SCALE*180.f/PI;
//	
//	MPU_data.temperature = (float)MPU_data.temperature;    // ℃

	
		
}

void mag_bmp_read()
{
	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x00); //  disable master , if open ,0x20
	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x02); // open passby
			
	MPU_data.mag_x = GetData_L(0x18,AK8963_HXL);
	MPU_data.mag_y = GetData_L(0x18,AK8963_HYL);
  MPU_data.mag_z = GetData_L(0x18,AK8963_HZL);			
	
	I2C1_ByteRead_Reg(0x18,0x09);  // read st2 to finish reading mag, only after this ,data can be reflush!!!!
			
	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x20);
	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x00);
}


