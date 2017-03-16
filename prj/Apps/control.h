#pragma ONCE
#include "stm32f4xx.h"
typedef struct pwm_data
{
	u16 pwm1;
	u16 pwm2;
	
	u16 pwm3;
	u16 pwm4;
	
}pwm_data_t;

extern pwm_data_t moto_pwm;
extern pwm_data_t thro_pwm;

void motot_ctrl();