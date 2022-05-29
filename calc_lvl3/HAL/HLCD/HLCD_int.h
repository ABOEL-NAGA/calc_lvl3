/*
 * HLCD.h
 *
 *  Created on: May 23, 2022
 *      Author: Abo El-Naga
 */

#ifndef HAL_HLCD_HLCD_INT_H_
#define HAL_HLCD_HLCD_INT_H_
#include "../../MCAL/DIO/DIO_int.h"
#include "HLCD_config.h"

#define N_DECIMAL_POINTS_PRECISION (100000)
#define NUMBERS_AFTER_DECIMAL       5







#define LCD_CLR_DISPLAY     (0x01U)
#define LCD_RETURN_HOME     (0x02U)
#define LCD_EntryMode_Set   (0x04U|LCD_INCREMENT_MODE<<1|LCD_ENTRY_MODE_DISPLAY_SHIFT)
#define LCD_DISPLAY_ON      (0x0CU|LCD_CURSOR<<1|LCD_BLINK)
#define LCD_DISPLAY_OFF     (0x08U)
#define LCD_CUSRSOR_SHIFT_RIGHT (0x14U)
#define LCD_CUSRSOR_SHIFT_LEFT  (0x10U)
#define LCD_DISPLAY_SHIFT_RIGHT (0x1CU)
#define LCD_DISPLAY_SHIFT_LEFT  (0x18U)
#define LCD_FUNCTION_SET   ((0x20U)|(EIGHT_BIT_MODE<<4)|(LCD_LINES_DISPLAYED<<3)|(LCD_5_7_DOT<<2))
#define LCD_DDRAM_CONST             (0x80U)



#define LCD_1ST_LINE_BASE           (0x00U)
#define LCD_2ND_LINE_BASE           (0x40U)

typedef enum
{
	SHIFT_lEFT,
	SHIFT_RIGHT
}HLCD_DirEnum;

void HLCD_vInit();
void HLCD_vSendCommand(uint8 A_u8Cmd);
void HLCD_vDisplayChar(uint8 A_u8Data);
void HLCD_vDisplayNum(float32 A_f32Num);
void HLCD_vDisplayStr(char* AR_u8Data);
void HLCD_RowCol_Select(uint8 Row, uint8 Col);
void HLCD_vShiftDisplay (HLCD_DirEnum A_u8Dir);
void HLCD_vShiftCursor (HLCD_DirEnum A_u8Dir);






#endif /* HAL_HLCD_HLCD_INT_H_ */
