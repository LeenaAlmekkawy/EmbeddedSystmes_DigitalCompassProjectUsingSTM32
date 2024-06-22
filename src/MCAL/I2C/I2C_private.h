/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  Module: I2C              *********/
/*********  Target: STM32F401CCU6    *********/
/*********  File: I2C_private.h      *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

/**********************************************/
/* 				CR1 BITS Mapping 			  */
/**********************************************/

//PE
#define MI2C_CR1_PE_BIT	        0

//START
#define MI2C_CR1_START_BIT	    8

//STOP
#define MI2C_CR1_STOP_BIT     	9
#define MI2C_CR1_ACK_BIT	    10


#define MI2C_CR1_SWRST_BIT      15


/**********************************************/
/* 				SR1 BITS Mapping 			  */
/**********************************************/

//SB
#define MI2C_SR1_SB_BIT	        0
#define MI2C_SR1_ADDR_BIT       1
#define MI2C_SR1_BTF_BIT        2
#define MI2C_SR1_RxNE_BIT       6
#define MI2C_SR1_TxE_BIT        7


/**********************************************/
/* 				SR2 BITS Mapping 			  */
/**********************************************/

//SB
#define MI2C_SR2_BUSY_BIT	    1

#endif
