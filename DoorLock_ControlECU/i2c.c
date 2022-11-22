/******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: i2c.h
 *
 * Description: source file for the I2C AVR driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#include <avr/io.h>
#include "i2c.h"
#include "Relavent_Macros.h"

void I2C_init(const I2C_ConfigType * Config_Ptr)
{
	/* Setting register TWSR as 0 , means our prescaler =0*/
	TWSR = 0x00;

	/*/* Bit Rate: we recieve from user taken in
	 * consederation that we use zero pre-scaler TWPS=00  */
	TWBR = (uint8)(((F_CPU/Config_Ptr->bit_rate)-16) /2);
    TWAR = Config_Ptr->address;

	/*Enabling I2C module so now it can control the I/O pins connected to the SCL and SDA*/
	TWCR = (1<<TWEN);

}


void I2C_start(void)
{
	/*
		 * Clear the TWINT flag before sending the start bit TWINT=1
		 * send the start bit by TWSTA=1
		 * Enable TWI Module TWEN=1
		 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully)
	 * I2C speed is much slower than our CPU so we have to wait till it successfully do
	 * its required task otherwise CPU will call this function and exit it and it will continue executing code
	 * and all of that will happen so fast before start bit even sent..  */
	while(BIT_IS_CLEAR(TWCR,TWINT)){}
}

void I2C_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);

}


void I2C_writeByte(uint8 data)
{
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/*Waiting till it complete the sending */
	while(BIT_IS_CLEAR(TWCR,TWINT)){}
}

uint8 I2C_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */

	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT)){}

	return TWDR;
}

uint8 I2C_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 NO ACKNOLEDGEMENT BIT IS SET IN THIS CASE
	 * Enable TWI Module TWEN=1
	 */

	TWCR = (1 << TWINT) | (1 << TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT)){}

	return TWDR;
}

uint8 I2C_getStatus(void)
{

/*We did masking becoz we only need last 5 bits so we eliminated the first 3 bits */
return (TWSR & 0xF8);

}
