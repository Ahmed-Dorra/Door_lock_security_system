/******************************************************************************
 *
 * Module: MOTOR
 *
 * File Name: motor.c
 *
 * Description: Source file for the AVR MOTOR driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#include "motor.h"
#include "pwm.h"
#include "gpio.h"

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(MOTOR_PORT, MOTOR_IN1, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT, MOTOR_IN2, PIN_OUTPUT);
	GPIO_writePin(MOTOR_PORT, MOTOR_IN1, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT, MOTOR_IN2, LOGIC_LOW);

}


void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	switch(state)
	{
	case STOP :
		GPIO_writePin(MOTOR_PORT, MOTOR_IN1, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT, MOTOR_IN2, LOGIC_LOW);
		break;
	case CW :
		GPIO_writePin(MOTOR_PORT, MOTOR_IN1, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT, MOTOR_IN2, LOGIC_HIGH);
		break;
	case A_CW :
		GPIO_writePin(MOTOR_PORT, MOTOR_IN1, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT, MOTOR_IN2, LOGIC_LOW);
		break;
	}
	PWM_Timer0_Start(speed);
}

