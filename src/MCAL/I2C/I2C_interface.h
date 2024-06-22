/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  Module: I2C              *********/
/*********  Target: STM32F401CCU6    *********/
/*********  File: I2C_interface.h    *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H



#define I2C1 ((I2Cx_MemMap_t*)(0x40005400))
#define I2C2 ((I2Cx_MemMap_t*)(0x40005800))
#define I2C3 ((I2Cx_MemMap_t*)(0x40005C00))


typedef struct
{
	volatile    u32 CR1;
	volatile 	u32 CR2;
	volatile 	u32 OAR1;
	volatile 	u32 OAR2;
	volatile 	u32 DR;
	volatile 	u32 SR1;
	volatile 	u32 SR2;
	volatile 	u32 CCR;
	volatile 	u32 TRISE;
	volatile 	u32 FLTR;

}I2Cx_MemMap_t;

#define I2C_8M               8


void MI2C_voidMasterInit(I2Cx_MemMap_t *I2Cx);

void MI2C_SendStartCondition(I2Cx_MemMap_t *I2Cx);

void MI2C_SendStopCondition(I2Cx_MemMap_t *I2Cx);

void MI2C_SendRepeatedStart(I2Cx_MemMap_t *I2Cx);

void MI2C_SendSlaveAddressWithWrite(I2Cx_MemMap_t *I2Cx, u8 Copy_u8SlaveAddress);

void MI2C_SendSlaveAddressWithRead(I2Cx_MemMap_t *I2Cx, u8 Copy_u8SlaveAddress);

void MI2C_MasterWriteDataByte(I2Cx_MemMap_t *I2Cx, u8 Copy_u8DataByte);

u8 MI2C_MasterReadDataByte(I2Cx_MemMap_t *I2Cx);

#endif
