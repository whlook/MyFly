#pragma ONCE

#include "stm32f4xx.h"


// 倒数第一个页，到结束共128K字节的容量
#define START_ADDR 0x080E0000

//void flash_init();

u8 flash_write(u16 *write_data,u8 lenth);

void flash_read(u16 *read_data,u8 lenth);