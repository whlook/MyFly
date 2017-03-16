#pragma ONCE

typedef struct offset_data
{
  float gyro_offset_x;
	float gyro_offset_y;
	float gyro_offset_z;
	
	float acc_offset_x;
	float acc_offset_y;
	float acc_offset_z;
}offset_data_t;

void offset();

void read_offset(); // acc xyz  gyro xyz

extern offset_data_t offset_data;

