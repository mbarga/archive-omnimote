/*
 *  OmnimoteFoundation.c
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/13/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#include "OmnimoteFoundation.h"

BYTE WiFiStrength;
enum OFMode OmnimoteMode;

void setOmnimoteMode(enum OFMode mode){
	OmnimoteMode = mode;
}

void setWiFiStrength(BYTE wifi){
	if(wifi < 6){
	  WiFiStrength = wifi;
	}else{
		WiFiStrength = 0;
	}
}

enum OFMode getOmnimoteMode(void){
	return OmnimoteMode;
}

BYTE getWiFiStrength(void){
	return WiFiStrength;
}
