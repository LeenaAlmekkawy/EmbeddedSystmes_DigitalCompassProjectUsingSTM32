#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_interface.h"
#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/STK/STK_interface.h"
#include "../MCAL/USART/USART_interface.h"
#include "../MCAL/I2C/I2C_interface.h"
#include "../HAL/GY271/GY271_interface.h"


#include <math.h>

void main(void)
{

    MRCC_voidSystemClkInit();


    //MSTK_voidInit();

    MRCC_voidEnablePerClk(RCC_AHB1, RCC_EN_GPIOA);
    MRCC_voidEnablePerClk(RCC_AHB1, RCC_EN_GPIOB);

    //enable I2C clock
    MRCC_voidEnablePerClk(RCC_APB1, RCC_EN_I2C1);

    //USART
    MRCC_voidEnablePerClk(RCC_APB2,RCC_EN_USART1);


    //Testing
    PIN_st PinOut= {OUTPUT,PP,LS,NPP};


    PIN_st PinIn= {INPUT,PP,HS,PU};

    GPIO_voidSetPinDirection(GPIO_PORTA,PIN0,&PinOut);




    //set pins direction
    PIN_st I2C_PinAF= {AF,OD,VHS,PU};
    GPIO_voidSetPinDirection (GPIO_PORTB,PIN8, &I2C_PinAF);
    GPIO_voidSetPinDirection (GPIO_PORTB,PIN9, &I2C_PinAF);

    GPIO_voidSetAlternativeFunction(GPIO_PORTB,PIN8, GPIO_AF_4);
    GPIO_voidSetAlternativeFunction(GPIO_PORTB,PIN9,  GPIO_AF_4);


    USART_InitType uart= {9600,MODE_8BIT,STOP_BIT_1,DISABLE,EVEN_PARITY,TX_RX,DISABLE,OVER_SAMPLING_16};
    USART_ClockInitType uartclock = {DISABLE,0,0,0};
    PIN_st USART_PinAF= {AF,PP,HS,NPP};

    //USART1


    GPIO_voidSetPinDirection (GPIO_PORTA,PIN10, &USART_PinAF);
    GPIO_voidSetPinDirection (GPIO_PORTA,PIN9, &USART_PinAF);

    GPIO_voidSetAlternativeFunction(GPIO_PORTA,PIN10, GPIO_AF_7);
    GPIO_voidSetAlternativeFunction(GPIO_PORTA,PIN9,  GPIO_AF_7);

    // Initialization of USART1
    MUSART_voidInit(&uart, &uartclock, USART1);

    // Enable USART1
    MUSART_voidEnable(USART1);


    MI2C_voidMasterInit(I2C1);

    GY271_voidInit();

    f64 Xmin=1000.0;
    f64 Xmax=-1000.0;
    f64 Ymin=1000.0;
    f64 Ymax=-1000.0;

    volatile	f64 ys=0.0;
    volatile f64 xb=0.0;
    volatile	f64 yb=0.0;



    while(1)
    {


        volatile	s16 val =GY271_s16GetHeadingReading();


        u8 Local_ReadArr[8]= {0};

        MI2C_SendStartCondition(I2C1);
        MI2C_SendSlaveAddressWithWrite(I2C1, 0x1E);//slave address with write
        MI2C_MasterWriteDataByte(I2C1,0x03);
        MI2C_SendStartCondition(I2C1);
        MI2C_MasterRead(I2C1,0x1E, Local_ReadArr, 6);


        volatile	s16 Local_s16accel_x=( (Local_ReadArr[0]<<8)|Local_ReadArr[1] );
        volatile	s16 Local_s16accel_z=( (Local_ReadArr[2]<<8)|Local_ReadArr[3] );
        volatile	s16 Local_s16accel_y=( (Local_ReadArr[4]<<8)|Local_ReadArr[5] );

        volatile	f64 x=  (f64)Local_s16accel_x  *  1.22;
        volatile	f64 y=   (f64)Local_s16accel_y  *  1.22;



        if(Xmin>x)
        {
            Xmin=x;
        }
        if(Ymin>y)
        {
            Ymin=y;
        }
        if(Xmax<x)
        {
            Xmax=x;
        }
        if(Ymax<y)
        {
            Ymax=y;
        }


        ys=(Xmax-Xmin)/(Ymax-Ymin);
        xb =1*(0.5*(Xmax-Xmin)-Xmax);
        yb =1*(0.5*(Ymax-Ymin)-Ymax);


        USART_voidTransmitString("\nYS");
        USART_voidSendNumber( ((s32)(ys*100 ) ));
        USART_voidTransmitString("\nxb");
        USART_voidSendNumber( ((s32)(xb*100 ) ));
        USART_voidTransmitString("\nyb");
        USART_voidSendNumber( ((s32)(yb*100 ) ) );


        asm("NOP");
    }
}
