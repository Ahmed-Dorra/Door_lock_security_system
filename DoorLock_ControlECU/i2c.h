/******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: i2c.h
 *
 * Description: header file for the I2C AVR driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/


#ifndef I2C_H_
#define I2C_H_

#include"std_types.h"

/*******************************************************************************
 *>>>>>>>>>>>>>>>>>             Definitions                <<<<<<<<<<<<<<<<<<<  *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */



typedef struct{
uint8 address;
uint32 bit_rate;
}I2C_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*Setting up the I2C with the settings chosen by user and initiating it */
void I2C_init(const I2C_ConfigType * Config_Ptr);

/* Function Responsible for sending Start bit to begin communication*/
void I2C_start(void);

/* Function Responsible for sending Stop bit to end communication*/
void I2C_stop(void);

/* Function Responsible for sending data*/
void I2c_writeByte(uint8 data);

/* Function Responsible for reading bytes (it tells slave that it can send the next automatically)*/
uint8 I2C_readByteWithACK(void);

/* Function Responsible for reading one byte only
 * (here slave send only one byte and not sending the next automatically coz we didn't respond with ack)*/
uint8 I2C_readByteWithNACK(void);

/*Reading the status register to check if the values written there
 * correspond to the commands we gave or not  */
uint8 I2C_getStatus(void);

#endif /* I2C_H_ */
