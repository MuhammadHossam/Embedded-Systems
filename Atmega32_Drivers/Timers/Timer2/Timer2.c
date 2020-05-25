/*
 * Timer2.c
 *
 *  Created on: May 11, 2020
 *      Author: Muhammad Hossam
 */
#include "Timer2.h"

struct STimer2_Settings Timer2_Configuration;
u8 TOV_Number_2 ;

static void (*Ptr_To_OVFI2)(void);
static void (*Ptr_To_OCMI2)(void);


extern void TMR2_Init(struct STimer2_Settings Configuration)
{
	Timer2_Configuration = Configuration ;
	SREG_R |= 0x80;   // Enable SREG [global interrupt Enable]

	/*********************Adjust Mode***********************/
	if (Timer2_Configuration.Timer2_Mode == TMR2_NORMAL )
	{
		TCCR2_R &= ~(1<<WGM20);
		TCCR2_R &= ~(1<< WGM21);
	}
	else if (Timer2_Configuration.Timer2_Mode == TMR2_PHASECORRECTPWM )
	{
		TCCR2_R |= (1<< WGM20);
		TCCR2_R &= ~(1<<WGM21);
	}
	else if (Timer2_Configuration.Timer2_Mode == TMR2_CTC )
	{
		TCCR2_R &= ~(1<<WGM20);
		TCCR2_R |= (1<< WGM21);
	}
	else if (Timer2_Configuration.Timer2_Mode == TMR2_FASTPWM )
	{
		TCCR2_R |= (1<<WGM20);
		TCCR2_R |= (1<< WGM21);
	}

	/************************Compare output mode Normal mode*********************************/
	if (Timer2_Configuration.Timer2_NONPWM == TMR2_DISCONNECTED )
	{
		TCCR2_R &= ~(1<<COM21);
		TCCR2_R &= ~(1<< COM20);
	}
	else if (Timer2_Configuration.Timer2_NONPWM == TMR2_TOGGLE_ON_COMPARE )
	{
		TCCR2_R &= ~(1<<COM21);
		TCCR2_R |= (1<<COM20);
	}
	else if (Timer2_Configuration.Timer2_NONPWM == TMR2_CLEAR_ON_COMPARE )
	{
		TCCR2_R |= (1<<COM21);
		TCCR2_R &= ~(1<< COM20);
	}
	else if (Timer2_Configuration.Timer2_NONPWM == TMR2_SET_ON_COMPARE )
	{
		TCCR2_R |= (1<<COM21);
		TCCR2_R |= (1<< COM20);
	}
	/************************Compare output mode PWM mode*********************************/
	if (Timer2_Configuration.Timer2_PWM == TMR2_DISCONNECT )
	{
		TCCR2_R &= ~(1<<COM21);
		TCCR2_R &= ~(1<< COM20);
	}
	else if (Timer2_Configuration.Timer2_PWM == TMR2_RESERVED )
	{
		TCCR2_R &= ~(1<<COM21);
		TCCR2_R |= (1<< COM20);
	}
	else if (Timer2_Configuration.Timer2_PWM == TMR2_NON_INVERTING )
	{
		TCCR2_R |= (1<<COM21);
		TCCR2_R &= ~(1<< COM20);
	}
	else if (Timer2_Configuration.Timer2_PWM == TMR2_INVERTING )
	{
		TCCR2_R |= (1<<COM21);
		TCCR2_R |= (1<< COM20);
	}

	/************************Adjust prescalar************************/
	TCCR2_R = TCCR2_R | Timer2_Configuration.Timer2_PRESCALAR;

	/**************************TMR0 Enable/Disable********************/
	if (Timer2_Configuration.Timer2_OVFI == TOIE2_enable )
	{
		TIMSK_R |= 1<< TOIE2 ;
	}
	else if (Timer2_Configuration.Timer2_OVFI == TOIE2_disable)
	{
		TIMSK_R &= ~(1<< TOIE2) ;

	}

	/**************************OCR0 Enable/Disable********************/
	if (Timer2_Configuration.Timer2_OCIE == OCIE2_enable )
	{
		TIMSK_R |= 1<< OCIE2 ;
	}
	else if (Timer2_Configuration.Timer2_OCIE == OCIE2_disable)
	{
		TIMSK_R &= ~(1<< OCIE2);

	}

}

extern void TMR2_ReadCounterValue(u8 *u8NumOfTicks)
{
	*u8NumOfTicks = TCNT2_R;
}
extern void TMR2_Set_Compare_Value(u8 u8Val)
{
	OCR2_R = u8Val;
}

extern void TMR2_Set_Counter_Value(u8 u8Val)
{
	TCNT2_R = u8Val;

}


//used for set the Number of OverFlow (Used for SW Counters)

extern void TMR2_Set_TOV_Number(u8 u8Val)
{
	TOV_Number_2 = u8Val;

}
extern void TMR2_Get_TOV_Number(u8 *u8Val)
{
	*u8Val = TOV_Number_2 ;
}


extern void TMR2_Get_Ticks_of_SWcounter (u32 *u8Val)
{
	*u8Val =  256*TOV_Number_2 + TCNT2_R;
}



extern void callback_TMR2_Overflow_Interrupt (void(*Ptr_to_OVI_Function)(void))
{
	Ptr_To_OVFI2 = Ptr_to_OVI_Function ;

}
extern void callback_OCR2_Compare_Match_Interrupt(void(*Ptr_to_OCM_Function)(void))
{
	Ptr_To_OCMI2 = Ptr_to_OCM_Function ;
}

ISR(__vector_4)
{
	(*Ptr_To_OCMI2)();
}

ISR(__vector_5)
{
	TOV_Number_2++;
	(*Ptr_To_OVFI2)();
}

