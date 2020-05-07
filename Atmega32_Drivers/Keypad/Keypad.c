/*
 * Keypad.c
 *
 *  Created on: May 6, 2020
 *      Author: Muhammad Hossam
 */

#include "keypad.h"
int Key_padRow[] = {R0, R1, R2, R3}; //rows of the keypad
int Key_padCol[] = {C0, C1, C2, C3}; //columns
void  Keypad_init()
{
	/*
	 * set upper part of keypad port as input
	 */
	keypadDDR &= ~ (1<<R0)|(1<<R1)|(1<<R2)|(1<<R3);

	/*set lower part of keypad port as output.
	 * This is the part of the keypad port
	 * where the cols are connected.*/
	keypadDDR |= ((1<<C0)|(1<<C1)|(1<<C2)|(1<<C3));

	/*
	 *	Set all input and output pins HIGH which means that input pins are pull up resistors
	 */
	keypadPORT = 0xFF ;

}



u8 Keypad_getkey()
{
	u8 i, j;
	for(i = 0; i < 4; i++)
	{
		keypadPORT |= ((1<<Key_padCol[0] ) | (1<<Key_padCol[1] ) | (1<<Key_padCol[2] ) | (1<<Key_padCol[3] ));

		keypadPORT &= ~ (1 << Key_padCol[i]);//send a low to a particular row of the keypad
		DELAY_MS(100);
		for(j = 0; j < 4; j++)
		{
			if(!(keypadPIN & (1<<Key_padRow[j])))//check if key is pressed
			{
				while(!(keypadPIN & (1<<Key_padRow[j])));  //wait for key to be released  (Single press)
				switch(i)
				{
				case(0):
                	{
					if (j == 0) return '7';
					else if (j == 1) return '4';
					else if (j == 2) return '1';
					else if (j == 3) return '?';
					break;
                	}
				case(1):
                	{
					if (j == 0) return '8';
					else if (j == 1) return '5';
					else if (j == 2) return '2';
					else if (j == 3) return '0';
					break;
                	}
				case(2):
                	{
					if (j == 0) return '9';
					else if (j == 1) return '6';
					else if (j == 2) return '3';
					else if (j == 3) return '=';
					break;
                	}
				case(3):
                	{
					if (j == 0) return '/';
					else if (j == 1) return '*';
					else if (j == 2) return '-';
					else if (j == 3) return '+';
					break;
                	}
				}
			}
		}
	}
	return 'A';//Return 'A' if no key is pressed.
}


/*
 *  Array of strings to integer function
 */
s32 myAtoi(u8* str)
{
    s32 res = 0; // Initialize result
    s8 sign = 1; // Initialize sign as positive
    u8 i = 0; // Initialize index of first digit

    // If number is negative, then update sign
    if (str[0] == '-') {
        sign = -1;
        i++; // Also update index of first digit
    }

    // Iterate through all digits and update the result
    for (; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    // Return result with sign
    return (s32)sign * res;
}
