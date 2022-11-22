/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for the AVR PWM driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*Static configuration*/

#define PWM_PIN		3
#define PWM_PORT	DDRB	/* we put DDR as we will need it to set the pin direction*/


/*******************************************************************************
 *------->>>>>>>>>>        Functions Prototypes             <<<<<<------------  *
*******************************************************************************/

/*
 * Description:
 * Generate a PWM signal with frequency 500Hz
 * Timer0 will be used with pre-scaler F_CPU/8
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * Duty Cycle can be changed by updating the value
 * in The Compare Register
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
