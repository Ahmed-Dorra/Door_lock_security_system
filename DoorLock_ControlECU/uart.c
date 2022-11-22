/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/
#include "uart.h"
#include "avr/io.h"
#include "Relavent_Macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void UART_init(const UART_ConfigType *Config_Ptr)
{
	/*for the baud_rate value*/
	uint16 ubrr_value = 0;

	/*for double transmission speed */
	UCSRA = (1 << U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 (used with 9bit mode so it is not needed currently)
	 * RXB8 & TXB8 (used with 9bit mode so it is not needed currently)
	here we did direct equal operation coz we only need to set these two bits and
	we don't need the others so we make them = zero
	 ***********************************************************************/
	UCSRB = (1 << RXEN) | (1 << TXEN);


	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = parity bit option- received according to user configuration.
	 * USBS    = stop bit either one or 2 bits - received according to user configuration.
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only - we only work with ASync.
	 ***********************************************************************/
	SET_BIT(UCSRC,URSEL);
	CLEAR_BIT(UCSRC,UMSEL);
	UCSRC = (UCSRC & 0xCF) | ((Config_Ptr->parity << UPM0)); // UPM0 is bit4 same if we write Config_Ptr->parity << 4
	UCSRC = (UCSRC & 0xF7) | ((Config_Ptr->stop_bit << USBS));
	UCSRC = (UCSRC & 0xF9) | ((Config_Ptr->bit_data << UCSZ0));
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baudrate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH
	 * like this URSEL is also written to Zero so value go to UBRRH*/
	UBRRL = ubrr_value;
	UBRRH = ubrr_value>>8;
}


void UART_sendByte(uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for transmitting a new byte so wait
	 * until this flag is set to one by this technique we assure that no data overwrite will happen even we call this
	 * function multiple times so we avoided the problem that can occur as result of the difference between speed of
	 * processor and speed of sending by UART
	 */
	while( BIT_IS_CLEAR(UCSRA,UDRE) ){}

	/*
	 * writing data in the UDR register and it also clear the UDRE flag as the UDR register is not empty now
	 */
	UDR = data;

	/*>>>>>>>>>>> Another Method <<<<<<<<<<<
	 * is to use pooling but with the transmit complete flag TXC but in this method
	 * we will send data first then wait in a loop till the TXC flag is set and that happen
	 * when the data transmission complete so the Previous method is better coz we don't have to stay
	 * inside a function that is executed by the speed of UART (which is slow) for too long (check notes for more details)
	 * */
}



uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}

void UART_sendString(uint8 *Str_Ptr)
{

	while(*Str_Ptr != '\0')
	{
		UART_sendByte(*Str_Ptr);
		Str_Ptr++;

	}

}

void UART_recieveString(uint8 *Str_Ptr)
{
	uint8 index=0;

	/* We have to Receive the first byte in order to have something to check
	 * because the address we recieve is for an empty array that we created
	 * in our application so that we can fill it by the string we recieve from
	 * another micro_controller */
	Str_Ptr[index] = UART_recieveByte();


	/*Here we use the $ sign as a terminator for the message we sent*/
	while(Str_Ptr[index] != '$')
	{
		index++;
		Str_Ptr[index] = UART_recieveByte();

	}
	/* After receiving the whole string plus the '$', replace the '$' with '\0'
	 * because in our application the LCD for example in order to display
	 * it loop till it find the null as well as any other function that do a
	 * proccessing on a string it loops till the null so we need that null  */
	Str_Ptr[index] = '\0';
}
