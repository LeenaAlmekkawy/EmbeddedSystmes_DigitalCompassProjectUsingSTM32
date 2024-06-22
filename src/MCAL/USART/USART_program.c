/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: USART                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../GPIO/GPIO_interface.h"



#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

#include <math.h>

void (*Global_pvUSART1NotificationFunction)(void)=NULL_ptr;
void (*Global_pvUSART2NotificationFunction)(void)=NULL_ptr;
void (*Global_pvUSART6NotificationFunction)(void)=NULL_ptr;





void MUSART_voidInit(USART_InitType *Copy_pstInitStruct,USART_ClockInitType *Copy_pstClockInitStruct,USARTx_MemMap_t *USARTx)
{

	switch(Copy_pstInitStruct->OverSampling)
	{

	case OVER_SAMPLING_8:
	{
		USARTx->BRR=UART_BRR_SAMPLING8(USART1_CLK,Copy_pstInitStruct->BaudRate);
		break;
	}
	case OVER_SAMPLING_16:
	{
		USARTx->BRR=UART_BRR_SAMPLING16(USART1_CLK,Copy_pstInitStruct->BaudRate);
		break;
	}

	}
	USARTx->CR1= (Copy_pstInitStruct->OverSampling << MUSART_CR1_OVER8_BIT)     |
			     (Copy_pstInitStruct->HardwareonControl<<MUSART_CR1_UE_BIT)     |
			     (Copy_pstInitStruct->DataWidth <<MUSART_CR1_M_BIT)             |
			     (Copy_pstInitStruct->Parity_Enable <<MUSART_CR1_PCE_BIT)       |
			     (Copy_pstInitStruct->Parity_Selection <<MUSART_CR1_PS_BIT)     ;


    switch(Copy_pstInitStruct->TransferDirection)
    {
    case TX_ONLY:
	{
    	SET_BIT(USARTx->CR1,MUSART_CR1_TE_BIT);
    	break;
	}
    case RX_ONLY:
	{
    	SET_BIT(USARTx->CR1,MUSART_CR1_RE_BIT);
    	break;
	}
    case TX_RX:
	{
		SET_BIT(USARTx->CR1,MUSART_CR1_TE_BIT);
    	SET_BIT(USARTx->CR1,MUSART_CR1_RE_BIT);
    	break;
	}
    }

	USARTx->CR2 =   (Copy_pstInitStruct->StopBits<<MUSART_CR2_STOP_BIT)			    	|
					(Copy_pstClockInitStruct->ClockOutput <<MUSART_CR2_CLKEN_BIT)       |
					(Copy_pstClockInitStruct->ClockPhase <<MUSART_CR2_CPHA_BIT)         |
					(Copy_pstClockInitStruct->ClockPolarity <<MUSART_CR2_CPOL_BIT)      |
					(Copy_pstClockInitStruct->LastBitClockPulse <<MUSART_CR2_LBCL_BIT)  ;


//******try it first/
	USARTx->SR=0;
	//Enable USART
	//SET_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);



}

void MUSART_voidEnable(USARTx_MemMap_t *USARTx)
{
	SET_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);

}

void MUSART_voidDisable(USARTx_MemMap_t *USARTx)
{
	CLR_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);

}

void MUSART_voidTransmitByte(USARTx_MemMap_t *USARTx,u8 Copy_u8Byte)
{//Wait until the transmit buffer in empty

 while(GET_BIT(USARTx->SR,MUSART_SR_TXE_BIT)==0);
  //send data
  USARTx->DR=Copy_u8Byte;
  //wait until transmission complete
  while(GET_BIT(USARTx->SR,MUSART_SR_TC_BIT)==0);
  //clear the flag by writing 0 to it

  CLR_BIT(USARTx->SR,MUSART_SR_TC_BIT);

}

void MUSART_voidTransmitString(USARTx_MemMap_t *USARTx,const u8* Copy_pcString)
{
	  u8 Local_u8Counter=0;
	  while(Copy_pcString[Local_u8Counter]!='\0')
	  {
		  MUSART_voidTransmitByte(USARTx, Copy_pcString[Local_u8Counter]);
		  Local_u8Counter++;
	  }
}

u8 MUSART_u8ReceiveByteNonBlocking(USARTx_MemMap_t *USARTx)
{
	u8 Local_u8Data=0;
	u32 Local_u32TimeOut=0;
	while((GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)==0) /*&& (Local_u32TimeOut<THRESHOLD_VALUE)*/ )
	{
		//Local_u32TimeOut++;
	}
	if(Local_u32TimeOut==THRESHOLD_VALUE)
	{  //value that remark timeout occurrence
		Local_u8Data=255;
	}
	else
	{
		Local_u8Data=USARTx->DR;
	}
	return Local_u8Data;
}

void MUSART1_voidSetCallBack(void (*Copy_pvNotificationFunction)(void))
{
	Global_pvUSART1NotificationFunction=Copy_pvNotificationFunction;
}

void MUSART2_voidSetCallBack(void (*Copy_pvNotificationFunction)(void))
{
	Global_pvUSART2NotificationFunction=Copy_pvNotificationFunction;
}

void MUSART6_voidSetCallBack(void (*Copy_pvNotificationFunction)(void))
{
	Global_pvUSART6NotificationFunction=Copy_pvNotificationFunction;
}

void USART1_IQRHandler(void)
{
	 if(Global_pvUSART1NotificationFunction!=NULL_ptr)
	    {
		 Global_pvUSART1NotificationFunction();
	    }
}

void USART2_IQRHandler(void)
{
	 if(Global_pvUSART2NotificationFunction!=NULL_ptr)
	    {
		 Global_pvUSART2NotificationFunction();
	    }
}

void USART3_IQRHandler(void)
{
	 if(Global_pvUSART6NotificationFunction!=NULL_ptr)
	    {
		 Global_pvUSART6NotificationFunction();
	    }

}

void USART_voidTransmitString(const char* Copy_pcString)
{
  u8 Local_u8Counter=0;
  while(Copy_pcString[Local_u8Counter]!='\0')
  {

	  MUSART_voidTransmitByte(USART1,Copy_pcString[Local_u8Counter]);
	  Local_u8Counter++;
  }

}

void USART_voidSendNumber(s32 Copy_s32Number)
{
   u8 Local_u8Str[10];
   itoa(Copy_s32Number, Local_u8Str,10);
   USART_voidTransmitString(Local_u8Str);

}




