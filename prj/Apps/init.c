#include "includes.h"

#define OFFSET_ON 0  // 进行offset的开关



/* Externs */




//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////

static void delay_m(u16 nms) // 不精确延时
{	
	
	uint16_t i,j;
	
	for(i=0;i<nms;i++)
		for(j=0;j<30000;j++);
	
} 

void Init_all(void)
{
	/* LED init */
	GPIO_InitTypeDef gpio_struct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	gpio_struct.GPIO_Pin = GPIO_Pin_9;
	gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_struct.GPIO_OType = GPIO_OType_PP;
	gpio_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&gpio_struct);
	
	LED_OFF;
//---------------------------------------+
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	I2C1_Init();
	
	MPU9250_init();

	PWM_Init();
	
	Set_PWM1(4000);
	Set_PWM2(4000);
	Set_PWM3(4000);
	Set_PWM4(4000);
	
	delay_m(2000);
	
	LPF2pSetCutoffFreq_1(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);		//20Hz  
	LPF2pSetCutoffFreq_2(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);
	LPF2pSetCutoffFreq_3(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);
		
	LPF2pSetCutoffFreq_4(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);
	LPF2pSetCutoffFreq_5(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);
	LPF2pSetCutoffFreq_6(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);
	
	LPF2pSetCutoffFreq_7(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);
	LPF2pSetCutoffFreq_8(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);
	LPF2pSetCutoffFreq_9(IMU_SAMPLE_RATE,IMU_FILTER_CUTOFF_FREQ);

	USART1_Init(9600);
	
	PID_Init();
	
	LED_ON;
	delay_m(2000);
	LED_OFF;
	
	sys_time_init();
	
}