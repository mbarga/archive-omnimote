/*
 *  OFIRInterface.c
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/14/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#ifndef __OFIRInterface
#include "OFIRInterface.h"
#endif

#include "LPC23xx.h"
#include "irq.h"

/************************************************
* INTERNAL FUNCTION DECLARATIONS
************************************************/
//Sending IR Signals
void StopIROutput(void);
void SetPWMFrequency( short );
void SetPWMDutyCycle( short );
void EnablePWM( void );
void DisablePWM( void );
void BuildSignal( int, int );
void SetPort( int );

//Receiving IR Signals
void StopIRInput(void);
void processCommand(int*, int*);
int parseStandardProtocol(short*, int, int, int, int);
int parseSIRCProtocol(short*, int);
int parseRC5(short*, int);
int findClosestProtocol(short*);
int findOpenCommandIndex(void);
int findBestArray(void);

int getTime(int prev, int now);
#define DISABLEIRINPUT	T2TCR = 0x02; T2MCR = 0x00; IO0_INT_CLR = 0xFFFFFFFF; IO0_INT_EN_R = 0; IO0_INT_EN_F = 0;	

extern OFBool OFIRReadFlag;
/************************************************/

/*************************************************
* EVENT HANDLERS
*************************************************/

void PWMHandler (void) __irq 
{
  unsigned long regVal;
	int dutyCycle;

  //IENABLE;				/* handles nested interrupt */

  regVal = PWM1IR;
  if ( regVal & MR0_INT )
  {
		pulseCounter--;	

		if (pulseCounter < 0) //if pulseCounter has reached it's limit
		{
			if (IRSignalIndex >= StaticIRSignal.length) //if finished sending IR signal
			{
				StopIROutput();
			}
			else
			{
				pulseCounter = StaticIRSignal.components[IRSignalIndex]->pulses; 

				if (StaticIRSignal.components[IRSignalIndex]->modulated)
				{
					dutyCycle = StaticIRSignal.carrier * 1/3;
				}
				else
				{
	 				dutyCycle = 0;
				}	

				PWM1MR1 = dutyCycle;
				PWM1LER = LER1_EN;

				IRSignalIndex = IRSignalIndex + 1;
			}
		}
  }
  PWM1IR |= regVal;		/* clear interrupt flag on match 0 */

  //IDISABLE;
  VICVectAddr = 0;		/* Acknowledge Interrupt */
  return;
}

void IRInputHandler (void) __irq 
{											 
  unsigned long IntReg;
  unsigned long timerVal = T2TC;
	int val;
	

  //IENABLE;				/* handles nested interrupt */

  IntReg = IO0_INT_STAT_R | IO0_INT_STAT_F;

	if (timerVal < 20)
	{
	 	T2TC = 0;
	}

	
  if ( IntReg & IR_36_IN )
  {
	  //rising edge on ir 36
		val = getTime(IR_36_COUNTER, timerVal);
		if (val > 10)
		{
			IR_36_INPUT_ARRAY[IR_36_INDEX++] = val;
			IR_36_COUNTER = timerVal;
			IR_36_DATA_RX = TRUE;
		
	
			if (IR_36_INDEX > 68)
			{		
				DISABLEIRINPUT;
				OFIRReadFlag = TRUE;
				informationReceived = TRUE;
			}
		}
  }	
  
						
  if ( IntReg & IR_38_IN )
  {
	  //rising edge on ir 38
		val = getTime(IR_38_COUNTER, timerVal);
		if (val > 10)
		{
			IR_38_INPUT_ARRAY[IR_38_INDEX++] = val;
			IR_38_COUNTER = timerVal;
			IR_38_DATA_RX = TRUE;
		
	
			if (IR_38_INDEX > 68)
			{		
				DISABLEIRINPUT;
				OFIRReadFlag = TRUE;
				informationReceived = TRUE;
			}
		}
  }					 

  if ( IntReg & IR_40_IN )
  {
  	//rising edge on ir 40
		val = getTime(IR_40_COUNTER, timerVal);
		if (val > 10)
		{
			IR_40_INPUT_ARRAY[IR_40_INDEX++] = val;
			IR_40_COUNTER = timerVal;
			IR_40_DATA_RX = TRUE;
		
	
			if (IR_40_INDEX > 68)
			{		
				DISABLEIRINPUT;
				OFIRReadFlag = TRUE;
				informationReceived = TRUE;
			}
		}
  }
		
  if ( IntReg & IR_56_IN )
  {
  	//rising edge on ir 56
		val = getTime(IR_56_COUNTER, timerVal);
		if (val > 10)
		{
			IR_56_INPUT_ARRAY[IR_56_INDEX++] = val;
			IR_56_COUNTER = timerVal;
			IR_56_DATA_RX = TRUE;
		
	
			if (IR_56_INDEX > 68)
			{		
				DISABLEIRINPUT;
				OFIRReadFlag = TRUE;
				informationReceived = TRUE;
			}
		}
  }		

  IO0_INT_CLR = IntReg;

  //IDISABLE;
  VICVectAddr = 0;		/* Acknowledge Interrupt */
  return;
}

