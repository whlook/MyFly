#include "pwm_driver.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"



static void delay_ms(u16 nms) // 不精确延时
{	
	
	uint16_t i,j;
	
	for(i=0;i<nms;i++)
		for(j=0;j<30000;j++);
	
} 

/*使用的是TIM3*/
void PWM_Init(void)
{
	/*相关结构体定义*/
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/*使能相关时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	   
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB,ENABLE); 	
	
	/*GPIO端口复用*/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); //复用为定时器3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); //复用为定时器3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //复用为定时器3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //复用为定时器3

	/*端口初始化*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;   //GPIOA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;  //GPIOB
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化
	
	/*定时器初始化*/
	TIM_TimeBaseStructure.TIM_Prescaler=21-1;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=10000-1;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器3
	
	//初始化TIM3 Channel PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  

  //使能预装载值
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	
}

void Set_ESC(void)
{
		TIM3->CCR1 = 8000; 
		TIM3->CCR2 = 8000;
		TIM3->CCR3 = 8000; 
		TIM3->CCR4 = 8000;
		delay_ms(4000);
	
		TIM3->CCR1 = 4000; 
		TIM3->CCR2 = 4000;
		TIM3->CCR3 = 4000; 
		TIM3->CCR4 = 4000;
		delay_ms(2000);
	
		TIM3->CCR1 = 5000; 
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000; 
		TIM3->CCR4 = 5000;
}

void Set_PWM1(u16 pwm_value)
{
	if(pwm_value<4000)
		pwm_value = 4000;
	if(pwm_value>8000)
		pwm_value = 8000;
	
	TIM3->CCR1 = pwm_value;
}
void Set_PWM2(u16 pwm_value)
{
	if(pwm_value<4000)
		pwm_value = 4000;
	if(pwm_value>8000)
		pwm_value = 8000;
	
	TIM3->CCR2 = pwm_value;
}
void Set_PWM3(u16 pwm_value)
{
	if(pwm_value<4000)
		pwm_value = 4000;
	if(pwm_value>8000)
		pwm_value = 8000;
	
	TIM3->CCR3 = pwm_value;
}
void Set_PWM4(u16 pwm_value)
{
	if(pwm_value<4000)
		pwm_value = 4000;
	if(pwm_value>8000)
		pwm_value = 8000;
	TIM3->CCR4 = pwm_value;
}