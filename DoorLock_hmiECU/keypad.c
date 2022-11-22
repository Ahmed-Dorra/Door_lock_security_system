/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author:  Ahmed_Dorra
 ******************************************************************************/

#include"gpio.h"
#include "keypad.h"
#include <util/delay.h>
/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/
#ifdef KEYPAD_4x3
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8);
#endif

#ifdef KEYPAD_4x4
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8);
#endif



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint8 KEYPAD_getPressedKey(void)
{
	uint8 currentRow, currentColumn;
	GPIO_setupPinDirection(KEYPAD_PORT, KEYPAD_ROW_START_PIN, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_PORT, KEYPAD_ROW_START_PIN+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_PORT, KEYPAD_ROW_START_PIN+2, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_PORT, KEYPAD_ROW_START_PIN+3, PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_PORT, KEYPAD_COLUMN_START_PIN, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_PORT, KEYPAD_COLUMN_START_PIN+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_PORT, KEYPAD_COLUMN_START_PIN+2, PIN_INPUT);
#if (KEYPAD_NUM_OF_COLUMNS ==4)
	GPIO_setupPinDirection(KEYPAD_PORT, KEYPAD_COLUMN_START_PIN+3, PIN_INPUT);
#endif

	while(1)
	{
		for(currentRow=0; currentRow < KEYPAD_NUM_OF_ROWS; currentRow++)
		{
			GPIO_setupPinDirection(KEYPAD_PORT, (KEYPAD_ROW_START_PIN + currentRow), PIN_OUTPUT);
			GPIO_writePin(KEYPAD_PORT, (KEYPAD_ROW_START_PIN + currentRow), KEYPAD_KEY_PRESSED);

			for(currentColumn =0; currentColumn < KEYPAD_NUM_OF_COLUMNS; currentColumn++)
			{
				if(GPIO_readPin(KEYPAD_PORT, (KEYPAD_COLUMN_START_PIN + currentColumn)) ==KEYPAD_KEY_PRESSED )
				{
#ifdef STANDARD_KEYPAD
					return ((currentRow * KEYPAD_NUM_OF_COLUMNS)+currentColumn+1);
#endif

#ifdef KEYPAD_4x3
					return KEYPAD_4x3_adjustKeyNumber((currentRow * KEYPAD_NUM_OF_COLUMNS)+currentColumn+1);
#endif

#ifdef KEYPAD_4x4
					return KEYPAD_4x4_adjustKeyNumber((currentRow * KEYPAD_NUM_OF_COLUMNS)+currentColumn+1);
#endif
				}
				_delay_ms(10);
			}
			GPIO_setupPinDirection(KEYPAD_PORT, (KEYPAD_ROW_START_PIN + currentRow), PIN_INPUT);
			_delay_ms(10);
		}
	}
}

#ifdef KEYPAD_4x3
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 keyPressedId)
{
	if(keyPressedId == 10)
	{
		return '*';
	}
	else if(keyPressedId == 11)
	{
		return 0;
	}
	else if(keyPressedId == 12)
	{
		return '#';
	}
	return 0;
}
#endif

#ifdef KEYPAD_4x4
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 keyPressedId)
{
	uint8 keypadButton=0;
	switch(keyPressedId)
	{
	case 1: keypadButton =7;
	break;

	case 2:	keypadButton =8;
	break;

	case 3:keypadButton =9;
	break;

	case 4: keypadButton = '/';
	break;

	case 5: keypadButton =4;
	break;

	case 6: keypadButton =5;
	break;

	case 7: keypadButton =6;
	break;

	case 8: keypadButton ='*';
	break;

	case 9: keypadButton =1;
	break;

	case 10: keypadButton =2;
	break;

	case 11:keypadButton =3;
	break;

	case 12: keypadButton ='-';
	break;

	case 13: keypadButton = 13;	/* ASCII of Enter */
	break;

	case 14:  keypadButton = 0;
	break;

	case 15:  keypadButton = '=';
	break;

	case 16:  keypadButton = '+';
	break;
	}
	return keypadButton;
}


#endif
