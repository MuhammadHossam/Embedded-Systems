/*
 * Timer2.h
 *
 *  Created on: May 11, 2020
 *      Author: Muhammad Hossam
 */

#ifndef TIMER2_H_
#define TIMER2_H_
#include "GPIO.h"
#include <avr/interrupt.h>
enum TMR2_WAVE_FORM_GEN
{
	TMR2_CTC = 1,
	TMR2_NORMAL = 2,
	TMR2_FASTPWM = 3,
	TMR2_PHASECORRECTPWM = 4
};
enum TMR2_COMPARE_OUTPUT_MODE_NONPWM
{
	TMR2_DISCONNECTED = 1,
	TMR2_TOGGLE_ON_COMPARE = 2,
	TMR2_CLEAR_ON_COMPARE = 3,
	TMR2_SET_ON_COMPARE = 4
};
enum TMR2_COMPARE_OUTPUT_MODE_PWM
{
	TMR2_DISCONNECT = 1,
	TMR2_RESERVED = 2,
	TMR2_NON_INVERTING = 3,
	TMR2_INVERTING = 4,
};
enum TOVFIE2  //Timer/Counter0 Overflow Interrupt Enable
{
	TOIE2_enable,
	TOIE2_disable
} ;

enum OCMIE2   //Timer/Counter0 Output Compare Match Interrupt Enable
{
	OCIE2_enable ,
	OCIE2_disable
} ;



enum TMR2_PRESCALAR
{
	TMR2_NO_CLK_SRC = 0, //Timer Disable
	TMR2_NO_PRESCALING = 1,
	TMR2_PRESCALING_CLK8 = 2,
	TMR2_PRESCALING_CLK32 = 3,
	TMR2_PRESCALING_CLK64 = 4,
	TMR2_PRESCALING_CLK128 = 5,
	TMR2_PRESCALING_CLK256 = 6,
	TMR2_PRESCALING_CLK1024 = 7
} ;


struct STimer2_Settings
{
	enum TOVFIE2 Timer2_OVFI ;
	enum OCMIE2 Timer2_OCIE;
	enum TMR2_WAVE_FORM_GEN Timer2_Mode ;
	enum TMR2_PRESCALAR Timer2_PRESCALAR;
	enum TMR2_COMPARE_OUTPUT_MODE_NONPWM Timer2_NONPWM;
	enum TMR2_COMPARE_OUTPUT_MODE_PWM Timer2_PWM;

};
//////////////////////////////////////////

/////////////////////Timer2 Interface


extern void TMR2_Init(struct STimer2_Settings Configuration);
extern void TMR2_ReadCounterValue(u8* u8NumOfTicks);
extern void TMR2_Set_Compare_Value(u8 u8Val);

extern void TMR2_Set_OV_Number(u8 u8Val);
extern void TMR2_Get_TOV_Number(u8 *u8Val);

////SW Counter
extern void TMR2_Get_Ticks_of_SWcounter (u32 *u8Val);

//ISR
extern void callback_TMR2_Overflow_Interrupt (void(*Ptr_to_OVI_Function)(void));
extern void callback_OCR2_Compare_Match_Interrupt(void(*Ptr_to_OCM_Function)(void));








//////////////////////////////////////////

//////////////////////////////Private HW registers


/********************************EXT INT ISR**********************************/

#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)


/**************************TCCR0 Registers*************************************/
#define FOC2	7
#define WGM20	6
#define COM21 	5
#define COM20	4
#define WGM21	3
#define CS22 	2
#define CS21 	1
#define CS20 	0
/**************************Enable TMR0 Pin*************************************/
#define TOIE2	6
#define OCIE2	7


/////////////////////////////////////////////////




#endif /* TIMER2_H_ */
