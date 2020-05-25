/*
 * Timer0.c
 *
 *  Created on: May 10, 2020
 *      Author: Muhammad Hossam
 */

#include "Timer0.h"


struct STimer0_Settings Timer0_Configuration;
u8 TOV_Number ;

static void (*Ptr_To_OVFI)(void);
static void (*Ptr_To_OCMI)(void);


extern void TMR0_Init(struct STimer0_Settings Configuration)
{
	Timer0_Configuration = Configuration ;
	SREG_R |= 0x80;   // Enable SREG [global interrupt Enable]


	/*********************Adjust Mode***********************/
	if (Timer0_Configuration.Timer0_Mode == NORMAL )
	{
		TCCR0_R &= ~(1<<WGM00);
		TCCR0_R &= ~(1<< WGM01);
	}
	if (Timer0_Configuration.Timer0_Mode == PHASECORRECTPWM )
	{
		TCCR0_R |= (1<< WGM00);
		TCCR0_R &= ~(1<<WGM01);
	}
	if (Timer0_Configuration.Timer0_Mode == CTC )
	{
		TCCR0_R &= ~(1<<WGM00);
		TCCR0_R |= (1<< WGM01);
	}
	if (Timer0_Configuration.Timer0_Mode == FASTPWM )
	{
		TCCR0_R |= (1<<WGM00);
		TCCR0_R |= (1<< WGM01);
	}

	/************************Compare output mode Normal mode*********************************/
	if (Timer0_Configuration.Timer0_NONPWM == DISCONNECTED )
	{
		TCCR0_R &= ~(1<<COM01);
		TCCR0_R &= ~(1<< COM00);
	}
	if (Timer0_Configuration.Timer0_NONPWM == TOGGLE_ON_COMPARE )
	{
		TCCR0_R &= ~(1<<COM01);
		TCCR0_R |= (1<< COM00);
	}
	if (Timer0_Configuration.Timer0_NONPWM == CLEAR_ON_COMPARE )
	{
		TCCR0_R |= (1<<COM01);
		TCCR0_R &= ~(1<< COM00);
	}
	if (Timer0_Configuration.Timer0_NONPWM == SET_ON_COMPARE )
	{
		TCCR0_R |= (1<<COM01);
		TCCR0_R |= (1<< COM00);
	}
	/************************Compare output mode PWM mode*********************************/
	if (Timer0_Configuration.Timer0_PWM == DISCONNECT )
	{
		TCCR0_R &= ~(1<<COM01);
		TCCR0_R &= ~(1<< COM00);
	}
	if (Timer0_Configuration.Timer0_PWM == RESERVED )
	{
		TCCR0_R &= ~(1<<COM01);
		TCCR0_R |= (1<< COM00);
	}
	if (Timer0_Configuration.Timer0_PWM == NON_INVERTING )
	{
		TCCR0_R |= (1<<COM01);
		TCCR0_R &= ~(1<< COM00);
	}
	if (Timer0_Configuration.Timer0_PWM == INVERTING )
	{
		TCCR0_R |= (1<<COM01);
		TCCR0_R |= (1<< COM00);
	}

	/************************Adjust prescalar************************/
	TCCR0_R = TCCR0_R | Timer0_Configuration.Timer0_PRESCALAR;

	/**************************TMR0 Enable/Disable********************/
	if (Timer0_Configuration.Timer0_OVFI == TOIE0_enable )
	{
		TIMSK_R |= 1<< TOIE0 ;
	}
	else if (Timer0_Configuration.Timer0_OVFI == TOIE0_disable)
	{
		TIMSK_R &= ~(1<< TOIE0) ;

	}

	/**************************OCR0 Enable/Disable********************/
	if (Timer0_Configuration.Timer0_OCIE == OCIE0_enable )
	{
		TIMSK_R |= 1<< OCIE0 ;
	}
	else if (Timer0_Configuration.Timer0_OCIE == OCIE0_disable)
	{
		TIMSK_R &= ~(1<< OCIE0) ;

	}

}

extern void TMR0_ReadCounterValue(u8 *u8NumOfTicks)
{
	*u8NumOfTicks = TCNT0_R;
}
extern void TMR0_Set_Compare_Value(u8 u8Val)
{
	OCR0_R = u8Val;
}

extern void TMR0_Set_Counter_Value(u8 u8Val)
{
	TCNT0_R = u8Val;

}


//used for set the Number of OverFlow (Used for SW Counters)

extern void TMR0_Set_TOV_Number(u8 u8Val)
{
	TOV_Number = u8Val;

}
extern void TMR0_Get_TOV_Number(u8 *u8Val)
{
	*u8Val = TOV_Number ;
}


extern void TMR0_Get_Ticks_of_SWcounter (u32 *u8Val)
{
	*u8Val =  256*TOV_Number + TCNT0_R;
}



extern void callback_TMR0_Overflow_Interrupt (void(*Ptr_to_OVI_Function)(void))
{
	Ptr_To_OVFI = Ptr_to_OVI_Function ;

}
extern void callback_OCR0_Compare_Match_Interrupt(void(*Ptr_to_OCM_Function)(void))
{
	Ptr_To_OCMI = Ptr_to_OCM_Function ;
}



ISR(__vector_10)
{
	(*Ptr_To_OCMI)();
}
ISR(__vector_11)
{
	TOV_Number++;
	(*Ptr_To_OVFI)();
}


