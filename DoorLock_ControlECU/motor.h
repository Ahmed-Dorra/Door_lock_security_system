/******************************************************************************
 *
 * Module: MOTOR
 *
 * File Name: motor.h
 *
 * Description: header file for the AVR MOTOR driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/


#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Static Configurations*/
#define MOTOR_PORT	PORTD_ID
#define MOTOR_IN1	PIN5_ID
#define MOTOR_IN2	PIN6_ID

/*For Direction Selection*/
typedef enum
{
	STOP, CW, A_CW
}DcMotor_State;

/*******************************************************************************
 *------->>>>>>>>>>>>        Functions Prototypes             <<<<<<<<----------*
*******************************************************************************/

/*Description :
 * The Function responsible for setup the direction for the two
motor pins through the GPIO driver.

* Stop at the DC-Motor at the beginning through the GPIO driver*/
void DcMotor_Init(void);



/*Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
stop the motor based on the state input state value*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
