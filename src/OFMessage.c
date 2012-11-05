/*
 *  OFMessage.c
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/14/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */



#ifndef __OFMessage
#include "OFMessage.h"
#endif

#include "OFIRInterface.h"
#include "timer.h"

BYTE OFMessageTxBuffer[TX_MAX_LEN];
BYTE OFMessageRxBuffer[RX_MAX_LEN];
BYTE TXIndex;
BYTE RXIndex;
BYTE OFDeviceConn;
OFBool OFRxFlag; // Set when OF_EOM is received, cleared when message is proccessed
OFBool OFTxFlag; // Set when OF_EOM is written to transmit buffer, cleared when OF_EOM is transmitted
OFBool OFCmdFlag = FALSE; // Set when OF_EOM is written to transmit buffer, cleared when OF_EOM is transmitted
int OFMessageTimer;
int OFConnectTimer = 0;
OFBool InitFlag = FALSE;
const BYTE OFReplyEXIT[] = {0x45, 0x58, 0x49};
const BYTE OFReplyAOK[] = {0x41, 0x4F, 0x4B};
const BYTE OFReplyCMD[] = {0x43, 0x4D, 0x44};


void initializeMessage(void){
	BYTE t;
	BYTE r;
	TXIndex = 0;
	RXIndex = 0;
	OFRxFlag = FALSE;
	OFTxFlag = FALSE;
	for(t = 0; t < TX_MAX_LEN; t++){
		OFMessageTxBuffer[t] = OFNullRef;
	}
	for(r = 0; r < RX_MAX_LEN; r++){
		OFMessageRxBuffer[r] = OFNullRef;
	}
}

void updateWiFi(void){
 
	BYTE ch = 0;
	BYTE ct = 2;
	BYTE co = 1;
	int signal = 0;
	if(enterCmdMode() == FALSE)	{
		exitCmdMode();
	 	return; 
	}

	TxString("show connection");
	TxByte(0x0D);
	TxByte(0xFF);
	RXIndex = 0;
	OFRxFlag = FALSE;
	TxData();
	OFMessageWait(1);
  co = OFMessageRxBuffer[4];
	if(co != '3' && co != '7' && co != 'B' && co != 'F') {
		setWiFiStrength(0);
		return;
	} 

	TxString("show rssi");
	TxByte(0x0D);
	TxByte(0xFF);
	RXIndex = 0;
	OFRxFlag = FALSE;
	TxData();
	OFMessageWait(1);
	
	ch = OFMessageRxBuffer[7];
	ct = OFMessageRxBuffer[8];
	co = OFMessageRxBuffer[9];

	if(ct == ')'){
	  signal = ch - 0x30;
	}else if(co == ')'){
		 signal = (ch-0x30)*10 + (ct-0x30);
	}else{	
		 signal = (ch-0x30)*100 + (ct-0x30)*10 + (co-0x30);
	}
  
	signal = 120-signal;

	if(signal <= 120){
		if(signal >= 100){
		  setWiFiStrength(5);
		}else if(signal >= 80){
			setWiFiStrength(4);
		}else if(signal >= 60){
		  setWiFiStrength(3);
		}else if (signal >= 40){
		  setWiFiStrength(2);
		}else if (signal >= 0){
		  setWiFiStrength(1);
		}else{
			setWiFiStrength(0);
		}
	}
	
	exitCmdMode();
	return;  

}

OFBool enterCmdMode(void){
	OFCmdFlag = TRUE;
	TXIndex = 0;
	OFTxFlag = FALSE;
	TxString("$$$");
	TxByte(0xFF);
	TxData();
	return waitForReply(OFReplyCMD);
}

OFBool exitCmdMode(void){
	TxString("save");
	if(endCmd(0x00) == FALSE) {OFCmdFlag = FALSE; return FALSE;}
	TxString("exit");
	if(endCmd(OFReplyEXIT) == FALSE) {OFCmdFlag = FALSE; return FALSE;}
	OFCmdFlag = FALSE;
	return TRUE;
}

OFBool endCmd(const BYTE* array){
	TxByte(0x0D);
	TxByte(0xFF);
	TxData();
	return waitForReply(array);
}

