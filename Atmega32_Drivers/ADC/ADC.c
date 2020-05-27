/*
 * ADC.c
 *
 *  Created on: May 26, 2020
 *      Author: Muhammad Hossam
 */

#include "ADC.h"
struct ADC_Settings ADC_Configuration;
static void (*Ptr_To_ADC_INT)(void);

extern void ADC_Init(struct ADC_Settings Configuration)
{
	ADC_Configuration = Configuration ;
	SREG_R |= 0x80;   // Enable SREG [global interrupt Enable]

	/*************ADC Voltage Reference Selection*****************/
	if(ADC_Configuration.ADC_VOLT_REF == AREF)
	{
		ADMUX_R &= ~(1<<6);
		ADMUX_R &= ~(1<<7);
	}
	else if(ADC_Configuration.ADC_VOLT_REF == AVCC)
	{
		ADMUX_R |= (1<<6);
		ADMUX_R &= ~(1<<7);
	}
	else if(ADC_Configuration.ADC_VOLT_REF == INTERNAL_VOLTAGE)
	{
		ADMUX_R |= (1<<6);
		ADMUX_R |= (1<<7);
	}

	/******************ADC Input channel and gain selections*************/

	ADMUX_R |= ADC_Configuration.ADC_INPUT_CHANNEL;


	/********** ADC interrupt Enable/Disable****************************/
	if(ADC_Configuration.ADC_ADIE == ADIE_ENABLE)
	{
		ADCSRA_R |= (1<<ADIE);
	}
	else if(ADC_Configuration.ADC_ADIE == ADIE_DISABLE)
	{
		ADCSRA_R &= ~(1<<ADIE);
	}

	/*******************ADC Auto Trigger Enable/Disable********************/
	if(ADC_Configuration.ADC_ADATE == ADATE_ENABLE)
	{
		ADCSRA_R |= (1<<ADATE);
	}
	else if(ADC_Configuration.ADC_ADATE == ADATE_DISABLE)
	{
		ADCSRA_R &= ~(1<<ADATE);
	}


	/******************** ADC Enable/Disable*****************************/

	if(ADC_Configuration.ADC_ADEN == ADC_ON)
	{
		ADCSRA_R |= (1<<ADEN);
	}
	else if(ADC_Configuration.ADC_ADEN == ADC_OFF)
	{
		ADCSRA_R &= ~(1<<ADEN);
	}


	/*****************ADC Left Adjust Result*****************************/
	if(ADC_Configuration.ADC_ADLAR == LEFT)
	{
		ADCSRA_R |= (1<<ADLAR);
	}
	else if(ADC_Configuration.ADC_ADLAR == RIGHT)
	{
		ADCSRA_R &= ~(1<<ADLAR);
	}

	/*************** ADC Prescaler Selections*****************************/
	ADCSRA_R |= ADC_Configuration.ADC_PRESC;

	/*************** ADC Auto Trigger Source Selections ******************/
	SFIOR_R |= (ADC_Configuration.ADC_ADTS <<5);

}

extern void ADC_Start_Conversion(void)
{
	//ADCSRA_R |= (1<<ADSC);
	ADCSRA_R |= (1<<6);
}

extern u8 ADC_Read_Interrupt_Flag(void)
{
	return (ADCSRA_R&(1<<4));
}
extern void callback_ADC_CONVERSION_COMPLETE_Interrupt(void(*Ptr_to_ADC_Function)(void))
{
	Ptr_To_ADC_INT = Ptr_to_ADC_Function;
}

extern void ADC_Read_Data(u16* Ptr_to_ADC_Val)
{
	*Ptr_to_ADC_Val = ADCL;
	*Ptr_to_ADC_Val |= (*Ptr_to_ADC_Val)|(ADCH<<8);
}
//ISR

ISR(__vector_16)
{
	(*Ptr_To_ADC_INT)();
	ADC_Start_Conversion();
}
