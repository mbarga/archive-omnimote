/*
 *  OmnimoteFoundation.h
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/13/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#define __OmnimoteFoundation

#ifndef NULL
#include <stdio.h>
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef MAX_BUTTONS
#define MAX_BUTTONS (BYTE)0x7F
#endif

#ifndef NAME_MAX
#define NAME_MAX (BYTE)20
#endif
						                 
#ifndef MAX_CONTROLLERS
#define MAX_CONTROLLERS (BYTE)0x0F
#endif

#ifndef MAX_CONTROLLER_BUTTONS
#define MAX_CONTROLLER_BUTTONS (BYTE)0x11
#endif

#ifndef MAX_COMPONENTS 
#define MAX_COMPONENTS (BYTE)0x08
#endif

#ifndef MAX_MODES
#define MAX_MODES (BYTE)0x06
#endif

#ifndef MAX_COMMANDS 
#define MAX_COMMANDS (BYTE)0x1F
#endif

#ifndef MAX_BUTTON_COMMANDS
#define MAX_BUTTON_COMMANDS (BYTE)0x08
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef GRAPHIC
#define GRAPHIC unsigned char
#endif

#define OFNullRef (BYTE)0xFF

typedef BYTE OFBool;
typedef BYTE OFButtonRef;
typedef BYTE OFControllerRef;
typedef BYTE OFImageRef;
typedef BYTE OFCommandRef;
typedef BYTE OFComponentRef;

enum OFMode{
 	HEY,
	OK,
	USB,
	CON,
	REC,
	CFG,
	ERR
};

void setOmnimoteMode(enum OFMode mode);
void setWiFiStrength(BYTE wifi);
enum OFMode getOmnimoteMode(void);
BYTE getWiFiStrength(void);
