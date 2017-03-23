/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#ifndef _PID_H_
#define _PID_H_

typedef struct pid_data
{
	float inner_rol_p;
	float inner_rol_i;
	float inner_rol_d;
	
	float inner_pitch_p;
	float inner_pitch_i;
	float inner_pitch_d;

	float inner_yaw_p;
	float inner_yaw_i;
	float inner_yaw_d;
		
	float outer_rol_p;
	float outer_rol_i;
	float outer_rol_d;
	
	float outer_pitch_p;
	float outer_pitch_i;
	float outer_pitch_d;

	float outer_yaw_p;
	float outer_yaw_i;
	float outer_yaw_d;	
	
	float single_rol_p;
	float single_rol_i;
	float single_rol_d;
	
	float single_pitch_p;
	float single_pitch_i;
	float single_pitch_d;

	float single_yaw_p;
	float single_yaw_i;
	float single_yaw_d;	
	
	
}pid_data_t;

extern pid_data_t PID_data;

enum {
    PIDROLL,
    PIDPITCH,
    PIDYAW,
		PID4,
		PID5,
		PID6,

		PIDITEMS
};

typedef struct 
{
  float x;
	float y;
	float z;
}xyz_f_t;

typedef struct
{
	float kp;
	float kd;
	float ki;
	float kdamp;

}pid_t;

typedef struct
{
	xyz_f_t err;
	xyz_f_t err_old;
	xyz_f_t err_i;
	xyz_f_t eliminate_I;
	xyz_f_t err_d;
	xyz_f_t damp;
	xyz_f_t out;
	pid_t 	PID[PIDITEMS];
	xyz_f_t err_weight;
	float FB;

}ctrl_t;


void PID_Init();

void inner_ctrl();
void outer_ctrl();
void single_pid();

#endif