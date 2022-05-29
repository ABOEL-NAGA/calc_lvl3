/*
 * HLCD_prg.c
 *
 *  Created on: May 23, 2022
 *      Author: Abo El-Naga
 */

#include "HLCD_int.h"
#include <util/delay.h>
static uint8 S_u8ConvertAscii(uint8 A_u8Num);
static uint8 S_u8IsFloat(float32 A_f32Num);



void HLCD_vInit()
{
_delay_ms(20);
DIO_vSetPinDir(HLCD_CTRL_PORT,RS_PIN,DIO_OUTPUT);
DIO_vSetPinDir(HLCD_CTRL_PORT,RW_PIN,DIO_OUTPUT);
DIO_vSetPinDir(HLCD_CTRL_PORT,EN_PIN,DIO_OUTPUT);




#if EIGHT_BIT_MODE

*HLCD_DATA_DIR_REG=0xFFU;

#elif FOUR_BIT_MODE

*HLCD_DATA_DIR_REG |=(LCD_4_DATA_PINS);
HLCD_vSendCommand(LCD_RETURN_HOME);

#endif

_delay_ms(1);

HLCD_vSendCommand(LCD_DISPLAY_ON);
_delay_ms(1);
HLCD_vSendCommand(LCD_FUNCTION_SET);
_delay_ms(1);
HLCD_vSendCommand(LCD_CLR_DISPLAY);
_delay_ms(3);
HLCD_vSendCommand(LCD_EntryMode_Set);
_delay_ms(1);

}
void HLCD_vSendCommand(uint8 A_u8Cmd)
{

	DIO_vSetPinVal(HLCD_CTRL_PORT,RS_PIN,DIO_LOW);
	DIO_vSetPinVal(HLCD_CTRL_PORT,RW_PIN,DIO_LOW);


	DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_HIGH);
	_delay_ms(1);

#if EIGHT_BIT_MODE

DIO_vSetPortVal(HLCD_DATA_PORT,A_u8Cmd);


_delay_ms(1);

DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_LOW);
	_delay_ms(1);

#elif FOUR_BIT_MODE
*HLCD_OUT_DATA_REG &= (~(LCD_4_DATA_PINS));


*HLCD_OUT_DATA_REG |= ((A_u8Cmd>>LCD_4_BIT_SHIFT) & LCD_4_DATA_PINS);


_delay_ms(10);

DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_LOW);
	   _delay_ms(10);

DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_HIGH);
		_delay_ms(10);
*HLCD_OUT_DATA_REG &= (~(LCD_4_DATA_PINS));

*HLCD_OUT_DATA_REG |= ((A_u8Cmd<<(4-LCD_4_BIT_SHIFT)) & LCD_4_DATA_PINS);
_delay_ms(10);


DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_LOW);
	  _delay_ms(10);



#endif
}
void HLCD_vDisplayChar(uint8 A_u8Data)
{
DIO_vSetPinVal(HLCD_CTRL_PORT,RS_PIN,DIO_HIGH);
DIO_vSetPinVal(HLCD_CTRL_PORT,RW_PIN,DIO_LOW);

DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_HIGH);
		_delay_ms(10);


	#if EIGHT_BIT_MODE
DIO_vSetPortVal(HLCD_DATA_PORT,A_u8Data);
DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_LOW);
		_delay_ms(1);

#elif FOUR_BIT_MODE

*HLCD_OUT_DATA_REG &= (~(LCD_4_DATA_PINS));
*HLCD_OUT_DATA_REG |= ((A_u8Data>>LCD_4_BIT_SHIFT) & LCD_4_DATA_PINS);
_delay_ms(1);

DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_LOW);
	   _delay_ms(1);

DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_HIGH);
		_delay_ms(1);
	*HLCD_OUT_DATA_REG &= (~(LCD_4_DATA_PINS));
	*HLCD_OUT_DATA_REG |= ((A_u8Data<<(4-LCD_4_BIT_SHIFT)) & LCD_4_DATA_PINS);
      _delay_ms(1);


