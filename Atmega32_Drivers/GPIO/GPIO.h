/*
 * GPIO.h
 *
 *  Created on: Apr 25, 2020
 *      Author: Muhammad Hossam
 */


#ifndef GPIO_H_
#define GPIO_H_
#include "DATA_Types.h"
#include "ATMEGA32_registers.h"
#include "std_macros.h"
#include "Delay.h"
#include <stdlib.h>
#include <stdio.h>

extern volatile unsigned char* GPIO_ports[];
extern volatile unsigned char* GPIO_dirs[];
extern volatile unsigned char* GPIO_pins[];

#define u8_Direction_input 0x00
#define u8_Direction_output 0xFF

// choose the default initialization for GPIO
// initialize the pins by zeros or ones

#define Init_direction_default u8_Direction_input
#define no_of_pins_on_port 8

//=====================Initialization=======================
/*comment! : Initialization Function */
void GPIO_voidInit(void);
//==========================================================

//======================PIN=================================
//Data
/*comment!: Read Pin Value */
extern u8 GPIO_u8_ReadPinVal(u8 PinIdx,u8* PtrToVal,u8 Port_Name);

/*comment!: Read Pin Value Long Pressed*/
extern u8 GPIO_u8_ReadPinVal_LONG_PRESS(u8 PinIdx,u8* PtrToVal,u8 Port_Name);

/*Comment!: Write Pin Value */
extern u8 GPIO_u8_WritePinVal(u8 PinIdx,u8 PinVal, u8 Port_Name);

//Direction
/*Comment!: Write Pin Direction */
extern u8 GPIO_u8_WritePinDir(u8 PinIdx,u8 PinDir, u8 Port_Name);

/*comment!: Read Pin Direction */
extern u8 GPIO_u8_ReadPinDir(u8 PinIdx,u8* PtrToDir,u8 Port_Name);

//========================PORT===============================
//Data
/*Comment! : Read Port Value*/
extern u8 GPIO_u8_ReadPortVal(u8* PtrToVal, u8 Port_Name);

/*Comment! : Write Port Value*/
extern u8 GPIO_u8_WritePortVal(u8 PortVal, u8 Port_Name);

//Direction
/*Comment! : Write Port Direction*/
extern u8 GPIO_u8_WritePortDir(u8 PortDir, u8 Port_Name);

/*Comment! : Read Port Direction*/
extern u8 GPIO_u8_ReadPortDir(u8* PtrToDir, u8 Port_Name);

/*Comment! : Get Port index*/
extern u8 get_port_index (u8 port_name);

#define LONG_PRESS
#endif /* GPIO_H_ */
