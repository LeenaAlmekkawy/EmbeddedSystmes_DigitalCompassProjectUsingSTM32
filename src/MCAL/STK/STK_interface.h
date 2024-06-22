/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: STK                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

#define STK_AHB_DIV_BY_8     0
#define STK_AHB              1

#define ENABLE               1
#define DISABLE              0

void MSTK_voidInit(void);

void MSTK_voidStopTimer(void);

void MSTK_voidStartTimer(void);

void MSTK_voidSetBusyWait(u32 Copy_u32Ticks);

void MSTK_voidSetIntervalSingle(u32 Copy_u32Ticks, void(*CallbackFunction)(void));

void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void(*CallbackFunction)(void));

u32 MSTK_u32GetElapsedTime(void);

u32 MSTK_u32GetRemainingTime(void);

void MSTK_voidSetTime_ms_2MHZ(u32 Copy_u32Time);

void MSTK_voidSetTime_us_2MHZ(u32 Copy_u32Time);

#endif
