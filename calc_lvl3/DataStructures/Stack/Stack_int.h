/*
 * Stack_int.h
 *
 *  Created on: May 25, 2022
 *      Author: Abo El-Naga
 */

#ifndef DATASTRUCTURES_STACK_STACK_INT_H_
#define DATASTRUCTURES_STACK_STACK_INT_H_
#include "../../LIB/Std_Types.h"

#define MAX 100

void Stack_vPush(float32 A_f32data);
float32 Stack_f32Pop (void);
uint8 Stack_u8Isempty(void);


extern float32 GR_u16stack[MAX];
extern sint8  G_s8Top;

#endif /* DATASTRUCTURES_STACK_STACK_INT_H_ */
