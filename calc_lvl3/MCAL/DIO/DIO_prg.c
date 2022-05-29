/*
/ * DIO_prg.c
 *
 *  Created on: May 20, 2022
 *      Author: Abo El-Naga
 */



#include "DIO_int.h"


void DIO_vSetPinDir(DIO_PortEnum A_u8Port,DIO_PinEnum A_u8PinNO,DIO_DirEnum A_u8Dir)
{
switch(A_u8Port)
{
case PORTA:
	switch(A_u8Dir)
	{
	case DIO_INPUT:
	    CLEAR_BIT(*PORTA_DIR_REG,A_u8PinNO);
	  break;
	case DIO_OUTPUT:
		SET_BIT(*PORTA_DIR_REG,A_u8PinNO);
		break;
	default:
		break;

	}
	break;
case PORTB:
	switch(A_u8Dir)
		{
		case DIO_INPUT:
		    CLEAR_BIT(*PORTB_DIR_REG,A_u8PinNO);
		  break;
		case DIO_OUTPUT:
			SET_BIT(*PORTB_DIR_REG,A_u8PinNO);
			break;
		default:
			break;

		}
		break;
case PORTC:
	switch(A_u8Dir)
		{
		case DIO_INPUT:
		    CLEAR_BIT(*PORTC_DIR_REG,A_u8PinNO);
		  break;
		case DIO_OUTPUT:
			SET_BIT(*PORTC_DIR_REG,A_u8PinNO);
			break;
		default:
			break;

		}
		break;
	case PORTD:
		switch(A_u8Dir)
			{
			case DIO_INPUT:
			    CLEAR_BIT(*PORTD_DIR_REG,A_u8PinNO);
			  break;
			case DIO_OUTPUT:
				SET_BIT(*PORTD_DIR_REG,A_u8PinNO);
				break;
			default:
				break;

			}
			break;

		default:
			break;

}
}
void DIO_vSetPinVal(DIO_PortEnum A_u8Port,DIO_PinEnum A_u8PinNO,Dio_ValEnum A_u8Val)
{
	switch(A_u8Port)
	{
	case PORTA:
		switch(A_u8Val)
		{
		case DIO_LOW:
		    CLEAR_BIT(*PORTA_OUT_REG,A_u8PinNO);
		  break;
		case DIO_HIGH:
			SET_BIT(*PORTA_OUT_REG,A_u8PinNO);
			break;
		default:
			break;

		}
		break;
	case PORTB:
		switch(A_u8Val)
			{
			case DIO_LOW:
			    CLEAR_BIT(*PORTB_OUT_REG,A_u8PinNO);
			  break;
			case DIO_HIGH:
				SET_BIT(*PORTB_OUT_REG,A_u8PinNO);
				break;
			default:
				break;

			}
			break;
	case PORTC:
		switch(A_u8Val)
			{
			case DIO_LOW:
			    CLEAR_BIT(*PORTC_OUT_REG,A_u8PinNO);
			  break;
			case DIO_HIGH:
				SET_BIT(*PORTC_OUT_REG,A_u8PinNO);
				break;
			default:
				break;

			}
			break;
		case PORTD:
			switch(A_u8Val)
				{
				case DIO_LOW:
				    CLEAR_BIT(*PORTD_OUT_REG,A_u8PinNO);
				  break;
				case DIO_HIGH:
					SET_BIT(*PORTD_OUT_REG,A_u8PinNO);
					break;
				default:
					break;

				}
				break;

		default:
				break;

	}

}
Dio_ValEnum DIO_u8GetPinVal(DIO_PortEnum A_u8Port,DIO_PinEnum A_u8PinNO)
{
 Dio_ValEnum L_u8Val=0;
switch(A_u8Port)
{
case PORTA:
	L_u8Val=READ_BIT(*PORTA_IN_REG,A_u8PinNO);
	break;
case PORTB:
	L_u8Val=READ_BIT(*PORTB_IN_REG,A_u8PinNO);
	break;
case PORTC:
	L_u8Val=READ_BIT(*PORTC_IN_REG,A_u8PinNO);
	break;
case PORTD:
	L_u8Val=READ_BIT(*PORTD_IN_REG,A_u8PinNO);
	break;
default:
	break;


}
 return L_u8Val;
}
void DIO_vSetPortDir(DIO_PortEnum A_u8Port,uint8 A_u8Val)
{

	switch(A_u8Port)
	{
	case PORTA:
		*PORTA_DIR_REG=A_u8Val;
		break;
	case PORTB:
		*PORTB_DIR_REG=A_u8Val;
		break;
	case PORTC:
		*PORTC_DIR_REG=A_u8Val;
			break;
	case PORTD:

		*PORTD_DIR_REG=A_u8Val;

			break;
	default:
			break;

	}
}
void DIO_vSetPortVal(DIO_PortEnum A_u8Port,uint8 A_u8Val)
{
	switch(A_u8Port)
		{
		case PORTA:
			*PORTA_OUT_REG=A_u8Val;
			break;
		case PORTB:
			*PORTB_OUT_REG=A_u8Val;
			break;
		case PORTC:
			*PORTC_OUT_REG=A_u8Val;
				break;
		case PORTD:
			*PORTD_OUT_REG=A_u8Val;

				break;
		default:
				break;

		}

}
uint8 DIO_u8GetPortVal(DIO_PortEnum A_u8Port)
{  uint8 L_u8VAL=0;
   switch(A_u8Port)
   {
   case PORTA:
	   L_u8VAL=*PORTA_IN_REG;
	  break;
   case PORTB:
   	   L_u8VAL=*PORTB_IN_REG;
   	  break;
   case PORTC:
   	   L_u8VAL=*PORTC_IN_REG;
   	  break;
   case PORTD:
   	   L_u8VAL=*PORTD_IN_REG;
   	  break;
   default:
	   break;

   }

return L_u8VAL;

}

void DIO_vSetGroupDir(DIO_PortEnum A_u8Port,uint8 A_u8Dir)
{
	switch(A_u8Port)
	{
	case PORTA:
		*PORTA_DIR_REG|=A_u8Dir;
		break;
	case PORTB:
			*PORTB_DIR_REG|=A_u8Dir;
			break;
	case PORTC:
			*PORTC_DIR_REG|=A_u8Dir;
			break;
	case PORTD:
			*PORTD_DIR_REG|=A_u8Dir;
			break;
	default:
		   break;

	}

}
void DIO_vSetGroupVal(DIO_PortEnum A_u8Port,uint8 A_u8Val)
{



	switch(A_u8Val)
		{
		case PORTA:
			*PORTA_OUT_REG|=A_u8Val;
			break;
		case PORTB:
				*PORTB_OUT_REG|=A_u8Val;
				break;
		case PORTC:
				*PORTC_OUT_REG|=A_u8Val;
				break;
		case PORTD:
				*PORTD_OUT_REG|=A_u8Val;
				break;
		default:
			   break;

		}



}
