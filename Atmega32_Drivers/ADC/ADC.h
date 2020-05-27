/*
 * ADC.h
 *
 *  Created on: May 26, 2020
 *      Author: Muhammad Hossam
 */

#ifndef ADC_H_
#define ADC_H_
#include "GPIO.h"
#include <avr/interrupt.h>

/* ADC Voltage Reference Selection*/

enum VOLTAGE_REF_SELECTION{
	AREF = 1,              //AREF, Internal Vref turned off
	AVCC = 2, 			   //AVCC with external capacitor at AREF pin
	V_RESERVED = 3,
	INTERNAL_VOLTAGE = 4   // internal 2.56V Voltage Reference with external capacitor at AREF pin
};


/* Input channel and gain selection*/

enum INPUT_CHANNEL_AND_GAIN_SELECTION{
	/*************Single Ended Input***************/
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,

	/************Differential Input******************/
	POSTIVE_ADC0_NEGATIVE_ADC0_X10,
	POSTIVE_ADC1_NEGATIVE_ADC0_X10,

	POSTIVE_ADC0_NEGATIVE_ADC0_X200,
	POSTIVE_ADC1_NEGATIVE_ADC0_X200,

	POSTIVE_ADC2_NEGATIVE_ADC2_X10,
	POSTIVE_ADC3_NEGATIVE_ADC2_X10,

	POSTIVE_ADC2_NEGATIVE_ADC2_X200,
	POSTIVE_ADC3_NEGATIVE_ADC2_X200,

	/*************Differential Input with Gain X1**********/
	POSTIVE_ADC0_NEGATIVE_ADC1,
	POSTIVE_ADC1_NEGATIVE_ADC1,
	POSTIVE_ADC2_NEGATIVE_ADC1,
	POSTIVE_ADC3_NEGATIVE_ADC1,
	POSTIVE_ADC4_NEGATIVE_ADC1,
	POSTIVE_ADC5_NEGATIVE_ADC1,
	POSTIVE_ADC6_NEGATIVE_ADC1,
	POSTIVE_ADC7_NEGATIVE_ADC1,

	POSTIVE_ADC0_NEGATIVE_ADC2,
	POSTIVE_ADC1_NEGATIVE_ADC2,
	POSTIVE_ADC2_NEGATIVE_ADC2,
	POSTIVE_ADC3_NEGATIVE_ADC2,
	POSTIVE_ADC4_NEGATIVE_ADC2,
	POSTIVE_ADC5_NEGATIVE_ADC2,

	/*********Single Ended Input*************/
	SINGLE_ENDED_1_22V,
	SINGLE_ENDED_GND
};

/*ADC interrupt Enable*/
enum ADC_INT_EN{
	ADIE_ENABLE,
	ADIE_DISABLE
};

/*ADC auto trigger Enable*/
enum ADC_AUTO_TRIGGER_EN{
	ADATE_DISABLE,
	ADATE_ENABLE
};

/*ADC enable*/
enum ADC_ENABLE{
	ADC_OFF,
	ADC_ON
};

/*ADC left adjust result*/
enum ADC_RESULT_ADJUST{
	RIGHT,
	LEFT
};

/*ADC prescaler*/
enum ADC_PRESCALER{
	ADC_NO_PRESCALING,
	ADC_PRESCALING_CLK2,
	ADC_PRESCALING_CLK4,
	ADC_PRESCALING_CLK8,
	ADC_PRESCALING_CLK16,
	ADC_PRESCALING_CLK32,
	ADC_PRESCALING_CLK64,
	ADC_PRESCALING_CLK128
};

/*ADC auto trigger source*/
enum ADC_AUTO_TRIGGER_SOURCE
{
	FREE_RUNING_MODE,
	ANALOG_COMPARATOR,
	EXTERNAL_INTERRUPT_Rq0,
	TMR0_COMPARE_MATCH,
	TMR0_OVERFLOW,
	TMR1_COMPARE_MATCH,
	TMR1_OVERFLOW,
	TMR1_CAPTURE_UNIT
};

struct ADC_Settings
{
	enum VOLTAGE_REF_SELECTION ADC_VOLT_REF;
	enum INPUT_CHANNEL_AND_GAIN_SELECTION ADC_INPUT_CHANNEL;
	enum ADC_INT_EN ADC_ADIE;
	enum ADC_AUTO_TRIGGER_EN ADC_ADATE;
	enum ADC_ENABLE ADC_ADEN;
	enum ADC_RESULT_ADJUST ADC_ADLAR;
	enum ADC_PRESCALER ADC_PRESC;
	enum ADC_AUTO_TRIGGER_SOURCE ADC_ADTS;
};


extern void ADC_Init(struct ADC_Settings Configuration);
extern u8 ADC_Read_Interrupt_Flag(void);
extern void ADC_Start_Conversion(void);
extern void callback_ADC_CONVERSION_COMPLETE_Interrupt(void(*Ptr_to_ADC_Function)(void));
extern void ADC_Read_Data(u16* Ptr_to_ADC_Val);


/********************************EXT INT ISR**********************************/

#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)


/*ADMUX-ADC Multiplexer Selection Register*/
#define MUX0	0
#define MUX1	1
#define MUX2	2
#define MUX3	3
#define MUX4	4
#define ADLAR	5
#define REFS0	6
#define REFS1	7

/*ADCSRA-ADC Control and Status Register*/
#define ADPS0	0
#define ADPS1	1
#define ADPS2	2
#define ADIE	3
#define ADIF	4
#define ADATE	5
#define ADSC	6
#define ADEN	7

/*SFIOR-Special Function IO Register*/
#define ADTS0	5
#define ADTS1	6
#define ADTS2	7

#endif /* ADC_H_ */
