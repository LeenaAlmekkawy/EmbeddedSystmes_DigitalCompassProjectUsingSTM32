/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: RCC                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#define RCC_BASE_ADD   (u32)(0x40023800)

typedef struct
{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Reserved1;
	u32 Reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Reserved3;
	u32 Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Reserved5;
	u32 Reserved6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Reserved7;
	u32 Reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Reserved9;
	u32 Reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Reserved11;
	u32 Reserved12;
	u32 BDCR;
	u32 CSR;
	u32 Reserved13;
	u32 Reserved14;
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 Reserved15;
	u32 DCKCFGR;

}RCC_MemMap_t;

#define RCC ((volatile RCC_MemMap_t*)(RCC_BASE_ADD ))


#define RCC_HSEBYP                18
#define RCC_HSEON                 16
#define RCC_HSION                 0
#define RCC_LSEBYP                2
#define RCC_CSSON                 19
#define RCC_PLLON                 24
#define RCC_SW0                   0
#define RCC_SW1                   1
#define RCC_PLLSRC                22
#define PLLP_MASK                 0x30000
#define PLLN_MASK                 0x7FC0
#define PLLM_MASK                 0x1F
#define PLLQ_MASK                 0xF000000

#define AHB_PRESCALER_MASK        0b1111
#define APB1_PRESCALER_MASK       0b111
#define APB2_PRESCALER_MASK       0b111

#endif
