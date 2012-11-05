/*
 *  OFButtonRef.h
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/13/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#define __OFButton

#ifndef __OmnimoteFoundation
#include "OmnimoteFoundation.h"
#endif

#ifndef __OFCommand
#include "OFCommand.h"
#endif

#ifndef __OFIRInterface
#include "OFIRInterface.h"
#endif



void initializeButtons(void);

OFBool setButtonName(OFButtonRef button, unsigned char* name);
unsigned char* getButtonName(OFButtonRef button);

OFBool addButtonCommand(OFButtonRef button, OFCommandRef cmd);
OFBool removeButtonCommand(OFButtonRef button, OFCommandRef cmd);
OFCommandRef* getButtonCommands(OFButtonRef button);
unsigned char countButtonCommands(OFButtonRef button);

OFBool setButtonImage(OFButtonRef button, OFImageRef image);
OFImageRef getButtonImage(OFButtonRef button);

OFBool isButtonValid(OFButtonRef button);
OFBool isButtonActive(OFButtonRef button);

OFButtonRef getFreeButton(void);
OFButtonRef addButton(BYTE* name);

OFButtonRef removeButton(OFButtonRef button);
