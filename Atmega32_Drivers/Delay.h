/*
 * Delay.h
 *
 *  Created on: Apr 25, 2020
 *      Author: Muhammad Hossam
 */

#ifndef DELAY_H_
#define DELAY_H_
#include "Data_Types.h"

// 1MHZ clock means 1000000 cycles per second
// so 1 cycle equals 1/1000000 seconds or 1us
// to get 1 second delay, you need 1000000 cycles
// so it means that you have to DELAY_MS(1000) which means number of cycles (1000000/1000)*1000 = 1000000 cycles = 1sec
// the NOP takes only 1 cycle ....
// and there is an error ratio due to for loop

#define clock 1000000
#define error_ratio 30
u32 DelayCount;
#define DELAY_MS(x) \
	for(DelayCount = ((clock/1000)*x/error_ratio);DelayCount > 0;DelayCount--)\
	{\
		__asm("NOP");\
	}

#endif /* DELAY_H_ */
