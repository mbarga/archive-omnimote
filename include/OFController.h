/*
 *  OController.h
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/13/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#define __OFController

#ifndef __OmnimoteFoundation
#include "OmnimoteFoundation.h"
#endif

#ifndef __OFButton
#include "OFButton.h"
#endif

void initializeControllers(void);

OFBool setControllerName(OFControllerRef ctrl, unsigned char* name);
unsigned char* getControllerName(OFControllerRef ctrl);

OFBool addControllerButton(OFControllerRef ctrl, OFButtonRef button);
OFBool removeControllerButton(OFControllerRef ctrl, OFButtonRef button);
OFButtonRef* getControllerButtons(OFControllerRef ctrl);
unsigned char countControllerButtons(OFControllerRef controller);

OFBool isControllerValid(OFControllerRef ctrl);
OFBool isControllerActive(OFControllerRef ctrl);

OFControllerRef getFreeController(void);
OFControllerRef addController(BYTE* name);
OFControllerRef removeController(OFControllerRef ctrl);
