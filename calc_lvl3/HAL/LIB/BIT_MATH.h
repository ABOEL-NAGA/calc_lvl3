/*
 * BIT_MATH.h
 *
 *  Created on: May 20, 2022
 *      Author: Abo El-Naga
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(REG,Bit_no)      ((REG)|=1U<<Bit_no)
#define CLEAR_BIT(REG,Bit_no)    ((REG)&=~(1U<<Bit_no))
#define TOGGLE_BIT(REG,Bit_no)   ((REG)^=(1U<<Bit_no))
#define READ_BIT(REG,Bit_no)     (((REG)&(1U<<Bit_no))>>(Bit_no))

#endif /* LIB_BIT_MATH_H_ */
