/*
 * LCD.c
 *
 *  Created on: May 06, 2020
 *      Author: Muhammad Hossam
 */

#include "lcd.h"

/*comment! : LCD INIT */
void LCD_lcd_init(void)
{

	DELAY_MS(20);
	DataDir_LCD_control |= (1<<EN_switch | 1<<ReadWrite | 1<<RS_switch) ; // Set direction output for Control pins
	LCD_control &= ~(1<<EN_switch | 1<<ReadWrite | 1<<RS_switch) ;  // Clear control pins as initialization


#ifdef EIGHT_BIT_MODE
	DataDir_LCD_port = 0xff ;   // Set data Direction
	DELAY_MS(15);
	LCD_clear_screen ();
	LCD_Send_A_Command(LCD_FUNCTION_8BIT_2LINES);

#endif
#ifdef FOUR_BIT_MODE
	DataDir_LCD_port = 0xf0 ;   // Set data Direction
	DELAY_MS(15);
	LCD_clear_screen ();
	LCD_Send_A_Command(0x02);
	LCD_Send_A_Command(LCD_FUNCTION_4BIT_2LINES);

#endif

	LCD_Send_A_Command(LCD_ENTRY_MODE);
	LCD_Send_A_Command(LCD_BEGIN_AT_FIRST_RAW);
	LCD_Send_A_Command(LCD_DISP_ON_CURSOR_BLINK);

}

/*comment! : LCD Clear Screen*/

u8 LCD_clear_screen ()
{
	LCD_Send_A_Command(LCD_CLEAR_SCREEN); // clear the screen
	return No_error;
}

/*comment! : Goto a certain position in the LCD */
u8 LCD_GotoXY(u8 line, u8 position )
{

	if(line==0)
	{
		if (position < 16 && position >=0)
			LCD_Send_A_Command(0x80+position);
	}
	else if (line==1)
	{
		if (position < 16 && position >=0)
			LCD_Send_A_Command(0xc0 + position);
	}
	return No_error;
}




/*comment! : Check lcd is busy */

u8 LCD_check_lcd_isbusy()
{
	static u8 x = 0;
	DataDir_LCD_port &= ~(0xff<<DATA_shift) ;
	LCD_control |= (1<<ReadWrite); // read
	LCD_control &= ~ (1<<RS_switch);

	DataDir_LCD_port = 0xFF; //0xFF means 0b11111111
	LCD_control &= ~ (1<<ReadWrite); //write

	return No_error;
}



/*comment! : Set the Enable pin from High to low pulse in minimum 230 ns to latch the data */

u8 LCD_lcd_kick ()
{
	LCD_control |= 1<<EN_switch;
	asm volatile ("nop");
	asm volatile ("nop");
	DELAY_MS (50) ;
	LCD_control &= ~ (1<<EN_switch);
	return No_error;
}


/*comment! : Send a command to LCD controller */

u8 LCD_Send_A_Command(u8 command)
{
#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();

	LCD_port = command  ;
	LCD_control &= ~ ((1<<ReadWrite)|(1<<RS_switch));
	LCD_lcd_kick ();
	//LCD_port = 0;
#endif
#ifdef FOUR_BIT_MODE
	LCD_check_lcd_isbusy();

	LCD_port = (LCD_port & 0x0F) | (command & 0xF0);
	LCD_control &= ~ ((1<<ReadWrite)|(1<<RS_switch));
	LCD_lcd_kick ();
	LCD_port = (LCD_port & 0x0F) | (command << 4);
	LCD_control &= ~ ((1<<ReadWrite)|(1<<RS_switch));
	LCD_lcd_kick ();
#endif

	return No_error;
}


/*comment! : Send a character to LCD controller */

u8 LCD_Send_A_Character(u8 character)
{

#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();

	LCD_control |= 1<<RS_switch; //turn RS ON for Data mode.
	LCD_control &= ~ (1<<ReadWrite);//turn RW off so you can write.
	LCD_port = ( ( (character  ) << DATA_shift)   )  ;

	LCD_lcd_kick ();
	//LCD_port = 0;
#endif

#ifdef FOUR_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_control |= 1<<RS_switch; //turn RS ON for Data mode.
	LCD_control &= ~ (1<<ReadWrite);//turn RW off so you can write.
	LCD_port = (LCD_port & 0x0F) | (character & 0xF0);

	LCD_lcd_kick ();
	LCD_port = (LCD_port & 0x0F) | (character << 4);

	LCD_lcd_kick ();

#endif

	return No_error;

}

/*comment! : Send a string to LCD controller */

u8 LCD_Send_A_String(u8 *StringOfCharacters)
{


	int count=0 ;//to count how much char on the line (it should be 16 char only)
	while(*StringOfCharacters > 0)
	{
		count++;
		LCD_Send_A_Character(*StringOfCharacters++);
		if (count == 16  ) // go to the second line
		{
			LCD_GotoXY(1,0); //line 1 position zero
		}
		else if (count == 32 || count==33) // clear screen and show again
		{
			LCD_clear_screen();
			LCD_GotoXY(0,0); //line 0 position zero
			count = 0 ;
		}
	}
	return No_error;
}


/*comment! : Display a number to LCD */

u8 LCD_display_number (u16 Number )
{

	u8 str[7];

	sprintf((char*)str,"%d",Number);	// Adjust the formatting to your liking.

	LCD_Send_A_String (str) ;

	return No_error;
}

/*comment! : Display a real number to LCD */

u8 LCD_display_real_number (f64  Number )
{

	u8 str[16];
	u8 *tmpSign = (Number < 0) ? (u8 *)"-" : (u8 *)"";
	f32 tmpVal = (Number < 0) ? -Number : Number;

	s16 tmpInt1 = tmpVal;                  // Get the integer (678).
	f32 tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
	s16 tmpInt2 = tmpFrac * 10000;  // Turn into integer (123).

	// Print as parts, note that you need 0-padding for fractional bit.

	sprintf ((char*)str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);


	LCD_Send_A_String (str) ;

	return No_error;
}
