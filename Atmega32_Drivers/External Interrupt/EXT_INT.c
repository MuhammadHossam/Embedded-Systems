/*
 * EXT_INT.c
 *
 *  Created on: May 7, 2020
 *      Author: Muhammad Hossam
 */


#include "EXT_INT.h"



void(*p0)(void);   // Declare Pointer to function that takes void and return void...
void(*p1)(void);   // Declare Pointer to function that takes void and return void...
void(*p2)(void);   // Declare Pointer to function that takes void and return void...

void EXT_INIT()
{
	u8 INT0_TYPE = INT0_TRIG_TYPE;
	u8 INT1_TYPE = INT1_TRIG_TYPE;
	u8 INT2_TYPE = INT2_TRIG_TYPE;
	SREG_R |= 0x80;   // Enable SREG [global interrupt Enable]
#ifdef EXT_INT0
	GPIO_u8_WritePinDir(INT0_PIN,0,INT0_PORT);
		switch(INT0_TYPE)
	{
		case LOW_LEVEL:
		{
			MCUCR_R|= 0b00000000;
			GICR_R|= 0b01000000;
			break;
		}
		case ANY_LOGICAL_CHANE:
		{
			MCUCR_R|= 0b00000001;
			GICR_R|= 0b01000000;
			break;
		}
		case FALLING_EDGE:
		{
			MCUCR_R|= 0b00000010;
			GICR_R|= 0b01000000;
			break;
		}
		case RISING_EDGE:
		{
			MCUCR_R|= 0b00000011;
			GICR_R|= 0b01000000;
			break;
		}
	}
#endif
#ifdef EXT_INT1
		GPIO_u8_WritePinDir(INT1_PIN,0,INT1_PORT);
		switch(INT1_TYPE)
	{
		case LOW_LEVEL:
		{
			MCUCR_R|= 0b00000000;
			GICR_R|= 0b10000000;
			break;
		}
		case ANY_LOGICAL_CHANE:
		{
			MCUCR_R|= 0b00000100;
			GICR_R|= 0b10000000;
			break;
		}
		case FALLING_EDGE:
		{
			MCUCR_R|= 0b00001000;
			GICR_R|= 0b10000000;
			break;
		}
		case RISING_EDGE:
		{
			MCUCR_R|= 0b00001100;
			GICR_R|= 0b10000000;
			break;
		}
	}
#endif
#ifdef EXT_INT2
		GPIO_u8_WritePinDir(INT2_PIN,0,INT2_PORT);
		switch(INT2_TYPE)
	{
		case FALLING_EDGE:
		{
			MCUCSR_R|= 0b00000000;
			GICR_R|= 0b00100000;
			break;
		}
		case RISING_EDGE:
		{
			MCUCSR_R|= 0b01000000;
			GICR_R|= 0b00100000;
			break;
		}
	}
#endif
}

/* Interrupt Service Routine */

ISR(INT0_vect)
{
	// Call the function by pointer to function
	p0();

}
ISR(INT1_vect)
{
	// Call the function by pointer to function
	p1();

}
ISR(INT2_vect)
{
	// Call the function by pointer to function
	p2();



}
/* Function that takes pointer to function which will be called by the ISR */
void EXT_SET_INTO(void (*ptr0)(void))
{
	p0=ptr0;
}
/* Function that takes pointer to function which will be called by the ISR */
void EXT_SET_INT1(void (*ptr1)(void))
{
	p1=ptr1;
}
/* Function that takes pointer to function which will be called by the ISR */
void EXT_SET_INT2(void (*ptr2)(void))
{
	p2=ptr2;
}

