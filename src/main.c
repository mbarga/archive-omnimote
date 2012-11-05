/*----------------------------------------------------------------------------
 *      Name:    main.c
 *      Purpose: Interrupt Driven SIO Using printf for Philips LPC2300
 *      Version: V1.0
 *----------------------------------------------------------------------------
 *      This file is part of the uVision/ARM development tools.
 *      This software may only be used under the terms of a valid, current,
 *      end user licence from KEIL for a compatible version of KEIL software
 *      development tools. Nothing else gives you the right to use it.
 *
 *      Copyright (c) 2005-2007 Keil Software.
 *---------------------------------------------------------------------------*/

#include <LPC23XX.H>                                  /* LPC23xx definitions */
#include <stdio.h>
#include "sio.h"
#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "mscuser.h"
#include "memory.h"
#include "irq.h"
#include "timer.h"
#include "OFmessage.h"
#include "OFButton.h"
#include "OFController.h"
#include "OFCommand.h"
#include "OFComponent.h"
#include "OFIRInterface.h"
#include "OFLCD.h"
#include "flashos.h"

extern BYTE* OFReplyAOK;
extern BYTE OFDeviceConn;


OFBool readConfig(U8 *Mem);
void TxData(void);

unsigned char response [16];
int index = 0;
FILE *ignore;

int k;

const int writeOffset = 128*16;
int writePtr = 0;
extern U8 Memory[MSC_MemorySize];           /* MSC Memory in RAM */ 
extern OFBool OFRxFlag;
extern int OFLCDTimer;
extern OFBool OFCmdFlag;
extern OFBool OFTxFlag;
OFBool OFIRReadFlag;
int OFWiFiUpdateTimer = 0;
int BLINKYTimer = 0;
extern int OFConnectTimer;

//unsigned char flashBuf[512] = "I am a string";
unsigned char *flashdata;

/*------------------------------------------------------------------------------
  Switch on LEDs
 *------------------------------------------------------------------------------*/
void LED_On (unsigned int value) {

  //FIO2SET = (value);                        /* Turn On  LED */
}

///*------------------------------------------------------------------------------
//  Switch off LEDs
// *------------------------------------------------------------------------------*/
void LED_Off (unsigned int value) {

  //FIO2CLR = (value);                        /* Turn Off LED */
}

