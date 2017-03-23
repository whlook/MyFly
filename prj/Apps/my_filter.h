/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#ifndef _MY_FILTER_H_
#define _MY_FILTER_H_
#include "stm32f4xx.h"
#include "mpu9250_driver.h"
#include <math.h>

#define MOV_AVR_NUM 10

#define IMU_SAMPLE_RATE 			100.0f	//1000.0f/(float)DMP_CALC_PRD

#define IMU_FILTER_CUTOFF_FREQ	20.0f

MPU9250_read_data_t move_average(MPU9250_read_data_t t);

void LPF2pSetCutoffFreq_1(float sample_freq, float cutoff_freq);
float LPF2pApply_1(float sample);
void LPF2pSetCutoffFreq_2(float sample_freq, float cutoff_freq);
float LPF2pApply_2(float sample);
void LPF2pSetCutoffFreq_3(float sample_freq, float cutoff_freq);
float LPF2pApply_3(float sample);
void LPF2pSetCutoffFreq_4(float sample_freq, float cutoff_freq);
float LPF2pApply_4(float sample);
void LPF2pSetCutoffFreq_5(float sample_freq, float cutoff_freq);
float LPF2pApply_5(float sample);
void LPF2pSetCutoffFreq_6(float sample_freq, float cutoff_freq);
float LPF2pApply_6(float sample);
void LPF2pSetCutoffFreq_7(float sample_freq, float cutoff_freq);
float LPF2pApply_7(float sample);
void LPF2pSetCutoffFreq_8(float sample_freq, float cutoff_freq);
float LPF2pApply_8(float sample);
void LPF2pSetCutoffFreq_9(float sample_freq, float cutoff_freq);
float LPF2pApply_9(float sample);

#endif
