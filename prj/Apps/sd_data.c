#include "sd_data.h"
#include "offset.h"
#include "pid.h"
#include "sdio_sd_driver.h"
#include "my_protocol.h"

/* Externs */

extern pid_data_t PID_data;
extern data_from_slave_t      data_from_slave; // 保存来自从机的数据

//////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\////////////////////\\\\\\\\\\//////////

SD_Error err = SD_OK;

u8 data[512];

unsigned char read_PID()
{
	if(SD_ReadBlock(data,0x0000,512) == SD_OK)
	{
		PID_data.inner_rol_p = (float)(data[0])/10.0f;
		PID_data.inner_rol_i = (float)(data[1])/10.0f;
		PID_data.inner_rol_d = (float)(data[2])/10.0f;
		
		PID_data.outer_rol_p = (float)(data[3])/10.0f;
		PID_data.outer_rol_i = (float)(data[4])/10.0f;
		PID_data.outer_rol_d = (float)(data[5])/10.0f;
		
	}
		if(SD_ReadBlock(data,0x0200,512) == SD_OK)
	{
		PID_data.inner_pitch_p = (float)(data[0])/10.0f;
		PID_data.inner_pitch_i = (float)(data[1])/10.0f;
		PID_data.inner_pitch_d = (float)(data[2])/10.0f;
		
		PID_data.outer_pitch_p = (float)(data[3])/10.0f;
		PID_data.outer_pitch_i = (float)(data[4])/10.0f;
		PID_data.outer_pitch_d = (float)(data[5])/10.0f;
		
	}
		if(SD_ReadBlock(data,0x0400,512) == SD_OK)
	{
		PID_data.inner_yaw_p = (float)(data[0])/10.0f;
		PID_data.inner_yaw_i = (float)(data[1])/10.0f;
		PID_data.inner_yaw_d = (float)(data[2])/10.0f;
		
		PID_data.outer_yaw_p = (float)(data[3])/10.0f;
		PID_data.outer_yaw_i = (float)(data[4])/10.0f;
		PID_data.outer_yaw_d = (float)(data[5])/10.0f;
		
		return 1;
		
	}
	return 0;
}
//  pid.rol  0x0000
//  pid.pit  0x0200
//  pid.yaw  0x0400
//
unsigned char save_PID()
{
	u8 i = 0;
	data[i++] = data_from_slave.data.order[1];  //inner
	data[i++] = data_from_slave.data.order[2];  
	data[i++] = data_from_slave.data.order[3];  
	
	data[i++] = data_from_slave.data.order[4];  // outer
	data[i++] = data_from_slave.data.order[5];
	data[i++] = data_from_slave.data.order[6];
	
	if(data_from_slave.data.order[0] == WRITE_PID_ROL)
	{
		err = SD_WriteBlock(data,0x0000,512);
		if(err == SD_OK)
		{
			PID_data.inner_rol_p = ((float)data_from_slave.data.order[1])/10.0f;
			PID_data.inner_rol_i = ((float)data_from_slave.data.order[2])/10.0f;
			PID_data.inner_rol_d = ((float)data_from_slave.data.order[3])/10.0f;
			
			PID_data.outer_rol_p = ((float)data_from_slave.data.order[4])/10.0f;
			PID_data.outer_rol_i = ((float)data_from_slave.data.order[5])/10.0f;
			PID_data.outer_rol_d = ((float)data_from_slave.data.order[6])/10.0f;			
			return 1;
		}
		else
			return 0;
	}
		if(data_from_slave.data.order[0] == WRITE_PID_PIT)
	{
				err = SD_WriteBlock(data,0x0200,512);
		if(err == SD_OK)
		{
			PID_data.inner_pitch_p = ((float)data_from_slave.data.order[1])/10.0f;
			PID_data.inner_pitch_i = ((float)data_from_slave.data.order[2])/10.0f;
			PID_data.inner_pitch_d = ((float)data_from_slave.data.order[3])/10.0f;
			
			PID_data.outer_pitch_p = ((float)data_from_slave.data.order[4])/10.0f;
			PID_data.outer_pitch_i = ((float)data_from_slave.data.order[5])/10.0f;
			PID_data.outer_pitch_d = ((float)data_from_slave.data.order[6])/10.0f;			
			return 1;
		}
		else
			return 0;
	}
		if(data_from_slave.data.order[0] == WRITE_PID_YAW)
	{
				err = SD_WriteBlock(data,0x0400,512);
		if(err == SD_OK)
		{
			PID_data.inner_yaw_p = ((float)data_from_slave.data.order[1])/10.0f;
			PID_data.inner_yaw_i = ((float)data_from_slave.data.order[2])/10.0f;
			PID_data.inner_yaw_d = ((float)data_from_slave.data.order[3])/10.0f;
			
			PID_data.outer_yaw_p = ((float)data_from_slave.data.order[4])/10.0f;
			PID_data.outer_yaw_i = ((float)data_from_slave.data.order[5])/10.0f;
			PID_data.outer_yaw_d = ((float)data_from_slave.data.order[6])/10.0f;			
			return 1;
		}
		else
			return 0;
	}
	
	
	return 0;
}


// 0x0600

unsigned char read_offsetData()
{
	return 1;
}
unsigned char save_offsetData()
{
	return 1;
}
