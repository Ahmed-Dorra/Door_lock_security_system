/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: timer1.h
 *
 * Description: Header file for the AVR Timer1 driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/


#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK, FCPU, FCPU_8, FCPU_64, FCPU_256, FCPU_1024,
	EXT_FALLING, EXT_RISING
}Timer1_Prescaler;


typedef enum
{
	OVF_MODE, COMP_MODE=8
}Timer1_Mode;

typedef enum
{
	NORMAL, TOGGLE_ON_COMP, CLEAR_ON_COMP, SET_ON_COMP
}Timer1_OC1A_OC1B;

typedef struct
{
uint16 initial_value;
uint16 compare_value;
Timer1_Prescaler prescaler;
Timer1_Mode mode;
Timer1_OC1A_OC1B comp_pins_setting;
} Timer1_ConfigType;



/*******************************************************************************
 *------->>>>>>>>>>        Functions Prototypes             <<<<<<------------  *
 *******************************************************************************/


/*Description
⮚ Function to initialize the Timer driver*/

void Timer1_init(const Timer1_ConfigType * Config_Ptr);


/*Description
⮚ Function to disable the Timer1.*/
void Timer1_deInit(void);


/*Description
⮚ Function to set the Call Back function address.*/
void Timer1_setCallBack(void(*a_ptr)(void));



#endif /* TIMER1_H_ */
