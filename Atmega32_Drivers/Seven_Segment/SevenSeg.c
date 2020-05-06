/*
 * SevenSeg.c
 *
 *  Created on: Apr 25, 2020
 *      Author: Muhammad Hossam
 */

#include "SevenSeg.h"


/* Global Variables to be Store the PORT and pin index of every seven segment pin*/
u8 SEGA_PORT;
u8 SEGB_PORT;
u8 SEGC_PORT;
u8 SEGD_PORT;
u8 EN1_PORT;
u8 EN2_PORT;
u8 SEGA_PinIndex;
u8 SEGB_PinIndex;
u8 SEGC_PinIndex;
u8 SEGD_PinIndex;
u8 EN1_PinIndex;
u8 EN2_PinIndex;

//=====================Initialization=======================
/*comment! : Initialization Function */
void SEV_SEG_voidInit(void)
{
	u8 Port_num, Pin_Index;
	Port_num = SEG_A/8;
	Pin_Index = SEG_A%8;
	switch(Port_num)
	{
	case 0:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'A');
		SEGA_PORT = 'A';
		SEGA_PinIndex = Pin_Index;
		break;
	}
	case 1:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'B');
		SEGA_PORT = 'B';
		SEGA_PinIndex = Pin_Index;
		break;
	}
	case 2:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'C');
		SEGA_PORT = 'C';
		SEGA_PinIndex = Pin_Index;
		break;
	}
	case 3:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'D');
		SEGA_PORT = 'D';
		SEGA_PinIndex = Pin_Index;
		break;
	}
	}

	Port_num = SEG_B/8;
	Pin_Index = SEG_B%8;
	switch(Port_num)
	{
	case 0:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'A');
		SEGB_PORT = 'A';
		SEGB_PinIndex = Pin_Index;
		break;
	}
	case 1:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'B');
		SEGB_PORT = 'B';
		SEGB_PinIndex = Pin_Index;
		break;
	}
	case 2:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'C');
		SEGB_PORT = 'C';
		SEGB_PinIndex = Pin_Index;
		break;
	}
	case 3:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'D');
		SEGB_PORT = 'D';
		SEGB_PinIndex = Pin_Index;
		break;
	}
	}

	Port_num = SEG_C/8;
	Pin_Index = SEG_C%8;
	switch(Port_num)
	{
	case 0:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'A');
		SEGC_PORT = 'A';
		SEGC_PinIndex = Pin_Index;
		break;
	}
	case 1:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'B');
		SEGC_PORT = 'B';
		SEGC_PinIndex = Pin_Index;
		break;
	}
	case 2:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'C');
		SEGC_PORT = 'C';
		SEGC_PinIndex = Pin_Index;
		break;
	}
	case 3:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'D');
		SEGC_PORT = 'D';
		SEGC_PinIndex = Pin_Index;
		break;
	}
	}

	Port_num = SEG_D/8;
	Pin_Index = SEG_D%8;
	switch(Port_num)
	{
	case 0:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'A');
		SEGD_PORT = 'A';
		SEGD_PinIndex = Pin_Index;
		break;
	}
	case 1:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'B');
		SEGD_PORT = 'B';
		SEGD_PinIndex = Pin_Index;
		break;
	}
	case 2:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'C');
		SEGD_PORT = 'C';
		SEGD_PinIndex = Pin_Index;
		break;
	}
	case 3:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'D');
		SEGD_PORT = 'D';
		SEGD_PinIndex = Pin_Index;
		break;
	}
	}

	Port_num = SEV_SEG_EN1/8;
	Pin_Index = SEV_SEG_EN1%8;
	switch(Port_num)
	{
	case 0:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'A');
		EN1_PORT = 'A';
		EN1_PinIndex = Pin_Index;
		break;
	}
	case 1:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'B');
		EN1_PORT = 'B';
		EN1_PinIndex = Pin_Index;
		break;
	}
	case 2:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'C');
		EN1_PORT = 'C';
		EN1_PinIndex = Pin_Index;
		break;
	}
	case 3:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'D');
		EN1_PORT = 'D';
		EN1_PinIndex = Pin_Index;
		break;
	}
	}


	Port_num = SEV_SEG_EN2/8;
	Pin_Index = SEV_SEG_EN2%8;
	switch(Port_num)
	{
	case 0:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'A');
		EN2_PORT = 'A';
		EN2_PinIndex = Pin_Index;
		break;
	}
	case 1:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'B');
		EN2_PORT = 'B';
		EN2_PinIndex = Pin_Index;
		break;
	}
	case 2:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'C');
		EN2_PORT = 'C';
		EN2_PinIndex = Pin_Index;
		break;
	}
	case 3:
	{
		GPIO_u8_WritePinDir(Pin_Index,1,'D');
		EN2_PORT = 'D';
		EN2_PinIndex = Pin_Index;
		break;
	}
	}
}

