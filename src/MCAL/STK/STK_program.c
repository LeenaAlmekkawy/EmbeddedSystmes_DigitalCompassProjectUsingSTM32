/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: STK                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "STK_config.h"
#include "STK_interface.h"
#include "STK_private.h"

static void (*GS_STK_CallBack)(void);
static u8 Glbal_u8SingleFlag=0;

void MSTK_voidInit(void)
{
	//Clock source
#if STK_CLK_SOURCE == STK_AHB
	SET_BIT(STK->CTRL,CLKSOURCE);

#elif STK_CLK_SOURCE == STK_AHB_DIV_BY_8
	CLR_BIT(STK->CTRL,CLKSOURCE);

#endif

	//interrupt enable or disable

#if STK_INTERRUPT_EN == ENABLE
	SET_BIT(STK->CTRL,TICKINT);

#elif  STK_INTERRUPT_EN == DISABLE
	CLR_BIT(STK->CTRL,TICKINT);

#endif

}


void MSTK_voidStopTimer(void)
{
	CLR_BIT(STK->CTRL,TICKINT);
}

void MSTK_voidStartTimer(void)
{
	SET_BIT(STK->CTRL,TICKINT);
}

void MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{
	//reset timer value and clear count  flag
	STK->VAL=0;

	//load timer with value
	STK->LOAD=Copy_u32Ticks;

	//start the timer
	SET_BIT(STK->CTRL,STK_ENABLE);

	//wait for timer flag to be raised
	while(GET_BIT(STK->CTRL, COUNTFLAG)!= 1){}


	//stop the timer
	CLR_BIT(STK->CTRL,STK_ENABLE);


}

void MSTK_voidSetIntervalSingle(u32 Copy_u32Ticks, void(*CallbackFunction)(void))
{   // Set call back
	GS_STK_CallBack=CallbackFunction;
	Glbal_u8SingleFlag=1;

	//reset timer value and clear flag
	STK->VAL=0;

	//load timer with value
	STK->LOAD=Copy_u32Ticks;

	//start the timer
	SET_BIT(STK->CTRL,STK_ENABLE);

}

void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void(*CallbackFunction)(void))
{     // Set call back
	GS_STK_CallBack=CallbackFunction;
	Glbal_u8SingleFlag=0;

	//reset timer value and clear flag
	STK->VAL=0;

	//load timer with value
	STK->LOAD=Copy_u32Ticks;

	//start the timer
	SET_BIT(STK->CTRL,STK_ENABLE);

}

u32 MSTK_u32GetElapsedTime(void)
{
	return ((STK->LOAD)-(STK->VAL));
}

u32 MSTK_u32GetRemainingTime(void)
{
	return STK->VAL;
}

void  SysTick_Handler(void)
{
	if(GS_STK_CallBack!=NULL)
	{
		GS_STK_CallBack();
	}
	if(Glbal_u8SingleFlag==1)
	{
		Glbal_u8SingleFlag=0;
		//stop the timer
		CLR_BIT(STK->CTRL,STK_ENABLE);
	}


}

void MSTK_voidSetTime_ms_2MHZ(u32 Copy_u32Time)
{  for(u32 Local_u32Counter=0 ;Local_u32Counter<Copy_u32Time;Local_u32Counter++)
   {
	u32 Local_u32Ticks=2000;
	//reset timer value and clear count  flag
	STK->VAL=0;

	//load timer with value
	STK->LOAD=Local_u32Ticks;

	//start the timer
	SET_BIT(STK->CTRL,STK_ENABLE);

	//wait for timer flag to be raised
	while(GET_BIT(STK->CTRL, COUNTFLAG)!= 1){}


	//stop the timer
	CLR_BIT(STK->CTRL,STK_ENABLE);

    }


}

void MSTK_voidSetTime_us_2MHZ(u32 Copy_u32Time)
{  for(u32 Local_u32Counter=0 ;Local_u32Counter<Copy_u32Time;Local_u32Counter++)
   {
	u32 Local_u32Ticks=2;
	//u32 Local_u32Ticks=16;
	//reset timer value and clear count  flag
	STK->VAL=0;

	//load timer with value
	STK->LOAD=Local_u32Ticks;

	//start the timer
	SET_BIT(STK->CTRL,STK_ENABLE);

	//wait for timer flag to be raised
	while(GET_BIT(STK->CTRL, COUNTFLAG)!= 1){}


	//stop the timer
	CLR_BIT(STK->CTRL,STK_ENABLE);

    }


}



