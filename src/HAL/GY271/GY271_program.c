/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: HAL               *********/
/*********  SWC: GY271               *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/I2C/I2C_interface.h"

#include "GY271_interface.h"
#include "GY271_private.h"
#include "GY271_config.h"

#include <math.h>


s16 filter(s16 prev,s16 new)
{
	return 0.85*prev+0.15*new;
}

void GY271_voidInit(void)
{
	MI2C_SendStartCondition(I2C1);
	MI2C_SendSlaveAddressWithWrite(I2C1, 0x1E);
	MI2C_MasterWriteDataByte(I2C1,GY271_CONFIGA); // Write to config register A
	MI2C_MasterWriteDataByte(I2C1,0b00111000);      // 8 samples & normal mode &15 Hz
	MI2C_SendStopCondition(I2C1);

	MI2C_SendStartCondition(I2C1);
	MI2C_SendSlaveAddressWithWrite(I2C1, 0x1E);
	MI2C_MasterWriteDataByte(I2C1,GY271_CONFIGB); // Write to config register B
	MI2C_MasterWriteDataByte(I2C1,0b01000000);  // Set gain to 1.9
	MI2C_SendStopCondition(I2C1);


	MI2C_SendStartCondition(I2C1);
	MI2C_SendSlaveAddressWithWrite(I2C1, 0x1E);
	MI2C_MasterWriteDataByte(I2C1,GY271_MODE); // Write to mode register
	MI2C_MasterWriteDataByte(I2C1,0);  // Set GY271  to continuous measurement mode
	MI2C_SendStopCondition(I2C1);


}

s16 GY271_s16GetHeadingReading(void)
{


	u8 Local_ReadArr[8]={0};

	MI2C_SendStartCondition(I2C1);
	MI2C_SendSlaveAddressWithWrite(I2C1, 0x1E);//slave address with write
	MI2C_MasterWriteDataByte(I2C1,0x03);
	MI2C_SendStartCondition(I2C1);
	MI2C_MasterRead(I2C1,0x1E , Local_ReadArr, 6);


	s16 Local_s16accel_x=( (Local_ReadArr[0]<<8)|Local_ReadArr[1] );
	s16 Local_s16accel_z=( (Local_ReadArr[2]<<8)|Local_ReadArr[3] );
	s16 Local_s16accel_y=( (Local_ReadArr[4]<<8)|Local_ReadArr[5] );

	f32 x=  (f32)Local_s16accel_x  *  GY271_GAIN;
	f32 y=   (f32)Local_s16accel_y  *  GY271_GAIN;


	x = x * GY271_xs + GY271_xb;
	y = y * GY271_ys + GY271_yb;


	volatile 	 f32 Local_f32HeadingInRad = atan2((float)x,(float) y);
	Local_f32HeadingInRad +=( 4.75*M_PI/180.0);


	if (Local_f32HeadingInRad < 0.0)
		Local_f32HeadingInRad += 2 *  M_PI;


	else if( Local_f32HeadingInRad > 2 *  M_PI)
		Local_f32HeadingInRad-= 2 *  M_PI;


	volatile   f32 Local_f32HeadingInDegree = Local_f32HeadingInRad * 180 /  M_PI;
	return (s16)Local_f32HeadingInDegree;


}