OFBool waitForReply(const BYTE* array){
	OFRxFlag = FALSE;
	RXIndex = 0;
	OFMessageTimer = 0;
	while(OFMessageTimer < 20){
		if(RxMatch(array) == TRUE){ RXIndex = 0; return TRUE; }
	}
	RXIndex = 0;
	if(array == 0x00) return TRUE;
	return FALSE;
}

void OFMessageWait(int sec){
	int i = 0;
	while(i<sec){
		OFMessageTimer = 0;
		while(OFMessageTimer < 20);
		i++;
	}
}


OFBool RxByte(unsigned char b){
	if(OFRxFlag == TRUE) return FALSE;
	if(RXIndex >= RX_MAX_LEN) return FALSE;
	OFMessageRxBuffer[RXIndex++] = b;
	if(b == OFMessage_EOM) {
		RXIndex = 0;
		OFRxFlag = TRUE;
	}//else if(closeMsg()){
//		RXIndex = 0;
//		OFRxFlag = FALSE;
//		disconnect();
//	}else if(openMsg()){
//		replyOFBool(connect());
//		RXIndex = 0;
////	}
//	if((OFCmdFlag == TRUE) && RXIndex == 3){
//		OFRxFlag = TRUE;
//	}
	return TRUE;
}

OFBool TxByte(unsigned char b){
	if(OFTxFlag == TRUE) return FALSE;
	if(TXIndex >= TX_MAX_LEN){
		TXIndex = 0;
		OFMessageTxBuffer[0] = OFNullRef;
		OFTxFlag = TRUE;
		return FALSE;
	}
	OFMessageTxBuffer[TXIndex++] = b;
	if(b == OFMessage_EOM) {
		TXIndex = 0;
		OFTxFlag = TRUE;
	}
	return TRUE;
}

OFBool RxMatch(const BYTE* array){
  int i;
	if(array == 0x00) return FALSE;
	for(i = 0; i < 3; i++){
		if(array[i] != OFMessageRxBuffer[i]) return FALSE;
	}
	return TRUE;	
}

OFBool openMsg(void){

	 if(OFMessageRxBuffer[0] == 0x2A &&
		 OFMessageRxBuffer[1] == 0x4F &&
		 OFMessageRxBuffer[2] == 0x50 &&
		 OFMessageRxBuffer[3] == 0x45 &&
		 OFMessageRxBuffer[4] == 0x4E &&
		 OFMessageRxBuffer[5] == 0x2A) return TRUE;
		 return FALSE;
}

OFBool closeMsg(void){
	 if(OFMessageRxBuffer[0] == 0x2A &&
	   OFMessageRxBuffer[1] == 0x43 &&
		 OFMessageRxBuffer[2] == 0x4C &&
		 OFMessageRxBuffer[3] == 0x4F &&
		 OFMessageRxBuffer[4] == 0x53 &&
		 OFMessageRxBuffer[5] == 0x2A) return TRUE;
	 if(OFMessageRxBuffer[0] == 0x43 &&
		 OFMessageRxBuffer[1] == 0x4C &&
		 OFMessageRxBuffer[2] == 0x4F &&
		 OFMessageRxBuffer[3] == 0x53 &&
		 OFMessageRxBuffer[4] == 0x2A) return TRUE;
		 return FALSE;
}

void replyIRCommand(OFCommandRef cmd){
	if(cmd != (OFCommandRef)OFNullRef){
		TxByte(cmd);
	}
	TxByte(OFMessage_EOM);
}

void replyAOK(void){
	TxByte(OFMessage_AOK);
	TxByte(OFMessage_EOM);
}

void replyERR(void){
	TxByte(OFMessage_ERR);
}

void replyOFBool(OFBool result){
	if(result == TRUE){
		replyAOK();
	}else{
		replyERR();
	}
}

void replyByte(OFMessageArg reply){
	if(reply != (OFMessageArg)OFNullRef){
		TxByte(reply);
	}
	TxByte(OFMessage_EOM);
}