void Timer2Handler (void) __irq
{
  unsigned long regVal;

  //IENABLE;				/* handles nested interrupt */

  regVal = T2IR;
  if ( regVal & MR0_INT )
  {
		if ( ( !IR_36_DATA_RX && !IR_38_DATA_RX && !IR_40_DATA_RX && !IR_56_DATA_RX ) &&
				 (  IR_36_INDEX || IR_38_INDEX || IR_40_INDEX || IR_56_INDEX  ) )
		{
			StopIRInput();
			OFIRReadFlag = TRUE;
			informationReceived = TRUE;
		}

		IR_36_DATA_RX = IR_38_DATA_RX = IR_40_DATA_RX = IR_56_DATA_RX = FALSE;
  }
  T2IR |= regVal;		/* clear interrupt flag on match 0 */

  //IDISABLE;
  VICVectAddr = 0;		/* Acknowledge Interrupt */
  return;
}

/************************************************/

int getTime(int prev, int now)
{
 	if (prev < now)
	{
	 	return now - prev;
	}
	else
	{
	 	return (T2MR0 - prev) + now;
	}
}

/*************************************************
* EXTERNAL FUNCTION DEFINITIONS
*************************************************/

void STDInitIR(void)
{
	//TV Commands
	commandArray[0].BinaryCommand = 0x02FD48B7;//power
	commandArray[0].Properties = 0x22;
	commandArray[1].BinaryCommand = 0x02FDD827;//channel up
	commandArray[1].Properties = 0x22;
	commandArray[2].BinaryCommand = 0x02FDF807;//channe down
	commandArray[2].Properties = 0x22;
	commandArray[3].BinaryCommand = 0x02FD58A7;//volume up
	commandArray[3].Properties = 0x22;
	commandArray[4].BinaryCommand = 0x02FD7887;//volume down
	commandArray[4].Properties = 0x22;
	commandArray[5].BinaryCommand = 0x02FD00FF;//0
	commandArray[5].Properties = 0x22;
	commandArray[6].BinaryCommand = 0x02FD807F;//1
	commandArray[6].Properties = 0x22;
	commandArray[7].BinaryCommand = 0x02FD40BF;//2
	commandArray[7].Properties = 0x22;
	commandArray[8].BinaryCommand = 0x02FDC03F;//3
	commandArray[8].Properties = 0x22;
	commandArray[9].BinaryCommand = 0x02FD20DF;//4
	commandArray[9].Properties = 0x22;
	commandArray[10].BinaryCommand = 0x02FDA05F;//5
	commandArray[10].Properties = 0x22;
	commandArray[11].BinaryCommand = 0x02FD609F;//6
	commandArray[11].Properties = 0x22;
	commandArray[12].BinaryCommand = 0x02FDE01F;//7
	commandArray[12].Properties = 0x22;		 
	commandArray[13].BinaryCommand = 0x02FD10EF;//8
	commandArray[13].Properties = 0x22;
	commandArray[14].BinaryCommand = 0x02FD906F;//9
	commandArray[14].Properties = 0x22;

	//Mac Commands
	commandArray[15].BinaryCommand = 0x77E1A073;//Play
	commandArray[15].Properties = 0x26;
	commandArray[16].BinaryCommand = 0x77E15073;//Volume Up
	commandArray[16].Properties = 0x26;
	commandArray[17].BinaryCommand = 0x77E13073;//Volume Down
	commandArray[17].Properties = 0x26;
	commandArray[18].BinaryCommand = 0x77E16073;//Next
	commandArray[18].Properties = 0x26;		 
	commandArray[19].BinaryCommand = 0x77E19073;//Prev
	commandArray[19].Properties = 0x26;
	commandArray[20].BinaryCommand = 0x77E1C073;//Menu
	commandArray[20].Properties = 0x26;

}


