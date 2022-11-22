/******************************************************************************
 * Project: Door_Locker_Security_System
 *
 * File Name: control_mcu2.h
 *
 * Description: header file for the application that will be running on the second
 * MCU which will be responsible for decision making (control ECU)
 *
 * Author:  Ahmed_Dorra
 ******************************************************************************/


#ifndef CONTROL_MCU2_H_
#define CONTROL_MCU2_H_



/*******************************************************************************
 *                                Driver Used                                 *
 *******************************************************************************/
#include "i2c.h"
#include "uart.h"
#include "eeprom.h"
#include "motor.h"
#include "timer1.h"
#include "avr/io.h"
#include<util/delay.h>
#include "buzzer.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define OPEN_DOOR 				0x11
#define PASSWORD_CHANGE 		0x22
#define MCU2_READY	0xFF
#define MCU1_READY	0x00
#define PASS_CORRECT 1u
#define PASS_WRONG	 0u
#define PASSWORD_SIZE 5
#define SAVED_PASSWORD_MEMORY_START_ADDRESS	0x0000
#define ENTERY_LIMIT 	3
#define ONE_MIN			60000
#define DONE		1u
#define NOT_YET		0u
#define ONE_MINUITE	60000
/*******************************************************************************
 *------->>>>>>>>>>        Functions Prototypes             <<<<<<------------  *
*******************************************************************************/

void PASSWORD_recieveFirstTime(void);
void PASSWORD_confirmationRecieve(void);
uint8 Ispassword_correct(void);
void Send_confirmation();

void PASSWORD_creatingSequence(void);
void PASSWORD_saving(void);
uint8 Decision_making(void);
void PASSWORD_checkAgainstSaved(void);

void DOOR_open(void);


void ALARM(void);

#endif /* CONTROL_MCU2_H_ */
