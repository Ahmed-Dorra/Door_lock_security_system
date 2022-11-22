/******************************************************************************
 *
 * Module: EEPROM driver
 *
 * File Name: eeprom.h
 *
 * Description: source file for the EEPROM AVR driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#include "eeprom.h"
#include "i2c.h"


uint8 EEPROM_writeByte(uint16 addr_11bit, uint8 data)
{
	I2C_start();

	/*checking if the status bits now have the unique value that signals that start bit is sent */
	if(I2C_getStatus() != TWI_START)
	{
		return ERROR;
	}

	/*Sending the slave address + the last 3 bit in the memory
	 * address(memory address is 11 bit address) that we will write at..
	 * so we send (1010-->0xA0) which is the constant device address
	 * and do or operation with only the last 3 MSB in the memory address that we will write at*/
	I2C_writeByte((uint8) (0xA0 | ( (addr_11bit & 0x0700) >>7 )));

	/*checking if the status bits now have the unique value that signals that address
	 * is sent and slave acknowledged us */
	if(I2C_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR;
	}

	/*Sending first 8bits of the memory location that we will deal with*/
	I2C_writeByte((uint8)(addr_11bit));
	if(I2C_getStatus() != TWI_MT_DATA_ACK)
		{
			return ERROR;
		}

	/*IF everything is correct we send data now to eeprom*/
	I2C_writeByte(data);
	if(I2C_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}

	I2C_stop();
	return SUCCESS;
}


uint8 EEPROM_readByte(uint16 addr_11bit, uint8 *data)
{
	I2C_start();

	/*checking if the status bits now have the unique value that signals that start bit is sent */
	if(I2C_getStatus() != TWI_START)
	{
		return ERROR;
	}

	/*Sending the slave address + the last 3 bit in the memory
	 * address(memory address is 11 bit address) that we will write at..
	 * so we send (1010-->0xA0) which is the constant device address
	 * and do or operation with only the last 3 MSB in the memory address that we will write at*/
	I2C_writeByte((uint8) (0xA0 | ( (addr_11bit & 0x0700) >>7 )));

	/*checking if the status bits now have the unique value that signals that address
	 * is sent and slave acknowledged us */
	if(I2C_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR;
	}

	/*Sending first 8bits of the memory location that we will deal with*/
	I2C_writeByte((uint8)(addr_11bit));
	if(I2C_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}

	/* Send the Repeated Start Bit coz we don't want to end connection yet
	 * we just want to reverse directions -- instead of writing we will
	 * read from that location(that we specified in previous frame) in memory */
	I2C_start();

	/*Checking if the repeated start is sent successfully*/
	if(I2C_getStatus() != TWI_REP_START)
	{
		return ERROR;
	}

	/*Here we merge the last 3 bits of the location we want with the slave address like we
	 * did previously but the different this time is that we send a read command not write thats
	 * why we did an OR operation with the one */
	I2C_writeByte((uint8) (0xA0 | ( (addr_11bit & 0x0700) >>7 ) | 1));
	if(I2C_getStatus() !=TWI_MT_SLA_R_ACK)
	{
		return ERROR;
	}

	/* Read Byte from Memory without send ACK --> means we only recieve one byte coz if
	 * we responded with ack the slave will send the next byte  */
	*data = I2C_readByteWithNACK();

	I2C_stop();
	return SUCCESS;
}









