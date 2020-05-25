/*
 * Timer1.c
 *
 *  Created on: May 22, 2020
 *      Author: Muhammad Hossam
 */


#include "Timer1.h"


struct STimer1_Settings Timer1_Configuration;
volatile u8 TOV_Number = 0;
volatile u8 OCR1A_Number = 0;
volatile u8 OCR1B_Number = 0;
static void (*Ptr_To_OVFI)(void);
static void (*Ptr_To_OCMIA)(void);
static void (*Ptr_To_OCMIB)(void);


extern void TMR1_Init(struct STimer1_Settings Configuration)
{
	Timer1_Configuration = Configuration ;
	SREG_R |= 0x80;   // Enable SREG [global interrupt Enable]
    sei();   // Enable Global Interrupt ...
	// WGM10 WGM 11  ---> TCCR1A
	// WGM12 WGM 13  ---> TCCR1B
	/*********************Adjust Mode***********************/
	if (Timer1_Configuration.Timer1_Mode == TMR1_NORMAL )
	{
		TCCR1A_R &= ~(1<<WGM10);
		TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R &= ~(1<<WGM12);
		TCCR1B_R &= ~(1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_PHASECORRECTPWM_8_BIT )
	{
		TCCR1A_R |=  (1<<WGM10);
		TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R &= ~(1<<WGM12);
		TCCR1B_R &= ~(1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_PHASECORRECTPWM_9_BIT )
	{
		TCCR1A_R &= ~(1<<WGM10);
		TCCR1A_R |=  (1<<WGM11);
		TCCR1B_R &= ~(1<<WGM12);
		TCCR1B_R &= ~(1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_PHASECORRECTPWM_10_BIT )
	{
		TCCR1A_R |=  (1<<WGM10);
		TCCR1A_R |=  (1<<WGM11);
		TCCR1B_R &= ~(1<<WGM12);
		TCCR1B_R &= ~(1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_CTC_OUTPUT_COMPARE )
	{
	//	TCCR1A_R &= ~(1<<WGM10);
	//	TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
	//	TCCR1B_R &= ~(1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_FASTPWM_8_BIT )
	{
		TCCR1A_R |=  (1<<WGM10);
		TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
		TCCR1B_R &= ~(1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_FASTPWM_9_BIT )
	{
		TCCR1A_R &= ~(1<<WGM10);
		TCCR1A_R |=  (1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
		TCCR1B_R &= ~(1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_FASTPWM_10_BIT )
	{
		TCCR1A_R |=  (1<<WGM10);
		TCCR1A_R |=  (1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
		TCCR1B_R &= ~(1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_PWM_PHASE_FREQ_CORRECT_INPUT_COMPARE )
	{
		TCCR1A_R &= ~(1<<WGM10);
		TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R &= ~(1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_PWM_PHASE_FREQ_CORRECT_OUTPUT_COMPARE )
	{
		TCCR1A_R |=  (1<<WGM10);
		TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R &= ~(1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_PWM_PHASE_CORRECT_INPUT_COMPARE )
	{
		TCCR1A_R &= ~(1<<WGM10);
		TCCR1A_R |=  (1<<WGM11);
		TCCR1B_R &= ~(1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_PWM_PHASE_CORRECT_OUTPUT_COMPARE )
	{
		TCCR1A_R |=  (1<<WGM10);
		TCCR1A_R |=  (1<<WGM11);
		TCCR1B_R &= ~(1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_CTC_INPUT_COMPARE )
	{
		TCCR1A_R &= ~(1<<WGM10);
		TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_RESERVED_R )
	{
		TCCR1A_R |=  (1<<WGM10);
		TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_CTC_INPUT_COMPARE )
	{
		TCCR1A_R &= ~(1<<WGM10);
		TCCR1A_R &= ~(1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_FASTPWM_INPUT_COMPARE )
	{
		TCCR1A_R &= ~(1<<WGM10);
		TCCR1A_R |=  (1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	else if (Timer1_Configuration.Timer1_Mode == TMR1_FASTPWM_OUTPUT_COMPARE )
	{
		TCCR1A_R |=  (1<<WGM10);
		TCCR1A_R |=  (1<<WGM11);
		TCCR1B_R |=  (1<<WGM12);
		TCCR1B_R |=  (1<<WGM13);
	}
	/************************Compare output mode Normal mode*********************************/
	if (Timer1_Configuration.Timer1_NONPWM == TMR1_DISCONNECTED )
	{
		TCCR1A_R &= ~(1<<COM1A1);
		TCCR1B_R &= ~(1<<COM1B1);

		TCCR1A_R &= ~(1<<COM1A0);
		TCCR1B_R &= ~(1<<COM1B0);
	}
	else if (Timer1_Configuration.Timer1_NONPWM == TMR1_TOGGLE_ON_COMPARE )
	{
		TCCR1A_R &= ~(1<<COM1A1);
		TCCR1B_R &= ~(1<<COM1B1);

		TCCR1A_R |=  (1<<COM1A0);
		TCCR1B_R |=  (1<<COM1B0);
	}
	else if (Timer1_Configuration.Timer1_NONPWM == TMR1_CLEAR_ON_COMPARE )
	{
		TCCR1A_R |=  (1<<COM1A1);
		TCCR1B_R |=  (1<<COM1B1);

		TCCR1A_R &= ~(1<<COM1A0);
		TCCR1B_R &= ~(1<<COM1B0);
	}
	else if (Timer1_Configuration.Timer1_NONPWM == TMR1_SET_ON_COMPARE )
	{
		TCCR1A_R |=  (1<<COM1A1);
		TCCR1B_R |=  (1<<COM1B1);

		TCCR1A_R |=  (1<<COM1A0);
		TCCR1B_R |=  (1<<COM1B0);
	}
	/************************Compare output mode PWM mode*********************************/
	if (Timer1_Configuration.Timer1_PWM == TMR1_DISCONNECT )
	{
		TCCR1A_R &= ~(1<<COM1A1);
		TCCR1B_R &= ~(1<<COM1B1);

		TCCR1A_R &= ~(1<<COM1A0);
		TCCR1B_R &= ~(1<<COM1B0);
	}
	if (Timer1_Configuration.Timer1_PWM == TMR1_RESERVED )
	{
		TCCR1A_R &= ~(1<<COM1A1);
		TCCR1B_R &= ~(1<<COM1B1);

		TCCR1A_R |=  (1<<COM1A0);
		TCCR1B_R |=  (1<<COM1B0);
	}
	if (Timer1_Configuration.Timer1_PWM == TMR1_NON_INVERTING )
	{

		TCCR1A_R |=  (1<<COM1A1);
		TCCR1B_R |=  (1<<COM1B1);

		TCCR1A_R &= ~(1<<COM1A0);
		TCCR1B_R &= ~(1<<COM1B0);
	}
	if (Timer1_Configuration.Timer1_PWM == TMR1_INVERTING )
	{
		TCCR1A_R |=  (1<<COM1A1);
		TCCR1B_R |=  (1<<COM1B1);

		TCCR1A_R |=  (1<<COM1A0);
		TCCR1B_R |=  (1<<COM1B0);
	}

	/************************Adjust prescalar************************/
	TCCR1B_R = TCCR1B_R | Timer1_Configuration.Timer1_PRESCALAR;

	/**************************TMR0 Enable/Disable********************/
	if (Timer1_Configuration.Timer1_OVFI == TOIE1_enable )
	{
		TIMSK_R |= (1<<TICIE1);
	}
	else if (Timer1_Configuration.Timer1_OVFI == TOIE1_disable)
	{
		TIMSK_R &= ~(1<< TICIE1);

	}

	/**************************Output compare A interrupt Enable/Disable********************/
	if (Timer1_Configuration.Timer1_OCIEA == OCIE1A_enable )
	{
		TIMSK_R |= (1<<OCIE1A);
	}
	else if (Timer1_Configuration.Timer1_OCIEA == OCIE1A_disable)
	{
		TIMSK_R &= ~(1<<OCIE1A);
	}

	if (Timer1_Configuration.Timer1_OCIEB == OCIE1B_enable )
	{
		TIMSK_R |= (1<<OCIE1B);
	}
	else if (Timer1_Configuration.Timer1_OCIEB == OCIE1B_disable)
	{
		TIMSK_R &= ~(1<<OCIE1B);
	}

}

extern void TMR1_ReadCounterValue(u16 *u16NumOfTicks)
{
	u8 sreg = SREG_R;  // save global interrupt flag
	cli();  // Disable interrupts to prevent data corruption
	*u16NumOfTicks = (u16)TCNT1L_R;
	*u16NumOfTicks = (*u16NumOfTicks) | (u16)(TCNT1H_R<<8);
	/*Restore global interrupt flag*/
	SREG_R = sreg;
}
extern void TMR1_Set_Compare_A_Value(u16 u16Val)
{
	u8 sreg = SREG_R;  // save global interrupt flag
	cli();  // Disable interrupts to prevent data corruption
	OCR1AH_R = (u8)(u16Val>>8);
	OCR1AL_R = (u8)u16Val;
	/*Restore global interrupt flag*/
	SREG_R = sreg;
}
extern void TMR1_Set_Compare_B_Value(u16 u16Val)
{
	u8 sreg = SREG_R;  // save global interrupt flag
	cli();  // Disable interrupts to prevent data corruption
	OCR1BH_R = (u16)(u16Val>>8);
	OCR1BL_R = (u16)u16Val;
	/*Restore global interrupt flag*/
	SREG_R = sreg;
}
extern void TMR1_Set_Counter_Value(u16 u16Val)
{
	u8 sreg = SREG_R;  // save global interrupt flag
	cli();  // Disable interrupts to prevent data corruption
	TCNT1H_R = (u16)(u16Val>>8);
	TCNT1L_R =  (u16)u16Val;
	/*Restore global interrupt flag*/
	SREG_R = sreg;
}


//used for set the Number of OverFlow (Used for SW Counters)

extern void TMR1_Set_TOV_Number(u8 u8Val)
{
	TOV_Number = u8Val;

}
extern void TMR1_Get_TOV_Number(u8 *u8Val)
{
	*u8Val = TOV_Number ;
}


extern void TMR1_Get_Ticks_of_SWcounter (u32 *u32Val)
{
	u16* u16NumOfTicks;
	TMR1_ReadCounterValue(u16NumOfTicks);
	*u32Val =  (65536U)*(u32)TOV_Number + (u32)u16NumOfTicks;
}



extern void callback_TMR1_Overflow_Interrupt (void(*Ptr_to_OVI_Function)(void))
{
	Ptr_To_OVFI = Ptr_to_OVI_Function ;

}
extern void callback_OCR1A_Compare_Match_Interrupt(void(*Ptr_to_OCM_Function)(void))
{
	Ptr_To_OCMIA = Ptr_to_OCM_Function ;
}
extern void callback_OCR1B_Compare_Match_Interrupt(void(*Ptr_to_OCM_Function)(void))
{
	Ptr_To_OCMIB = Ptr_to_OCM_Function ;
}


ISR(__vector_7)
{
	OCR1A_Number++;
	if(OCR1A_Number>=30U)
	{
		(*Ptr_To_OCMIA)();
		OCR1A_Number = 0;
	}
}
ISR(__vector_8)
{
	OCR1B_Number++;
	if(OCR1B_Number>=30U)
	{
		(*Ptr_To_OCMIB)();
		 OCR1B_Number = 0;
	}
}
ISR(__vector_9)
{
	TOV_Number++;
	(*Ptr_To_OVFI)();
}

