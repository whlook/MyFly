/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#include "my_imu.h"
#include "my_math.h"
#include "math.h"


#define RtA 		57.324841				//弧度到角度
#define AtR    	0.0174533				//角度到弧度
#define Acc_G 	0.0011963				//加速度变成G
#define Gyro_G 	0.0152672				//角速度变成度
#define Gyro_Gr	0.0002663			  //角速度到弧度
#define M_PI  (float)3.1415926535 


//10
#define Kp	  8.0f
#define Ki 	  0.008f
#define halfT 0.027f //0.01

IMU_data_t             IMU_data;  // 姿态解算出的数据

/* Externs */


extern MPU9250_read_data_t    MPU_data;  // mpu9250的数据

extern float                  inner_loop_time; // 内环时间
extern float                  outer_loop_time; // 外环时间

//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////

static float invSqrt(float x)  
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}



volatile float exInt=0.0, eyInt=0.0, ezInt=0.0; 
volatile float q0=1.0f, q1=0.0f, q2=0.0f, q3=0.0f; 



void get_pit_rol_yaw()
{
	//float halfT = outer_loop_time*0.5;

	float gx,gy,gz,ax,ay,az;
	
	gx = MPU_data.gyro_x;
	gy = MPU_data.gyro_y;
	gz = MPU_data.gyro_z;
	
	ax = MPU_data.acc_x;
	ay = MPU_data.acc_y;
	az = MPU_data.acc_z;
	
	gx = gx*Gyro_Gr;
	gy = gy*Gyro_Gr;
	gz = gz*Gyro_Gr;

	float norm;
  float vx, vy, vz;
  float ex, ey, ez;
	
	float q0q0 = q0*q0;
  float q0q1 = q0*q1;
  float q0q2 = q0*q2;
  float q0q3 = q0*q3;
  float q1q1 = q1*q1;
  float q1q2 = q1*q2;
  float q1q3 = q1*q3;
  float q2q2 = q2*q2;
  float q2q3 = q2*q3;
  float q3q3 = q3*q3;
	
	if(ax*ay*az==0)
 		return;
	
	norm = invSqrt(ax*ax + ay*ay + az*az);       
  ax = ax * norm;
  ay = ay * norm;
  az = az * norm;
	
	vx = 2*(q1q3 - q0q2);		
  vy = 2*(q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3 ;
	
	ex = (ay*vz - az*vy) ; 
  ey = (az*vx - ax*vz) ;
  ez = (ax*vy - ay*vx) ;
	
	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
  ezInt = ezInt + ez * Ki;
	
	gx = gx + Kp*ex + exInt;
  gy = gy + Kp*ey + eyInt;
  gz = gz + Kp*ez + ezInt;
	
	q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
  q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
  q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
  q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;
	
  norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  q0 = q0 *norm;
  q1 = q1 *norm;
  q2 = q2 *norm;
  q3 = q3 *norm;
	
	IMU_data.rol = fast_atan2(2*(q0*q1+q2*q3),1-2*(q1*q1+q2*q2))*57.3f;
	IMU_data.pitch = asin(2*(q1*q3-q0*q2))*57.3f;
	IMU_data.yaw = fast_atan2(2*(-q1*q2-q0*q3),2*(q0*q0+q1*q1)-1)*57.3f;
	
	
}