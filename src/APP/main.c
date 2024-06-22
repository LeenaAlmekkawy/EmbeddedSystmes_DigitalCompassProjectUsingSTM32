/*****************************************************************
 *****************************************************************
 ** Project :- Digital Compass                                  **
 ** Author  :- Leena Almekkawy                                  **
 ** Date    :- 12/6/2024                                        **
 ** Version :-  (1)                                             **
 *****************************************************************
 ****************************************************************/


/*****************  Linking section  ***************************/
/**-----------------------------------------------------------**/

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_interface.h"
#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/STK/STK_interface.h"
#include "../MCAL/I2C/I2C_interface.h"

#include "../HAL/GY271/GY271_interface.h"
#include "../HAL/TFT/TFT_interface.h"

#include <math.h>

/**-----------------------------------------------------------**/
/***************** End of Linking section  *********************/




/***************  Functions declaration section  ****************/
/**------------------------------------------------------------**/

void APP_voidInit(void);

s16 APP_s16CorrectCompassValue(s16 Copy_s16Val);

/************  End of Functions declaration section  ************/
/**------------------------------------------------------------**/





/*********************  Definition section   ********************/
/**------------------------------------------------------------**/

#define APP_NORTH_VAL          90
#define APP_CHANGE_RATE        4

/****************  End of Definition section  *******************/
/**------------------------------------------------------------**/





/*****************  Main program section  **********************/
/**-----------------------------------------------------------**/

s16 Local_s16Reference;
void main(void)
{
	//Initialize APP MCAL and HAL important modules
	APP_voidInit();

	//Get the first read of the compass and display it
	Local_s16Reference=GY271_s16GetHeadingReading();
	s16 Local_s16CompassRef=  APP_s16CorrectCompassValue(Local_s16Reference);
	HTFT_voidDigitalCompass(Local_s16CompassRef);



	while(1)
	{
		//Get the current sensor read
		volatile s16 val =GY271_s16GetHeadingReading();

		//if the difference between current sensor read and the last read greater than a specific value then update the compass with the new value
		if(abs(Local_s16Reference-val)>=APP_CHANGE_RATE )
		{
            //update the compass with the new value
			s16 Local_s16CompassNewVal= APP_s16CorrectCompassValue(val);
			HTFT_voidClearDigitalCompass(Local_s16CompassRef);
			HTFT_voidDigitalCompass(Local_s16CompassNewVal);
			Local_s16Reference=val;
			Local_s16CompassRef=Local_s16CompassNewVal;
		}



	}



}

/***************** End of Main program section  **********************/
/**-----------------------------------------------------------------**/





/***************  Functions definition section  ****************/
/**-----------------------------------------------------------**/
void APP_voidInit(void)
{

	//Initialize system clock (HSI)
	MRCC_voidSystemClkInit();



	//Enable GPIOA, GPOIB clock
	MRCC_voidEnablePerClk(RCC_AHB1, RCC_EN_GPIOA);
	MRCC_voidEnablePerClk(RCC_AHB1, RCC_EN_GPIOB);

	//enable I2C clock
	MRCC_voidEnablePerClk(RCC_APB1, RCC_EN_I2C1);

	//Enable SPI clock
	MRCC_voidEnablePerClk(RCC_APB2, RCC_EN_SPI1);


	//Enable SYSCFG
	MRCC_voidEnablePerClk(RCC_APB2,RCC_EN_SYSCFG);


	//set pins direction for I2C
	PIN_st I2C_PinAF= {AF,OD,VHS,PU};
	GPIO_voidSetPinDirection (GPIO_PORTB,PIN8, &I2C_PinAF);
	GPIO_voidSetPinDirection (GPIO_PORTB,PIN9, &I2C_PinAF);

	GPIO_voidSetAlternativeFunction(GPIO_PORTB,PIN8, GPIO_AF_4);
	GPIO_voidSetAlternativeFunction(GPIO_PORTB,PIN9,  GPIO_AF_4);

	//Initialize stm32 as master
	MI2C_voidMasterInit(I2C1);

	//Initialize GY271 Magnetometer sensor
	GY271_voidInit();

	//Initialize TFT
	HTFT_voidInit();


	//Draw Digital Compass back ground
	HTFT_voidDrawDigitalCompass();


}

s16 APP_s16CorrectCompassValue(s16 Copy_s16Val)
{


	s16 Local_s16Increase=0;
	if(Copy_s16Val>APP_NORTH_VAL)
	{
		Local_s16Increase=Copy_s16Val-APP_NORTH_VAL;
	}
	else
	{
		Local_s16Increase=(360-APP_NORTH_VAL)+Copy_s16Val;
	}

	s16 Local_s16NewPos=APP_NORTH_VAL-Local_s16Increase;
	if(Local_s16NewPos<0)
	{
		Local_s16NewPos=360+Local_s16NewPos;
	}

	return Local_s16NewPos;

}

/************  End of Functions definition section  ************/
/**-----------------------------------------------------------**/
