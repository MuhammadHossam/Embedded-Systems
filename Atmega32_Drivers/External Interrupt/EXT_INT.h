/*
 * EXT_INT.h
 *
 *  Created on: May 7, 2020
 *      Author: Muhammad Hossam
 */

#ifndef EXT_INT_H_
#define EXT_INT_H_

#include "GPIO.h"
#include <avr/interrupt.h>

extern void(*p0)(void);   // Declare Pointer to function that takes void and return void...
extern void(*p1)(void);   // Declare Pointer to function that takes void and return void...
extern void(*p2)(void);   // Declare Pointer to function that takes void and return void...
extern void EXT_INIT();  // initialization function for external interrupts
extern void EXT_SET_INTO(void (*ptr0)(void));  // function that takes pointer to function by Application user..
extern void EXT_SET_INT1(void (*ptr1)(void));  // function that takes pointer to function by Application user..
extern void EXT_SET_INT2(void (*ptr2)(void));  // function that takes pointer to function by Application user..

#define INT0_PIN	2
#define INT1_PIN	3
#define INT2_PIN	2

#define INT0_PORT  'D'
#define INT1_PORT  'D'
#define INT2_PORT  'B'

#define EXT_INT0
#define EXT_INT1
#define EXT_INT2

#define INT0_TRIG_TYPE	ANY_LOGICAL_CHANE
#define INT1_TRIG_TYPE	RISING_EDGE
#define INT2_TRIG_TYPE	RISING_EDGE

#define LOW_LEVEL	0
#define ANY_LOGICAL_CHANE 1
#define FALLING_EDGE 2
#define RISING_EDGE 3

#endif /* EXT_INT_H_ */
