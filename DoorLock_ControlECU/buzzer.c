/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#include"gpio.h"
#include"buzzer.h"

/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/

void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}



void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);

}


void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

