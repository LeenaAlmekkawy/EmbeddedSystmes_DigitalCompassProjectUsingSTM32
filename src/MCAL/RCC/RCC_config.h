/*********************************************/
/*********************************************/
/*********  Author: Leena Almekkawy  *********/
/*********  Layer: MCAL              *********/
/*********  SWC: RCC                 *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* clock

   1-HSI(16M)
   2-HSE
   3-PLL
*/

#define RCC_CLK_SOURCE HSI

/* CSS
 *1- ENABLE
 *2- DISABLE
 */
#define RCC_CLK_SECURITY_SYSTEM  DISABLE

/*
 * 1-  NO: HSE oscillator not bypassed
 * 2- YES: HSE oscillator bypassed with an external clock

  //note: always make it NO
*/

#define RCC_HSE_CLK_BYBASS    NO

/*
 * PLL (PLLI2S) entry clock source
 1- HSI :clock selected as PLL and PLLI2S clock entry
 2- HSE :oscillator clock selected as PLL and PLLI2S clock entry
 *
 *
 */

/*
 *  (PLLSRC*N)/(M*P)
 *
 */
#define RCC_PLL_CLK_SRC       HSI

/*
 * PLLP :
 * 1- 0---->2
 * 2- 1---->4
 * 3- 2---->6
 * 4- 3---->8
 */
#define RCC_PLLP               3

/*
 * PLLN from 192 to 432
 *
 */

#define RCC_PLLN               200

/*
 * PLLM from 2 to 63
 *
 */
#define RCC_PLLM               50

#define RCC_PLLQ               10


/*
0xxx: system clock not divided
1000: system clock divided by 2
1001: system clock divided by 4
1010: system clock divided by 8
1011: system clock divided by 16
1100: system clock divided by 64
1101: system clock divided by 128
1110: system clock divided by 256
1111: system clock divided by 512
*/
#define AHB_PRESCALER         0b0000

/*
0xx: AHB clock not divided
100: AHB clock divided by 2
101: AHB clock divided by 4
110: AHB clock divided by 8
111: AHB clock divided by 16
 */

#define APB1_PRESCALER        0b100

#define APB2_PRESCALER        0b100









#endif
