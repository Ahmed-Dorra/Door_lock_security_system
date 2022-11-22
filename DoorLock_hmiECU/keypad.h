 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*** Static configuration ***/

//#define STANDARD_KEYPAD
//#define KEYPAD_4x3
#define KEYPAD_4x4


#define KEYPAD_NUM_OF_COLUMNS						4
#define KEYPAD_NUM_OF_ROWS							4

#define KEYPAD_PORT									PORTA_ID
#define KEYPAD_ROW_START_PIN						PIN0_ID
#define KEYPAD_COLUMN_START_PIN						PIN4_ID

/*columns are connected to VCC so we check for zero input and thats why the logic
 * of key pressed is low while released is high */
#define KEYPAD_KEY_PRESSED							LOGIC_LOW
#define KEYPAD_KEY_RELEASED 						LOGIC_HIGH


/*******************************************************************************
 *>>>>>>>>>>                 Functions Prototypes                <<<<<<<<<<<<< *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button, we have 12 buttons in keypad 4x3 so this function will
 * return a number from 1 --> 12 depending on which button is pressed first one or second or---
 * the order goes from upper left to right .. so upper left key represent 1 the next one is 2 and so on
 * but this function is not responsible for mapping these buttons to match whatever keypad version
 * you purchased.. this functionality is implemented in another separate function
 */
uint8 KEYPAD_getPressedKey(void);



#endif /* KEYPAD_H_ */
