/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/
#include "avr/io.h" /* To use the IO Ports Registers */
#include "Relavent_Macros.h"
#include"gpio.h"


/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionState direction)
{
	if(port_num > MAX_NUM_OF_PORTS || port_num < MIN_NUM_OF_PORTS || pin_num < PIN0_ID || \
			pin_num > MAX_NUM_OF_PINS_PER_PORT)
	{
		/*DO NOTHING*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			if(direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			else if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID :
			if(direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			else if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID :
			if(direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			else if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID :
			if(direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			else if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 * ***REMEMBER TO USE OUR MACRO --> SET_BIT(REG,BIT_NUM)*****
 */

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	if(port_num > MAX_NUM_OF_PORTS || port_num < MIN_NUM_OF_PORTS || pin_num < PIN0_ID || \
			pin_num > MAX_NUM_OF_PINS_PER_PORT)
	{
		/*DO NOTHING*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID :

			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;

		case PORTB_ID :

			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;

		case PORTC_ID :
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;

		case PORTD_ID :

			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else if(value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}

}
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 * HINT --> USE OUR MACRO BIT_IS_SET ALONG WITH PIN REGISTER TO READ STATUS	*****
 */

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	if(port_num > MAX_NUM_OF_PORTS || port_num < MIN_NUM_OF_PORTS || pin_num < PIN0_ID || \
			pin_num > MAX_NUM_OF_PINS_PER_PORT)
	{
		/*No Condition so it will break if -else statement and reach the end of the function
		 *  which is return LOGIC_LOW and that is what we want in case there is something
		 *  wrong with inputs coming to the function*/
	}
	else
	{
		switch(port_num)
		{

		case PORTA_ID :
			if(BIT_IS_SET(PINA,pin_num))
			{
				return LOGIC_HIGH;
			}
			else
			{
				return LOGIC_LOW;
			}
			break;

		case PORTB_ID :
			if(BIT_IS_SET(PINB,pin_num))
			{
				return LOGIC_HIGH;
			}
			else
			{
				return LOGIC_LOW;
			}
			break;

		case PORTC_ID :
			if(BIT_IS_SET(PINC,pin_num))
			{
				return LOGIC_HIGH;
			}
			else
			{
				return LOGIC_LOW;
			}
			break;

		case PORTD_ID :
			if(BIT_IS_SET(PIND,pin_num))
			{
				return LOGIC_HIGH;
			}
			else
			{
				return LOGIC_LOW;
			}
			break;
		}

	}

	return LOGIC_LOW;
}


/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PORTDirectionState direction)
{
	if(port_num > MAX_NUM_OF_PORTS || port_num < MIN_NUM_OF_PORTS)
	{
		/*DO NOTHING*/
	}
	else
	{
		if(port_num == PORTA_ID)
		{
			if(direction == PORT_OUTPUT)
			{
				SET_ALL(DDRA);
			}
			else
			{
				CLEAR_ALL(DDRA);
			}
		}

		else if(port_num == PORTB_ID)
		{
			if(direction == PORT_OUTPUT)
			{
				SET_ALL(DDRB);
			}
			else
			{
				CLEAR_ALL(DDRB);
			}
		}

		else if(port_num == PORTC_ID)
		{
			if(direction == PORT_OUTPUT)
			{
				SET_ALL(DDRC);
			}
			else
			{
				CLEAR_ALL(DDRC);
			}
		}

		else
		{
			if(direction == PORT_OUTPUT)
			{
				SET_ALL(DDRD);
			}
			else
			{
				CLEAR_ALL(DDRD);
			}
		}

	}

}
/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	if(port_num > MAX_NUM_OF_PORTS || port_num < MIN_NUM_OF_PORTS)
		{
			/*DO NOTHING*/
		}
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			PORTA = value;
			break;

		case PORTB_ID :
			PORTB = value;
			break;

		case PORTC_ID :
			PORTC = value;
			break;

		case PORTD_ID :
			PORTD = value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 *
 * >>*****DON'T FORGET THAT WE READ FROM PIN REGISTER *** <<
 */
uint8 GPIO_readPort(uint8 port_num)
{
	if(port_num > MAX_NUM_OF_PORTS || port_num < MIN_NUM_OF_PORTS)
			{
				/*DO NOTHING*/
			}
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			return PINA;
			break;

		case PORTB_ID :
			return PINB;
			break;

		case PORTC_ID :
			return PINC;
			break;

		case PORTD_ID :
			return PIND;
			break;
		}
	}
	return LOGIC_LOW;
}

/*DESCRIPTION:-
 * This function is used to set the direction of the pins of any port as
 *  an output/input pins manually according to the value given to the function
 *  IF the port number is incorrect the function will not handle the request
 * */
void GPIO_manualPinSetDirection(uint8 port_num, uint8 value)
{
	if(port_num > MAX_NUM_OF_PORTS || port_num < MIN_NUM_OF_PORTS)
	{
		/*DO NOTHING*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			DDRA = value;
			break;
		case PORTB_ID :
			DDRB = value;
			break;
		case PORTC_ID :
			DDRC = value;
			break;
		case PORTD_ID :
			DDRD = value;
			break;
		}
	}
}

void GPIO_insertInLast4Bits(uint8 port_num, uint8 value)
{
	switch(port_num)
			{
			case PORTA_ID :
				INSERT_IN_4MSB(PORTA, value);
				break;
			case PORTB_ID :
				INSERT_IN_4MSB(PORTB, value);
				break;
			case PORTC_ID :
				INSERT_IN_4MSB(PORTC, value);
				break;
			case PORTD_ID :
				INSERT_IN_4MSB(PORTD, value);
				break;
			}
}
