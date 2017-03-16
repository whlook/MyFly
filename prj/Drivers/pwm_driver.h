#ifndef _PWM_DRIVER_H_
#define _PWM_DRIVER_H_
#include "stm32f4xx.h"

void PWM_Init(void); // 初始化 ，最大10000

void Set_ESC(void);  // 行程为 4000-8000

void Set_PWM1(u16 pwm_value);
void Set_PWM2(u16 pwm_value);
void Set_PWM3(u16 pwm_value);
void Set_PWM4(u16 pwm_value);


#endif