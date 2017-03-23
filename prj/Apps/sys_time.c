/***********************************************

	Fly2017  < 2017-1-13 >

************************************************/
#include "sys_time.h"
#include "duty.h"

volatile u32 sysTickCnt = 0;

static u16 timeCnt1ms = 0;
static u16 timeCnt2ms = 0;
static u16 timeCnt5ms = 0;
static u16 timeCnt10ms = 0;
static u16 timeCnt20ms = 0;

uint32_t GetSysTime_us(void) 
{
	register uint32_t us;
	u32 value;
	us = sysTickCnt;
	value = us + (SysTick->LOAD - SysTick->VAL) / SysTick->LOAD;
	return value;
}

void sysTime()
{
	timeCnt1ms++;
	timeCnt2ms++;
	timeCnt5ms++;
	timeCnt10ms++;
	//timeCnt20ms++;
	
	if(timeCnt1ms==1000)
	{
		timeCnt1ms = 0;
		duty1ms();
	}
	if(timeCnt2ms == 2000)
	{
		timeCnt2ms = 0;
		duty2ms();
	}
	if(timeCnt5ms == 5000)
	{
		timeCnt5ms = 0;
		duty5ms();
	}
	if(timeCnt10ms == 10000)
	{
		timeCnt10ms = 0;
		duty10ms();
	}
	
//	if(timeCnt20ms ==20000)
//	{
//		timeCnt20ms = 0;
//		duty20ms();
//	}
}

void sys_time_init()
{
	
	while(SysTick_Config(SystemCoreClock/1000000));  // 1us

}

void delay_ms(u16 ms)
{
	for(u16 i = 0;i<ms;i++)
		delay_us(1000);
}

void delay_us(u16 us)
{
	u32 temp = sysTickCnt;
	while((GetSysTime_us()-temp)<us);
}