void replyBytes(OFMessageArgRef reply){
	BYTE i;
	if(reply != NULL){
		for(i = 0; i < (TX_MAX_LEN-MSG_OVERHEAD); i++){
			if((reply[i] != OFMessage_EOM) && (reply[i] != OFNullRef)){
				TxByte(reply[i]);
			}else{
				break;
			}
		}
	}
	TxByte(OFMessage_EOM);
}


unsigned char nextByte(void){
	BYTE b;
	b = OFMessageTxBuffer[TXIndex++];
	if(OFTxFlag == FALSE) return OFMessage_EOM;
	if(b == OFMessage_EOM){
		TXIndex = 0;
		OFTxFlag = FALSE;
	}
	return b;
}

void processMessage(void){
	enum OFMessage msg;
	OFMessageArg arg0;
	OFMessageArgRef arg0Ref;
	OFMessageArg arg1;
	OFMessageArgRef arg1Ref;
	BYTE i;
	msg = (enum OFMessage) OFMessageRxBuffer[0];
	arg0 = (OFMessageArg) OFMessageRxBuffer[1];
	arg0Ref = (OFMessageArgRef) &(OFMessageRxBuffer[1]);
	arg1 = (OFMessageArg) OFMessageRxBuffer[2];
	arg1Ref = (OFMessageArgRef) &(OFMessageRxBuffer[2]);
	
	//if((msg != OFMessageConnect) && (OFDeviceConn == FALSE))	 replyERR();
	OFConnectTimer = 0;
	switch (msg) {
		case OFMessageConnect:
			//enterCmdMode();

			//TxString("open");
			//for(i = 0; arg0Ref[i] != OFMessage_EOM; i++){
			//	TxByte(arg0Ref[i]);
			//}
			//TxString(" 3000");
			//endCmd();
		

			//exitCmdMode();

			//TxString("Test");
			//TxByte(0xFF);

			//while (OFTxFlag == TRUE);

			//enterCmdMode();
			
			//TxString("close");
			//endCmd();
			
			//exitCmdMode();		
			replyOFBool(connect());
			break;
		case OFMessageSetControllerName:
			replyOFBool(setControllerName(arg0, arg1Ref));
			break;
		case OFMessageGetControllers:
			for(i = 0; i < MAX_CONTROLLERS; i++){
				if(isControllerActive(i) == TRUE){
					TxByte(i);
				}
			}
			TxByte(OFMessage_EOM);
			break;
		case OFMessageGetControllerName:
			replyBytes(getControllerName(arg0));
			break;
		case OFMessageAddControllerButton:
			replyOFBool(addControllerButton(arg0, arg1));
			break;
		case OFMessageRemoveControllerButton:
			replyOFBool(removeControllerButton(arg0, arg1));
			break;
		case OFMessageGetControllerButtons:
			replyBytes(getControllerButtons(arg0));
			break;
		case OFMessageAddController:
			replyByte(addController(arg0Ref));
			break;
		case OFMessageRemoveController:
			replyByte(removeController(arg0));
			break;
		case OFMessageGetButtons:
			for(i = 0; i < MAX_BUTTONS; i++){
				if(isButtonActive(i)){
					TxByte(i);
				}
			}
			TxByte(OFMessage_EOM);
			break;
		case OFMessageSetButtonName:
			replyOFBool(setButtonName(arg0,arg1Ref));
			break;
		case OFMessageGetButtonName:
			replyBytes(getButtonName(arg0));
			break;
		case OFMessageGetButtonCommands:
			replyBytes(getButtonCommands(arg0));
			break;
		case OFMessageAddButtonCommand:
			replyOFBool(addButtonCommand(arg0, arg1));
			break;
		case OFMessageRemoveButtonCommand:
			replyOFBool(removeButtonCommand(arg0, arg1));
			break;
		case OFMessageSetButtonImage:
			replyOFBool(setButtonImage(arg0, arg1));
			break;
		case OFMessageGetButtonImage:
			replyByte(getButtonImage(arg0));
			break;
		case OFMessageAddButton:
			replyByte(addButton(arg0Ref));
			break;
		case OFMessageRemoveButton:
			if(removeButton(arg0) == arg0){
				for(i = 0; i < MAX_CONTROLLERS; i++){
					removeControllerButton(i, arg0);
				}
				replyByte(arg0);
			}else{
				replyERR();
			}
			break;
		case OFMessageSetCommandName:
			replyOFBool(setCommandName(arg0, arg1Ref));
			break;
		case OFMessageGetCommandName:
			replyBytes(getCommandName(arg0));
			break;
		case OFMessageSetComponentName:
			replyOFBool(setComponentName(arg0, arg1Ref));
			break;
		case OFMessageGetComponentName:
			replyBytes(getComponentName(arg0));
			break;
		case OFMessageRemoveComponent:
			replyOFBool(removeComponent(arg0));
			break;
		case OFMessageGetCommands:
		//arg0
			for(i = 0; i < MAX_COMMANDS;  i++){
				if( (isIRCommandActive(i) != FALSE) && (getPort(i) == arg0)){
					TxByte(i);
				}
			}
			TxByte(OFMessage_EOM);
			break;
		// ******* DYNAMIC REPLY
		case OFMessageRecordCommand:
			if(isComponentActive(arg0) == FALSE){
				replyERR();
			}else{
				recordIRCommand(arg0);
			}
			break;
		case OFMessageSendCommand:
			if(isIRCommandActive(arg0) == FALSE){
				replyERR();
			}else{
				sendIRCommand(arg0);
			}
			break;
		case OFMessageRemoveCommand:
			if(isIRCommandActive(arg0) == FALSE){
				replyERR();
			}else{
				if(removeIRCommand(arg0) == FALSE){
					replyERR();
				}else{
					for(i = 0; i < MAX_BUTTONS; i++){
						removeButtonCommand(i,arg0);
					}
					replyAOK();
				}
			}
			break;
		case OFMessageCancel:
			cancelIR();
			replyAOK();
			break;
		// ******* END DYNAMIC REPLY
		case OFMessageDisconnect:
			replyOFBool(disconnect());
			break;
		case OFMessageSTDInit:
			replyOFBool(STDInit());
			break;
		case OFMessageConnPulse:
			break;
		default:
			replyERR();
			break;
	}
	OFRxFlag = FALSE;
}