OFBool intializeIRControl(void)
{
	int i;

	pulseCounter = 0;
	PINSEL4 |= 0x01;	 //set GPIO pin 2.0 as PWM output
	PINSEL10 = 0x00; //Turn off ETM Trace

	FIO2DIR |= 0x1C; //set control pins for IR port to outputs
	FIO2MASK = 0xFFFFFFE3; //mask allows IR port select pins to be controlled via SET and CLR registers

	FIO2PIN = 0x0;  //intially, IR port select is 0

	//timer2 setup
	PCLKSEL1 = 0x00002000;
	PCONP |= (1 << 22); //enable timer2
	T2TCR = 0x02; //resest counter but leave it disabled
	T2PR = 0x1C;  //set prescalar for timer to get ~1us interval
	T2MR0 = 15000; //set match register for 15000 us (15 ms)
	T2MCR = 0x03; //set match register 0 to cause interrupt (when timer reaches 15 ms)
	
	//pwm setup
	PWM1TCR = TCR_RESET;			/* Reset pwm counter */ 
	PWM1PR = 0x00;					/* pwm counter is ticked every pr + 1 cycles of pll */
	PWM1MCR = PWMMR0R | PWMMR0I;	/* interrupt on PWMMR0, reset on PWMMR0 */				
	PWM1MR0 = PWM_CYCLE_36;			/* PWM1MR0 sets the period of PWM */
	PWM1MR1 = 0;		/* PWM1MR1 sets the duty cycle to 0% */
	PWM1LER = LER0_EN | LER1_EN;	/* Latch the two pwm pins */
	
	//default commandReceived boolean
	informationReceived = FALSE;

	//try and add the handlers for interrupts
  if ( install_irq( PWM0_1_INT, (void *)PWMHandler, 1 ) == FALSE )
  	{
		//couldn't add handler
		return FALSE;
  	}

	if ( install_irq( EINT3_INT, (void *)IRInputHandler, 1 ) == FALSE )
  	{
		//couldn't add handler
		return FALSE;
  	}
	
	if ( install_irq( TIMER2_INT, (void *)Timer2Handler, 3) == FALSE )
	{
		//couldn't add handler
		return FALSE;
	}
	
	//intiailize arrays
	for (i = 0; i < MAX_COMMANDS; i++)
	{
	 	commandArray[i].BinaryCommand = 0;
		commandArray[i].Properties = 0;
	}

	return TRUE;
}

void sendIRCommand(OFCommandRef cmd)
{
	int command, protocol, port;
	int commandID = cmd;

	//if commandID is invalid
	if ((commandID < 0) || (commandID >= MAX_COMMANDS))
	{
		//ReplyERR();
	 	return;
	}

	//if command in array is not valid
	if ((commandArray[commandID].Properties & COMMAND_VALID_MASK) == 0)
	{
		//ReplyERR();
		return;
	}

	//parse relevant information
	command = commandArray[commandID].BinaryCommand;
	protocol = (commandArray[commandID].Properties >> 5) & 0x07;
	port = (commandArray[commandID].Properties >> 2) & 0x07;

	//build signal
	BuildSignal(command, protocol);

	//select the desired port for the mux
	SetPort(port);

	//reset index to one
	IRSignalIndex = 1;

	//set pulse counter to first length
	pulseCounter = StaticIRSignal.components[0]->pulses;

	//set the pwm frequency
 	SetPWMFrequency(StaticIRSignal.carrier);

	//set initial duty cycle
	if (StaticIRSignal.components[0]->modulated)
	{
		SetPWMDutyCycle(StaticIRSignal.carrier * 1/3);
	}
	else
	{
	 	SetPWMDutyCycle(0);
	}	

	//enable pwm output and interrupts
	EnablePWM();

	//replyAOK();
}

OFBool isSendingCommand()
{
	return (unsigned char)sendingInformation;
}

OFBool removeIRCommand(OFCommandRef cmd)
{
	commandArray[(int)cmd].BinaryCommand = 0;
	commandArray[(int)cmd].Properties = 0;

	return TRUE;
}

