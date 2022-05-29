/*
 * DIO_int.h
 *
 *  Created on: May 20, 2022
 *      Author: Abo El-Naga
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_


#include "../../LIB/Std_Types.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Configuration.h"
typedef enum
{
	DIO_LOW,
	DIO_HIGH
}Dio_ValEnum;

typedef enum
{
	DIO_INPUT,
	DIO_OUTPUT
}DIO_DirEnum;

typedef enum
{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7,
}DIO_PinEnum;

typedef enum
{
	PORTA,
	PORTB,
	PORTC,
	PORTD
}DIO_PortEnum;

void DIO_vSetPinDir(DIO_PortEnum A_u8Port,DIO_PinEnum A_u8PinNO,DIO_DirEnum A_u8Dir);
void DIO_vSetPinVal(DIO_PortEnum A_u8Port,DIO_PinEnum A_u8PinNO,Dio_ValEnum A_u8Val);
Dio_ValEnum DIO_u8GetPinVal(DIO_PortEnum A_u8Port,DIO_PinEnum A_u8PinNO);
void DIO_vSetPortDir(DIO_PortEnum A_u8Port,DIO_DirEnum A_u8Dir);
void DIO_vSetPortVal(DIO_PortEnum A_u8Port,uint8 A_u8Val);
uint8 DIO_u8GetPortVal(DIO_PortEnum A_u8Port);



#endif /* MCAL_DIO_DIO_INT_H_ */
