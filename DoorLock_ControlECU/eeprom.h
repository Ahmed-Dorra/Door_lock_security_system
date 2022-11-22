/******************************************************************************
 *
 * Module: EEPROM driver
 *
 * File Name: eeprom.h
 *
 * Description: header file for the EEPROM AVR driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/



#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *>>>>>>>>>>>>>>>>>             Definitions                <<<<<<<<<<<<<<<<<<<  *
 *******************************************************************************/
#define SUCCESS 1
#define ERROR 0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


uint8 EEPROM_writeByte(uint16 address,uint8 data);


uint8 EEPROM_readByte(uint16 address, uint8 *data);





#endif /* EEPROM_H_ */
