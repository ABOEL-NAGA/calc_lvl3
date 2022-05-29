/*
 * main.c

 *
 *  Created on: May 24, 2022
 *      Author: Abo El-Naga
 */
#include "../HAL/HLCD/HLCD_int.h"

#include "../HAL/keypad/Keybad_int.h"
#include "../DataStructures/Stack/Stack_int.h"
#include <util/delay.h>


#define MAX_CHAR   16

float32  APP_f32InfixEval(uint8* A_u8Input,uint8* A_u8NumOfChar);
float32 APP_f32TwoOperandEval(float32 A_u8operandA,float32 A_u8operandB,uint8 A_u8Opertor);
uint8 APP_u8CheckExpValidity(uint8* A_u8Input);
uint8 APP_u8CheckPrecedence(uint8 A_u8Operator);
uint8 APP_u8Check_op_num(uint8 A_u8Char);
uint8* APP_u8InfixTopostFix(uint8* A_u8Str,uint8* A_u8NumOfChar);
uint8* APP_u8IdentifyDec(uint8* A_u8Str,uint8* A_u8Length);
float32 APP_f32Evaluate(uint8* A_u8Input,uint8* A_u8NumOfChar);
float APP_f32Power(uint8 A_u8Base, sint8 A_u8Exp);




int main(void)
{



uint8 LR_u8Str[MAX_CHAR];
uint8 L_u8Counter=0;
uint8 L_u8PressedButton;
float32 L_f32Evaluation;
uint8  L_u8PushTimes;
uint8* L_u8Ptr=&L_u8PushTimes;



Keypad_vInit();
HLCD_vInit();



	while(1)
	{



		while((L_u8PressedButton=Keypad_u8GetNum())!='='&&L_u8Counter<16)
		{


			if(L_u8PressedButton)
			{

			LR_u8Str[L_u8Counter++]=L_u8PressedButton;
			HLCD_vDisplayChar(L_u8PressedButton);
			(*L_u8Ptr)++;
			}



		}


		if(!APP_u8CheckExpValidity(LR_u8Str))
		{

        HLCD_RowCol_Select(1,0);
		L_f32Evaluation=APP_f32InfixEval(LR_u8Str,&L_u8PushTimes);

		HLCD_vDisplayNum(L_f32Evaluation);


		}
		else
		{
			HLCD_vSendCommand(LCD_CLR_DISPLAY);
          HLCD_vDisplayStr("EXPR. INVALID!!");

		}


}
	return 0;

}
float32 APP_f32Evaluate(uint8* A_u8Input,uint8* A_u8NumOfChar)
{

  uint8 L_u8Symbol;
  float32 L_u8OperatorA;
  float32 L_u8OperatorB;
  float32 L_u8HighDec=0;
  uint8 L_u8CounterA=0;
  uint8 L_u8CounterB=0;
  uint8 L_u8CounterC=0;
  uint8 L_u8CounterD=0;




  float32 L_f32Result;
  uint8 L_u8FolatFlag	=0;
for(uint8 i=0;i<(*A_u8NumOfChar);i++)
{
//47.74!36.25!*
	L_u8Symbol=A_u8Input[i];

	if(L_u8Symbol=='.')
		{

		L_u8FolatFlag=1;
		}
	else if(L_u8Symbol=='!')
	{

		{
					if(L_u8FolatFlag)
					{
						L_u8CounterA=L_u8CounterC;
								for(int i=0;i<L_u8CounterA;i++)
								{
						L_u8HighDec+=Stack_f32Pop()*APP_f32Power(10,L_u8CounterC*-1)*10;

						L_u8CounterC--;
                        L_u8CounterD++;




								}
								L_u8FolatFlag=0;

								for(int i=0;i<L_u8CounterB-L_u8CounterD;i++)
															{
												L_u8HighDec+=Stack_f32Pop()*APP_f32Power(10,i);

												L_u8CounterA++;
															}

					}
					else
					{
								for(int i=0;i<L_u8CounterB;i++)
								{
					L_u8HighDec+=Stack_f32Pop()*APP_f32Power(10,i);

								}
					}
				}

				L_u8CounterA=0;

				Stack_vPush(L_u8HighDec);

				L_u8HighDec=0;
				L_u8CounterB=0;
				L_u8CounterC=0;
				L_u8CounterD=0;

	}

	else if(!APP_u8Check_op_num(L_u8Symbol))
		{
		if(L_u8FolatFlag)
		{
			   L_u8CounterC++;
				Stack_vPush(L_u8Symbol-'0');
				L_u8CounterB++;
		}
		else
		{


		Stack_vPush(L_u8Symbol-'0');
	L_u8CounterB++;
		}
		}
		else

			{
			L_u8OperatorA=Stack_f32Pop();
			L_u8OperatorB=Stack_f32Pop();


			Stack_vPush(APP_f32TwoOperandEval(L_u8OperatorB,L_u8OperatorA,A_u8Input[i]));


			}


		}




L_f32Result=Stack_f32Pop();

return(L_f32Result);
}

