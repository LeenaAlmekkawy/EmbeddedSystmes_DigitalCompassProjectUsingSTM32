/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: GPIO                *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#define GPIO_PORTA         0
#define GPIO_PORTB         1
#define GPIO_PORTC         2


#define PIN0          0
#define PIN1          1
#define PIN2          2
#define PIN3          3
#define PIN4          4
#define PIN5          5
#define PIN6          6
#define PIN7          7
#define PIN8          8
#define PIN9          9
#define PIN10         10
#define PIN11         11
#define PIN12         12
#define PIN13         13
#define PIN14         14
#define PIN15         15

#define INPUT         0
#define OUTPUT        1

#define LOW           0
#define HIGH          1

#define PORT_RANGE    3
#define PIN_RANGE     16

/*GPIO Mode
 *
 *
 *  Input
    General purpose output mode
    Alternate function mode
    Analog mode
 */

#define INPUT         0
#define OUTPUT        1
#define AF            2
#define ANALOG        3
/*Output type
	 *    push-pull -->PP
         open-drain --> OD
	 *
	 */

#define PP            0
#define OD            1


/*  Low speed--->LS
     Medium speed--->MS
      High speed--->HS
      Very high speed--->VHS
           */
#define LS           0
#define MS           1
#define HS           2
#define VHS          3

/*
 *        pull-up/pull-down register
	 *   No pull-up, pull-down--->NPP
         Pull-up             ---->PU
         Pull-down           ---->PD
	 */
#define NPP          0
#define PU           1
#define PD           2


#define GPIO_AF_0    0
#define GPIO_AF_1    1
#define GPIO_AF_2    2
#define GPIO_AF_3    3
#define GPIO_AF_4    4
#define GPIO_AF_5    5
#define GPIO_AF_6    6
#define GPIO_AF_7    7
#define GPIO_AF_8    8
#define GPIO_AF_9    9
#define GPIO_AF_10   10
#define GPIO_AF_11   11
#define GPIO_AF_12   12
#define GPIO_AF_13   13
#define GPIO_AF_14   14
#define GPIO_AF_15   15

typedef struct
{
    u8 PIN_MOD;
    /*INPUT
     OUTPUT
    Alternate function mode-->AF
    ANALOG */
    u8 PIN_OT;
    /*Output type
     *    push-pull -->PP
         open-drain --> OD
     *
     */
    u8 PIN_SPD;
    /*
     *     Low speed--->LS
           Medium speed--->MS
           High speed--->HS
           Very high speed--->VHS
     *
     */
    u8 PIN_PUPD;
    /*    pull-up/pull-down register
     *   No pull-up, pull-down--->NPP
         Pull-up             ---->PU
         Pull-down           ---->PD
     */
}PIN_st;

void GPIO_voidSetPinDirection (u8 Copy_u8PortName, u8 Copy_u8PinNumber, PIN_st*  Copy_psPinInfo);
void GPIO_voidSetAlternativeFunction(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8AltFun);
void GPIO_voidSetPinValue     (u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinValue);
u8   GPIO_u8GetPinValue       (u8 Copy_u8PortName, u8 Copy_u8PinNumber);
u8   GPIO_u8GetPortValue      (u8 Copy_u8PortName);





#endif
