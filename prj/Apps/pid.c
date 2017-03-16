#include "pid.h"
#include "includes.h"

/* Externs */

extern IMU_data_t             IMU_data;  // 姿态解算出的数据
extern MPU9250_read_data_t    MPU_data;  // mpu9250的数据

extern float                  inner_loop_time; // 内环时间
extern float                  outer_loop_time; // 外环时间

extern u8 Flag_Fly_Start;  // 允许飞行标志

pid_data_t PID_data;

//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////

ctrl_t ctrl_1;
ctrl_t ctrl_2;

float set_angle_x = 0;  // 回中
float set_angle_y = 0;
float set_angle_z = 0;

float inner_set_val = 0.0;

float outer_x_err,outer_y_err;
float inner_x_err,inner_y_err,inner_z_err;

float outer_x_err_old,outer_y_err_old;
float inner_x_err_old,inner_y_err_old,inner_z_err_old; // 上一次的误差值

float outer_xi,outer_yi;   // 内外环积分
float inner_xi,inner_yi,inner_zi;

u8 flag_outer_xi_de = 1,flag_outer_yi_de = 1;  // 积分分离标志
u8 flag_inner_xi_de = 1,flag_inner_yi_de,flag_inner_zi_de = 1; 

float outer_xout,outer_yout; // 内外环输出
float inner_xout,inner_yout,inner_zout;



void inner_ctrl() // 内环 角速度
{
	inner_x_err = outer_xout - MPU_data.gyro_x;
	
	inner_xi+=inner_x_err;
	if(!Flag_Fly_Start)
		inner_xi = 0;
	
	if(inner_xi>1000)// 积分限幅
		inner_xi = 1000;
	if(inner_xi<-1000)
		inner_xi = -1000;
	
	inner_xout = PID_data.inner_rol_p*inner_x_err + PID_data.inner_rol_i*inner_xi*flag_inner_xi_de*0.1 + PID_data.inner_rol_d*(inner_x_err - inner_x_err_old);
	
	inner_x_err_old = inner_x_err;
//---------------------------------------------------------------+
	inner_y_err = outer_yout - MPU_data.gyro_y;
	
	inner_yi+=inner_y_err;
		if(!Flag_Fly_Start)
		inner_yi = 0;
	
	if(inner_yi>1000)// 积分限幅
		inner_yi = 1000;
	if(inner_yi<-1000)
		inner_yi = -1000;
	
	inner_yout = PID_data.inner_pitch_p*inner_y_err + PID_data.inner_pitch_i*inner_yi*flag_inner_yi_de*0.01 + PID_data.inner_pitch_d*(inner_y_err - inner_y_err_old);
	

	inner_y_err_old = inner_y_err;
	
	moto_pwm.pwm2 = (- inner_xout - inner_yout + 0 );
	if(moto_pwm.pwm2>1500)
		moto_pwm.pwm2 = 1500;
	moto_pwm.pwm1 = (+ inner_xout - inner_yout - 0 );
		if(moto_pwm.pwm1>1500)
		moto_pwm.pwm1 = 1500;

	moto_pwm.pwm4 = (+ inner_xout + inner_yout + 0 );
		if(moto_pwm.pwm4>1500)
		moto_pwm.pwm4 = 1500;
	moto_pwm.pwm3 = (- inner_xout + inner_yout - 0 );
		if(moto_pwm.pwm3>1500)
		moto_pwm.pwm3 = 1500;
	
	
}
void outer_ctrl()
{
	outer_x_err = set_angle_x - IMU_data.rol;
	
	outer_xi += outer_x_err;
		if(!Flag_Fly_Start)
		outer_xi = 0;
	if(outer_xi>30)// 积分限幅
		outer_xi = 30;
	if(outer_xi<-30)
		outer_xi = -30;
	
	outer_xout = PID_data.outer_rol_p*outer_x_err + PID_data.outer_rol_i*outer_xi*0.01 + PID_data.outer_rol_d*(outer_x_err - outer_x_err_old);
	
	outer_x_err_old = outer_x_err;
//---------------------------------------------+	
	
	outer_y_err = IMU_data.pitch -set_angle_y;
	
	outer_yi += outer_y_err;
		if(!Flag_Fly_Start)
		outer_yi = 0;
	
	if(outer_yi>30)// 积分限幅
		outer_yi = 30;
	if(outer_yi<-30)
		outer_yi = -30;
	
	outer_yout = PID_data.outer_pitch_p*outer_y_err + PID_data.outer_pitch_i*outer_yi*0.01 + PID_data.outer_pitch_d*(outer_y_err - outer_y_err_old);
	
	outer_y_err_old = outer_y_err;
}

void PID_Init()
{
	PID_data.inner_rol_p = 0.21;
	PID_data.inner_rol_i = 0.01;//0.002;//0.02;
	PID_data.inner_rol_d =0.6;// 0.5;//0.5;//1;
	
	PID_data.inner_pitch_p = 0.2;
	PID_data.inner_pitch_i = 0.9;
	PID_data.inner_pitch_d = 0.3;
	
	PID_data.inner_yaw_p = 0;
	PID_data.inner_yaw_i = 0;
	PID_data.inner_yaw_d = 0;
	
	PID_data.outer_rol_p = 95;//50;//37;
	PID_data.outer_rol_i = 0;//0;//10;//5;
	PID_data.outer_rol_d = 20;//0.2;//0.3;//20;//20;//30;//20;//30;
	
	PID_data.outer_pitch_p = 120;//95;//95;
	PID_data.outer_pitch_i = 0;
	PID_data.outer_pitch_d = 20;//20;
}