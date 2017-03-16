#include "delay.h"
#include "sys.h"

 

static u32 sysTickCnt = 0;


void delay_init(u8 SYSCLK)
{

while(SysTick_Config(SystemCoreClock/1000000)!=0);

}								    



void delay_us(u32 nus)
{		

}

void delay_xms(u16 nms)
{	 		  	  
  	    
} 

void delay_ms(u16 nms)
{	 	 

	
} 

