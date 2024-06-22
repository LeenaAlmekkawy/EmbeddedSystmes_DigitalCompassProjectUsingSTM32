/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: HAL               *********/
/*********  SWC: TFT                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/SPI/SPI_interface.h"
#include "../../MCAL/STK/STK_interface.h"



#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

#include <math.h>
#include <stdlib.h>
static u16 Global_u16CurrentXPosStart;
static u16 Global_u16CurrentXPosEnd;

static u16 Global_u16CurrentYPosStart;
static u16 Global_u16CurrentYPosEnd;



void HTFT_voidWriteCmd(u16 Copy_u16Cmd)
{
	GPIO_voidSetPinValue(TFT_A0_PORT,TFT_A0_PIN,LOW);
	(void)MSPI1_u16Transceive(Copy_u16Cmd);

}

void HTFT_voidWriteData(u16 Copy_u16Data)
{
	GPIO_voidSetPinValue(TFT_A0_PORT,TFT_A0_PIN,HIGH);
	(void)MSPI1_u16Transceive(Copy_u16Data);
}

void HTFT_voidResetSequence(void)
{
	GPIO_voidSetPinValue(TFT_RST_PORT,TFT_RST_PIN,HIGH);

	MSTK_voidSetBusyWait(200);
	GPIO_voidSetPinValue(TFT_RST_PORT,TFT_RST_PIN,LOW);

	MSTK_voidSetBusyWait(4);
	GPIO_voidSetPinValue(TFT_RST_PORT,TFT_RST_PIN,HIGH);

	MSTK_voidSetBusyWait(200);
	GPIO_voidSetPinValue(TFT_RST_PORT,TFT_RST_PIN,LOW);

	MSTK_voidSetBusyWait(200);
	GPIO_voidSetPinValue(TFT_RST_PORT,TFT_RST_PIN,HIGH);

	MSTK_voidSetBusyWait(240000);

}

void HTFT_voidInit(void)
{   //1- SET Pin directions
	PIN_st TFT={OUTPUT,PP,VHS,NPP};
	GPIO_voidSetPinDirection ( TFT_A0_PORT,TFT_A0_PIN,&TFT);

	GPIO_voidSetPinDirection ( TFT_RST_PORT,TFT_RST_PIN,&TFT);

	MSPI1_voidInit();

	//2- reset sequence
	HTFT_voidResetSequence();

	//3- send sleep out command (0x11)
	HTFT_voidWriteCmd(0x11);

	//4- wait 15ms
	//MSTK_voidSetTime_ms_2MHZ(30000);
	MSTK_voidSetBusyWait(30000);

	//5- send color mode command ->RGB565 (0x3A)& argument (0x05)
	HTFT_voidWriteCmd(0x3A);
	HTFT_voidWriteData(0X05);

	//6- Display on command(0x29)
	HTFT_voidWriteCmd(0x29);


}

void HTFT_voidShowImage(u16 Copy_pu16Img[],u32 Copy_u32ImgSize)
{
	//1- set x position
	HTFT_voidWriteCmd(0x2A);
	//X start=0 , x end=127
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(127);


	//2- set Y position
	HTFT_voidWriteCmd(0x2B);
	//y start=0 , y end=159
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(159);

	//3- send image data
	HTFT_voidWriteCmd(0x2C);

	u32 Local_counter;
	for(Local_counter=0;Local_counter< Copy_u32ImgSize;Local_counter++)
	{
		HTFT_voidWriteData( (Copy_pu16Img[Local_counter]>>8) ); //MSB byte
		HTFT_voidWriteData( (Copy_pu16Img[Local_counter] & 0x00FF) );  //LSB Byte
	}



}

void HTFT_voidSetXPos(u16 Copy_u16xStart, u16 Copy_u16xEnd)
{
	Global_u16CurrentXPosStart=Copy_u16xStart;
	Global_u16CurrentXPosEnd=Copy_u16xEnd;

	HTFT_voidWriteCmd(0x2A);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u16xStart);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u16xEnd);



}

void HTFT_voidSetYPos(u16 Copy_u16yStart, u16 Copy_u16yEnd)
{
	Global_u16CurrentYPosStart=Copy_u16yStart;
	Global_u16CurrentYPosEnd=Copy_u16yEnd;

	HTFT_voidWriteCmd(0x2B);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u16yStart);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(Copy_u16yEnd);
}

void HTFT_voidFillRectangle(Color_t Copy_u16Color)
{
	Copy_u16Color.color=~Copy_u16Color.color;
	HTFT_voidWriteCmd(0x2C);

	u32 Local_u32NumOfPixels=(Global_u16CurrentYPosEnd - Global_u16CurrentYPosStart)*(Global_u16CurrentXPosEnd - Global_u16CurrentXPosStart);

	u32 Local_counter;
	for(Local_counter=0;Local_counter< Local_u32NumOfPixels;Local_counter++)
	{
		HTFT_voidWriteData( Copy_u16Color.color>>8); //MSB byte
		HTFT_voidWriteData( Copy_u16Color.color & 0x00FF );  //LSB Byte

	}

}

void HTFT_voidFillBackGround(Color_t Copy_u16Color)
{
	HTFT_voidWriteCmd(0x2A);
	//X start=0 , x end=127
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(127);


	//2- set Y position
	HTFT_voidWriteCmd(0x2B);
	//y start=0 , y end=159
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(0);
	HTFT_voidWriteData(159);
	Global_u16CurrentYPosStart=0;
	Global_u16CurrentYPosEnd=159;
	Global_u16CurrentXPosStart=0;
	Global_u16CurrentXPosEnd=127;


	HTFT_voidFillRectangle(Copy_u16Color);

}

void HTFT_voidDrawPixel(u16 Copy_u16x, u16 Copy_u16y ,Color_t Copy_u16Color)
{
	HTFT_voidSetXPos(Copy_u16x,Copy_u16x+3);
	HTFT_voidSetYPos(Copy_u16y,Copy_u16y+3);
	HTFT_voidFillRectangle( Copy_u16Color);


}

void HTFT_voidDrawCircle(u16 Copy_u16centerX, u16 Copy_u16centerY, u16 radius, Color_t Copy_u16Color) {
	u16 x = radius - 1;
	u16 y = 0;
	u16 dx = 1;
	u16 dy = 1;
	s16 err = dx - (radius << 1);

	while (x >= y) {
		HTFT_voidDrawPixel(Copy_u16centerX + x, Copy_u16centerY + y, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u16centerX - x, Copy_u16centerY + y, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u16centerX - x, Copy_u16centerY - y, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u16centerX + x, Copy_u16centerY - y, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u16centerX + y, Copy_u16centerY + x, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u16centerX - y, Copy_u16centerY + x, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u16centerX - y, Copy_u16centerY - x, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u16centerX + y, Copy_u16centerY - x, Copy_u16Color);

		if (err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0) {
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}
	}
}

void HTFT_voidDrawLine(s16 Copy_u16x1, s16 Copy_u16y1, s16 Copy_u16x2, s16 Copy_u16y2 ,Color_t Copy_u16Color)
{
	s16 dx = abs(  Copy_u16x2- Copy_u16x1);
	s16 dy = abs(  Copy_u16y2 - Copy_u16y1);
	s16 sx = (Copy_u16x1 <   Copy_u16x2) ? 1 : -1;
	s16 sy = (Copy_u16y1 <   Copy_u16y2) ? 1 : -1;
	s16 err = dx - dy;

	while (1) {
		HTFT_voidDrawPixel(Copy_u16x1, Copy_u16y1, Copy_u16Color);

		if (Copy_u16x1 ==   Copy_u16x2 &&   Copy_u16y1 ==   Copy_u16y2) {
			break;
		}

		s16 e2 = err * 2;

		if (e2 > -dy) {
			err -= dy;
			Copy_u16x1 += sx;
		}

		if (e2 < dx) {
			err += dx;
			Copy_u16y1 += sy;
		}
	}
}

void HTFT_voidDigitalCompass(u16 Copy_u16Angle)
{


	f32 Local_f32AngleinRad=((Copy_u16Angle*M_PI)/180.0);


	u16 Local_u16Xnew=TFT_Xcenter+ (TFT_CompassRedius-5)*sin(Local_f32AngleinRad);

	u16 Local_u16Ynew=TFT_Ycenter+ (TFT_CompassRedius-5)*cos(Local_f32AngleinRad);

	Color_t white;
	white.pixel.Blu=0b11111;
	white.pixel.Grn=0b111111;
	white.pixel.Red=0b11111;

	HTFT_voidDrawLine(TFT_Xcenter, TFT_Ycenter, Local_u16Xnew,Local_u16Ynew  ,white);





}


void HTFT_voidClearDigitalCompass(u16 Copy_u16Angle)
{


	f32 Local_f32AngleinRad=((Copy_u16Angle*M_PI)/180.0);


	u16 Local_u16Xnew=TFT_Xcenter+ (TFT_CompassRedius-5)*sin(Local_f32AngleinRad);

	u16 Local_u16Ynew=TFT_Ycenter+ (TFT_CompassRedius-5)*cos(Local_f32AngleinRad);

	Color_t black;
	black.pixel.Blu=0;
	black.pixel.Grn=0;
	black.pixel.Red=0;

	HTFT_voidDrawLine(TFT_Xcenter, TFT_Ycenter, Local_u16Xnew,Local_u16Ynew  ,black);





}

void HTFT_voidDrawDigitalCompass(void)
{

	Color_t red;
	red.pixel.Blu=0;
	red.pixel.Grn=0;
	red.pixel.Red=0b11111;


	Color_t black;
	black.pixel.Blu=0;
	black.pixel.Grn=0;
	black.pixel.Red=0;

	HTFT_voidFillBackGround(black);
	HTFT_voidDrawCircle(TFT_Xcenter ,TFT_Ycenter ,  TFT_CompassRedius , red);
}
