/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
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

float outer_x_err,outer_y_err,outer_z_err;
float inner_x_err,inner_y_err,inner_z_err;

float outer_x_err_old,outer_y_err_old,outer_z_err_old;
float inner_x_err_old,inner_y_err_old,inner_z_err_old; // 上一次的误差值

float outer_xi,outer_yi,outer_zi;   // 内外环积分
float inner_xi,inner_yi,inner_zi;

u8 flag_outer_xi_de = 1,flag_outer_yi_de = 1,flag_outer_zi_de = 1;  // 积分分离标志
u8 flag_inner_xi_de = 1,flag_inner_yi_de = 1,flag_inner_zi_de = 1; 

float outer_xout,outer_yout,outer_zout; // 内外环输出
float inner_xout,inner_yout,inner_zout;

float single_xerr,single_yerr,single_zerr;  // 单环
float single_xout,single_yout,single_zout;
float single_xerr_old,single_yerr_old,single_zerr_old;

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
//---------------------------------------------------------------+
	inner_z_err = outer_zout - MPU_data.gyro_z;
	
	inner_zi+=inner_z_err;
		if(!Flag_Fly_Start)
		inner_zi = 0;
	
	if(inner_zi>1000)// 积分限幅
		inner_zi = 1000;
	if(inner_zi<-1000)
		inner_zi = -1000;
	
	inner_zout = PID_data.inner_yaw_p*inner_z_err + PID_data.inner_yaw_i*inner_zi*flag_inner_zi_de*0.01 + PID_data.inner_yaw_d*(inner_z_err - inner_z_err_old);
	

	inner_z_err_old = inner_z_err;
	
	moto_pwm.pwm2 = (- inner_xout - inner_yout + inner_zout );

	moto_pwm.pwm1 = (+ inner_xout - inner_yout - inner_zout );

	moto_pwm.pwm4 = (+ inner_xout + inner_yout + inner_zout );

	moto_pwm.pwm3 = (- inner_xout + inner_yout - inner_zout );

	
	
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
		
	outer_y_err = IMU_data.pitch -set_angle_y ;
	
	outer_yi += outer_y_err;
		if(!Flag_Fly_Start)
		outer_yi = 0;
	
	if(outer_yi>30)// 积分限幅
		outer_yi = 30;
	if(outer_yi<-30)
		outer_yi = -30;
	
	outer_yout = PID_data.outer_pitch_p*outer_y_err + PID_data.outer_pitch_i*outer_yi*0.01 + PID_data.outer_pitch_d*(outer_y_err - outer_y_err_old);
	
	outer_y_err_old = outer_y_err;
//---------------------------------------------+	
		
	outer_z_err = IMU_data.yaw -set_angle_z ;
	
	outer_zi += outer_z_err;
		if(!Flag_Fly_Start)
		outer_zi = 0;
	
	if(outer_zi>30)// 积分限幅
		outer_zi = 30;
	if(outer_zi<-30)
		outer_zi = -30;
	
	outer_zout = PID_data.outer_yaw_p*outer_z_err + PID_data.outer_yaw_i*outer_zi*0.01 + PID_data.outer_yaw_d*(outer_z_err - outer_z_err_old);
	
	outer_z_err_old = outer_z_err;
}

void single_pid()
{
	single_xerr = set_angle_x - IMU_data.rol;
	single_xout = PID_data.single_rol_p*single_xerr+PID_data.single_rol_d*(single_xerr - single_xerr_old);
	single_xerr_old = single_xerr;
	
	single_yerr = set_angle_y - IMU_data.pitch;
	single_yout = PID_data.single_pitch_p*single_yerr+PID_data.single_pitch_d*(single_yerr - single_yerr_old);
	single_yerr_old = single_yerr;
	
	single_zerr = set_angle_z - IMU_data.yaw;
	single_zout = PID_data.single_yaw_p*single_zerr+PID_data.single_yaw_d*(single_zerr - single_zerr_old);
	single_zerr_old = single_zerr;
	
	moto_pwm.pwm2 = (- single_xout - single_yout + single_zout );

	moto_pwm.pwm1 = (+ single_xout - single_yout - single_zout );

	moto_pwm.pwm4 = (+ single_xout + single_yout + single_zout );

	moto_pwm.pwm3 = (- single_xout + single_yout - single_zout );
	
}

void PID_Init()
{
	PID_data.inner_rol_p = 0.21;
	PID_data.inner_rol_i =0;// 0.01;//0.002;//0.02;
	PID_data.inner_rol_d =0.6;// 0.5;//0.5;//1;
	
	PID_data.inner_pitch_p = 0.2;
	PID_data.inner_pitch_i = 0;//0.9;
	PID_data.inner_pitch_d = 0.3;
	
	PID_data.inner_yaw_p = 0.07;
	PID_data.inner_yaw_i = 0;
	PID_data.inner_yaw_d = 0.2;
	
	PID_data.outer_rol_p = 165;//50;//37;
	PID_data.outer_rol_i = 0;//0;//10;//5;
	PID_data.outer_rol_d = 35;//0.2;//0.3;//20;//20;//30;//20;//30;
	
	PID_data.outer_pitch_p = 165;//95;//95;
	PID_data.outer_pitch_i = 0;
	PID_data.outer_pitch_d = 35;//20;
	
	PID_data.outer_yaw_p = 100;
	PID_data.outer_yaw_i = 0;
	PID_data.outer_yaw_d = 25;
}