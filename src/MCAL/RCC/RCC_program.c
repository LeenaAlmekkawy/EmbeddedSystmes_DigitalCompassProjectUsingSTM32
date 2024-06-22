/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: RCC                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "RCC_private.h"
#include "RCC_interface.h"
#include "RCC_config.h"




void MRCC_voidSystemClkInit(void)
{


#if RCC_CLK_SECURITY_SYSTEM==ENABLE
    SET_BIT(RCC->CR, RCC_CSSON);

# elif RCC_CLK_SECURITY_SYSTEM==DISABLE
    CLR_BIT(RCC->CR, RCC_CSSON);

#endif

#if RCC_HSE_CLK_BYBASS==NO
    CLR_BIT(RCC->CR, RCC_HSEBYP);

# elif RCC_HSE_CLK_BYBASS==YES
    SET_BIT(RCC->CR, RCC_HSEBYP);

#endif

#if RCC_CLK_SOURCE==HSE

    SET_BIT(RCC->CR, RCC_HSEON);
    SET_BIT(RCC->CFGR, RCC_SW0);
    CLR_BIT(RCC->CFGR, RCC_SW1);
    MRCC_voidSetBusesPrescaler(AHB_PRESCALER, APB1_PRESCALER, APB2_PRESCALER);

#elif RCC_CLK_SOURCE==HSI
    SET_BIT(RCC->CR, RCC_HSION);
    CLR_BIT(RCC->CFGR, RCC_SW0);
    CLR_BIT(RCC->CFGR, RCC_SW1);

    MRCC_voidSetBusesPrescaler(AHB_PRESCALER, APB1_PRESCALER, APB2_PRESCALER);

#elif RCC_CLK_SOURCE==PLL

    u8 PLLSRC=1;
    #if RCC_PLL_CLK_SRC==HSI
    SET_BIT(RCC->CR, RCC_HSION);
    CLR_BIT(RCC->PLLCFGR, RCC_PLLSRC);
    PLLSRC=HSI_FRE ;// HSI Fre

    #elif RCC_PLL_CLK_SRC==HSE
    SET_BIT(RCC->CR, RCC_HSEON);
    SET_BIT(RCC->PLLCFGR, RCC_PLLSRC);
    SET_BIT(RCC->CR, RCC_HSEON);
     PLLSRC=HSE_FRE; //HSE fre

    #endif

    u16 Local_PLL_CLK_OUTPUT=(PLLSRC*RCC_PLLN)/(RCC_PLLM*((RCC_PLLP+1)*2) );

  if(Local_PLL_CLK_OUTPUT<=SYS_MAX_FRE)
   {


	   RCC->PLLCFGR&=(~(PLLP_MASK));
	   RCC->PLLCFGR&=(~(PLLM_MASK));
	   RCC->PLLCFGR&=(~(PLLN_MASK));
	   RCC->PLLCFGR&=(~(PLLQ_MASK));
	   RCC->PLLCFGR|=(RCC_PLLP<<16);
	   RCC->PLLCFGR|=(RCC_PLLN<<6);
	   RCC->PLLCFGR|=(RCC_PLLQ<<24);
	   RCC->PLLCFGR|=(RCC_PLLM);
	   SET_BIT(RCC->CR, RCC_PLLON);
	   CLR_BIT(RCC->CFGR, RCC_SW0);
	   SET_BIT(RCC->CFGR, RCC_SW1);
   }
   else
   {

   }








#endif


}

void MRCC_voidEnablePerClk(u8 Copy_u8Bus, u8 Copy_u8Per)
{
    //RangeCheck
    if(Copy_u8Per<PerRange)
    {
        switch(Copy_u8Bus)
        {
        case  RCC_AHB1 :
            SET_BIT(RCC->AHB1ENR, Copy_u8Per);
            break;
        case  RCC_AHB2 :
            SET_BIT(RCC->AHB2ENR, Copy_u8Per);
            break;
        case  RCC_APB1 :
            SET_BIT(RCC->APB1ENR, Copy_u8Per);
            break;
        case  RCC_APB2 :
            SET_BIT(RCC->APB2ENR, Copy_u8Per);
            break;

        }
    }
    else
    {
        //out of range
    }
}

void MRCC_voidDisablePerClk(u8 Copy_u8Bus, u8 Copy_u8Per)
{
    //RangeCheck
    if(Copy_u8Per<PerRange)
    {
        switch(Copy_u8Bus)
        {
        case  RCC_AHB1 :
            CLR_BIT(RCC->AHB1ENR, Copy_u8Per);
            break;
        case  RCC_AHB2 :
            CLR_BIT(RCC->AHB2ENR, Copy_u8Per);
            break;
        case  RCC_APB1 :
            CLR_BIT(RCC->APB1ENR, Copy_u8Per);
            break;
        case  RCC_APB2 :
            CLR_BIT(RCC->APB2ENR, Copy_u8Per);
            break;

        }
    }
    else
    {
        //out of range
    }
}

void MRCC_voidSetBusesPrescaler(u8 Copy_u8AHBPrescaler,u8 Copy_u8APB1Prescaler,u8 Copy_u8APB2Prescaler)
{   //AHB Prescaler
	RCC->CFGR &=(~(AHB_PRESCALER_MASK<<4));
	RCC->CFGR |=((Copy_u8AHBPrescaler)<<4);

	//APB1 Prescaler
	RCC->CFGR &=(~(APB1_PRESCALER_MASK<<10));
	RCC->CFGR |=((Copy_u8APB1Prescaler)<<10);

	//APB2 Prescaler
	RCC->CFGR &=(~(APB2_PRESCALER_MASK<<13));
	RCC->CFGR |=((Copy_u8APB2Prescaler)<<13);


}

