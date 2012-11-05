/*
 *  OFMessage.h
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/14/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */
#define __OFMessage

#ifndef __OFButton
#include "OFButton.h"
#endif

#ifndef __OFController
#include "OFController.h"
#endif

#ifndef	__OFCommand
#include "OFCommand.h"
#endif

#ifndef __OFComponent
#include "OFComponent.h"
#endif

#ifndef __OFIRInterface
#include "OFIRInterface.h"
#endif

#define OFMessage_EOM (BYTE)0xFF
#define OFMessage_SOM	(BYTE)0xFE
#define OFMessage_ERR (BYTE)OFNullRef
#define OFMessage_AOK (BYTE)0x00
#define RX_MAX_LEN (BYTE)0xFF
#define TX_MAX_LEN (BYTE)0xFF
#define MSG_OVERHEAD (BYTE)3 //MessageByte + arg1 + EOM

typedef unsigned char OFMessageArg;
typedef unsigned char* OFMessageArgRef;

void initializeMessage(void);
extern void TxData(void);
void updateWifi(void);

void updateWiFi(void);

OFBool enterCmdMode(void);
OFBool exitCmdMode(void);
OFBool endCmd(const BYTE* );
OFBool waitForReply(const BYTE *);
OFBool RxMatch(const BYTE*);
void OFMessageWait(int sec);

void TxString(char* s);

OFBool STDInit(void);

OFBool connect(void);
OFBool disconnect(void);

OFBool RxByte(unsigned char b);
OFBool TxByte(unsigned char b);

void replyIRCommand(OFCommandRef cmd);
void replyOFBool(OFBool result);
void replyAOK(void);
void replyERR(void);
void replyByte(OFMessageArg reply);
void replyBytes(OFMessageArgRef reply);

OFBool openMsg(void);

OFBool closeMsg(void);

unsigned char nextByte(void);

void processMessage(void);
void stringToByte(char*s, BYTE*a);

enum OFMessage{
	OFMessageConnect,					//	byte byte*				// ret:	stat	-0
	OFMessageSetControllerName,		//	ctrl	unsigned char*	// ret:	stat 1
	OFMessageGetControllers,		//					// ret:	ctrl*							 2
	OFMessageGetControllerName,		//	ctrl			// ret:	unsigned char*	3
	OFMessageAddControllerButton,	//	ctrl	btn		// ret:	stat					 4
	OFMessageRemoveControllerButton, //	ctrl	btn		// ret:	stat					5
	OFMessageGetControllerButtons,	//	ctrl			// ret:	btn*						 6
	OFMessageAddController,			//					// ret:	ctrl									 7
	OFMessageRemoveController,		//	ctrl			// ret:	ctrl							 8
	OFMessageGetButtons,			//					// ret:	btn*										 9
	OFMessageSetButtonName,			//	btn		unsigned char*	// ret:	stat		 10
	OFMessageGetButtonName,			//	btn				// ret:	unsigned char*			 11
	OFMessageGetButtonCommands,		//	btn				// ret:	cmd*							 12
	OFMessageAddButtonCommand,		//	btn		cmd		// ret:	stat							13
	OFMessageRemoveButtonCommand,	//	btn		cmd		// ret:	stat						 14
	OFMessageSetButtonImage,			//	btn		img		// ret:	stat						 15
	OFMessageGetButtonImage,			//	btn				// ret:	img								 16
	OFMessageAddButton,				//					// ret:	btn												17
	OFMessageRemoveButton,			//	btn				// ret:	btn										18
	OFMessageSetCommandName,			//	cmd		unsigned char*	// ret:	stat		19
	OFMessageGetCommandName,			//	cmd				// ret:	unsigned char*			 20
	OFMessageSetComponentName,		//	cmp		unsigned char*	// ret:	stat			21
	OFMessageGetComponentName,		//	cmp				// ret:	unsigned char*				22
	OFMessageRemoveComponent,		//	cmp				// ret:	cmp											23
	OFMessageGetCommands,			//		cmp			// ret cmd*;										 24
	OFMessageRecordCommand,			//	cmp				// ret:	cmd										 25
	OFMessageRemoveCommand,			//	cmd				// ret:	stat									 26
	OFMessageSendCommand,			//	cmd				// ret:	stat										 27
	OFMessageCancel,					//					// ret:	stat											 28
	OFMessageDisconnect,																			//								 29
	OFMessageSTDInit,								// 30  
	OFMessageConnPulse						// 31
};



