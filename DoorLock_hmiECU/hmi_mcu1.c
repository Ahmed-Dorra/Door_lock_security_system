/******************************************************************************
 * Project: Door_Locker_Security_System
 *
 * File Name: hmi_mcu1.c
 *
 * Description: Source file for the application that will be running on the first
 * MCU which will be responsible for interaction with the user (HMI_ECU)
 *
 * Author:  Ahmed_Dorra
 ******************************************************************************/
#include "hmi_mcu1.h"
uint8 g_changeFlag= FALSE;
uint8 g_finish=NOT_YET;
uint8 g_interrupt_id=0;
uint8 Password[PASSWORD_SIZE];
uint8 Password_Confirm[PASSWORD_SIZE];
uint8 Password_State=PASS_WRONG;

void DOOR_openMessagesDisplay(void)
{

	g_interrupt_id++;
	if(g_interrupt_id ==8) //8
	{
		LCD_moveCursor(0,0);
		LCD_displayString("Door is locking !");

	}

	else if(g_interrupt_id == 15) //15
	{
		Timer1_deInit();
		LCD_clearScreen();
		g_interrupt_id=0;
		_delay_ms(1);

		g_finish = DONE;
	}
}



Timer1_ConfigType TIMER_settings ={0, 0, FCPU_256, OVF_MODE, NORMAL};
int main(void)
{
	SREG |= (1<<7);

	LCD_init();
	LCD_moveCursor(0,0);
	LCD_displayString("System Starting..");
	_delay_ms(250);
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	UART_ConfigType UART_settings ={BITS_8, DISABLED, ONE_BIT, 9600};
	UART_init(&UART_settings);
	uint8 state;
	uint8 Limit_passFlag = FALSE;
	uint8 Entery_limits=0;
	uint8 Door_state=NOT_YET;

	while(1)
	{
		while(1)
		{
			PASSWORD_creatingSequence();
			switch(Password_State)
			{
			case PASS_WRONG:
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				LCD_displayString("NOT MATCHED !");
				LCD_moveCursor(1,0);
				LCD_displayString("Try Again !");
				_delay_ms(500);
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				continue;
				break;

			case PASS_CORRECT :
				break;
			}
			break;
		}

		while(1)
		{
			switch(SYSTEM_mainOptions())
			{
			case '+' :
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				state = DOOR_openOption();

				while(state != PASS_CORRECT && Limit_passFlag == FALSE)
				{
					PASSWORD_notMatchedSendAgain();
					PASSWORD_send();
					switch(COMMAND_recieve())
					{
					case PASS_CORRECT:
						state = PASS_CORRECT;
						Door_state =DONE;
						DOOR_unlock();
						break;

					case PASS_WRONG :
						state = PASS_WRONG;
						Entery_limits++;
						break;
					}
					if(Entery_limits == ENTERY_LIMIT-1)
					{
						Entery_limits=0;
						Limit_passFlag = TRUE;
						ALARM();

					}
				}
				Limit_passFlag = FALSE;  // to force breaking larger while and go to start system main option

				if(state == PASS_CORRECT)
				{
					Door_state =DONE;
					DOOR_unlock();
				}

				break;

			case '-' :
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				state = PASSWORD_changeOption();
				while(state != PASS_CORRECT && Limit_passFlag == FALSE)
				{
					PASSWORD_notMatchedSendAgain();
					PASSWORD_send();
					switch(COMMAND_recieve())
					{
					case PASS_CORRECT:
						state = PASS_CORRECT;
						LCD_clearScreen();
						LCD_moveCursor(0,0);
						LCD_displayString("Change acc granted");
						_delay_ms(1000);
						break;

					case PASS_WRONG :
						state = PASS_WRONG;
						Entery_limits++;
						break;
					}
					if(Entery_limits == ENTERY_LIMIT-1)
					{
						Entery_limits=0;
						Limit_passFlag = TRUE; //to exit while
						ALARM();

					}
				}
				Limit_passFlag = FALSE;
				break;
			}


			//end of switch
			if( (Limit_passFlag == FALSE || g_changeFlag == TRUE) && Door_state != DONE )
			{
				g_changeFlag = FALSE;
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				break;
			}
			else
			{
				while(g_finish != DONE){}
				g_finish = NOT_YET;
				Door_state = NOT_YET;
			}
		}

		// end of the system main option loop
	}
	// end of the main loop
}
// end of main




void PASSWORD_creatingSequence(void)
{
	PASSWORD_set();
	//_delay_ms(50);
	PASSWORD_confirm();
	PASSWORD_send();
	PASSWORD_confirmationSend();
	CONFIRMATION_recieve();

}

