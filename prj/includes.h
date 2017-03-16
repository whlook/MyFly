#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include "stm32f4xx.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_flash.h"
#include "misc.h"

#include "i2c_driver.h"
#include "mpu9250_driver.h"
#include "pwm_driver.h"
#include "sdio_sd_driver.h"
#include "time_driver.h"
#include "usart_driver.h"
#include "sys_time.h"

#include "init.h"
#include "my_filter.h"
#include "my_imu.h"
#include "my_math.h"
#include "my_protocol.h"
#include "sd_data.h"
#include "offset.h"
#include "pid.h"
#include "control.h"
#include "to_pc.h"
#include  "duty.h"
#include "flash.h"




#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
	
#define LED_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_9)


#endif 