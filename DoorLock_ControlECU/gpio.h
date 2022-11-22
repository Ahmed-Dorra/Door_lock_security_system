/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: header file for the AVR GPIO driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_
#include"std_types.h"


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	PIN_INPUT , PIN_OUTPUT
}GPIO_PinDirectionState;

typedef enum{
	PORT_INPUT , PORT_OUTPUT=0xFF
}GPIO_PORTDirectionState;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*Description :-
 * specify the direction of a specific pin at any port to be input/ output pin.
 * if the input port or pin is not right the function will not respond.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionState direction);


/*Description
 * This function used to output a LOGIC_HIGH or LOGIC_LOW to a specified pin in any port.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * if the pin was input and you wrote a logic high it will activate internal pull-up resistor
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);


/*Description
* Read and return the value for the required pin, it should be Logic High or Logic Low.
• If the input port number or pin number are not correct, The function will return Logic Low
*/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);



/*Description
 * Setup the direction of the required port all pins input/output.
• If the direction value is PORT_INPUT all pins in this port should be input pins.
• If the direction value is PORT_OUTPUT all pins in this port should be output pins.
• If the input port number is not correct, The function will not handle the request
*/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PORTDirectionState direction);



/*Description
 * Write the value on the required port.
• If any pin in the port is output pin the value will be written.
• If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
• If the input port number is not correct, The function will not handle the request.
*/
void GPIO_writePort(uint8 port_num, uint8 value);



/*Description
* Read and return the value of the required port.
* If the input port number is not correct, The function will return ZERO value.
*/
uint8 GPIO_readPort(uint8 port_num);



/*DESCRIPTION:-
 * This function is used to set the direction of the pins of any port as
 *  an output/input pins manually according to the value given to the function
 * */
void GPIO_manualPinSetDirection(uint8 port_num, uint8 value);


/*DESCRIPTION:-
 * Insertion in the last 4 bits of a register --> MSB
 */
void GPIO_insertInLast4Bits(uint8 port_num,uint8 value);


/*******************************************************************************
 *                              PORT & PIN Definitions                         *
 *******************************************************************************/
#define MAX_NUM_OF_PORTS           	   4
#define MIN_NUM_OF_PORTS           	   1
#define MAX_NUM_OF_PINS_PER_PORT   	   8


#define PORTA_ID               1
#define PORTB_ID               2
#define PORTC_ID               3
#define PORTD_ID               4

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

#endif /* GPIO_H_ */
