/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: SPI                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#define SPI1_BASE_ADD   (u32)(0x40013000)

typedef struct
{
	volatile    u16 CR1;
	volatile 	u16 Reserved1;
	volatile 	u16 CR2;
	volatile 	u16 Reserved2;
	volatile 	u16 SR;
	volatile 	u16 Reserved3;
	volatile 	u16 DR;
	volatile 	u16 Reserved4;
	volatile 	u16 CRCPR;
	volatile 	u16 Reserved5;
	volatile 	u16 RXCRCR;
	volatile 	u16 Reserved6;
	volatile 	u16 TXCRCR;
	volatile 	u16 Reserved7;
	volatile 	u16 I2SCFGR;
	volatile 	u16 Reserved8;
	volatile 	u16 I2SPR;

}SPI1_MemMap_t;

#define SPI1 ((volatile SPI1_MemMap_t*)(SPI1_BASE_ADD ))

#define  SPI_CHPA                   0
#define  SPI_CPOL                   1
#define  SPI_MSTR                   2
#define  SPI_SPE                    6
#define  SPI_LSBFIRST               7
#define  SPI_SSI                    8
#define  SPI_SSM                    9
#define  SPI_DFF                    11

#define  SPI_BSY                    7

#define SPI1_MASK                  0XFFFFFFC7

#define MOSI1_PORT                  GPIO_PORTA
#define MOSI1_PIN                   PIN7

#define MISO1_PORT                  GPIO_PORTA
#define MISO1_PIN                   PIN6

#define SCK1_PORT                   GPIO_PORTA
#define SCK1_PIN                    PIN5

#endif
