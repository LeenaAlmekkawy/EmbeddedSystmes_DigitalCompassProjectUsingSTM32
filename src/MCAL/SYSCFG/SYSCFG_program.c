/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: SYSCFG              *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "SYSCFG_private.h"
#include "SYSCFG_interface.h"
#include "SYSCFG_config.h"

void MSYSCFG_voidSetExtiPort(u8 Copy_u8LineNum,u8 Copy_u8PortNum)
{
	u8 Local_u8Index=Copy_u8LineNum/4;
	u8 Local_u8ShiftAmount=((Copy_u8LineNum%4)*4);
    SYSCFG->EXTICR[Local_u8Index]&= ~( (0b1111)<<  ( Local_u8ShiftAmount ) );
    SYSCFG->EXTICR[Local_u8Index]|= ( (Copy_u8PortNum)<<  ( Local_u8ShiftAmount) );
}