void cancelIR(void)
{
	StopIROutput();
	StopIRInput();
	
	//replyAOK();
}

OFBool isIRCommandActive(OFCommandRef cmd)
{
	return commandArray[(int)cmd].Properties & COMMAND_VALID_MASK;
}

OFCommandRef getPort(OFCommandRef cmd)
{
  return (commandArray[(int)cmd].Properties & COMMAND_PORT_MASK) >> 2;
}

void recordIRCommand(OFComponentRef cmp)
{
	informationReceived = FALSE;	
	recordingPort = cmp;
	setOmnimoteMode(REC);
	
	//reset input array index
	IR_36_INDEX = 0;
	IR_38_INDEX = 0;
	IR_40_INDEX = 0;
	IR_56_INDEX = 0;

	IR_36_COUNTER = 0;
  IR_38_COUNTER = 0;
  IR_40_COUNTER = 0;
  IR_56_COUNTER = 0;

	IR_36_DATA_RX = FALSE;
  IR_38_DATA_RX = FALSE;
  IR_40_DATA_RX = FALSE;
  IR_56_DATA_RX = FALSE;

	//enable timer
	T2TCR = 0x01;

	//enable interrupts on input pins
	IO0_INT_EN_R = IR_36_IN | IR_38_IN | IR_40_IN | IR_56_IN;
	IO0_INT_EN_F = IR_36_IN | IR_38_IN | IR_40_IN | IR_56_IN;

	IO0_INT_CLR = 0xFFFFFFFF;
	
	//replyAOK();
}


OFBool isInformationReceived()
{
	return informationReceived;
}

BYTE finishRecording()
{
	int command, protocol;
	BYTE newIndex;
	int properties;
	COMMAND newCommand;

	processCommand(&command, &protocol);
	
	if ((command == -1) || (protocol == -1))
	{
		setOmnimoteMode(ERR);
		return 0xFF;
	}
	
	newIndex = (BYTE) findOpenCommandIndex();
	
	if (newIndex == 0xFF)
	{
		setOmnimoteMode(ERR);
		return 0xFF;
	}

	newCommand.BinaryCommand = command;
	
	properties = 0;
	properties += (protocol << 5);
	properties += (recordingPort << 2);
	properties += 1 << 1;
	
	newCommand.Properties = properties;
	
	commandArray[newIndex] = newCommand;

	setOmnimoteMode(OK);
	return newIndex;
}


/**********************************************************/



/*************************************************
* INTERNAL FUNCTION DEFINITIONS
*************************************************/

int findOpenCommandIndex()
{
	BYTE i;
	
	for (i = 0; i < MAX_COMMANDS;  i++)
	{
		if ((commandArray[i].Properties & 0x02) == 0) //found a place
		{
			return i;
		}
	}
	
	//no spot found for new command
	return 0xFF;
}

void StopIROutput()
{
	DisablePWM();
	sendingInformation = FALSE;
}

void StopIRInput()
{
	//disable interrupts on Timer0
	T2TCR = 0x02;
	T2MCR = 0x00;

	//clear any interrupts that may be pending
	IO0_INT_CLR = 0xFFFFFFFF;	

	//disable interrupts on input pins
	IO0_INT_EN_R = 0;
	IO0_INT_EN_F = 0;
}

void SetPWMFrequency( short cycle )
{
	PWM1MR0 = cycle;		/* set PWM cycle */

	/* Writing 1 to LER register tells micro to update match register the
		next time the timer gets reset */
	PWM1LER = LER0_EN;
}


void SetPWMDutyCycle( short cycle )
{
	PWM1MR1 = cycle;  /* set duty cycle to 1/3 active-high (2/3 active-low) */

	/* Writing 1 to LER register tells micro to update match register the
		next time the timer gets reset */
	PWM1LER = LER1_EN;
}


void EnablePWM( void )
{
	sendingInformation = TRUE;

	/* All single edge, all enable */
	PWM1PCR = PWMENA1;
	PWM1TCR = TCR_CNT_EN | TCR_PWM_EN;	/* counter enable, PWM enable */
}


void DisablePWM( void )
{
	PWM1TCR = 0;	/* Counter Reset */ 
	PWM1PCR = 0;
}


