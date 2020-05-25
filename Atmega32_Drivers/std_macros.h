/*
 * std_macros.h
 *
 * Created: 4/25/2017 4:00:26 PM
 *  Author: Muhammad Hossam
 */ 


#ifndef STD_MACROS_H_
#define STD_MACROS_H_
#define F_CPU 8000000UL  // 8MHZ clock

#define SETBIT(REG,BIT)  (REG |= 1 << BIT)
#define CLRBIT(REG,BIT)  (REG &= ~(1 << BIT))
#define TOGBIT(REG,BIT)  (REG ^= 1 << BIT)
#define READBIT(REG,BIT)  ((REG >> BIT) & 1)
//#define READBIT(REG,BIT)  (REG&(1<<BIT))
#endif /* STD_MACROS_H_ */
