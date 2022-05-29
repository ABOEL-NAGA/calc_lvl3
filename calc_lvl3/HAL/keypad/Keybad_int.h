/*
 * Keybad_int.h
 *
 *  Created on: May 23, 2022
 *      Author: Abo El-Naga
 */

#ifndef HAL_KEYBAD_KEYBAD_INT_H_
#define HAL_KEYBAD_KEYBAD_INT_H_
#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO/DIO_int.h"

#define Keypad_PORT     PORTD



#define ColNumber  4U
#define RowNumber   4U






void Keypad_vInit();
uint8 Keypad_u8GetNum();

extern const uint8 CGR_KeypadArr[][ColNumber];

#endif /* HAL_KEYBAD_KEYBAD_INT_H_ */