void BuildSignal( int command, int protocol )
{
	int i;
	int bit;
	IR_SIGNAL* signal;

	//if you've already built the command before, don't need to do it again
	if ((command == lastCommand) && (protocol == lastProtocol))
	{
		return;
	}

	lastCommand = command;
	lastProtocol = protocol;

	signal = &StaticIRSignal;

	switch (protocol)
	{
		case JVC_PROTOCOL:
			signal->carrier = PWM_CYCLE_38;
			signal->length = (JVC_STANDARD_LENGTH + 1) * 2; //length of command plus start bit

			signal->components[0] = &(JVC_START.first_half);
			signal->components[1] = &(JVC_START.second_half);

			for (i = 0; i < JVC_STANDARD_LENGTH - 1; i++)
			{
				bit = (command >> ((JVC_STANDARD_LENGTH - 2) - i)) & 0x01;

				if (bit == 0) //send a zero
				{
					signal->components[2*i + 2] = &(JVC_LOGIC_0.first_half);
					signal->components[2*i + 3] = &(JVC_LOGIC_0.second_half);
				}
				else //send a one
				{
					signal->components[2*i + 2] = &(JVC_LOGIC_1.first_half);
					signal->components[2*i + 3] = &(JVC_LOGIC_1.second_half);
				}
			}

			signal->components[2*i + 2] = &(JVC_LOGIC_0.first_half);
			signal->components[2*i + 3] = &(JVC_LOGIC_0.second_half);

			break;

		case NEC_PROTOCOL:
			signal->carrier = PWM_CYCLE_38;
			signal->length = (NEC_STANDARD_LENGTH + 1) * 2; //length of command plus start bit

			signal->components[0] = &(NEC_START.first_half);
			signal->components[1] = &(NEC_START.second_half);

			for (i = 0; i < NEC_STANDARD_LENGTH - 1; i++)
			{
				bit = (command >> ((NEC_STANDARD_LENGTH - 2) - i)) & 0x01;

				if (bit == 0) //send a zero
				{
					signal->components[2*i + 2] = &(NEC_LOGIC_0.first_half);
					signal->components[2*i + 3] = &(NEC_LOGIC_0.second_half);
				}
				else //send a one
				{
					signal->components[2*i + 2] = &(NEC_LOGIC_1.first_half);
					signal->components[2*i + 3] = &(NEC_LOGIC_1.second_half);
				}
			}

			signal->components[2*i + 2] = &(NEC_LOGIC_0.first_half);
			signal->components[2*i + 3] = &(NEC_LOGIC_0.second_half);

			break;

		case SIRC_PROTOCOL:
			signal->carrier = PWM_CYCLE_40;
			signal->length = SIRC_STANDARD_LENGTH * 2; //length of command plus start bit

			signal->components[0] = &(SIRC_START.first_half);
			signal->components[1] = &(SIRC_START.second_half);

			for (i = 0; i < SIRC_STANDARD_LENGTH - 1; i++)
			{
				bit = (command >> ((SIRC_STANDARD_LENGTH - 2) - i)) & 0x01;

				if (bit == 0) //send a zero
				{
					signal->components[2*i + 2] = &(SIRC_LOGIC_0.first_half);
					signal->components[2*i + 3] = &(SIRC_LOGIC_0.second_half);
				}
				else //send a one
				{
					signal->components[2*i + 2] = &(SIRC_LOGIC_1.first_half);
					signal->components[2*i + 3] = &(SIRC_LOGIC_1.second_half);
				}
			}
			break;

 		case RCA_PROTOCOL:
			signal->carrier = PWM_CYCLE_56;
			signal->length = (RCA_STANDARD_LENGTH + 1) * 2; //length of command plus start bit

			signal->components[0] = &(RCA_START.first_half);
			signal->components[1] = &(RCA_START.second_half);

			for (i = 0; i < RCA_STANDARD_LENGTH - 1; i++)
			{
				bit = (command >> ((RCA_STANDARD_LENGTH - 2) - i)) & 0x01;

				if (bit == 0) //send a zero
				{
					signal->components[2*i + 2] = &(RCA_LOGIC_0.first_half);
					signal->components[2*i + 3] = &(RCA_LOGIC_0.second_half);
				}
				else //send a one
				{
					signal->components[2*i + 2] = &(RCA_LOGIC_1.first_half);
					signal->components[2*i + 3] = &(RCA_LOGIC_1.second_half);
				}
			}

			signal->components[2*i + 2] = &(RCA_LOGIC_0.first_half);
			signal->components[2*i + 3] = &(RCA_LOGIC_0.second_half);

			break;

		default: //this case handles RC5 as well as any undefined protocols
			signal->carrier = PWM_CYCLE_36;
			signal->length = RCA_STANDARD_LENGTH * 2; //length of command plus two start bits and a toggle

			signal->components[0] = &(RC5_LOGIC_1.first_half);
			signal->components[1] = &(RC5_LOGIC_1.second_half);
			signal->components[2] = &(RC5_LOGIC_1.first_half);
			signal->components[3] = &(RC5_LOGIC_1.second_half);

			if (rc5Toggle == 0)
			{
				signal->components[4] = &(RC5_LOGIC_0.first_half);
				signal->components[5] = &(RC5_LOGIC_0.second_half);
			}
			else
			{
			 	signal->components[4] = &(RC5_LOGIC_1.first_half);
				signal->components[5] = &(RC5_LOGIC_1.second_half);
			}

			rc5Toggle = 1 - rc5Toggle; //1 - 1 = 0. 1 - 0 = 1.  Toggles the variable between 1 and 0

			for (i = 0; i < RC5_STANDARD_LENGTH - 3; i++)
			{
				bit = (command >> ((RC5_STANDARD_LENGTH - 4) - i)) & 0x01;

				if (bit == 0) //send a zero
				{
					signal->components[2*i + 6] = &(RC5_LOGIC_0.first_half);
					signal->components[2*i + 7] = &(RC5_LOGIC_0.second_half);
				}
				else //send a one
				{
					signal->components[2*i + 6] = &(RC5_LOGIC_1.first_half);
					signal->components[2*i + 7] = &(RC5_LOGIC_1.second_half);
				}
			}
			break;
	}

  	return;
}

