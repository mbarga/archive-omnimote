/*
 *  OFCommand.c
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/14/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#ifndef __OFCommand
#include "OFCommand.h"
#endif

unsigned char CommandNames[MAX_COMMANDS][NAME_MAX+1];

/***************************************************************
 * Initializes all OFCommand resources
 ***************************************************************/
void initializeCommands(void){
	BYTE i;
	for(i = 0; i < MAX_COMMANDS; i++){
		// CommandNames
		CommandNames[i][0] = OFNullRef;
		CommandNames[i][NAME_MAX] = OFNullRef;
	}
}

/***************************************************************
 * setCommandName - sets the name associated with command
 * 
 * Returns:
 * TRUE if command name was modified, FALSE otherwise
 *
 ***************************************************************/
OFBool setCommandName(OFCommandRef cmd, BYTE* name){
	int i;
	if(name == NULL){
		CommandNames[cmd][0] = OFNullRef;
		return TRUE;
	}
	if(name[0] == OFNullRef) return FALSE;
	//if(isIRCommandActive(cmd) == FALSE) return FALSE;
	for(i = 0; i < NAME_MAX; i++){
		CommandNames[cmd][i] = name[i];
		if(name[i] == OFNullRef) i = NAME_MAX;
	}
	return TRUE;
}

/***************************************************************
 * getCommandName - gets the name associated with command
 *
 * Returns:
 * name associated with command, 
 * an empty string if command was not active or invalid
 *
 ***************************************************************/
BYTE* getCommandName(OFCommandRef cmd){
	if(isCommandValid(cmd) == FALSE) return NULL;
	return CommandNames[cmd];
}

/***************************************************************
 * isCommandValid - checks if OFCommandRef value is within valid
 * range
 * 
 * Returns:
 * TRUE if OFCommandRef is valid, FALSE otherwise
 *
 ***************************************************************/
OFBool isCommandValid(OFCommandRef cmd){
	if(cmd < MAX_COMMANDS) return TRUE;
	return FALSE;
}

