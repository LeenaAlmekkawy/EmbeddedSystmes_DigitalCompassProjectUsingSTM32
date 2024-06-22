/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: USART                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H


/*#define USART1_BASE_ADD   (u32)(0x40011000)
#define USART2_BASE_ADD   (u32)(0x40014400)
#define USART6_BASE_ADD   (u32)(0x40011400)
*/




#define USART1 ((USARTx_MemMap_t*)(0x40011000))
#define USART2 ((USARTx_MemMap_t*)(0x40004400))
#define USART6 ((USARTx_MemMap_t*)(0x40011400 ))




typedef struct
{
	volatile    u32 SR;
	volatile 	u32 DR;
	volatile 	u32 BRR;
	volatile 	u32 CR1;
	volatile 	u32 CR2;
	volatile 	u32 CR3;
	volatile 	u32 GTPR;

}USARTx_MemMap_t;

typedef struct
{
	u32 BaudRate;
	u8 DataWidth;
	u8 StopBits;
	u8 Parity_Enable;
	u8 Parity_Selection;
	u8 TransferDirection;//enable tx or rx or both
	u8 HardwareonControl;
	u8 OverSampling;
}USART_InitType;


typedef struct
{
	u8 ClockOutput;
	u8 ClockPolarity;
	u8 ClockPhase;
	u8 LastBitClockPulse;

}USART_ClockInitType;


#define OVER_SAMPLING_8           1
#define OVER_SAMPLING_16          0

#define TX_ONLY                   0
#define RX_ONLY                   1
#define TX_RX                     2

#define EVEN_PARITY               0
#define ODD_PARITY                1

#define MODE_8BIT			      0
#define MODE_9BIT			      1

#define STOP_BIT_1			      0
#define STOP_BIT_0_5		      1
#define STOP_BIT_2			      2
#define STOP_BIT_1_5		      3

#define ENABLE				      1
#define DISABLE				      0


void MUSART_voidInit(USART_InitType *Copy_pstInitStruct,USART_ClockInitType *Copy_pstClockInitStruct,USARTx_MemMap_t *USARTx);

void MUSART_voidEnable(USARTx_MemMap_t *USARTx);

void MUSART_voidDisable(USARTx_MemMap_t *USARTx);

void MUSART_voidTransmitByte(USARTx_MemMap_t *USARTx,u8 Copy_u8Byte);

void MUSART_voidTransmitString(USARTx_MemMap_t *USARTx,const u8* Copy_pcString);

u8 MUSART_u8ReceiveByteNonBlocking(USARTx_MemMap_t *USARTx);

u8 *MUSART_ptrReceiveStringSyncNonBlocking(USARTx_MemMap_t *USARTx);

void MUSART1_voidSetCallBack(void (*Copy_pvNotificationFunction)(void));

void MUSART2_voidSetCallBack(void (*Copy_pvNotificationFunction)(void));

void MUSART6_voidSetCallBack(void (*Copy_pvNotificationFunction)(void));

void USART_voidTransmitString(const char* Copy_pcString);

void USART_voidSendNumber(s32 Copy_s32Number);

#endif
