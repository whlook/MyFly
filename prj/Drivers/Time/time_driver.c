#include "time_driver.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
void TIM3_Init(u16 reload_value_us)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = reload_value_us-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void TIM2_Init(u16 reload_value_us)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = reload_value_us-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
	
	TIM_Cmd(TIM2,DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}



/************************************** Ä£°å **************************************|

void TIM2_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) 
	{

	  // here is the code to run;
		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 

}

====================================================================================

void TIM3_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) 
	{

	  // here is the code to run;
		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 

}

**************************************************************************************/