/*Comment!: Enable the First Seven Segment*/
u8 SEV_SEG_u8_EN1(void)
{
	GPIO_u8_WritePinVal(EN1_PinIndex,1,EN1_PORT);
	return No_error;
}

/*Comment!: Enable the Second Seven Segment*/
u8 SEV_SEG_u8_EN2(void)
{
	GPIO_u8_WritePinVal(EN2_PinIndex,1,EN2_PORT);
	return No_error;
}


/*Comment!: Disble the First Seven Segment*/
u8 SEV_SEG_u8_DIS1(void)
{
	GPIO_u8_WritePinVal(EN1_PinIndex,0,EN1_PORT);
	return No_error;
}

/*Comment!: Disable the Second Seven Segment*/
u8 SEV_SEG_u8_DIS2(void)
{
	GPIO_u8_WritePinVal(EN2_PinIndex,0,EN2_PORT);
	return No_error;
}

/*Comment! : Write on the First Seven Segment*/
u8 SEV_SEG_1_u8_WriteVal(u8 count)
{
	SEV_SEG_u8_EN1();
	SEV_SEG_u8_DIS2();
	SEV_SEG_u8_A(READBIT(count,0));
	SEV_SEG_u8_B(READBIT(count,1));
	SEV_SEG_u8_C(READBIT(count,2));
	SEV_SEG_u8_D(READBIT(count,3));
	return No_error;

}

/*Comment! : Write on the Second Seven Segment*/
u8 SEV_SEG_2_u8_WriteVal(u8 count)
{
	SEV_SEG_u8_EN2();
	SEV_SEG_u8_DIS1();
	SEV_SEG_u8_A(READBIT(count,0));
	SEV_SEG_u8_B(READBIT(count,1));
	SEV_SEG_u8_C(READBIT(count,2));
	SEV_SEG_u8_D(READBIT(count,3));
	return No_error;

}

/*Comment! : Write the Value on SEG_A*/
u8 SEV_SEG_u8_A(u8 BIT)
{
   if(BIT==0)
   {
	   GPIO_u8_WritePinVal(SEGA_PinIndex,0,SEGA_PORT);
   }
   else
   {
	   GPIO_u8_WritePinVal(SEGA_PinIndex,1,SEGA_PORT);
   }
   return No_error;
}

/*Comment! : Write the Value on SEG_B*/
u8 SEV_SEG_u8_B(u8 BIT)
{
	 if(BIT==0)
     {
	   GPIO_u8_WritePinVal(SEGB_PinIndex,0,SEGB_PORT);
     }
	  else
     {
	   GPIO_u8_WritePinVal(SEGB_PinIndex,1,SEGB_PORT);
     }
	 return No_error;
}

/*Comment! : Write the Value on SEG_C*/
u8 SEV_SEG_u8_C(u8 BIT)
{
	   if(BIT==0)
	   {
		   GPIO_u8_WritePinVal(SEGC_PinIndex,0,SEGC_PORT);
	   }
	   else
	   {
		   GPIO_u8_WritePinVal(SEGC_PinIndex,1,SEGC_PORT);
	   }
	   return No_error;
}

/*Comment! : Write the Value on SEG_D*/
u8 SEV_SEG_u8_D(u8 BIT)
{
	   if(BIT==0)
	   {
		   GPIO_u8_WritePinVal(SEGD_PinIndex,0,SEGD_PORT);
	   }
	   else
	   {
		   GPIO_u8_WritePinVal(SEGD_PinIndex,1,SEGD_PORT);
	   }
	   return No_error;
}


/*Comment! : Count UP in Seven Seg*/
u8 SEV_SEG_1_u8_COUNT_UP(void)
{
	u8 i;
	for(i=0;i<10;i++)
	{
		SEV_SEG_1_u8_WriteVal(i);
		DELAY_MS(1000);
	}
	return No_error;

}

/*Comment! : Count UP in Seven Seg*/
u8 SEV_SEG_2_u8_COUNT_UP(void)
{
	u8 i;
	for(i=0;i<10;i++)
	{
		SEV_SEG_2_u8_WriteVal(i);
		DELAY_MS(1000);
	}
	return No_error;

}


/*Comment! : Display Two numbers*/
u8 SEV_SEG_2Num_u8(u8 Count)
{
	u8 temp;
	temp=Count%10;
	SEV_SEG_1_u8_WriteVal(temp);
	DELAY_MS(2);
	temp=Count/10;
	SEV_SEG_2_u8_WriteVal(temp);
	DELAY_MS(2);
	return No_error;
}



