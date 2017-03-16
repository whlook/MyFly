#pragma ONCE
#include "stm32f4xx.h"

void sysTime();

void sys_time_init();

void delay_ms(u16 ms);

void delay_us(u16 us);

uint32_t GetSysTime_us(void) ;


extern volatile u32 sysTickCnt;