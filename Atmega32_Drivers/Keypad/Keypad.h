/*
 * Keypad.h
 *
 *  Created on: May 6, 2020
 *      Author: Muhammad Hossam
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_



#include "GPIO.h"



//Keypad Information
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define keypadPORT *GPIOD_PORT
#define keypadPIN *GPIOD_PIN
#define keypadDDR *GPIOD_DDR


//Keypad functions and global variables


extern void  Keypad_init();
extern u8 Keypad_getkey();
extern s32 myAtoi(u8* str);



#endif /* KEYPAD_H_ */