uint8 APP_u8CheckPrecedence(uint8 A_u8Operator)
{
	uint8 L_u8Precedance;
		switch(A_u8Operator)
			{

				case'/': case '*':
					L_u8Precedance= 2;
				break;
				case '+': case '-':
					L_u8Precedance= 1;
				break;
				default :
					L_u8Precedance= 0;
                break;


			}
		return L_u8Precedance;


}
uint8 APP_u8Check_op_num(uint8 A_u8Char)
{
	char L_u8Checker;


		if(A_u8Char>47 &&A_u8Char<58)
			L_u8Checker=0;
		else
			L_u8Checker=1;

		return L_u8Checker;
}
float32 APP_f32TwoOperandEval(float32 A_u8operandA,float32 A_u8operandB,uint8 A_u8Opertor)
{
	float32 L_f32Result=0;
		switch(A_u8Opertor)
		{
		case '+': L_f32Result=A_u8operandA+A_u8operandB;
		   break;
		case '-': L_f32Result=A_u8operandA-A_u8operandB;
		   break;
		case '*': L_f32Result=A_u8operandA*A_u8operandB;
		   break;
		case '/': L_f32Result=A_u8operandA/A_u8operandB;
	       break;
		default :
		   break;


		}
		return L_f32Result;

}
uint8 APP_u8CheckExpValidity(uint8* A_u8Input)
{
	uint8 L_u8Checker=0,L_u8consective=0;
		if(APP_u8Check_op_num(A_u8Input[0])&&A_u8Input[0]!='.')
					L_u8Checker=1;
		else
		for(uint8 i=0;i<MAX_CHAR;i++)
		{
			if(APP_u8Check_op_num(A_u8Input[i])&&A_u8Input[i]!='.')
				L_u8consective++;
			else
						L_u8consective=0;
			if(L_u8consective>1)
			{
			L_u8Checker=1;
			break;

			}


		}
		return L_u8Checker;

}

uint8* APP_u8InfixTopostFix(uint8* A_u8Str,uint8* A_u8NumOfChar)
{

	static uint8 LR_u8ARR[MAX_CHAR];

	uint8 L_u8Counter=0;


	for(uint8 i=0;i<*A_u8NumOfChar;i++)
	{
		if(A_u8Str[i]=='!')
				{
					LR_u8ARR[L_u8Counter++]=A_u8Str[i];

				}

		else if(!APP_u8Check_op_num(A_u8Str[i])||A_u8Str[i]=='.')
			{LR_u8ARR[L_u8Counter++]=A_u8Str[i];


			}
		else
		{

			while(!Stack_u8Isempty()&&APP_u8CheckPrecedence(A_u8Str[i])<=APP_u8CheckPrecedence(GR_u16stack[G_s8Top]))
			{
				LR_u8ARR[L_u8Counter++]=Stack_f32Pop();




			}


			Stack_vPush(A_u8Str[i]);

		}
	}



	while(!Stack_u8Isempty())
	{

		LR_u8ARR[L_u8Counter++]=Stack_f32Pop();

	}


	return LR_u8ARR;
}

float32  APP_f32InfixEval(uint8* A_u8Input,uint8* A_u8NumOfChar)
{
	float32 L_f32Result;
uint8* L_s8Arr=A_u8Input;
L_s8Arr=APP_u8IdentifyDec(L_s8Arr,A_u8NumOfChar);
L_s8Arr=APP_u8InfixTopostFix(L_s8Arr,A_u8NumOfChar);

L_f32Result=APP_f32Evaluate(L_s8Arr,A_u8NumOfChar);


	return L_f32Result;

}



uint8* APP_u8IdentifyDec(uint8* A_u8Str,uint8* A_u8Length)
{

	static uint8 LR_u8New[MAX_CHAR];
	uint8 L_u8CounterA=0,L_u8CounterB=0;

		for(;L_u8CounterA<(*A_u8Length);L_u8CounterA++)
	{


	    if(A_u8Str[L_u8CounterB]=='.')
	    {
	    	LR_u8New[L_u8CounterA]=A_u8Str[L_u8CounterB];
	    }
	    else if(APP_u8Check_op_num(A_u8Str[L_u8CounterB]))
			{LR_u8New[L_u8CounterA]='!';
			  LR_u8New[++L_u8CounterA]=A_u8Str[L_u8CounterB];
            (*A_u8Length)++;

			}
		else
		{

			LR_u8New[L_u8CounterA]=A_u8Str[L_u8CounterB];


		}
		L_u8CounterB++;

}
		LR_u8New[L_u8CounterA]='!';
        (*A_u8Length)++;


		return LR_u8New;
}


float32 APP_f32Power(uint8 A_u8Base, sint8 A_u8Exp)
{
float32 result=1.00;
float32 L_f32Num=(float)A_u8Base;
if(A_u8Exp>=0)
   {
     for (; A_u8Exp>0; A_u8Exp--)
   {
   result = result * A_u8Base;
}
}
else
{   A_u8Exp*=-1;
L_f32Num=1/L_f32Num;


	for (uint8  i=0; i<=A_u8Exp; i++)
   {
	result=result*L_f32Num;


   }

}
return result;
}
