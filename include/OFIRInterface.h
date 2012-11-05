/*
 *  OFIRInterface.h
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/14/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */
 
#ifndef __OFIRInterface
#define __OFIRInterface

			
#ifndef __OmnimoteFoundation
#include "OmnimoteFoundation.h"
#endif

#ifndef	__OFMessage
#include "OFMessage.h"
#endif

//Definition Statements Used Exclusively by IR Interface
#define	PWMMR0I				1
#define	PWMMR0R				2

//Interrupt Constants
#define TIMER0_INT			4
#define	PWM0_1_INT			8
#define	EINT3_INT			17
//#define	HIGHEST_PRIORITY	1

//IR Input Ports
#define IR_36_IN			1 << 13
#define IR_38_IN			1 << 28
#define IR_40_IN			1 << 27
#define IR_56_IN			(unsigned int)1 << 31

//cycle count for each required carrier frequency
#define PWM_CYCLE_36		400
#define PWM_CYCLE_38		379
#define PWM_CYCLE_40		360
#define PWM_CYCLE_56		257

//MRX_INT is the bit for setting interrupt of MRX
#define MR0_INT			1 << 0

//Define the bits for managing the timer counter
#define TCR_CNT_EN		0x00000001
#define TCR_RESET		0x00000002
#define TCR_PWM_EN		0x00000008

//PWMENAX = enable pwm on port X
#define PWMSEL2			1 << 2
#define PWMSEL3			1 << 3
#define PWMSEL4			1 << 4
#define PWMSEL5			1 << 5
#define PWMSEL6			1 << 6
#define PWMENA1			1 << 9
#define PWMENA2			1 << 10
#define PWMENA3			1 << 11
#define PWMENA4			1 << 12
#define PWMENA5			1 << 13
#define PWMENA6			1 << 14

//Enables shadow latch on match register X.  This allows the
// match register to be updated on next PWM reset
#define LER0_EN			1 << 0
#define LER1_EN			1 << 1
#define LER2_EN			1 << 2
#define LER3_EN			1 << 3
#define LER4_EN			1 << 4
#define LER5_EN			1 << 5
#define LER6_EN			1 << 6

//******************************************************************
//*The following definitions set the protocol enums, as well as
//* the min/max lengths of each start bit so we can recognize them
//* as inputs. 
//*******************************************************************
#define JVC_PROTOCOL 					0
#define JVC_PROTOCOL_MIN			7500
#define JVC_PROTOCOL_MAX			8700
#define JVC_STANDARD_LENGTH			17 //16 bits + 1 start
#define JVC_PULSE_LENGTH			36

#define NEC_PROTOCOL 					1
#define NEC_PROTOCOL_MIN			8700
#define NEC_PROTOCOL_MAX			9500
#define NEC_STANDARD_LENGTH			33 //32 bits + 1 start
#define NEC_PULSE_LENGTH			68

#define SIRC_PROTOCOL 				2
#define SIRC_PROTOCOL_MIN			1645
#define SIRC_PROTOCOL_MAX			3200
#define SIRC_STANDARD_LENGTH		13 //12 bits + 1 start
#define SIRC_PULSE_LENGTH			26

#define RC5_PROTOCOL 					3	
#define RC5_PROTOCOL_MIN			400
#define RC5_PROTOCOL_MAX			1645
#define RC5_STANDARD_LENGTH			14 //11 bits + 2 start + 1 toggle

#define RCA_PROTOCOL 					4
#define RCA_PROTOCOL_MIN			3200
#define RCA_PROTOCOL_MAX			4800
#define RCA_STANDARD_LENGTH			25 //24 bits + 1 start
#define RCA_PULSE_LENGTH			52
//***************************************************************
												
//Masks used to determine information about a command												
#define COMMAND_PROTOCOL_MASK	0xE0
#define COMMAND_PORT_MASK 		0x1C
#define COMMAND_VALID_MASK		0x02

//holds a single pulse.  Modulated tells whether to modulate during
// the output, and pulses tells how long to keep the signal active
typedef struct  
{
	char modulated;
	short pulses;
} IR_PULSE;

//holds a logical value from any protocol. (ie '1' or '0')
typedef struct 
{
	IR_PULSE first_half;
	IR_PULSE second_half;
} SIGNAL_COMPONENT;

