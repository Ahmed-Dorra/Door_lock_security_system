 /******************************************************************************
 *
 * Module: Relevant_Macros
 *
 * File Name: Relevant_Macros.h
 *
 * Description: Commonly used Macros
 *
 * Author:	Ahmed_Dorra
 *
 *******************************************************************************/

#ifndef RELAVENT_MACROS_H_
#define RELAVENT_MACROS_H_

/* SET A BIT IN ANY REGISTER*/
#define SET_BIT(REG,BIT_NUM)		(REG |= (1<<BIT_NUM))

/*CLEAR BIIT IN ANY REGISTER */
#define CLEAR_BIT(REG,BIT_NUM)		( REG &= (~(1<<BIT_NUM)) )

/*TOGGLE BIT IN ANY REGISTER*/
#define TOGGLE_BIT(REG,BIT_NUM)		(REG = REG ^ (1<<BIT_NUM))

/*CHECK IF A SPECIFIC BIT IS SET ( = 1 ) IN ANY REGISTER AND RETURN TRUE IF BIT = 1 */
#define BIT_IS_SET(REG,BIT_NUM)		(REG & (1<<BIT_NUM))

/*CHECK IF A CERTAIN BIT IS CLEARED ( = 0 ) IN ANY REGISTER AND RETURN TRUE IF BIT =0 */
#define BIT_IS_CLEAR(REG,BIT_NUM)	( !(REG & (1<<BIT_NUM)) )

/*SETTING THE WHOLE REGISTER (WHOLE REGISTER = 0XFF)*/
#define SET_ALL(REG)				(REG=0xFF)

/*CLEARING THE WHOLE REGISTER (WHOLE REGISTER = 0X00)*/
#define CLEAR_ALL(REG)				(REG=0x00)

/* INSERTING A VALUE IN THE LAST 4 MOST SIGNIFICANT BITS --> LAST 4 BITS
 *  without affecting rest of pins*/
#define INSERT_IN_4MSB(REG, value)	(REG = ((REG & 0x0F) | (value<<4)))


/* INSERTING A VALUE IN THE SPECIFIED REGISTER */
#define INSERT_VALUE(REG, value)	(	REG = ( (REG & 0x0F) | (value) )	)


/* INSERTING A VALUE IN THE LAST 4 Least SIGNIFICANT BITS --> First 4 BITS
 * without affecting rest of pins*/
#define INSERT_IN_4LSB(REG, value)	(REG = ((REG & 0xF0) | (value & 0x0F)))

#endif /* RELAVENT_MACROS_H_ */
