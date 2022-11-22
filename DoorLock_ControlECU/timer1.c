/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: timer1.c
 *
 * Description: Source file for the AVR Timer1 driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include"timer1.h"

static volatile void (*g_Timer1_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *>>>>>>>>>>>>>>>             Interrupt Service Routines     <<<<<<<<<<<<<<<<< *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		(*g_Timer1_callBackPtr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		(*g_Timer1_callBackPtr)();
	}
}


/*******************************************************************************
 *>>>>>>>>>>>>>>>            Function Definitions             <<<<<<<<<<<<<<<<< *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/*Setting FOC1A , FOC1B = 1 --> Non PWm mode
	 * configuring the nature of working of OC1A/OC1B pins according to user preference
	 * configuring the timer mode according to user preference--> Normal / compare mode supported */
	TCCR1A = (Config_Ptr->comp_pins_setting << COM1A0)| (1<<FOC1A) | (Config_Ptr->mode & 0x03);


	/*Configuring rest of the bits that specify the timer mode
	 * Configuring the value of prescaler according to user preference  */
	TCCR1B = ( (TCCR1B & 0xC0) | Config_Ptr->mode | Config_Ptr->prescaler );


	/*Enabling the interrupt that correspond the mode which the user chose */
	switch(Config_Ptr->mode)
	{
	case OVF_MODE :
		/*initial value for the timer to start counting from it*/
		TCNT1 = Config_Ptr->initial_value;

		/* Timer/Counter1, Overflow Interrupt Enable*/
		TIMSK |= (1<<TOIE1);
		break;

	case COMP_MODE :
		/*configuring the compare value*/
		TCNT1 = Config_Ptr->initial_value;
		OCR1A = Config_Ptr->compare_value;
		/*Timer/Counter1, Output Compare A Match Interrupt Enable*/
		TIMSK |= (1<<OCIE1A);

		break;
	}

}


void Timer1_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 =0;
	OCR1A =0;
	TIMSK &= 0xC3; // Clearing only the bits specified for the timer1 interrupt enable
}


void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Storing the address of function passed to timer by the application (that timer will call back)
	 *  in a global variable so that we can execute this function later in the ISR */
	g_Timer1_callBackPtr = a_ptr;
}

