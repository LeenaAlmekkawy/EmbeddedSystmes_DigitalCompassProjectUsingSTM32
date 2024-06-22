/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: HAL               *********/
/*********  SWC: TFT                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

typedef struct
{
	u16 Blu:5;
	u16 Grn:6;
	u16 Red:5;

}Pixel_Color;

typedef union
{
	Pixel_Color pixel;
	u16 color;
}Color_t;
void HTFT_voidInit(void);

void HTFT_voidShowImage(u16 Copy_pu16Img[],u32 Copy_u32ImgSize);

void HTFT_voidSetXPos(u16 Copy_u16xStart, u16 Copy_u16xEnd);

void HTFT_voidSetYPos(u16 Copy_u16yStart, u16 Copy_u16yEnd);

void HTFT_voidFillRectangle(Color_t Copy_u16Color);

void HTFT_voidFillBackGround(Color_t Copy_u16Color);

void HTFT_voidDrawPixel(u16 Copy_u16x, u16 Copy_u16y ,Color_t Copy_u16Color);

void HTFT_voidDrawCircle(u16 Copy_u16centerX, u16 Copy_u16centerY, u16 radius, Color_t Copy_u16Color);

void HTFT_voidDrawLine(s16 Copy_u16x1, s16 Copy_u16y1, s16 Copy_u16x2, s16 Copy_u16y2 ,Color_t Copy_u16Color);

void HTFT_voidDigitalCompass(u16 Copy_u16Angle);

void HTFT_voidClearDigitalCompass(u16 Copy_u16Angle);

void HTFT_voidDrawDigitalCompass(void);
//self Study


void HTFT_voidDrawRectanguler(/*4 lines*/);

void HTFT_voidDrawTriangle(/* 3 lines*/);



#endif
