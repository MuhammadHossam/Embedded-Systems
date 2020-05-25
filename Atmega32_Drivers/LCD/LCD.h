/*
 * LCD.h
 *
 *  Created on: May 06, 2020
 *      Author: Muhammad Hossam
 */

#ifndef DRIVERS_LCD_LCD_H_
#define DRIVERS_LCD_LCD_H_


#include "GPIO.h"


//#define LCD_port *(GPIOA_PORT)
#define LCD_PORT 'A'
//#define DataDir_LCD_port *(GPIOA_DDR)
#define DATA_shift 0    //0:4bit data mode | 4:4bit data mode
#define LCD_control_PORT 'B'
//#define LCD_control *(GPIOB_PORT)
//#define DataDir_LCD_control *(GPIOB_DDR)
#define EN_switch 4
#define ReadWrite 2
#define RS_switch 0
#define LCD_DATA_PORT 'A'

//#define	EIGHT_BIT_MODE
#define FOUR_BIT_MODE



#define LCD_REGISTER_SELECT_PIN						(0)
#define LCD_READ_WRITE_PIN							(1)
#define LCD_ENABLE_PIN								(2)
#define LCD_REGISTER_SELECT_ENABLE					(1)
#define LCD_REGISTER_SELECT_DISABLE					(0)
#define READ_FROM_LCD								(1)
#define WRITE_TO_LCD								(0)
#define LCD_ENABLE									(1)
#define LCD_DISABLE									(0)
#define LCD_FIRST_LINE								(0)
#define LCD_SECOND_LINE								(1)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_RAW						(0x80)
#define LCD_BEGIN_AT_SECOND_RAW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

/*comment! : Check lcd is busy */
extern u8 LCD_check_lcd_isbusy(void);

/*comment! : Set the Enable pin from High to low pulse in minimum 230 ns to latch the data */
extern u8 LCD_lcd_kick (void);

/*comment! : Send a Command to LCD controller */
extern u8 LCD_Send_A_Command(u8 command);

/*comment! : Send a Character to LCD controller */
extern u8 LCD_Send_A_Character(u8 character);

/*comment! : Send a string to LCD controller */
extern u8 LCD_Send_A_String(u8 *string);

/*comment! : LCD Initialization */
extern void LCD_lcd_init(void);

/*comment! : Clear LCD */
extern u8 LCD_clear_screen ();

/*comment! : Goto a certain position in the LCD */
extern u8 LCD_GotoXY(u8 line, u8 position );

/*comment! : Display a number to LCD */
extern u8 LCD_display_number (u16 Number );

/*comment! : Display a real number to LCD */
extern u8 LCD_display_real_number (f64  Number );

#endif /* DRIVERS_LCD_LCD_H_ */
