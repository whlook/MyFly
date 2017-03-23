/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#include "duty.h"
#include "includes.h"


#define DEBUG_MODE 0 // 是否进入调试模式
#define PID_MODE 1 // 1 串级    0 单级
/********** Flags **********/

u8 Flag_Init_Finished = 0;  // 初始化完成标志

u8 Flag_Auto_Down = 0;  // 自动降落标志

u8 Flag_Fly_Start = 0;  // 允许飞行标志

u8 Flag_data_ready = 0;

/********** Ctrl **********/

float left_angel;
float right_angle;

float front_angle;
float back_angle;

extern float set_angle_x; 
extern float set_angle_y;

/********** Global Variables **********/

data_from_slave_t      data_from_slave; // 保存来自从机的数据
data_to_slave_t        data_to_slave;   // 保存发往从机的数据

float                  inner_loop_time; // 内环时间
float                  outer_loop_time; // 外环时间

float                  old_inner_loop_time = 0; // 上次内环时间
float                  old_outer_loop_time = 0; // 上次外环时间
float                  now_inner_loop_time = 0; // 上次内环时间
float                  now_outer_loop_time = 0; // 上次外环时间

u16 				  				 data_rec_from_slave[10]; // 保存来自从机的数据



//////////\\\\\\\\\\//////////\\\\\\\\\\//////////\\\\\\\\\\//////////\\\\\\\\\\//////////\\\\\\\\\\//////////\\\\\\\\\\//////////\\\\\\\\\\//////////\\\\\\\\\\//////////


void duty1ms()
{
	if(Flag_data_ready && data_from_slave.data.order[6] == THRO_CRTL)
	{
			data_rec_from_slave[0] = data_from_slave.data.GPS_data[0]+(data_from_slave.data.GPS_data[1]<<8);  
			data_rec_from_slave[1] = data_from_slave.data.GPS_data[2]+(data_from_slave.data.GPS_data[3]<<8);
			
			data_rec_from_slave[2] = data_from_slave.data.Height[0]+(data_from_slave.data.Height[1]<<8); 
			
		
		
			data_rec_from_slave[3] = data_from_slave.data.order[0];////////////////////////////////////////// 左右
			data_rec_from_slave[4] = data_from_slave.data.order[1]+(data_from_slave.data.order[2]<<8); //////
		
		if(data_from_slave.data.order[0] == LEFT)
		{
			left_angel = data_rec_from_slave[4]/10;
			if(left_angel>30)
				left_angel = 30;
			set_angle_x = -left_angel;
			
		}
		if(data_from_slave.data.order[0] == RIGHT)
		{
			right_angle = data_rec_from_slave[4]/10;
			if(right_angle>30)
				right_angle = 30;
			set_angle_x = right_angle;
			
		}
			
			data_rec_from_slave[5] = data_from_slave.data.order[3]; //////////////////////////////////////// 前后
			data_rec_from_slave[6] = data_from_slave.data.order[4]+(data_from_slave.data.order[5]<<8);//////
		
		if(data_from_slave.data.order[3] == FRONT)
		{
			front_angle = data_rec_from_slave[6]/10;
			if(front_angle>30)
				front_angle = 30;
			set_angle_y = -front_angle;
		}
		if(data_from_slave.data.order[3] == BACK)
		{
			back_angle = data_rec_from_slave[6]/10;
			if(back_angle>30)
				back_angle = 30;
			set_angle_y = back_angle;
		}
			
			data_rec_from_slave[7] = data_from_slave.data.order[6];////////////////////////////////////////// 油门
			data_rec_from_slave[8] = data_from_slave.data.order[7]+(data_from_slave.data.order[8]<<8); //////

	}
	
	if(Flag_data_ready && data_from_slave.data.order[0] == AUTO_DOWN)
	{	Flag_Fly_Start = 0;Flag_Auto_Down = 1;}
	else
	{
	if(Flag_data_ready && data_from_slave.data.order[0] != SAFE_STOP)
		Flag_Fly_Start = 1;
	else
	{Flag_Fly_Start = 0;Flag_Auto_Down = 0;}
	}
	thro_pwm.pwm1 = (data_from_slave.data.order[7]+(data_from_slave.data.order[8]<<8));
	thro_pwm.pwm2 = (data_from_slave.data.order[7]+(data_from_slave.data.order[8]<<8));
	thro_pwm.pwm3 = (data_from_slave.data.order[7]+(data_from_slave.data.order[8]<<8));
	thro_pwm.pwm4 = (data_from_slave.data.order[7]+(data_from_slave.data.order[8]<<8));
	
}

