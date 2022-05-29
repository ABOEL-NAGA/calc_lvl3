/*
 * Configuration.h
 *
 *  Created on: May 20, 2022
 *      Author: Abo El-Naga
 */

#ifndef LIB_CONFIGURATION_H_
#define LIB_CONFIGURATION_H_

#define PORTA_DIR_REG  ((volatile uint8*) 0x3AU)
#define PORTA_IN_REG   ((volatile uint8*) 0x39U)
#define PORTA_OUT_REG  ((volatile uint8*) 0x3BU)


#define PORTB_DIR_REG  ((volatile uint8*) 0x37U)
#define PORTB_IN_REG   ((volatile uint8*) 0x36U)
#define PORTB_OUT_REG  ((volatile uint8*) 0x38U)


#define PORTC_DIR_REG  ((volatile uint8*) 0x34U)
#define PORTC_IN_REG   ((volatile uint8*)0x33U)
#define PORTC_OUT_REG  ((volatile uint8*)0x35U)

#define PORTD_DIR_REG  ((volatile uint8* )0x31U)
#define PORTD_IN_REG   ((volatile uint8*)0x30U)
#define PORTD_OUT_REG  ((volatile uint8*)0x32U)




#endif /* LIB_CONFIGURATION_H_ */