void SetPort( int port )
{
   //set port
	 int reg = 0;

	//set least significant port bit
	if (port & 0x1)
	{
		reg |= 0x10;
	}

	//set middle port bit
	if (port & 0x2)
	{
		reg |= 0x08;
	}

	//set most significant port bit
	if (port & 0x4)
	{
		reg |= 0x04;
	}

	FIO2PIN = reg;
}

							 
int findBestArray(void)
{
 	if (IR_36_INDEX > IR_38_INDEX)
	{
		if (IR_36_INDEX > IR_40_INDEX)
		{
			if (IR_36_INDEX > IR_56_INDEX)
			{
				return 0;
			}
			else
			{
				return 3;
			}
		}
		else
		{
			if (IR_40_INDEX > IR_56_INDEX)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
	else
	{
		if (IR_38_INDEX > IR_40_INDEX)
		{
			if (IR_38_INDEX > IR_56_INDEX)
			{
				return 1;
			}
			else
			{
				return 3;
			}
		}
		else
		{
			if (IR_40_INDEX > IR_56_INDEX)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
}								 

/******************************************************************************
** Function name:		processCommand
**
** Descriptions:		Looks at the four IR arrays and tries to determine the command/protocol.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void processCommand( int* command, int* protocol )
{
	short* array;
	int arrayIndex;
	int arrayNum = -1;

	arrayNum = findBestArray();

	switch (arrayNum)
	{
	 	case 0:
			array = IR_36_INPUT_ARRAY;
			arrayIndex = IR_36_INDEX;
			break;

		case 1:
			array = IR_38_INPUT_ARRAY;
			arrayIndex = IR_38_INDEX;
			break;

		case 2:
			array = IR_40_INPUT_ARRAY;
			arrayIndex = IR_40_INDEX;
			break;

		case 3:
			array = IR_56_INPUT_ARRAY;
			arrayIndex = IR_56_INDEX;
			break;

		default:
			*command = -1;
			return;
	}
	
	*protocol = findClosestProtocol(array);
	
	switch (*protocol)
	{
		case JVC_PROTOCOL:
			*command = parseStandardProtocol(array, arrayIndex, 526, 1574, JVC_PULSE_LENGTH);
			break;
		
		case NEC_PROTOCOL:
			*command = parseStandardProtocol(array, arrayIndex, 560, 1690, NEC_PULSE_LENGTH);
			break;
			
		case SIRC_PROTOCOL:
			*command = parseSIRCProtocol(array, arrayIndex);
			break;
		
		case RC5_PROTOCOL:
			*command = parseRC5(array, arrayIndex);
			break;
			
		case RCA_PROTOCOL:
			*command = parseStandardProtocol(array, arrayIndex, 1000, 2000, RCA_PULSE_LENGTH);
			break;
		
		default:
			//no protocol found
			*command = -1;											    
	}

	return;
}

int parseStandardProtocol(short* array, int arrayIndex, int Logic_Zero, int Logic_One, int Pulse_Length)
{
	int i;
	int p2;
	int result = 0;
	
	//not enough input for real command
	if (arrayIndex < Pulse_Length)
	{
		return -1;
	}
	
	for (i = 3; i < Pulse_Length - 1; i += 2)
	{
		p2 = array[i + 1];
		
		if ((p2 > (Logic_Zero*0.8)) &&  (p2 < (Logic_Zero*1.2))) //logic 0
		{
			result = (result << 1);
		}
		else if ((p2 > (Logic_One*0.8)) &&  (p2 < (Logic_One*1.2))) //logic 1
		{
			result = (result << 1) + 1;
		}
		else //unrecognized bit, return
		{
			return -1;
		} 
	}

	return result;
}

int parseSIRCProtocol(short* array, int arrayIndex)
{
	int i;
	int p2;
	int result = 0;
	
	//not enough input for real command
	if (arrayIndex < SIRC_PULSE_LENGTH)
	{
		return -1;
	}
	
	for (i = 3; i < SIRC_PULSE_LENGTH; i += 2)
	{
		p2 = array[i];
		
		if ((p2 > (600*0.8)) &&  (p2 < (600*1.2))) //logic 0
		{
			result = (result << 1);
		}
		else if ((p2 > (1200*0.8)) &&  (p2 < (1200*1.2))) //logic 1
		{
			result = (result << 1) + 1;
		}
		else //unrecognized bit, return
		{
			return -1;
		} 
	}

	return result;
}

int parseRC5(short* array, int arrayIndex)
{
	int convertedCommand = 0;
	int state = 1;
	int i;
	int result = 0;

	for (i = 1; i < arrayIndex; i++)
	{
	 	if ((array[i] > (889*0.8)) && (array[i] < (889*1.2))) //one bit
		{
			convertedCommand = (convertedCommand << 1) + state;
		}
		else if ((array[i] > (1778*0.8)) && (array[i] < (1778*1.2))) //two bits
		{
			convertedCommand = (convertedCommand << 1) + state;
			convertedCommand = (convertedCommand << 1) + state;
		}
		else
		{
			//error parsing message
		 	return -1;
		}

		state = 1 - state; // 1 - 0 = 1, 1 - 1 = 0.  Toggles variable between 1 and 0
	}

	//check if another zero needs to be appended, in case last bit was a 1->0 transition
	if (convertedCommand < 0x04000000)
	{
	 	convertedCommand = (convertedCommand << 1);
	}

	//convertedCommand now holds binary representation of signal

	for (i = 20; i >= 0; i -= 2)
	{
		if (((convertedCommand >> i) & 0x03) == 0x01) // logic 1
		{
			result = (result << 1) + 1;
		}
		else if (((convertedCommand >> i) & 0x03) == 0x02) // logic 0
		{
			result = (result << 1);
		}
		else
		{
		 	//unrecognized sequence
			return -1;
		}
	}

	return result;
}

int findClosestProtocol(short* array)
{
	int firstBit = array[1];
	
	if ((firstBit >= JVC_PROTOCOL_MIN) && (firstBit <= JVC_PROTOCOL_MAX))
	{
		return JVC_PROTOCOL;
	}
	else if ((firstBit >= NEC_PROTOCOL_MIN) && (firstBit <= NEC_PROTOCOL_MAX))
	{
		return NEC_PROTOCOL;
	}
	else if ((firstBit >= SIRC_PROTOCOL_MIN) && (firstBit <= SIRC_PROTOCOL_MAX))
	{
		return SIRC_PROTOCOL;
	}
	else if ((firstBit >= RC5_PROTOCOL_MIN) && (firstBit <= RC5_PROTOCOL_MAX))
	{
		return RC5_PROTOCOL;
	}
	else if ((firstBit >= RCA_PROTOCOL_MIN) && (firstBit <= RCA_PROTOCOL_MAX))
	{
		return RCA_PROTOCOL;
	}

	return -1;
}

