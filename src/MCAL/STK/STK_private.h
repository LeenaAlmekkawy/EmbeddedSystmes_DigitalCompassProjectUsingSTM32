/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: STK                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

#define STK_BASE_ADD   (u32)(0xE000E010)

typedef struct 
{
	volatile u32 CTRL ;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;

}MSTK_MemMap_t;

#define STK   ((volatile MSTK_MemMap_t*)(STK_BASE_ADD))

#define CLKSOURCE              2
#define TICKINT                1
#define STK_ENABLE             0
#define COUNTFLAG              16
#define NULL                  (void *)0

#endif
