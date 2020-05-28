/*
 * USART.c
 *
 *  Created on: May 28, 2020
 *      Author: Muhammad Hossam
 */


#include "USART.h"
/******************Pointer to functions to be assigned to ISR*******************/

static void (*Ptr_To_Trans_Int) (void);
static void (*Ptr_To_Rec_Int) (void);
static void (*Ptr_To_UDRE_Int) (void);

struct USART_Config	Configuration ;


/*********************************/
 void USART_Init(struct USART_Config Config) {

	u16 UBRR_VAL ;
	Configuration = Config ;

	/*Comment: USART Sync Mode*/
	if(Configuration.SYNCH_MODE == USART_ASYNCH)
	{
		UCSRC_R &= ~(1<<UMSEL);
	}
	else if(Configuration.SYNCH_MODE == USART_SYNC)
	{
		UCSRC_R |=  (1<<UMSEL);
	}


	/*USART Speed Mode*/
	if(Configuration.SPEED_MODE ==  USART_NORMAL_SPEED)
	{
		UCSRA_R &= ~(1<<U2X);
	}
	else if((Configuration.SPEED_MODE == USART_DOUBLE_SPEED) && (Configuration.SYNCH_MODE == USART_ASYNCH))
	{
		UCSRA_R |= (1<<U2X);
	}

	/************** Enable/Disable transmitter **************/
	if(Configuration.TRANSMIT == USART_TRANSMIT_DISABLE)
	{
		UCSRB_R &= ~(1<<TXEN);
	}
	else if(Configuration.TRANSMIT == USART_TRANSMIT_ENABLE)
	{
		UCSRB_R |= (1<<TXEN);
	}

	/************** Enable/Disable Receiver **************/
	if(Configuration.RECEIVE == USART_RECEIVE_DISABLE)
	{
		UCSRB_R &= ~(1<<RXEN);
	}
	else if(Configuration.RECEIVE == USART_RECEIVE_ENABLE)
	{
		UCSRB_R |= (1<<RXEN);
	}


	/*USART Data Frame Size 5-9 bits*/
	if(Configuration.CHAR_SIZE == USART_5_Bit_CHAR )
	{
		UCSRC_R &= ~(1<<UCSZ0);
		UCSRC_R &= ~(1<<UCSZ1);
		UCSRB_R &= ~(1<<UCSZ2);
		// ALL bits are zeros
	}
	else if(Configuration.CHAR_SIZE == USART_6_Bit_CHAR )
	{
		UCSRC_R |= (1<<UCSZ0);
		UCSRC_R &= ~(1<<UCSZ1);
		UCSRB_R &= ~(1<<UCSZ2);
	}
	else if(Configuration.CHAR_SIZE == USART_7_Bit_CHAR )
	{
		UCSRC_R &= ~(1<<UCSZ0);
		UCSRC_R |=  (1<<UCSZ1);
		UCSRB_R &= ~(1<<UCSZ2);
	}
	else if(Configuration.CHAR_SIZE == USART_8_Bit_CHAR )
	{
		UCSRC_R |=  (1<<UCSZ0);
		UCSRC_R |=  (1<<UCSZ1);
		UCSRB_R &= ~(1<<UCSZ2);
	}
	else if(Configuration.CHAR_SIZE == USART_9_Bit_CHAR )
	{
		UCSRC_R |=  (1<<UCSZ0);
		UCSRC_R |=  (1<<UCSZ1);
		UCSRB_R |=  (1<<UCSZ2);
	}



	/*USART Parity bits*/
	if(Configuration.PARITY_MODE == USART_NO_PARITY)
	{
		UCSRC_R &= ~(1<<UPM0);
		UCSRC_R &= ~(1<<UPM1);
	}
	else if(Configuration.PARITY_MODE == USART_EVEN_PARITY)
	{
		UCSRC_R &= ~(1<<UPM0);
		UCSRC_R |=  (1<<UPM1);
	}
	else if(Configuration.PARITY_MODE == USART_ODD_PARITY)
	{
		UCSRC_R |=  (1<<UPM0);
		UCSRC_R |=  (1<<UPM1);
	}


	/*********************USART Stop Bits**************************/
	if(Configuration.STOPBIT == USART_1_STOPBIT)
	{
		UCSRC_R &= ~(1<<USBS);
	}
	else if(Configuration.STOPBIT == USART_2_STOPBIT)
	{
		UCSRC_R |=  (1<<USBS);
	}


	/*Transmitter Interrupt Enable/Disable */
	if(Configuration.TRANSMITER_INT == USART_TRANSMITER_ENABLE)
	{
		UCSRB_R |= (1<<TXCIE);
	}
	else if(Configuration.TRANSMITER_INT == USART_TRANSMITER_DISABLE)
	{
		UCSRB_R &= ~(1<<TXCIE);
	}

	/*Receiver Interrupt Enable/Disable*/
	if(Configuration.RECEIVE_INT == USART_RECIEVER_ENABLE)
	{
		UCSRB_R |= (1<<RXCIE);
	}
	else if(Configuration.RECEIVE_INT == USART_RECIEVER_DISABLE)
	{
		UCSRB_R &= ~(1<<RXCIE);
	}


	/*USART Data Register Empty Interrupt Enable/Disable*/
	if(Configuration.UDRE_INT == USART_UDRE_DISABLE)
	{
		UCSRB_R &= ~(1<<UDRIE);
	}
	else if(Configuration.UDRE_INT == USART_UDRE_ENABLE)
	{
		UCSRB_R |=  (1<<UDRIE);
	}


	/************** Set baud rate **************/
	if ((Configuration.SYNCH_MODE == USART_ASYNCH) && (Configuration.SPEED_MODE == USART_NORMAL_SPEED))
	{
		UBRR_VAL = (u16)((USART_FOSC/(16*USART_BAUD))-1) ;
	}
	else if ((Configuration.SYNCH_MODE == USART_ASYNCH) && (Configuration.SPEED_MODE == USART_DOUBLE_SPEED))
	{
		UBRR_VAL = (u16)((USART_FOSC/(8*USART_BAUD))-1) ;

	}
	else if  ((Configuration.SYNCH_MODE == USART_SYNC))
	{
		UBRR_VAL = (u16)((USART_FOSC/(2*USART_BAUD))-1) ;

	}

	/********************* Synchronous Mode Clock Polarity***************************/
	if ((Configuration.SYNCH_MODE == USART_SYNC) && (Configuration.CLK_POL == RISING_TX_FALLING_RX))
	{
		UCSRC_R &= ~(1<<UCPOL);
	}
	else if ((Configuration.SYNCH_MODE == USART_SYNC) && (Configuration.CLK_POL == FALLING_TX_RISING_RX))
	{
		UCSRC_R |=  (1<<UCPOL);
	}




	UBRRH_R =(u8) (UBRR_VAL >> 8);

	UBRRL_R = (u8) UBRR_VAL;

}



 void USART_Transmit(u16 data) {
	/* Wait for empty transmit buffer */
	while (!( UCSRA_R & (1 << UDRE)))
		;
	/***********if the data to be transmitted is 9 bits, write the MSB first*****************/
	if ( Configuration.CHAR_SIZE  ==	USART_9_Bit_CHAR )
	{
		UCSRB_R |= ((data >> 8) & 1);
	}
		/* Put data into buffer, sends the data */
	UDR = (u8)data;
}




 u8 USART_Receive(u16 *Ptr_To_Val) {
	u8 local_u8ParityError = 0;  // 0 means error
	*Ptr_To_Val = 0;
	/* Wait for data to be received */
	while (!(UCSRA_R & (1 << RXC)) )
		;
	/****************Check if parity error is not ON********/
	if(((UCSRA_R >> PE)& 1) != 1)
	{/***********if the data to be recieved is 9 bits, get the MSB first*****************/
	if (Configuration.CHAR_SIZE  ==	USART_9_Bit_CHAR)
	{
		*Ptr_To_Val = (((UCSRB_R >> 1)& 1) << 8) ;
	}

		/* Get and return received data from buffer */
		*Ptr_To_Val |= UDR;
		local_u8ParityError = 1; //no error
	}
	return local_u8ParityError;

}




 void USART_Rec_Int_Enable(void)
{
	UCSRB |= 1<< RXCIE ;

}

 void USART_Rec_Int_Disable(void)
{
	UCSRB &= ~(1<<RXCIE);
}




 void USART_Trans_Int_Enable(void)
{
	UCSRB |= 1<< TXCIE ;
}


 void USART_Trans_Int_Disable(void)
{
	UCSRB &= ~ (1<<TXCIE);

}



 void USART_Rec_Enable(void)
{
	UCSRB |= 1<< RXEN ;

}

 void USART_Rec_Disable(void)
{
	UCSRB &=~(1<<RXEN);

}





 void USART_Trans_Enable(void)
{
	UCSRB |= 1<<TXEN;
}

 void USART_Trans_Disable(void)
{
	UCSRB &= ~ (1<<TXEN) ;
}





 void USART_callback_Rec_Int(void (*Ptr_to_Func)(void))
{
	Ptr_To_Rec_Int = Ptr_to_Func;
}
 void USART_callback_Trans_Int(void (*Ptr_to_Func)(void))
{
	Ptr_To_Trans_Int = Ptr_to_Func;
}
 void USART_callback_UDRE_Int(void (*Ptr_to_Func)(void))
{
	 Ptr_To_UDRE_Int = Ptr_to_Func;
}


ISR(__vector_13)
{
	Ptr_To_Rec_Int();
}

ISR(__vector_14)
{
	Ptr_To_UDRE_Int();
}

ISR(__vector_15)
{
	Ptr_To_Trans_Int();
}