DIO_vSetPinVal(HLCD_CTRL_PORT,EN_PIN,DIO_LOW);
	  _delay_ms(1);
#endif
}
void HLCD_vDisplayNum(float32 A_f32Num)
{



	 uint8 LR_f32Arr[10]={0}; /*10 is the maximum number of digits that can exist in 32 bit binary*/
	 sint32 L_u32Temp=A_f32Num;
	uint8 L_u8Counter1;

	uint8 L_u8Counter2=0;


	uint32 L_u8Whole=0;

	uint32 L_u8Intger=0;




if(S_u8IsFloat(A_f32Num))
{


	L_u8Whole=(int)A_f32Num;


	L_u8Intger=A_f32Num*N_DECIMAL_POINTS_PRECISION;
	L_u8Intger=L_u8Intger%N_DECIMAL_POINTS_PRECISION;



	if(A_f32Num>0)
		{
		for(L_u8Counter1=0;L_u8Intger>0;L_u8Counter1++)
				{

			        	LR_f32Arr[L_u8Counter1]=L_u8Intger%10;


					L_u8Intger/=10;



				}
		 while(L_u8Counter1<NUMBERS_AFTER_DECIMAL)
					        		{
					        	LR_f32Arr[L_u8Counter1++]=0;
					        		}
		 LR_f32Arr[L_u8Counter1++]='.';

		for(;L_u8Whole>0;L_u8Counter1++)
		{
			LR_f32Arr[L_u8Counter1]=L_u8Whole%10;
			L_u8Whole/=10;

		}





	   while(L_u8Counter2<L_u8Counter1)
	   {
          if (LR_f32Arr[L_u8Counter1-1]=='.')

        	  {HLCD_vDisplayChar('.');
        	  L_u8Counter1--;
        	  }
          else
          {
		   uint8 L_u8Ascii=S_u8ConvertAscii(LR_f32Arr[L_u8Counter1-1]);

		   HLCD_vDisplayChar(L_u8Ascii);

		   L_u8Counter1--;
          }

	   }


		}
		else if(A_f32Num<0)
		{
			HLCD_vDisplayChar('-');
			A_f32Num*=-1;
			L_u8Whole=(int)A_f32Num;


				L_u8Intger=A_f32Num*N_DECIMAL_POINTS_PRECISION;
				L_u8Intger=L_u8Intger%N_DECIMAL_POINTS_PRECISION;



				if(A_f32Num>0)
					{
					for(L_u8Counter1=0;L_u8Intger>0;L_u8Counter1++)
							{

						        	LR_f32Arr[L_u8Counter1]=L_u8Intger%10;


								L_u8Intger/=10;



							}
					 while(L_u8Counter1<NUMBERS_AFTER_DECIMAL)
								        		{
								        	LR_f32Arr[L_u8Counter1++]=0;
								        		}
					 LR_f32Arr[L_u8Counter1++]='.';

					for(;L_u8Whole>0;L_u8Counter1++)
					{
						LR_f32Arr[L_u8Counter1]=L_u8Whole%10;
						L_u8Whole/=10;

					}





				   while(L_u8Counter2<L_u8Counter1)
				   {
			          if (LR_f32Arr[L_u8Counter1-1]=='.')

			        	  {HLCD_vDisplayChar('.');
			        	  L_u8Counter1--;
			        	  }
			          else
			          {
					   uint8 L_u8Ascii=S_u8ConvertAscii(LR_f32Arr[L_u8Counter1-1]);

					   HLCD_vDisplayChar(L_u8Ascii);

					   L_u8Counter1--;
			          }

				   }


					}



		}
		else
		{
			HLCD_vDisplayChar('0');
		}

	}









else if (!S_u8IsFloat(L_u32Temp))
{
	if(L_u32Temp>0)
	{


	for(L_u8Counter1=0;L_u32Temp>0;L_u8Counter1++)
	{
		LR_f32Arr[L_u8Counter1]=L_u32Temp%10;
		L_u32Temp/=10;

	}
   while(L_u8Counter2<L_u8Counter1)
   {
	   uint8 L_u8Ascii=S_u8ConvertAscii(LR_f32Arr[L_u8Counter1-1]);

	   HLCD_vDisplayChar(L_u8Ascii);

	   L_u8Counter1--;


   }


	}
	else if(L_u32Temp<0)
	{
		HLCD_vDisplayChar('-');
		L_u32Temp*=-1;
		for(L_u8Counter1=0;L_u32Temp>0;L_u8Counter1++)
			{
			LR_f32Arr[L_u8Counter1]=L_u32Temp%10;
			L_u32Temp/=10;

			}
		   while(L_u8Counter2<L_u8Counter1)
		   {

			   uint8 L_u8Ascii=S_u8ConvertAscii(LR_f32Arr[L_u8Counter1-1]);

			   HLCD_vDisplayChar(L_u8Ascii);

			   L_u8Counter1--;


		   }


	}
	else
	{
		HLCD_vDisplayChar('0');
	}



}
}



