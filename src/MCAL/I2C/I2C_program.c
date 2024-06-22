/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  Module: I2C              *********/
/*********  Target: STM32F401CCU6    *********/
/*********  File: I2C_program.c      *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"


void MI2C_voidMasterInit(I2Cx_MemMap_t *I2Cx)
{

	//reset i2c
	SET_BIT(I2Cx->CR1,MI2C_CR1_SWRST_BIT );
	CLR_BIT(I2Cx->CR1,MI2C_CR1_SWRST_BIT );


	//Set peripheral input clock to 8M
	I2Cx->CR2 |=10;

	//SM mode in enable by default

	//For instance: in Sm mode, to generate a 100 kHz SCL frequency:
	//If FREQR = 08, TPCLK1 = 125 ns so CCR must be programmed with 0x28
	//(0x28 <=> 40d x 125 ns = 5000 ns.)
	I2Cx->CCR=(50);

	//For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
	//  If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
	//therefore the TRISE[5:0] bits must be programmed with 09h.
	//(1000 ns / 125 ns = 8 + 1)
	//TRISE[5:0] must be configured only when the I2C is disabled (PE = 0).
	I2Cx->TRISE=11;

	//Enable peripheral
	SET_BIT(I2Cx->CR1,MI2C_CR1_PE_BIT);

}

void MI2C_SendStartCondition(I2Cx_MemMap_t *I2Cx)
{

	//Enable Ack
	SET_BIT(I2Cx->CR1,MI2C_CR1_ACK_BIT);

	//Generate start
	SET_BIT(I2Cx->CR1,MI2C_CR1_START_BIT);


	//Wait for SB bit to be set
	while(GET_BIT(I2Cx->SR1,MI2C_SR1_SB_BIT)==0)
	{
		asm("NOP");
	}


}

void MI2C_SendRepeatedStart(I2Cx_MemMap_t *I2Cx)
{
	SET_BIT(I2Cx->CR1,MI2C_CR1_START_BIT);

	while(GET_BIT(I2Cx->SR1,MI2C_SR1_SB_BIT)==0);

	(void)I2Cx->SR1;  //Dummy read
}

void MI2C_SendStopCondition(I2Cx_MemMap_t *I2Cx)
{
	SET_BIT(I2Cx->CR1,MI2C_CR1_STOP_BIT);

	while(GET_BIT(I2Cx->SR2,MI2C_SR2_BUSY_BIT)==0);
}

void MI2C_SendSlaveAddressWithWrite(I2Cx_MemMap_t *I2Cx, u8 Copy_u8SlaveAddress)
{

	/**** STEPS FOLLOWED  ************
	1. Send the Slave Address to the DR Register
	2. Wait for the ADDR (bit 1 in SR1) to set. This indicates the end of address transmission
	3. clear the ADDR by reading the SR1 and SR2
	 */

	I2Cx->DR=( Copy_u8SlaveAddress<<1 ); //7 bit slave address with write request

	//Wait for ADDR bit to set
	while(GET_BIT(I2Cx->SR1,MI2C_SR1_ADDR_BIT )==0)
	{
		asm("NOP");
	}

	//read SR1 and SR2 to clear the ADDR bit
	volatile u32 Local_u32Temp= (I2Cx->SR2|I2Cx->SR1);   //Dummy read


}

void MI2C_SendSlaveAddressWithRead(I2Cx_MemMap_t *I2Cx, u8 Copy_u8SlaveAddress)
{
	I2Cx->DR=( (Copy_u8SlaveAddress<<1)|1); //7 bit slave address with read


	//Wait for ADDR bit to set
	while(GET_BIT(I2Cx->SR1,MI2C_SR1_ADDR_BIT )==0)
	{
		asm("NOP");
	}

	//read SR1 and SR2 to clear the ADDR bit
	volatile u32 Local_u32Temp= (I2Cx->SR2|I2Cx->SR1);   //Dummy read


}

void MI2C_MasterWriteDataByte(I2Cx_MemMap_t *I2Cx, u8 Copy_u8DataByte)
{

	/**** STEPS FOLLOWED  ************
	1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
	2. Send the DATA to the DR Register
	3. Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
	 */

	while(GET_BIT(I2Cx->SR1,MI2C_SR1_TxE_BIT )==0) // wait for TXE bit to set
	{
		asm("NOP");
	}

	I2Cx->DR=Copy_u8DataByte;

	while(GET_BIT(I2Cx->SR1,MI2C_SR1_BTF_BIT )==0)//Data byte transfer flag
	{
		asm("NOP");
	}
}

