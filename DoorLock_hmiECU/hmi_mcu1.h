/******************************************************************************
 * Project: Door_Locker_Security_System
 *
 * File Name: hmi_mcu1.h
 *
 * Description: header file for the application that will be running on the first
 * MCU which will be responsible for interaction with the user (HMI_ECU)
 *
 * Author:  Ahmed_Dorra
 ******************************************************************************/

#ifndef HMI_MCU1_H_
#define HMI_MCU1_H_
/*******************************************************************************
 *                                Driver Used                                 *
 *******************************************************************************/
#include "timer1.h"
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "avr/io.h"
#include<util/delay.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MCU2_READY	0xFF
#define MCU1_READY	0x00
#define PASS_CORRECT 1u
#define PASS_WRONG	 0u
#define PASSWORD_SIZE 5
#define OPEN_DOOR 		0x11
#define PASSWORD_CHANGE 		0x22
#define ENTERY_LIMIT 	3
#define NOT_YET		0u
#define DONE		1u
#define ONE_MINUITE	60000

/*******************************************************************************
 *------->>>>>>>>>>        Functions Prototypes             <<<<<<------------  *
*******************************************************************************/

void PASSWORD_set(void);
void PASSWORD_confirm(void);

void PASSWORD_send(void);
void PASSWORD_confirmationSend(void);

void CONFIRMATION_recieve();
void PASSWORD_creatingSequence(void);
uint8 SYSTEM_mainOptions(void);
uint8 DOOR_openOption(void);

void PASSWORD_notMatchedSendAgain(void);

uint8 COMMAND_recieve(void);
void DOOR_unlock(void);
void ALARM(void);

uint8 PASSWORD_changeOption(void);


#endif /* HMI_MCU1_H_ */