uint8 SYSTEM_mainOptions(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("[+] Open Door");
	LCD_moveCursor(1,0);
	LCD_displayString("[-] change pass");
	uint8 SYSTEM_option;
	SYSTEM_option = KEYPAD_getPressedKey();
	_delay_ms(300);
	return SYSTEM_option;
}

void PASSWORD_set(void)
{

	uint8 digits=0;
	uint8 key;
	LCD_displayString("Enter pass..!");
	LCD_moveCursor(1,0);

	while(digits < PASSWORD_SIZE)
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(250);
		if(key == '+' || key == '-' || key == '*'|| key == '/' || key == '=' ||key == 13 )
		{
			continue;
		}
		Password[digits] = key;
		LCD_displayCharacter('*');
		//LCD_intgerToString(Password[digits]);
		digits++;
	}
	while(KEYPAD_getPressedKey() != '='){}
	_delay_ms(100);
}


void PASSWORD_confirm(void)
{
	uint8 digits=0;
	uint8 key;
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("confirm Pass:");
	LCD_moveCursor(1,0);
	while(digits < PASSWORD_SIZE)
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(300);
		if(key == '+' || key == '-' || key == '*'|| key == '/' || key == '=' ||key == 13 )
		{
			continue;
		}
		Password_Confirm[digits] = key;
		LCD_displayCharacter('*');
		//LCD_intgerToString(Password_Confirm[digits]);
		digits++;
	}
	while(KEYPAD_getPressedKey() != '='){}

}


void PASSWORD_send(void)
{
	uint8 i=0;
	UART_sendByte(MCU1_READY);

	while(UART_recieveByte() != MCU2_READY){}

	for(i=0; i < PASSWORD_SIZE; i++)
	{
		UART_sendByte(Password[i]);
	}

}
void PASSWORD_confirmationSend(void)
{
	uint8 i=0;
	while(UART_recieveByte() != MCU2_READY){}

	for(i=0; i < PASSWORD_SIZE; i++)
	{
		UART_sendByte(Password_Confirm[i]);
	}

}

void CONFIRMATION_recieve()
{
	UART_sendByte(MCU1_READY);
	Password_State = UART_recieveByte();
}



uint8 DOOR_openOption(void)
{
	uint8 pass_state;
	PORTB = 0;
	UART_sendByte(MCU1_READY);
	UART_sendByte(OPEN_DOOR);
	PASSWORD_set();
	PORTB = 255;
	PASSWORD_send();

	while(UART_recieveByte() != MCU2_READY ){}
	switch(UART_recieveByte())
	{
	case PASS_CORRECT:
		pass_state = PASS_CORRECT;
		break;

	case PASS_WRONG :
		pass_state = PASS_WRONG;
		break;
	}
	return pass_state;
}



void PASSWORD_notMatchedSendAgain(void)
{

	uint8 digits=0;
	uint8 key;
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Wrong Pass !");
	_delay_ms(250);
	LCD_moveCursor(0,0);
	LCD_displayString("ENTER AGAIN !");
	LCD_moveCursor(1,0);
	while(digits < PASSWORD_SIZE)
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(300);
		if(key == '+' || key == '-' || key == '*'|| key == '/' || key == '=' ||key == 13 )
		{
			continue;
		}
		Password[digits] = key;
		LCD_displayCharacter('*');
		//LCD_intgerToString(Password[digits]);
		digits++;

	}
	while(KEYPAD_getPressedKey() != '='){}


}

uint8 COMMAND_recieve(void)
{
	while(UART_recieveByte() != MCU2_READY){}
	return (UART_recieveByte());
}

void DOOR_unlock(void)
{
	LCD_clearScreen();
	LCD_displayString("Door Unlocking");
	Timer1_setCallBack(DOOR_openMessagesDisplay);
	Timer1_init(&TIMER_settings);
	//SYSTEM_mainOptions();

}

void ALARM(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("ERROR !!!");
	_delay_ms(ONE_MINUITE);// after testing use ONE_MIN
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	_delay_ms(10);


}


uint8 PASSWORD_changeOption(void)
{
	uint8 pass_state;
	PASSWORD_set();
	UART_sendByte(MCU1_READY);
	UART_sendByte(PASSWORD_CHANGE);
	PASSWORD_send();

	while(UART_recieveByte() != MCU2_READY ){}
	switch(UART_recieveByte())
	{
	case PASS_CORRECT:
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		_delay_ms(10);
		LCD_displayString("NEW ONE granted:");
		g_changeFlag = TRUE;
		_delay_ms(300);
		pass_state = PASS_CORRECT;

		break;

	case PASS_WRONG :
		pass_state = PASS_WRONG;
		break;

	}
	return pass_state;

}


