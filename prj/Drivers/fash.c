#include "stm32f4xx_flash.h"
#include "stm32f4xx_rcc.h"
#include "flash.h"

//void flash_init();

u8 flash_write(u16 *write_data,u8 lenth)
{
	u16 cnt = 0;
	// 开启HSI，默认开启的，以防万一
	RCC_HSICmd(ENABLE);
	
	// 解锁
	FLASH_Unlock();
	
	// 清除flag
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR);
	
	// 擦除该页
	while(FLASH_EraseSector(11,VoltageRange_3)!=FLASH_COMPLETE);
	
	
	// 写入数据
	do
	{
		FLASH_ProgramHalfWord((START_ADDR + cnt*2),write_data[cnt]);
		
		cnt++;
		
	}while(cnt != lenth);
	
	// 锁定
	FLASH_Lock();
	
// 进行读取校验
	
	u32 addr = START_ADDR;
	
	cnt = 0;
	
	u8 read_err_cnt = 0;
	
	u16 buf;
	
	while(cnt<lenth)
	{
		buf = *(u16 *)addr;  // 把地址转换成指针，然后取指针指向的内容
		if(buf!=write_data[cnt])
			read_err_cnt++;
		addr = addr+2;
		cnt++;
	}
	
	return read_err_cnt;
	
	
	
	
	
}

void flash_read(u16 *read_data,u8 lenth)
{
	u16 cnt = 0;
	
	u32 addr = START_ADDR;
	do
	{
		read_data[cnt] = *(u16 *)addr;
		addr+=2;
		cnt++;
	}while(cnt!=lenth);
}