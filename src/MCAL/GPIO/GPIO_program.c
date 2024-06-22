/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: GPIO                *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"



void GPIO_voidSetPinDirection (u8 Copy_u8PortName, u8 Copy_u8PinNumber, PIN_st*  Copy_psPinInfo)
{
    switch (Copy_u8PortName)
    {
    case GPIO_PORTA:
        switch( Copy_psPinInfo->PIN_MOD)
        {
        case INPUT:
            CLR_BIT(GPIOA->MODER,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOA->MODER,(Copy_u8PinNumber*2+1));
            break;
        case OUTPUT:
            SET_BIT(GPIOA->MODER,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOA->MODER,(Copy_u8PinNumber*2+1));
            break;
        case AF:
            CLR_BIT(GPIOA->MODER,(Copy_u8PinNumber*2));
            SET_BIT(GPIOA->MODER,(Copy_u8PinNumber*2+1));
            break;
        case ANALOG:
            SET_BIT(GPIOA->MODER,(Copy_u8PinNumber*2));
            SET_BIT(GPIOA->MODER,(Copy_u8PinNumber*2+1));
            break;
        }
        switch( Copy_psPinInfo->PIN_OT)
        {
        case PP:
            CLR_BIT(GPIOA->OTYPER,(Copy_u8PinNumber));
            break;
        case  OD:
            SET_BIT(GPIOA->OTYPER,(Copy_u8PinNumber));
            break;
        }
        switch( Copy_psPinInfo->PIN_SPD)
        {
        case LS:
            CLR_BIT(GPIOA->OSPEEDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOA->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case MS:
            SET_BIT(GPIOA->OSPEEDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOA->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case HS:
            CLR_BIT(GPIOA->OSPEEDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOA->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case VHS:
            SET_BIT(GPIOA->OSPEEDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOA->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        }
        switch( Copy_psPinInfo->PIN_PUPD)
        {
        case NPP:
            CLR_BIT(GPIOA->PUPDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOA->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        case PU:
            SET_BIT(GPIOA->PUPDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOA->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        case PD:
            CLR_BIT(GPIOA->PUPDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOA->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        }
        break;

    case  GPIO_PORTB:
        switch( Copy_psPinInfo->PIN_MOD)
        {
        case INPUT:
            CLR_BIT(GPIOB->MODER,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOB->MODER,(Copy_u8PinNumber*2+1));
            break;
        case OUTPUT:
            SET_BIT(GPIOB->MODER,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOB->MODER,(Copy_u8PinNumber*2+1));
            break;
        case AF:
            CLR_BIT(GPIOB->MODER,(Copy_u8PinNumber*2));
            SET_BIT(GPIOB->MODER,(Copy_u8PinNumber*2+1));
            break;
        case ANALOG:
            SET_BIT(GPIOB->MODER,(Copy_u8PinNumber*2));
            SET_BIT(GPIOB->MODER,(Copy_u8PinNumber*2+1));
            break;
        }
        switch( Copy_psPinInfo->PIN_OT)
        {
        case PP:
            CLR_BIT(GPIOB->OTYPER,(Copy_u8PinNumber));
            break;
        case  OD:
            SET_BIT(GPIOB->OTYPER,(Copy_u8PinNumber));
            break;
        }
        switch( Copy_psPinInfo->PIN_SPD)
        {
        case LS:
            CLR_BIT(GPIOB->OSPEEDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOB->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case MS:
            SET_BIT(GPIOB->OSPEEDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOB->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case HS:
            CLR_BIT(GPIOB->OSPEEDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOB->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case VHS:
            SET_BIT(GPIOB->OSPEEDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOB->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        }
        switch( Copy_psPinInfo->PIN_PUPD)
        {
        case NPP:
            CLR_BIT(GPIOB->PUPDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOB->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        case PU:
            SET_BIT(GPIOB->PUPDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOB->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        case PD:
            CLR_BIT(GPIOB->PUPDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOB->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        }

        break;

    case  GPIO_PORTC:
        switch( Copy_psPinInfo->PIN_MOD)
        {
        case INPUT:
            CLR_BIT(GPIOC->MODER,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOC->MODER,(Copy_u8PinNumber*2+1));
            break;
        case OUTPUT:
            SET_BIT(GPIOC->MODER,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOC->MODER,(Copy_u8PinNumber*2+1));
            break;
        case AF:
            CLR_BIT(GPIOC->MODER,(Copy_u8PinNumber*2));
            SET_BIT(GPIOC->MODER,(Copy_u8PinNumber*2+1));
            break;
        case ANALOG:
            SET_BIT(GPIOC->MODER,(Copy_u8PinNumber*2));
            SET_BIT(GPIOC->MODER,(Copy_u8PinNumber*2+1));
            break;
        }
        switch( Copy_psPinInfo->PIN_OT)
        {
        case PP:
            CLR_BIT(GPIOC->OTYPER,(Copy_u8PinNumber));
            break;
        case  OD:
            SET_BIT(GPIOC->OTYPER,(Copy_u8PinNumber));
            break;
        }
        switch( Copy_psPinInfo->PIN_SPD)
        {
        case LS:
            CLR_BIT(GPIOC->OSPEEDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOC->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case MS:
            SET_BIT(GPIOC->OSPEEDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOC->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case HS:
            CLR_BIT(GPIOC->OSPEEDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOC->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        case VHS:
            SET_BIT(GPIOC->OSPEEDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOC->OSPEEDR,(Copy_u8PinNumber*2+1));
            break;
        }
        switch( Copy_psPinInfo->PIN_PUPD)
        {
        case NPP:
            CLR_BIT(GPIOC->PUPDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOC->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        case PU:
            SET_BIT(GPIOC->PUPDR,(Copy_u8PinNumber*2));
            CLR_BIT(GPIOC->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        case PD:
            CLR_BIT(GPIOC->PUPDR,(Copy_u8PinNumber*2));
            SET_BIT(GPIOC->PUPDR,(Copy_u8PinNumber*2+1));
            break;
        }

        break;
    }
}

void GPIO_voidSetAlternativeFunction(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8AltFun)
{

//	GPIOB->AFRH=68;

	if(Copy_u8PinNumber<8)
	{
	      switch(Copy_u8PortName)
	       {
	        case  GPIO_PORTA:
	             GPIOA->AFRL &= ~(0b1111<<(Copy_u8PinNumber*4));
	             GPIOA->AFRL |= (Copy_u8AltFun<<(Copy_u8PinNumber*4));
	            break;

	        case  GPIO_PORTB:
	             GPIOB->AFRL &= ~(0b1111<<(Copy_u8PinNumber*4));
	             GPIOB->AFRL |= (Copy_u8AltFun<<(Copy_u8PinNumber*4));

	            break;

	        case  GPIO_PORTC:
	             GPIOC->AFRL &= ~(0b1111<<(Copy_u8PinNumber*4));
	             GPIOC->AFRL |= (Copy_u8AltFun<<(Copy_u8PinNumber*4));

	            break;
	       }
	}
	else if(Copy_u8PinNumber>=8&& Copy_u8PinNumber<16)
	{
	      switch(Copy_u8PortName)
	       {
	        case  GPIO_PORTA:
	             GPIOA->AFRH &= ~(0b1111<<( (Copy_u8PinNumber-8) *4) );
	             GPIOA->AFRH |= (Copy_u8AltFun<<(  (Copy_u8PinNumber-8)*4));
	            break;

	        case  GPIO_PORTB:
	             GPIOB->AFRH &= ~(0b1111<<( (Copy_u8PinNumber-8)*4));
	             GPIOB->AFRH |= (Copy_u8AltFun<<( (Copy_u8PinNumber-8)*4));

	            break;

	        case  GPIO_PORTC:
	             GPIOC->AFRH &= ~(0b1111<<( (Copy_u8PinNumber-8)*4));
	             GPIOC->AFRH |= (Copy_u8AltFun<<( (Copy_u8PinNumber-8)*4));

	            break;
	       }
	}

	//asm("NOP");
}

void GPIO_voidSetPinValue     (u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinValue)
{
    if(Copy_u8PortName< PORT_RANGE && Copy_u8PinNumber<PIN_RANGE)
    {
        if(  (Copy_u8PortName== GPIO_PORTA &&(Copy_u8PinNumber==PIN13||Copy_u8PinNumber==PIN14) ) ||
                (Copy_u8PortName== GPIO_PORTB &&(Copy_u8PinNumber==PIN3||Copy_u8PinNumber==PIN4) )  )
        {
            //error
        }
        else
        {
            switch(Copy_u8PortName)
            {
            case  GPIO_PORTA:
                switch(Copy_u8PinValue)
                {
                case HIGH:
                    SET_BIT(GPIOA->ODR,Copy_u8PinNumber);

                    break;

                case LOW:
                    CLR_BIT(GPIOA->ODR,Copy_u8PinNumber);

                    break;
                }
                break;

            case  GPIO_PORTB:
                switch(Copy_u8PinValue)
                {
                case HIGH:
                    SET_BIT(GPIOB->ODR,Copy_u8PinNumber);

                    break;

                case LOW:
                    CLR_BIT(GPIOB->ODR,Copy_u8PinNumber);

                    break;
                }
                break;

            case  GPIO_PORTC:
                switch(Copy_u8PinValue)
                {
                case HIGH:
                    SET_BIT(GPIOC->ODR,Copy_u8PinNumber);

                    break;

                case LOW:
                    CLR_BIT(GPIOC->ODR,Copy_u8PinNumber);

                    break;
                }
                break;
            }
        }
    }
    else
    {
        //error
    }
}
u8   GPIO_u8GetPinValue       (u8 Copy_u8PortName, u8 Copy_u8PinNumber)
{
    u8 Local_Variable=0x55;
    if(Copy_u8PortName< PORT_RANGE && Copy_u8PinNumber<PIN_RANGE)
    {
        if(  (Copy_u8PortName== GPIO_PORTA &&(Copy_u8PinNumber==PIN13||Copy_u8PinNumber==PIN14) ) ||
                (Copy_u8PortName== GPIO_PORTA &&(Copy_u8PinNumber==PIN13||Copy_u8PinNumber==PIN14) )  )
        {
            //error
        }
        else
        {
            switch(Copy_u8PortName)
            {
            case  GPIO_PORTA:
                Local_Variable=GET_BIT(GPIOA->IDR,Copy_u8PinNumber);
                break;

            case  GPIO_PORTB:
                Local_Variable=GET_BIT(GPIOB->IDR,Copy_u8PinNumber);
                break;

            case  GPIO_PORTC:
                Local_Variable=GET_BIT(GPIOC->IDR,Copy_u8PinNumber);
                break;
            }
        }
    }
    else
    {
        //error
    }
    return Local_Variable;

}

u32   GPIO_u32GetPortValue      (u8 Copy_u8PortName)
{
    u32 Local_u32PortValue=0;
    if(Copy_u8PortName< PORT_RANGE )
    {

        switch(Copy_u8PortName)
        {
        case  GPIO_PORTA:
            Local_u32PortValue=GPIOA->IDR;
            break;

        case  GPIO_PORTB:
            Local_u32PortValue=GPIOB->IDR;
            break;

        case  GPIO_PORTC:
            Local_u32PortValue=GPIOC->IDR;
            break;
        }

    }
    else
    {
        //error
    }
    return Local_u32PortValue;
}

