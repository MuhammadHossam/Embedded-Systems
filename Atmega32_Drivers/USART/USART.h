/*
 * USART.h
 *
 *  Created on: May 28, 2020
 *      Author: Muhammad Hossam
 */

#ifndef USART_H_
#define USART_H_
#include "GPIO.h"
#include <avr/interrupt.h>
//Configuration
#define USART_BAUD				1200		// USART baud rate
#define USART_FOSC				1000000     // System Oscillator clock frequency

/* Comment: USART Synch mode or Async mode*/
enum USART_SYNCH_MODE
{
	USART_ASYNCH,
	USART_SYNC
};

/* Comment: USART Speed Mode*/
enum USART_SPEED_MODE
{
	USART_NORMAL_SPEED,
	USART_DOUBLE_SPEED
};

/* Comment: USART Transmit Enable/Disable*/
enum USART_TRANSMIT
{
	USART_TRANSMIT_DISABLE,
	USART_TRANSMIT_ENABLE
};

/* Comment: USART Receive Enable/Disable*/
enum USART_RECEIVE
{
	USART_RECEIVE_DISABLE,
	USART_RECEIVE_ENABLE
};

/* Comment: USART Char Size */
enum USART_CHAR_SIZE
{
	USART_5_Bit_CHAR,
	USART_6_Bit_CHAR,
	USART_7_Bit_CHAR,
	USART_8_Bit_CHAR,
	USART_9_Bit_CHAR
};

/* Comment: USART Parity Mode*/
enum USART_PARITY_MODE
{
	USART_NO_PARITY,
	USART_EVEN_PARITY,
	USART_ODD_PARITY
};

/* Comment: USART Stop Bit*/
enum USART_STOPBIT
{
	USART_1_STOPBIT,
	USART_2_STOPBIT
};

/* Comment: USART Receive Interrupt Enable*/
enum USART_RECEIVE_INTTERRUPT
{
	USART_RECIEVER_DISABLE,
	USART_RECIEVER_ENABLE
};

/* Comment: USART Transmit Interrupt Enable*/
enum USART_TRANSMITER_INTERRUPT
{
	USART_TRANSMITER_DISABLE,
	USART_TRANSMITER_ENABLE
};

enum USART_DATA_REG_EMPTY_INTTERUPT_EN
{
	USART_UDRE_DISABLE,
	USART_UDRE_ENABLE
};

enum USART_SYNC_CLK_POL{
	RISING_TX_FALLING_RX,
	FALLING_TX_RISING_RX
};
struct USART_Config
{
	enum USART_SYNCH_MODE SYNCH_MODE ;
	enum USART_SPEED_MODE SPEED_MODE;
	enum USART_TRANSMIT TRANSMIT;
	enum USART_RECEIVE RECEIVE;
	enum USART_CHAR_SIZE CHAR_SIZE ;
	enum USART_PARITY_MODE PARITY_MODE;
	enum USART_STOPBIT STOPBIT;
	enum USART_RECEIVE_INTTERRUPT RECEIVE_INT;
	enum USART_TRANSMITER_INTERRUPT TRANSMITER_INT;
	enum USART_DATA_REG_EMPTY_INTTERUPT_EN UDRE_INT;
	enum USART_SYNC_CLK_POL CLK_POL;
};

///////////////////////////////////APIs
void USART_Init(struct USART_Config Config);
void USART_Transmit(u16 data);
u8 USART_Receive(u16 *Ptr_To_Val);
void USART_Rec_Int_Enable(void);
void USART_Rec_Int_Disable(void);
void USART_Trans_Int_Enable(void);
void USART_Trans_Int_Disable(void);
void USART_Rec_Enable(void);
void USART_Rec_Disable(void);
void USART_Trans_Enable(void);
void USART_Trans_Disable(void);
void USART_callback_Rec_Int(void (*Ptr_to_Func)(void));
void USART_callback_Trans_Int(void (*Ptr_to_Func)(void));
void USART_callback_UDRE_Int(void (*Ptr_to_Func)(void));

/********************************Registers***********************************/


/**********************UCSRA************************/
#define RXC 	7
#define TXC 	6
#define UDRE 	5
#define FE 		4
#define DOR		3
#define PE 		2
#define U2X		1
#define MPCM	0

/**********************UCSRB************************/
#define RXCIE 	7
#define TXCIE	6
#define UDRIE	5
#define RXEN 	4
#define TXEN	3
#define UCSZ2	2
#define RXB8	1
#define TXB8	0

/**********************UCSRC************************/
#define URSEL	7
#define UMSEL	6
#define UPM1	5
#define UPM0	4
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UCPOL	0



#endif /* USART_H_ */
