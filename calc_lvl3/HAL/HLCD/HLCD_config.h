/*
 * HLCD_config.h
 *
 *  Created on: May 23, 2022
 *      Author: Abo El-Naga
 */

#ifndef HAL_HLCD_HLCD_CONFIG_H_
#define HAL_HLCD_HLCD_CONFIG_H_

#define HLCD_CTRL_PORT   PORTA
#define HLCD_DATA_PORT   PORTA


#define HLCD_DATA_DIR_REG  PORTA_DIR_REG
#define HLCD_OUT_DATA_REG  PORTA_OUT_REG

#define HLCD_CTRL_DIR_REG  PORTA_DIR_REG
#define HLCD_CTRL_DATA_REG  PORTA_OUT_REG

#define RS_PIN    DIO_PIN0
#define RW_PIN    DIO_PIN1
#define EN_PIN    DIO_PIN2

#define EIGHT_BIT_MODE   0U
#define FOUR_BIT_MODE    1U

#define LCD_4_DATA_PINS   0x78U
#define LCD_4_BIT_SHIFT    1U

#define LCD_LINES_DISPLAYED    1U
#define LCD_BLINK              0U
#define LCD_CURSOR             1U
#define LCD_INCREMENT_MODE     1U
#define LCD_ENTRY_MODE_DISPLAY_SHIFT    0U
#define LCD_5_7_DOT            0U

#endif /* HAL_HLCD_HLCD_CONFIG_H_ */
