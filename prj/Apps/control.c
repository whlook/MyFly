#include "control.h"
#include "pwm_driver.h"
/* Externs */

extern u8 Flag_Fly_Start;  // 允许飞行标志

extern u8 Flag_Auto_Down;  // 允许飞行标志;  // 允许飞行标志
//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////

pwm_data_t moto_pwm;

pwm_data_t thro_pwm;

u16 safe_thro;

void motot_ctrl()
{
	if(Flag_Fly_Start)
	{
		Set_PWM1(4000+thro_pwm.pwm1+moto_pwm.pwm1);
		Set_PWM2(4000+thro_pwm.pwm2+moto_pwm.pwm2);
		Set_PWM3(4000+thro_pwm.pwm3+moto_pwm.pwm3);
		Set_PWM4(4000+thro_pwm.pwm4+moto_pwm.pwm4);
	}
	else 
	{
		Set_PWM1(4000);
		Set_PWM2(4000);
		Set_PWM3(4000);
		Set_PWM4(4000);
	}
		
}