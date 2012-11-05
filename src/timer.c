/*****************************************************************************
 *   timer.c:  Timer C file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "LPC23xx.h"		/* LPC23xx/24xx Peripheral Registers	*/
#include "stdio.h"
#include "type.h"
#include "irq.h"
#include "timer.h"
#include "string.h"
#include "OFmessage.h"

volatile DWORD timer0_counter = 0;
volatile DWORD timer1_counter = 0;

extern int init;
int bufPtr = 0;
extern OFBool OFCmdFlag;
extern int OFMessageTimer;
extern int OFLCDTimer;
extern int BLINKYTimer;
extern int OFConnectTimer;
extern int OFWiFiUpdateTimer;
//char cmd0[] = "\rexit\r";	//get into known state
//char cmd1[] = "$$$";
//char cmd2[] = "get option\r";
//char cmd3[] = "exit\r";
//const char *cmdBuf[] = {cmd0,cmd1,cmd2,cmd3}; 
//const char *cmdBuf[] = {"\rexit\r", "$$$", "get option\r", "exit\r"};


/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**						until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:		None
** 
*****************************************************************************/
//void delayMs(U8 timer_num, DWORD delayInMs)
//{
//  if ( timer_num == 0 )
//  {
//	/*
//	* setup timer #0 for delay
//	*/
//	T0TCR = 0x02;		/* reset timer */
//	T0PR  = 0x00;		/* set prescaler to zero */
//	T0MR0 = delayInMs * ((48000000 / 2) / 1000-1);
//	T0IR  = 0xff;		/* reset all interrrupts */
//	T0MCR = 0x04;		/* stop timer on match */
//	T0TCR = 0x01;		/* start timer */
//  
//	/* wait until delay time has elapsed */
//	while (T0TCR & 0x01);
//  }
//  else if ( timer_num == 1 )
//  {
//	/*
//	* setup timer #1 for delay
//	*/
//	T1TCR = 0x02;		/* reset timer */
//	T1PR  = 0x00;		/* set prescaler to zero */
//	T1MR0 = delayInMs * ((14400000) / 1000-1);
//	T1IR  = 0xff;		/* reset all interrrupts */
//	T1MCR = 0x04;		/* stop timer on match */
//	T1TCR = 0x01;		/* start timer */
//  
//	/* wait until delay time has elapsed */
//	while (T1TCR & 0x01);
//  }
//  return;
//}

#if !FIQ
/******************************************************************************
** Function name:		Timer0Handler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void Timer0Handler (void) __irq 
{   

  T0IR = 1;			/* clear interrupt flag */
	
  IENABLE;			/* handles nested interrupt */

	OFLCDTimer++;
	BLINKYTimer++;
	OFWiFiUpdateTimer++;
  timer0_counter++;
	OFConnectTimer++;
	if(OFCmdFlag == TRUE){
	  OFMessageTimer++;
	}
	
//	if (init==1) {
//		switch (bufPtr++) {
//			case 0:
//	 			printf("\rexit\r");	
//				break;
//			case 1:
//				printf("$$$");
//				break;
//			case 2:
//				printf("\rget option\r");
//				break;
//			case 3:
//				printf("\rexit\r");
//				break;
//			default:
//				bufPtr = 0;
//				init = 0;
//				break;
//		}	
//	}
//	if (init==1) {
//		printf("%s",*cmdBuf[bufPtr++]);

//	  if (bufPtr==3) {
//			init = 0;
//			bufPtr = 0;
//		}
//	}

  IDISABLE;
  VICVectAddr = 0;	/* Acknowledge Interrupt */
}

#else
/******************************************************************************
** Function name:		Timer0FIQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void Timer0FIQHandler(void) 
{  
  T0IR = 1;			/* clear interrupt flag */
  timer0_counter++;
//  VICVectAddr = 0;	/* Acknowledge Interrupt */
}
#endif

#if !FIQ
/******************************************************************************
** Function name:		Timer1Handler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void Timer1Handler (void) __irq 
{  
  T1IR = 1;			/* clear interrupt flag */
  IENABLE;			/* handles nested interrupt */

  timer1_counter++;

  IDISABLE;
  VICVectAddr = 0;	/* Acknowledge Interrupt */
}

#else
/******************************************************************************
** Function name:		Timer1Handler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void Timer1FIQHandler (void)
{  
  T1IR = 1;			/* clear interrupt flag */
  timer1_counter++;
//  VICVectAddr = 0;	/* Acknowledge Interrupt */
}
#endif

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void enable_timer( U8 timer_num )
{
  if ( timer_num == 0 )
  {
	T0TCR = 1;
  }
  else
  {
	T1TCR = 1;
  }
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void disable_timer( U8 timer_num )
{
  if ( timer_num == 0 )
  {
	T0TCR = 0;
  }
  else
  {
	T1TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void reset_timer( U8 timer_num )
{
  DWORD regVal;

  if ( timer_num == 0 )
  {
	regVal = T0TCR;
	regVal |= 0x02;
	T0TCR = regVal;
  }
  else
  {
	regVal = T1TCR;
	regVal |= 0x02;
	T1TCR = regVal;
  }
  return;
}

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**						install timer interrupt handler
**
** parameters:			timer number and timer interval
** Returned value:		__TRUE or __FALSE, if the interrupt handler can't be
**						installed, return __FALSE.
** 
******************************************************************************/
DWORD init_timer ( U8 timer_num, DWORD TimerInterval ) 
{
  if ( timer_num == 0 )
  {
	timer0_counter = 0;
	//T0MR0 = TimerInterval;
	T0MR0 = TimerInterval * (14400000 / 1000-1);
	T0MCR = 3;				/* Interrupt and Reset on MR0 */
#if FIQ
	/* FIQ is always installed. */
	VICIntSelect |= (0x1<<4);
	VICIntEnable = (0x1<<4);
	return (__TRUE);
#else
	if ( install_irq( TIMER0_INT, (void *)Timer0Handler, 5 ) == __FALSE )
	{
	  return (__FALSE);
	}  
	else
	{
	  return (__TRUE);
	}
#endif
  }
  else if ( timer_num == 1 )
  {
	timer1_counter = 0;
	T1MR0 = TimerInterval;
	T1MCR = 3;				/* Interrupt and Reset on MR1 */
#if FIQ
	VICIntSelect |= (0x1<<5);
	VICIntEnable = (0x1<<5);
	return (__TRUE);
#else
	if ( install_irq( TIMER1_INT, (void *)Timer1Handler, 5 ) == __FALSE )
	{
	  return (__FALSE);
	}  
	else
	{
	  return (__TRUE);
	}
#endif
  }
  return (__FALSE);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