int main (void) {
  U32 n;
//	int irCounter;
  PINSEL10 = 0;                             /* Disable ETM interface */

  //FIO2DIR |= LED_MSK;                     /* LEDs, port 2, bit 0~7 output only */
//  FIO2DIR  = 0x000000FF;                 	/* LEDs, port 2, bit 0~7 output only */
//  FIO2MASK = 0x00000000;
//  FIO2PIN  = 0x00000000;

  com_initialize ();                      	/* init interrupt driven serial I/O */
  //printf ("Interrupt-driven Serial I/O Example\r\n\r\n");	  printf statements get printed over the spi

  for (n = 0; n < MSC_ImageSize; n++) {     /* Copy Initial Disk Image */
    Memory[n] = DiskImage[n];               /*   from Flash to RAM     */
  }

  USB_Init();                               /* USB Initialization */
  USB_Connect(__TRUE);                      /* USB Connect */

	init_timer (0, 50); // 10 ms int on timer 0
	enable_timer(0);		// start timer 0
	
	initializeButtons();
	initializeControllers();
	initializeCommands();
	initializeComponents();
	initializeMessage();
	intializeIRControl();
	//initDebugMode();

	/* Flash write is done one USB suspend event (usbuser.c)*/
	// test: get data from flash
	flashdata = (unsigned char *)0x00058000;
	/* ---------------------------------------------------- */
	IODIR0 |= 1 << 21;
	initLCD();
	setOmnimoteMode(HEY);

  while (1) {
/*******IR Output Test*****
	sendIRCommand(0);

	while (isSendingCommand());

	delay some time
	irCounter = 0;
	while (irCounter++ < 10000000);
**************************/

/*******IR Input Test******/
/*	recordIRCommand(0);

	while (!isInformationReceived());

	finishRecording();

	irCounter = 0;
	while (irCounter++ < 10000000);

	recordIRCommand(1);

	while (!isInformationReceived());

	finishRecording();

	irCounter = 0;
	while (irCounter++ < 10000000);

	recordIRCommand(2);

	while (!isInformationReceived());

	finishRecording();

	irCounter = 0;
	while (irCounter++ < 10000000);

	while(1)
	{
		isInformationReceived();
	}; 
**************************/

/******** BLINKY **********/
if(BLINKYTimer > 4){
	BLINKYTimer = 0;
	if((IO0PIN & (1<<21))){
			IOCLR0 = 1 << 21;		
	}else{
		  IOSET0 = 1 << 21;
	}
}
/******** BLINKY **********/

/********IR Read********/
	if (OFConnectTimer > 300)
	{
	 	disconnect();
	}
/***********************/

/********WiFi********/
	if (OFWiFiUpdateTimer > 500)
	{
		OFWiFiUpdateTimer = 0;
	  if(getOmnimoteMode() == OK){
			//updateWiFi();

		}
	}
/***********************/

/******** LCD **********/
	if( OFLCDTimer>=60 ){ // 3 sec
		if(IOPIN1 & (1<<18)){
			if(getOmnimoteMode() == USB){
				setOmnimoteMode(CFG);	
			}
		}else{
			setOmnimoteMode(USB);
		}

		refreshLCD(getWiFiStrength(),getOmnimoteMode());
		switch(getOmnimoteMode()){
			case HEY:
				readConfig(Memory);
				updateWiFi();
				setOmnimoteMode(OK);
				break;
			case OK:
				if(OFDeviceConn == TRUE){
			 		setOmnimoteMode(CON);
				}
				break;
			case REC:
			break;
			case USB:
			break;
			case ERR:
			break;
			case CFG:
			break;
			case CON:
				if(OFDeviceConn == FALSE){
			 		setOmnimoteMode(OK);
				}
				break;
		}
	}

	
/******** LCD **********/
	if(getOmnimoteMode() == USB) continue;

/******** TX **********/
  TxData();
/******** TX **********/

/********IR Read********/
	if (OFIRReadFlag)
	{
	 	OFIRReadFlag = FALSE;
		replyByte(finishRecording());

	}
/***********************/




/******** Data Receive **********/
		
		if (OFRxFlag==TRUE && OFCmdFlag == FALSE) {
			processMessage();
		}
/******** Data Receive **********/



/******** Read Configuration **********/

		if(getOmnimoteMode()==CFG) {
			if(readConfig(Memory) == FALSE){
				setOmnimoteMode(ERR);
			}
			setOmnimoteMode(OK);
		}
/******** Read Configuration **********/

  }
}


/*----------------------------------------------------------------------------
 *---------------------------------------------------------------------------*/

void TxData(void){
  char c;
	while(OFTxFlag == TRUE){
		c = nextByte();
		if(OFCmdFlag==FALSE)
		{
			printf("%c",c);
		}else{
			if(c != 0xFF) printf("%c",c);
		}
	}	
}

OFBool readConfig(U8 *Mem) {
	char config [32];
	OFBool end = FALSE;
	OFBool result; 
 	U16 index = 0x800;//CHECK FAT system write; this may not be static
	U16 bufIndex = 0;
	result = enterCmdMode();
	if(result == FALSE)	{
	 	return exitCmdMode();
	}

	while (end==FALSE) {
		if (Mem[index]==0x0D & 
				Mem[index+1]==0x0A) {
			if (Mem[index+2]==0x0D & 
					Mem[index+3]==0x0A) {
				  end = TRUE;
			} 
				config[bufIndex]=0x00;
				bufIndex = 0;
				TxString(config);
				OFMessageWait(1);
				if (endCmd(0x00)==FALSE) {
				  result = FALSE;
					break;
				}
				index++;
			
		}	else {
			config[bufIndex++] = Mem[index];
		} 
		index++;
	}	
	OFMessageWait(3);

	if (result==FALSE) {
		exitCmdMode();
	 	return FALSE;
	}
	return exitCmdMode(); 
}	

//void putScreen (int *index) {
//	int i;
//	if (*index == 16) { 
//		*index = 0; 
//		for (i=0;i<16;i++) response[i] = NULL;	
//	}
//	response[*index++] = (unsigned char)fgetc(ignore);	 // nothing received = -1
//	LCD_gotoxy(16,1);
//	LCD_putc(*index+50);
//
//	LCD_puts("You pressed:    ");
//	LCD_gotoxy(1,2);
//	LCD_puts(response);
//
//	//c = getchar (); 	// hacky way to pause
//	LCD_gotoxy(1,1);
//}
