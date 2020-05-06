/*
 * SevenSeg.h
 *
 *  Created on: Apr 25, 2020
 *      Author: Muhammad Hossam
 */

#ifndef SEVENSEG_H_
#define SEVENSEG_H_
#include "DATA_Types.h"
#include "ATMEGA32_registers.h"
#include "std_macros.h"
#include "GPIO.h"
#include "Delay.h"
//=====================DATA Pins============================
/* choose the Data pins for Seven segment */
#define SEG_A	        20         // Means SEG_A at pin 4 port C
#define SEG_B           21         // Means SEG_B at pin 5 port C
#define SEG_C           22         // Means SEG_C at pin 6 port C
#define SEG_D           23         // Means SEG_D at pin 7 port C
#define SEV_SEG_EN1     18         // Means EN1 at pin 2 port C
#define SEV_SEG_EN2     19         // Means En2 at pin 3 port C

//=====================Initialization=======================
/*comment! : Initialization Function */
void SEV_SEG_voidInit(void);
//==========================================================

/*Comment! : Enable the first Seven Segment*/
extern u8 SEV_SEG_u8_EN1(void);

/*Comment! : Enable the Second Seven Segment*/
extern u8 SEV_SEG_u8_EN2(void);

/*Comment! : Disable the first Seven Segment*/
extern u8 SEV_SEG_u8_DIS1(void);

/*Comment! : Disable the Second Seven Segment*/
extern u8 SEV_SEG_u8_DIS2(void);

/*Comment! : Write on the First Seven Segment*/
extern u8 SEV_SEG_1_u8_WriteVal(u8 count);

/*Comment! : Write on the Second Seven Segment*/
extern u8 SEV_SEG_2_u8_WriteVal(u8 count);

/*Comment! : Write the Value on SEG_A*/
extern u8 SEV_SEG_u8_A(u8 BIT);

/*Comment! : Write the Value on SEG_B*/
extern u8 SEV_SEG_u8_B(u8 BIT);

/*Comment! : Write the Value on SEG_C*/
extern u8 SEV_SEG_u8_C(u8 BIT);

/*Comment! : Write the Value on SEG_D*/
extern u8 SEV_SEG_u8_D(u8 BIT);

/*Comment! : Count UP in Seven Seg*/
extern u8 SEV_SEG_1_u8_COUNT_UP(void);

/*Comment! : Count UP in Seven Seg*/
extern u8 SEV_SEG_2_u8_COUNT_UP(void);

/*Comment! : Display Two numbers*/
u8 SEV_SEG_2Num_u8(u8 Count);


#endif /* SEVENSEG_H_ */
