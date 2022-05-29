/*
 * Stack_prg.c
 *
 *  Created on: May 25, 2022
 *      Author: Abo El-Naga
 */
#include "Stack_int.h"



 float32 GR_u16stack[MAX];
 sint8  G_s8Top=-1;

 void Stack_vPush(float32 A_f32data)
 {
 	if(G_s8Top!=MAX-1)
 	{
 		G_s8Top++;
 		 	GR_u16stack[G_s8Top]=A_f32data;
 	}


 }

 float32 Stack_f32Pop (void)
 { float32 val=-1;
 	if(G_s8Top>=0)
 		{val=GR_u16stack[G_s8Top];
 		G_s8Top--;

 		}
 return val;




 }

 uint8 Stack_u8Isempty(void)
 	{
     uint8 L_u8Empty;
     if(G_s8Top==-1)
    	 {L_u8Empty=1;

    	 }
     else
    	 {L_u8Empty=0;
    	 }
     return(L_u8Empty);


 	}
