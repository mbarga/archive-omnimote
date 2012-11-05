/*
 *  OFLED.h
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/23/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#define __OFLED

#ifndef __OmnimoteFoundation
#include "OmnimoteFoundation.h"
#endif

#define LCD_E (0x00000001 << 6)
#define LCD_CS1 (0x00000001 << 7)
#define LCD_CS2 (0x00000001 << 9)
#define LCD_RST (0x00000001 << 8)
#define LCD_A0 (0x00000001 << 5)
#define LCD_SDAT (0x00000001 << 5)
#define LCD_SCLK (0x00000001 << 4)

#ifndef IO0SET
#define IO0SET IOSET0
#endif
#ifndef IO0CLR
#define IO0CLR IOCLR0
#endif
#ifndef IO0PIN
#define IO0PIN IOPIN0
#endif

GRAPHIC getLetter(enum OFMode mode, BYTE rot, BYTE pos);
GRAPHIC getSignal(BYTE wifi, BYTE rot);

void refreshLCD(BYTE wifi, enum OFMode mode);

void shiftLCDData(BYTE page);

void setCom(BYTE col, BYTE chip);
void setComBoth(BYTE b);

void writeData(char data, BYTE chip);

void initLCD(void);
BYTE checkVertical(void);

void drawLCDGraphic(GRAPHIC img, BYTE loc);

