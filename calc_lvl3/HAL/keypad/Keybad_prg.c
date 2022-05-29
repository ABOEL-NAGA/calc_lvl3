/*
 * Keybad_prg.c
 *
 *  Created on: May 23, 2022
 *      Author: Abo El-Naga
 */

#include "Keybad_int.h"
#include <util/delay.h>



 const uint8 CGR_KeypadArr[RowNumber][ColNumber]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'.','0','=','+' }};


void Keypad_vInit()
{
	DIO_vSetPortDir(Keypad_PORT,0x0F);
    DIO_vSetPortVal(Keypad_PORT,0xFF);

}
uint8 Keypad_u8GetNum()
{
	 uint8 L_KeypadVal = 0;

		for(uint8 col=0; col<ColNumber; col++)
		{


			DIO_vSetPinVal(Keypad_PORT,col,DIO_LOW);
			for(uint8 row=0; row<RowNumber; row++)
			{
				if(DIO_u8GetPinVal(Keypad_PORT, row+4) == 0)
				{
					L_KeypadVal = CGR_KeypadArr[row][col];
				}
				while(DIO_u8GetPinVal(Keypad_PORT, row+4) == 0){}
				_delay_ms(10);
			}

			DIO_vSetPinVal(Keypad_PORT, col, DIO_HIGH);
		}

		return L_KeypadVal;

}