OFBool connect(void){
	  OFDeviceConn = TRUE;
		return OFDeviceConn;
}

OFBool disconnect(void){
	  OFDeviceConn = FALSE;
		return OFDeviceConn;
}

void TxString(char* s){
	int i;

	for(i = 0; i < TX_MAX_LEN; i++){
		if(s[i] == 0x00)	break;
		TxByte((BYTE)s[i]);
	}
}

void str2Byte(char*s, BYTE*a){
	int i = 0;
	if(s == NULL) return;
	if(a == NULL) return;
	while(i < NAME_MAX){
		if(s[i] == NULL){
			a[i] = 0xFF;
			return;
		}else{
			a[i] = s[i];
		}
		i++;
	}
}

OFBool STDInit(void){
	BYTE array[NAME_MAX];
	int i;
	
	if(InitFlag == TRUE) return FALSE;
	InitFlag = TRUE;

	STDInitIR();

	for(i = 0; i< NAME_MAX; i++){
		array[i] = 0xFF;
	} 

	str2Byte("Power", array);
	addButton(array);
	str2Byte("CH UP", array);
	addButton(array);
	str2Byte("CH DOWN", array);
	addButton(array);
	str2Byte("VOL UP", array);
	addButton(array);
	str2Byte("VOL DOWN", array);
	addButton(array);
	str2Byte("0", array);
	addButton(array);
	str2Byte("1", array);
	addButton(array);
	str2Byte("2", array);
	addButton(array);
	str2Byte("3", array);
	addButton(array);
	str2Byte("4", array);
	addButton(array);
	str2Byte("5", array);
	addButton(array);
	str2Byte("6", array);
	addButton(array);
	str2Byte("7", array);
	addButton(array);
	str2Byte("8", array);
	addButton(array);
	str2Byte("9", array);
	addButton(array);

	str2Byte("Play", array);
	addButton(array);
	str2Byte("Vol Up", array);
	addButton(array);
	str2Byte("Vol Down", array);
	addButton(array);
	str2Byte("Next", array);
	addButton(array);
	str2Byte("Prev", array);
	addButton(array);
	str2Byte("Menu", array);
	addButton(array);

	str2Byte("Power", array);
	setCommandName(0,array);
	str2Byte("CH UP", array);
	setCommandName(1, array);
	str2Byte("CH DOWN", array);
	setCommandName(2,array);
	str2Byte("VOL UP", array);
	setCommandName(3,array);
	str2Byte("VOL DOWN", array);
	setCommandName(4,array);
	str2Byte("0", array);
	setCommandName(5,array);
	str2Byte("1", array);
	setCommandName(6,array);
	str2Byte("2", array);
	setCommandName(7,array);
	str2Byte("3", array);
	setCommandName(8,array);
	str2Byte("4", array);
	setCommandName(9,array);
	str2Byte("5", array);
	setCommandName(10,array);
	str2Byte("6", array);
	setCommandName(11,array);
	str2Byte("7", array);
	setCommandName(12,array);
	str2Byte("8", array);
	setCommandName(13,array);
	str2Byte("9", array);
	setCommandName(14,array);

	str2Byte("Play", array);
	setCommandName(15,array);
	str2Byte("Vol Up", array);
	setCommandName(16,array);
	str2Byte("Vol Down", array);
	setCommandName(17,array);
	str2Byte("Next", array);
	setCommandName(18,array);
	str2Byte("Prev", array);
	setCommandName(19,array);
	str2Byte("Menu", array);
	setCommandName(20,array);

	addButtonCommand(0,0);
	addButtonCommand(1,1);
	addButtonCommand(2,2);
	addButtonCommand(3,3);
	addButtonCommand(4,4);
	addButtonCommand(5,5);
	addButtonCommand(6,6);
	addButtonCommand(7,7);
	addButtonCommand(8,8);
	addButtonCommand(9,9);
	addButtonCommand(10,10);
	addButtonCommand(11,11);
	addButtonCommand(12,12);
	addButtonCommand(13,13);
	addButtonCommand(14,14);

	addButtonCommand(15,15);
	addButtonCommand(16,16);
	addButtonCommand(17,17);
	addButtonCommand(18,18);
	addButtonCommand(19,19);
	addButtonCommand(20,20);

	str2Byte("TV", array);
	setComponentName(0, array);
	str2Byte("MAC", array);
	setComponentName(1, array);

	str2Byte("TV Remote", array);
	addController(array);
	addControllerButton(0,0);
	addControllerButton(0,1);
	addControllerButton(0,2);
	addControllerButton(0,3);
	addControllerButton(0,4);
	addControllerButton(0,5);
	addControllerButton(0,6);
	addControllerButton(0,7);
	addControllerButton(0,8);
	addControllerButton(0,9);
	addControllerButton(0,10);
	addControllerButton(0,11);
	addControllerButton(0,12);
	addControllerButton(0,13);
	addControllerButton(0,14);

	str2Byte("Mac Remote", array);
	addController(array);
	addControllerButton(1,15);
	addControllerButton(1,16);
	addControllerButton(1,17);
	addControllerButton(1,18);
	addControllerButton(1,19);
	addControllerButton(1,20);

	

	str2Byte("Power All", array);
	addButton(array);
	addButtonCommand(21,0);
	addButtonCommand(21,15);

	str2Byte("Raise the Roof!!!", array);
	addButton(array);
	addButtonCommand(22,3);
	addButtonCommand(22,16);

	str2Byte("Quiet Down!", array);
	addButton(array);
	addButtonCommand(23,4);
	addButtonCommand(23,17);
	addButtonCommand(23,4);
	addButtonCommand(23,17);
	addButtonCommand(23,4);
	addButtonCommand(23,17);

	str2Byte("Disney Channel(33)", array);
	addButton(array);
	addButtonCommand(24,8);
	addButtonCommand(24,8);

	str2Byte("HBO(69)", array);
	addButton(array);
	addButtonCommand(25,11);
	addButtonCommand(25,14);

	str2Byte("Alex's Remote", array);
	addController(array);
	addControllerButton(2,21);
	addControllerButton(2,22);
	addControllerButton(2,23);
	addControllerButton(2,24);
	addControllerButton(2,25);   



	return TRUE;
}