void MI2C_MasterRead(I2Cx_MemMap_t *I2Cx,u8  Copy_u8SlaveAddress , u8 *buffer, u8 Copy_u8size)
{

	/**** STEPS FOLLOWED  ************
1. If only 1 BYTE needs to be Read
	a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
	b) the Acknowledge disable is made during EV6 (before ADDR flag is cleared) and the STOP condition generation is made after EV6
	c) Wait for the RXNE (Receive Buffer not Empty) bit to set
	d) Read the data from the DR

2. If Multiple BYTES needs to be read
  a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
	b) Clear the ADDR bit by reading the SR1 and SR2 Registers
	c) Wait for the RXNE (Receive buffer not empty) bit to set
	d) Read the data from the DR
	e) Generate the Acknowlegment by settint the ACK (bit 10 in SR1)
	f) To generate the nonacknowledge pulse after the last received data byte, the ACK bit must be cleared just after reading the
		 second last data byte (after second last RxNE event)
	g) In order to generate the Stop/Restart condition, software must set the STOP/START bit
	   after reading the second last data byte (after the second last RxNE event)
	 */

	u8 Local_u8Remaining = Copy_u8size;

	/**** STEP 1 ****/
	if (Copy_u8size == 1)
	{
		/**** STEP 1-a ****/
		I2Cx->DR=( (Copy_u8SlaveAddress<<1)|1) ;  //  send the address with read request

		//Wait for ADDR bit to set
		while(GET_BIT(I2Cx->SR1,MI2C_SR1_ADDR_BIT )==0)
		{
			asm("NOP");
		}


		/**** STEP 1-b ****/
		// clear the ACK bit
		CLR_BIT(I2Cx->CR1, MI2C_CR1_ACK_BIT);

		//read SR1 and SR2 to clear the ADDR bit
		volatile u32 Local_u32Temp= (I2Cx->SR2|I2Cx->SR1);   //Dummy read

		//Stop I2C
		MI2C_SendStopCondition(I2Cx);

		/**** STEP 1-c ****/

		// wait for RxNE to set
		while(GET_BIT(I2Cx->SR1,MI2C_SR1_RxNE_BIT )==0)
		{
			asm("NOP");
		}

		/**** STEP 1-d ****/
		buffer[Copy_u8size-Local_u8Remaining] = (u8)I2Cx->DR;  // Read the data from the DATA REGISTER

	}

	/**** STEP 2 ****/
	else
	{
		/**** STEP 2-a ****/
		I2Cx->DR=( (Copy_u8SlaveAddress<<1)|1) ;  //  send the address with read request

		//Wait for ADDR bit to set
		while(GET_BIT(I2Cx->SR1,MI2C_SR1_ADDR_BIT )==0)
		{
			asm("NOP");
		}


		/**** STEP 2-b ****/
		//read SR1 and SR2 to clear the ADDR bit
		volatile u32 Local_u32Temp= (I2Cx->SR2|I2Cx->SR1);   //Dummy read

		while (Local_u8Remaining>2)
		{
			/**** STEP 2-c ****/
			// wait for RxNE to set
			while(GET_BIT(I2Cx->SR1,MI2C_SR1_RxNE_BIT )==0)
			{
				asm("NOP");
			}

			/**** STEP 2-d ****/
			buffer[Copy_u8size-Local_u8Remaining] = (u8)I2Cx->DR;   // copy the data into the buffer

			/**** STEP 2-e ****/
			// Set the ACK bit to Acknowledge the data received
			SET_BIT(I2Cx->CR1, MI2C_CR1_ACK_BIT);

			Local_u8Remaining--;
		}

		// Read the SECOND LAST BYTE

		// wait for RxNE to set
		while(GET_BIT(I2Cx->SR1,MI2C_SR1_RxNE_BIT )==0)
		{
			asm("NOP");
		}

		buffer[Copy_u8size-Local_u8Remaining] = (u8)I2Cx->DR;

		/**** STEP 2-f ****/
	   // clear the ACK bit
		CLR_BIT(I2Cx->CR1, MI2C_CR1_ACK_BIT);

		/**** STEP 2-g ****/
		// Stop I2C
		MI2C_SendStopCondition(I2Cx);

		Local_u8Remaining--;

		// Read the Last BYTE
		// wait for RxNE to set
		while(GET_BIT(I2Cx->SR1,MI2C_SR1_RxNE_BIT )==0)
		{
			asm("NOP");
		}
		buffer[Copy_u8size-Local_u8Remaining] =  (u8)I2Cx->DR;  // copy the data into the buffer
	}

}

