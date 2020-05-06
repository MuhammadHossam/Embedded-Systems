/*
 * ATMEGA32_registers.h
 *
 *  Created on: Apr 25, 2020
 *      Author: Muhammad Hossam
 */

#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_


#define SREG_R *((volatile unsigned char* const)0x5F)
#define SPH_R *((volatile unsigned char* const)0x5E)
#define SPL_R *((volatile unsigned char* const)0x5D)
#define OCR0_R *((volatile unsigned char* const)0x5C)
#define GICR_R *((volatile unsigned char* const)0x5B)
#define GIFR_R *((volatile unsigned char* const)0x5A)
#define TIMSK_R *((volatile unsigned char* const)0x59)
#define TIFR_R *((volatile unsigned char* const)0x58)
#define SPMCR_R *((volatile unsigned char* const)0x57)
#define TWCR_R *((volatile unsigned char* const)0x56)
#define MCUCR_R *((volatile unsigned char* const)0x55)
#define MCUCSR_R *((volatile unsigned char* const)0x54)
#define TCCR0_R *((volatile unsigned char* const)0x53)
#define TCNT0_R *((volatile unsigned char* const)0x52)
#define OSCCAL_R *((volatile unsigned char* const)0x51)
#define OCDR_R *((volatile unsigned char* const)0x51)
#define SFIOR_R *((volatile unsigned char* const)0x50)
#define TCCR1A_R *((volatile unsigned char* const)0x4F)
#define TCCR1B_R *((volatile unsigned char* const)0x54E)
#define TCNT1H_R *((volatile unsigned char* const)0x4D)
#define TCNT1L_R *((volatile unsigned char* const)0x4C)
#define OCR1AH_R *((volatile unsigned char* const)0x4B)
#define OCR1AL_R *((volatile unsigned char* const)0x4A)
#define OCR1BH_R *((volatile unsigned char* const)0x49)
#define OCR1BL_R *((volatile unsigned char* const)0x48)
#define ICR1H_R *((volatile unsigned char* const)0x47)
#define ICR1L_R *((volatile unsigned char* const)0x46)
#define TCCR2_R *((volatile unsigned char* const)0x45)
#define TCNT2_R *((volatile unsigned char* const)0x44)
#define OCR2_R *((volatile unsigned char* const)0x43)
#define ASSR_R *((volatile unsigned char* const)0x42)
#define WDTCR_R *((volatile unsigned char* const)0x41)
#define UBRRH_R *((volatile unsigned char* const)0x40)
#define UCSRC_R *((volatile unsigned char* const)0x40)
#define EEARH_R *((volatile unsigned char* const)0x3F)
#define EEARL_R *((volatile unsigned char* const)0x3E)
#define EEDR_R *((volatile unsigned char* const)0x3D)
#define EECR_R *((volatile unsigned char* const)0x3C)
#define GPIOA_PORT ((volatile unsigned char* const)0x3B)
#define GPIOA_DDR  ((volatile unsigned char* const)0x3A)
#define GPIOA_PIN  ((volatile unsigned char* const)0x39)
#define GPIOB_PORT ((volatile unsigned char* const)0x38)
#define GPIOB_DDR  ((volatile unsigned char* const)0x37)
#define GPIOB_PIN  ((volatile unsigned char* const)0x36)
#define GPIOC_PORT ((volatile unsigned char* const)0x35)
#define GPIOC_DDR  ((volatile unsigned char* const)0x34)
#define GPIOC_PIN  ((volatile unsigned char* const)0x33)
#define GPIOD_PORT ((volatile unsigned char* const)0x32)
#define GPIOD_DDR  ((volatile unsigned char* const)0x31)
#define GPIOD_PIN  ((volatile unsigned char* const)0x30)
#define SPDR_R *((volatile unsigned char* const)0x2F)
#define SPSR_R *((volatile unsigned char* const)0x2E)
#define SPCR_R *((volatile unsigned char* const)0x2D)
#define UDR_R *((volatile unsigned char* const)0x2C)
#define UCSRA_R *((volatile unsigned char* const)0x2B)
#define UCSRB_R *((volatile unsigned char* const)0x2A)
#define UBRRL_R *((volatile unsigned char* const)0x29)
#define ACSR_R *((volatile unsigned char* const)0x28)
#define ADMUX_R *((volatile unsigned char* const)0x27)
#define ADCSRA_R *((volatile unsigned char* const)0x26)
#define ADCH_R *((volatile unsigned char* const)0x25)
#define ADCL_R *((volatile unsigned char* const)0x24)
#define TWDR_R *((volatile unsigned char* const)0x23)
#define TWAR_R *((volatile unsigned char* const)0x22)
#define TWSR_R *((volatile unsigned char* const)0x21)
#define TWBR_R *((volatile unsigned char* const)0x20)




#endif /* ATMEGA32_REGISTERS_H_ */
