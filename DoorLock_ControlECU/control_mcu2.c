/******************************************************************************
 * Project: Door_Locker_Security_System
 *
 * File Name: control_mcu2.c
 *
 * Description: Source file for the application that will be running on the second
 * MCU which will be responsible for decision making (control ECU)
 *
 * Author:  Ahmed_Dorra
 ******************************************************************************/

#include "control_mcu2.h"
uint8 g_finish=NOT_YET;
uint8 g_changeFlag= FALSE;
uint8 g_interrupt_id=0;
uint8 Password[PASSWORD_SIZE];

uint8 Password_Confirm[PASSWORD_SIZE];
uint8 Password_State = PASS_WRONG;


void DOOR_open(void)
{

	g_interrupt_id++;
	if(g_interrupt_id ==7) //2 test
	{
		DcMotor_Rotate(STOP, 0);

	}
	else if(g_interrupt_id == 8)//3 test
	{
		DcMotor_Rotate(A_CW, 100);

	}
	else if(g_interrupt_id == 15)//5 test
	{
		Timer1_deInit();
		DcMotor_Rotate(STOP, 0);
		g_interrupt_id=0;
		g_finish = DONE;
	}
}


Timer1_ConfigType TIMER_settings ={0, 0, FCPU_256, OVF_MODE, NORMAL};
int main(void)
{
	DDRA=255;
	SREG |= (1<<7);
	Buzzer_init();
	DcMotor_Init();
	I2C_ConfigType I2C_settings ={0x00, 400000};
	I2C_init(&I2C_settings);
	UART_ConfigType UART_settings;
	UART_settings.bit_data = BITS_8;
	UART_settings.parity = DISABLED;
	UART_settings.stop_bit = ONE_BIT;
	UART_settings.baudrate = 9600;
	UART_init(&UART_settings);
	uint8 Limit_passFlag = FALSE;
uint8 entery_Limits=0;
uint8 Door_state=NOT_YET;


	while(1)
	{
		while(1)
		{
			PASSWORD_creatingSequence();
			switch(Password_State)
				{
				case PASS_WRONG: continue;
					break;

				case PASS_CORRECT:
					break;
				}
			PASSWORD_saving();
			break;
		}
		while(1)
		{
			switch(Decision_making())
				{
				case OPEN_DOOR:
					PASSWORD_checkAgainstSaved();

					while(Ispassword_correct() != PASS_CORRECT && Limit_passFlag == FALSE)
					{

						UART_sendByte(MCU2_READY);
						UART_sendByte(PASS_WRONG);
						entery_Limits++; // 1 2 3
						if(entery_Limits == ENTERY_LIMIT)
						{
							Limit_passFlag = TRUE;
							ALARM();
							break;
						}
						PASSWORD_checkAgainstSaved();

					}

					if(Limit_passFlag == FALSE)
					{
						UART_sendByte(MCU2_READY);
						UART_sendByte(PASS_CORRECT);
						Door_state = DONE;
						DcMotor_Rotate(CW, 100);
						Timer1_setCallBack(DOOR_open);
						Timer1_init(&TIMER_settings);
					}
					Limit_passFlag = FALSE;
					break;

				case PASSWORD_CHANGE:
					PASSWORD_checkAgainstSaved();
					while(Ispassword_correct() != PASS_CORRECT && Limit_passFlag == FALSE)
					{
						UART_sendByte(MCU2_READY);
						UART_sendByte(PASS_WRONG);
						g_changeFlag = TRUE;
						entery_Limits++; // 1 2 3
						if(entery_Limits == ENTERY_LIMIT)
						{
							entery_Limits=0;
							Limit_passFlag = TRUE; //to exit while
							ALARM();

						}
						PASSWORD_checkAgainstSaved();

					}
					if(Limit_passFlag == FALSE)
					{
						UART_sendByte(MCU2_READY);
						UART_sendByte(PASS_CORRECT);
						PASSWORD_saving();
					}
						break;
				}
			//end of switch
			if( (Limit_passFlag == FALSE || g_changeFlag == TRUE) && Door_state != DONE )
			{
				// reseting
				g_changeFlag = FALSE;
				Limit_passFlag = FALSE;
				break;

			}
			if(g_changeFlag == TRUE)
			{
				g_changeFlag = FALSE;
				break;
			}
			else
			{
				while(g_finish != DONE){}
				g_finish = NOT_YET;
				Door_state = NOT_YET;
			}
			//end of system_option loop
		}
			//end of father loop
	}
		//end of main

}

void PASSWORD_recieveFirstTime(void)
{
	uint8 digit;

	while(UART_recieveByte() != MCU1_READY ){}
	UART_sendByte(MCU2_READY);

		for(digit=0; digit < PASSWORD_SIZE; digit++)
		{
			Password[digit] = UART_recieveByte();
		}

}
void PASSWORD_confirmationRecieve(void)
{
	uint8 digit;
	UART_sendByte(MCU2_READY);

	for(digit=0; digit < PASSWORD_SIZE; digit++)
	{
		Password_Confirm[digit] = UART_recieveByte();
	}
}

uint8 Ispassword_correct(void)
{
	uint8 counter=0;
	uint8 pass_state;
	uint8 digit;
	for(digit=0; digit < PASSWORD_SIZE; digit++)
	{
		if(Password[digit] == Password_Confirm[digit])
		{
			counter++;
		}
	}
	if(counter == digit )
	{
		pass_state = PASS_CORRECT;
		Password_State = PASS_CORRECT;
	}
	else
	{
		pass_state = PASS_WRONG;
		Password_State = PASS_WRONG;
	}
return pass_state;
}

void Send_confirmation()
{
	while(UART_recieveByte() != MCU1_READY ){}
	UART_sendByte(Ispassword_correct());

}

void PASSWORD_creatingSequence(void)
{
	PASSWORD_recieveFirstTime();
	PASSWORD_confirmationRecieve();
	Ispassword_correct();
	Send_confirmation();

}

void PASSWORD_saving(void)
{
	uint8 counter=0;
	for(counter=0; counter < PASSWORD_SIZE; counter++)
	{
		EEPROM_writeByte(SAVED_PASSWORD_MEMORY_START_ADDRESS+counter, Password[counter]);
		_delay_ms(15);
	}

//	Decision_making();
}
uint8 Decision_making(void)
{
	uint8 next_action;
	while(UART_recieveByte() != MCU1_READY ){}
	next_action = UART_recieveByte();
	return next_action;
}



void PASSWORD_checkAgainstSaved(void)
{
	uint8 digit;
	/*FETCHING FIRST*/
	while(UART_recieveByte() != MCU1_READY ){}
	UART_sendByte(MCU2_READY);
	for(digit=0; digit < PASSWORD_SIZE; digit++)
			{
		Password_Confirm[digit] = UART_recieveByte();
			}
	for(digit=0; digit < PASSWORD_SIZE; digit++)
		{
		EEPROM_readByte(SAVED_PASSWORD_MEMORY_START_ADDRESS+digit, &Password[digit]);
			_delay_ms(10);
		}
	/*COMPARE*/

}

void ALARM(void)
{
	Buzzer_on();
	_delay_ms(ONE_MINUITE); // after testing use ONE_MIN
	Buzzer_off();
	_delay_ms(10);
   //PASSWORD_creatingSequence();
}