//holds an IR signal.  Length shows how many components are involved in the command.
// components is the array of components to send.  carrier holds the frequency
typedef struct 
{
	char length;
	IR_PULSE* components[70];
	short carrier; //holds number of pwm cycles required for carrier
} IR_SIGNAL;

typedef struct 
{
	int BinaryCommand;
	char Properties; // b7-5 = protocol, b4-2 = port to send
					  			 // b1 = valid, b0 = undefined
} COMMAND;

static COMMAND commandArray[MAX_COMMANDS];

//Staticly define the values of each logic value for each protocol.  These will
//be used to build IR signals given a binary command.
//
//static SIGNAL_COMPONENT [PROTOCOL]_[VALUE] = {{bool,int},{bool,int}};

static SIGNAL_COMPONENT JVC_START = {{TRUE, 320}, {FALSE, 160}};
static SIGNAL_COMPONENT JVC_LOGIC_1 = {{TRUE, 20}, {FALSE, 60}};
static SIGNAL_COMPONENT JVC_LOGIC_0 = {{TRUE, 20}, {FALSE, 20}};

static SIGNAL_COMPONENT NEC_START = {{TRUE, 342}, {FALSE, 171}};
static SIGNAL_COMPONENT NEC_LOGIC_1 = {{TRUE, 21}, {FALSE, 65}};
static SIGNAL_COMPONENT NEC_LOGIC_0 = {{TRUE, 21}, {FALSE, 22}};

static SIGNAL_COMPONENT SIRC_START = {{TRUE, 96}, {FALSE, 24}};
static SIGNAL_COMPONENT SIRC_LOGIC_1 = {{TRUE, 48}, {FALSE, 24}};
static SIGNAL_COMPONENT SIRC_LOGIC_0 = {{TRUE, 24}, {FALSE, 24}};

static SIGNAL_COMPONENT RC5_LOGIC_1 = {{FALSE, 32}, {TRUE, 32}};
static SIGNAL_COMPONENT RC5_LOGIC_0 = {{TRUE, 32}, {FALSE, 32}};

static SIGNAL_COMPONENT RCA_START = {{TRUE, 152}, {FALSE, 152}};
static SIGNAL_COMPONENT RCA_LOGIC_1 = {{TRUE, 28}, {FALSE, 112}};
static SIGNAL_COMPONENT RCA_LOGIC_0 = {{TRUE, 28}, {FALSE, 56}};

static IR_SIGNAL StaticIRSignal;
static int lastCommand;
static int lastProtocol;
static int IRSignalIndex;
static int recordingPort = 0;
static int rc5Toggle = 0;
static int informationReceived = 0;
static int pulseCounter = 0;
static int sendingInformation = 0;

//arrays to hold ir inputs
static short IR_36_INPUT_ARRAY[70];
static short IR_38_INPUT_ARRAY[70];
static short IR_40_INPUT_ARRAY[70];
static short IR_56_INPUT_ARRAY[70];

//indexes to arrays declared above
static int IR_36_INDEX = 0;
static int IR_38_INDEX = 0;
static int IR_40_INDEX = 0;
static int IR_56_INDEX = 0;

//counts for each receiver
static int IR_36_COUNTER = 0;
static int IR_38_COUNTER = 0;
static int IR_40_COUNTER = 0;
static int IR_56_COUNTER = 0;

static int IR_36_DATA_RX = FALSE;
static int IR_38_DATA_RX = FALSE;
static int IR_40_DATA_RX = FALSE;
static int IR_56_DATA_RX = FALSE;

//external function declarations
void STDInitIR(void);
OFBool intializeIRControl(void);
void recordIRCommand(OFComponentRef cmp);
BYTE finishRecording(void);
OFBool isInformationReceived(void);
void sendIRCommand(OFCommandRef cmd);
OFBool isSendingCommand(void);
OFBool removeIRCommand(OFCommandRef cmd);
void cancelIR(void);
OFBool isIRCommandActive(OFCommandRef cmd);
OFCommandRef getPort(OFCommandRef cmd);

extern void setOmnimoteMode(enum OFMode mode);

						
#endif
