/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: RCC                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#define RCC_AHB1             0
#define RCC_AHB2             1
#define RCC_APB1             2
#define RCC_APB2             3
#define PerRange             32

#define HSI                  0
#define HSE                  1
#define PLL                  2

#define DISABLE              0
#define ENABLE               1

#define NO                   0
#define YES                  1

#define RCC_EN_GPIOA         0  //AHB1
#define RCC_EN_GPIOB         1
#define RCC_EN_GPIOC         2

//APB2
#define RCC_EN_SYSCFG        14
#define RCC_EN_SPI1          12
#define RCC_EN_USART1        4
#define RCC_EN_TIM1          0
#define RCC_EN_TIM9          16

//APB1
#define RCC_EN_TIM2          0
#define RCC_EN_TIM3          1
#define RCC_EN_TIM4          2
#define RCC_EN_TIM5          3
#define RCC_EN_I2C1          21
#define RCC_EN_I2C2          22
#define RCC_EN_I2C3          23



#define RCC_PLLSRC           22

#define HSI_FRE              16
#define HSE_FRE              25
#define SYS_MAX_FRE          84



 void MRCC_voidSystemClkInit(void);

 void MRCC_voidEnablePerClk(u8 Copy_u8Bus, u8 Copy_u8Per);

 void MRCC_voidDisablePerClk(u8 Copy_u8Bus, u8 Copy_u8Per);

 void MRCC_voidSetBusesPrescaler(u8 Copy_u8AHBPrescaler,u8 Copy_u8APB1Prescaler,u8 Copy_u8APB2Prescaler);



#endif
