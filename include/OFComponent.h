/*
 *  OFComponent.h
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/14/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#define __OFComponentRef

#ifndef __OmnimoteFoundation
#include "OmnimoteFoundation.h"
#endif

void initializeComponents(void);

OFBool setComponentName(OFComponentRef cmp, BYTE* name);
BYTE* getComponentName(OFComponentRef cmp);

OFBool isComponentValid(OFComponentRef cmp);
OFBool isComponentActive(OFComponentRef cmp);

OFComponentRef removeComponent(OFComponentRef cmp);

