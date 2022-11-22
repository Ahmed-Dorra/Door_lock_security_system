/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum
{
	BITS_5, BITS_6, BITS_7, BITS_8
}UART_BitData;

typedef enum
{
	DISABLED, RESERVED, EVEN, ODD
}UART_Parity;

typedef enum
{
	ONE_BIT, TWO_BIT
}UART_StopBit;

typedef struct{
UART_BitData bit_data;
UART_Parity parity;
UART_StopBit stop_bit;
uint32 baudrate;
}UART_ConfigType;




/*******************************************************************************
 *------->>>>>>>>>>        Functions Prototypes             <<<<<<------------  *
*******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);


/*
 * Description :
 * Function responsible for receiving byte from another UART device.
 */
uint8 UART_recieveByte(void);


/*
 * Description :
 * Function responsible for sending byte to another UART device.
 */
void UART_sendByte(uint8 data);



/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(uint8 *Str_Ptr);


/*
 * Description :
 * Receive the required string until the '$' symbol through UART from the other UART device.
 * '$' is a terminator sign acknowledging the receiver that string ended so stop receiving
 */
void UART_recieveString(uint8 *Str_Ptr);


#endif /* UART_H_ */
