/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: SPI                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../GPIO/GPIO_interface.h"


#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"



void MSPI1_voidInit(void)
{
	//1-SPI mode:  CPHA and CPOL
	CLR_BIT(SPI1->CR1,SPI_CHPA);
	CLR_BIT(SPI1->CR1,SPI_CPOL);

	//2-select Master/Slave mode
	SET_BIT(SPI1->CR1,SPI_MSTR);

	//3-Select baud rate prescaler


	SPI1->CR1=  (  (SPI1->CR1&~(0b111<<3)  )|(SPI1_BAUD_RATE<<3)  );


	//4-MSB/LSB first
	CLR_BIT(SPI1->CR1,SPI_LSBFIRST);

	//6- select software slave management
	SET_BIT(SPI1->CR1,SPI_SSM);
	SET_BIT(SPI1->CR1,SPI_SSI);

	//7-Data format
	CLR_BIT(SPI1->CR1,SPI_DFF);


	//set pins direction
	PIN_st SPI_PinAF= {AF,PP,HS,NPP};
	GPIO_voidSetPinDirection (MOSI1_PORT ,MOSI1_PIN, &SPI_PinAF);
	GPIO_voidSetPinDirection (SCK1_PORT ,SCK1_PIN, &SPI_PinAF);
	GPIO_voidSetPinDirection (MISO1_PORT ,MISO1_PIN, &SPI_PinAF);
	GPIO_voidSetAlternativeFunction(MOSI1_PORT ,MOSI1_PIN, GPIO_AF_5);
	GPIO_voidSetAlternativeFunction(SCK1_PORT ,SCK1_PIN, GPIO_AF_5);
	GPIO_voidSetAlternativeFunction(MISO1_PORT ,MISO1_PIN,  GPIO_AF_5);

	//8-Enable SPI


	SET_BIT(SPI1->CR1,SPI_SPE);



}

u16 MSPI1_u16Transceive(u16 Copy_u16Data)
{
	SPI1->DR =Copy_u16Data;

	while(GET_BIT(SPI1->SR,SPI_BSY)==1){
		asm("NOP");
	}

	return SPI1->DR;

}


