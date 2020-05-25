/*
 * Timer1.c
 *
 *  Created on: May 22, 2020
 *      Author: Muhammad Hossam
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "GPIO.h"
#include <avr/interrupt.h>

volatile extern u8 OCR1A_Number;
volatile extern u8 OCR1B_Number;
enum TMR1_WAVE_FORM_GEN
{
	TMR1_NORMAL = 1,
	TMR1_PHASECORRECTPWM_8_BIT  = 2,
	TMR1_PHASECORRECTPWM_9_BIT  = 3,
	TMR1_PHASECORRECTPWM_10_BIT = 4,
	TMR1_CTC_OUTPUT_COMPARE = 5,
	TMR1_FASTPWM_8_BIT = 6,
	TMR1_FASTPWM_9_BIT = 7,
	TMR1_FASTPWM_10_BIT = 8,
	TMR1_PWM_PHASE_FREQ_CORRECT_INPUT_COMPARE = 9,
	TMR1_PWM_PHASE_FREQ_CORRECT_OUTPUT_COMPARE = 10,
	TMR1_PWM_PHASE_CORRECT_INPUT_COMPARE = 11,
	TMR1_PWM_PHASE_CORRECT_OUTPUT_COMPARE = 12,
	TMR1_CTC_INPUT_COMPARE = 13,
	TMR1_RESERVED_R = 14,
	TMR1_FASTPWM_INPUT_COMPARE = 15,
	TMR1_FASTPWM_OUTPUT_COMPARE = 16,
};
enum TMR1_COMPARE_OUTPUT_MODE_NONPWM
{
	TMR1_DISCONNECTED = 1,
	TMR1_TOGGLE_ON_COMPARE = 2,
	TMR1_CLEAR_ON_COMPARE = 3,
	TMR1_SET_ON_COMPARE = 4
};
enum TMR1_COMPARE_OUTPUT_MODE_PWM
{
	TMR1_DISCONNECT = 1,
	TMR1_RESERVED = 2,
	TMR1_NON_INVERTING = 3,
	TMR1_INVERTING = 4,
};
enum TOVFIE1  //Timer/Counter1 Overflow Interrupt Enable
{
	TOIE1_enable =  1,
	TOIE1_disable = 2
};

enum OCMIE1A   //Timer/Counter1 Output Compare Match A Interrupt Enable
{
	OCIE1A_enable =  1,
	OCIE1A_disable = 2
} ;
enum OCMIE1B  //Timer/Counter1 Output Compare Match A Interrupt Enable
{
	OCIE1B_enable =  1,
	OCIE1B_disable = 2
} ;


enum TMR1_PRESCALAR
{
	TMR1_NO_CLK_SRC = 0, //Timer Disable
	TMR1_NO_PRESCALING = 1,
	TMR1_PRESCALING_CLK8 = 2,
	TMR1_PRESCALING_CLK64 = 3,
	TMR1_PRESCALING_CLK256 = 4,
	TMR1_PRESCALING_CLK1024 = 5,
	TMR1_PRESCALING_FALLING_EDGE = 6,
	TMR1_PRESCALING_RISING_EDGE = 7
};


struct STimer1_Settings
{
	enum TOVFIE1 Timer1_OVFI;
	enum OCMIE1A Timer1_OCIEA;
	enum OCMIE1B Timer1_OCIEB;
	enum TMR1_WAVE_FORM_GEN Timer1_Mode;
	enum TMR1_PRESCALAR Timer1_PRESCALAR;
	enum TMR1_COMPARE_OUTPUT_MODE_NONPWM Timer1_NONPWM;
	enum TMR1_COMPARE_OUTPUT_MODE_PWM Timer1_PWM;
};
//////////////////////////////////////////

/////////////////////Timer2 Interface


extern void TMR1_Init(struct STimer1_Settings Configuration);
extern void TMR1_ReadCounterValue(u16* u16NumOfTicks);
extern void TMR1_Set_Compare_A_Value(u16 u16Val);
extern void TMR1_Set_Compare_B_Value(u16 u16Val);
extern void TMR1_Set_Counter_Value(u16 u16Val);
extern void TMR1_Set_OV_Number(u8 u8Val);
extern void TMR1_Get_TOV_Number(u8 *u8Val);

////SW Counter
extern void TMR1_Get_Ticks_of_SWcounter (u32 *u32Val);

//ISR
extern void callback_TMR1_Overflow_Interrupt (void(*Ptr_to_OVI_Function)(void));
extern void callback_OCR1A_Compare_Match_Interrupt(void(*Ptr_to_OCMA_Function)(void));
extern void callback_OCR1B_Compare_Match_Interrupt(void(*Ptr_to_OCMB_Function)(void));








//////////////////////////////////////////

//////////////////////////////Private HW registers


/********************************EXT INT ISR**********************************/

#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)


/**************************TCCR1A Register*************************************/
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A  3
#define FOC1B  2
#define WGM11  1
#define WGM10  0

/**************************TCCR1B Register*************************************/
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12  2
#define CS11  1
#define CS10  0

/**************************Timer/Counter Interrupt Mask Register*************************************/
#define TICIE1  5   // Input capture interrupt enable
#define OCIE1A	4	// output compare A Match interrupt enable
#define OCIE1B	3	// Output compare B Match interrupt enable
#define TOIE1	2	// Timer 1 overflow interrupt enable

/**************************Timer/counter interrupt flag register**********************************/
#define ICF1    5   // Input capture flag
#define OCF1A	4	// output compare A Match flag
#define OCF1B	3	// Output compare B Match flag
#define TOV1	2	// Timer 1 overflow flag



/////////////////////////////////////////////////




#endif /* TIMER1_H_ */