void duty2ms()
{
//	now_inner_loop_time = GetSysTime_us()/1000000.0f; //换成秒////| 内环时间
//	inner_loop_time = now_inner_loop_time-old_inner_loop_time;////|
//	old_inner_loop_time = now_inner_loop_time;////////////////////|
	
	MPU9250_get_data();
	
	MPU_data.acc_x = LPF2pApply_1(MPU_data.acc_x);  // 低通滤波
	MPU_data.acc_y = LPF2pApply_2(MPU_data.acc_y);
	MPU_data.acc_z = LPF2pApply_3(MPU_data.acc_z);
			
	MPU_data.gyro_x = LPF2pApply_4(MPU_data.gyro_x);
	MPU_data.gyro_y = LPF2pApply_5(MPU_data.gyro_y);
	MPU_data.gyro_z = LPF2pApply_6(MPU_data.gyro_z);
			
	MPU_data = move_average(MPU_data); // 滑动滤波
	
	#if PID_MODE
		inner_ctrl(); // 内环控制
	#else
		single_pid();
	#endif
	
	motot_ctrl();
	

}


void duty5ms()
{
//	now_outer_loop_time = GetSysTime_us()/1000000.0f;/////////////| 外环时间
//	outer_loop_time = now_outer_loop_time - old_inner_loop_time;//|
//	old_inner_loop_time = now_inner_loop_time;////////////////////|
	
	get_pit_rol_yaw();
	
	#if PID_MODE
		outer_ctrl();
	#endif
	
}

void duty10ms()
{
	mag_bmp_read();
	
	#if DEBUG_MODE
		data_to_slave.data.yaw_pit_rol[0] = IMU_data.rol;
		data_to_slave.data.yaw_pit_rol[1] = IMU_data.rol;
		data_to_slave.data.yaw_pit_rol[2] = IMU_data.rol;
		
		data_to_slave.data.pwm1234[0] = BYTE0(moto_pwm.pwm1);
		data_to_slave.data.pwm1234[1] = BYTE1(moto_pwm.pwm1);
		
		data_to_slave.data.pwm1234[2] = BYTE0(moto_pwm.pwm2);
		data_to_slave.data.pwm1234[3] = BYTE1(moto_pwm.pwm2);
		
		data_to_slave.data.pwm1234[4] = BYTE0(moto_pwm.pwm3);
		data_to_slave.data.pwm1234[5] = BYTE1(moto_pwm.pwm3);
		
		data_to_slave.data.pwm1234[6] = BYTE0(moto_pwm.pwm4);
		data_to_slave.data.pwm1234[7] = BYTE1(moto_pwm.pwm4);
		
		data_to_slave.data.pid12[0] = PID_data.inner_rol_p*10;
		data_to_slave.data.pid12[1] = PID_data.inner_rol_i*10;
		data_to_slave.data.pid12[2] = PID_data.inner_rol_d*10;
		
		data_to_slave.data.pid12[3] = PID_data.outer_rol_p*10;
		data_to_slave.data.pid12[4] = PID_data.outer_rol_i*10;
		data_to_slave.data.pid12[5] = PID_data.outer_rol_d*10;

		data_to_slave.data.mag = 0x11;
		data_to_slave.data.bmp = 0x22;
		data_to_slave.data.err = 0x33;
	
		send_to_slave(data_to_slave);
	#endif
}

void duty20ms()
{
  
}