/*
 *  OFCommand.h
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/13/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#define __OFCommandRef

#ifndef __OmnimoteFoundation
#include "OmnimoteFoundation.h"
#endif

#ifndef __OFIRInterface
#include "OFIRInterface.h"
#endif

void initializeCommands(void);

OFBool setCommandName(OFCommandRef cmd, BYTE* name);
BYTE* getCommandName(OFCommandRef cmd);

OFBool isCommandValid(OFCommandRef cmd);


