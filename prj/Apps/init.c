/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#include "includes.h"
#include "init.h"

#define OFFSET_ON 1  // offset(1) or not(0) 
#define SET_ESC 1    // set_esc(1) or not (0) [electronic speed controller]


//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////

static void delay_m(u16 nms) // A not accurate delay func.
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

#if OFFSET_ON
	offset();
#endif

	PWM_Init();
	
#if SET_ESC
	Set_ESC();
#endif

	LPF_init(); // 20Hz

	USART1_Init(9600);
	
	PID_Init();
	
	LED_ON;
	
	delay_m(2000);
	
	LED_OFF;
	
	sys_time_init();
	
}