void HLCD_vDisplayStr(char* AR_u8Data)
{
	uint8 L_u8Index=0;
	while(AR_u8Data[L_u8Index]!='\0')
	{
		HLCD_vDisplayChar(AR_u8Data[L_u8Index]);
		L_u8Index++;
	}


}


void HLCD_RowCol_Select(uint8 Row, uint8 Col)
{
	uint8 u8LocalLineAddress = 0U;

	switch(Row)
	{
		case 0:

			u8LocalLineAddress = Col | LCD_1ST_LINE_BASE;
			break;
		case 1:
			u8LocalLineAddress = Col | LCD_2ND_LINE_BASE;
			break;

		default:
			break;
	}
	HLCD_vSendCommand(LCD_DDRAM_CONST | u8LocalLineAddress);
}
static uint8 S_u8ConvertAscii(uint8 A_u8Num)
{
	return(A_u8Num+48);  /*48 is the ascii for 0*/

}



void HLCD_vShiftDisplay (HLCD_DirEnum A_u8Dir)
{
	switch(A_u8Dir)
	{
	case SHIFT_RIGHT:
		HLCD_vSendCommand(LCD_DISPLAY_SHIFT_RIGHT);
		break;
	case  SHIFT_lEFT:
		HLCD_vSendCommand(LCD_DISPLAY_SHIFT_LEFT);
		break;
	default:
		break;

	}


}
void HLCD_vShiftCursor (HLCD_DirEnum A_u8Dir)
{
	switch(A_u8Dir)
	{
	case SHIFT_RIGHT:
		HLCD_vSendCommand(LCD_CUSRSOR_SHIFT_RIGHT);
		break;
	case  SHIFT_lEFT:
		HLCD_vSendCommand(LCD_CUSRSOR_SHIFT_LEFT);
		break;
	default:
		break;

	}

}




static uint8 S_u8IsFloat(float32 A_f32Num)
{
	uint32 L_u8Check=(int)A_f32Num;
	uint8 L_u8FloatFlag;

	if((float)(L_u8Check)==A_f32Num)
		{L_u8FloatFlag=0;
		}
	else if((float)(L_u8Check)!=A_f32Num)
	{
			L_u8FloatFlag=1;
	}

	return L_u8FloatFlag;

}

float32 Power(uint8 A_u8Base, uint8 A_u8Exp)
{
float32 result=1;
if(A_u8Exp>=0)
   {
     for (; A_u8Exp>0; A_u8Exp--)
   {
   result = result * A_u8Base;
}
}
else
{     for (; A_u8Exp<0; A_u8Exp++)
   {
	result=result/A_u8Base;


   }

}
return result;
}



