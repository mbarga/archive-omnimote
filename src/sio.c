/*----------------------------------------------------------------------------
 *      Name:    sio.c
 *      Purpose: Serial Communication Routines for Philips LPC2300
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
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "sio.h"
#include "type.h"
#include "OFmessage.h"

/*------------------------------------------------------------------------------
Notes:

The length of the receive and transmit buffers must be a power of 2.

Each buffer has a next_in and a next_out index.

If next_in = next_out, the buffer is empty.

(next_in - next_out) % buffer_size = the number of characters in the buffer.
------------------------------------------------------------------------------*/
#define TBUF_SIZE   256	     /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/
#define RBUF_SIZE   256      /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/
#define MemorySize  16384            /* = 0x4000 */

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
#if TBUF_SIZE < 2
#error TBUF_SIZE is too small.  It must be larger than 1.
#elif ((TBUF_SIZE & (TBUF_SIZE-1)) != 0)
#error TBUF_SIZE must be a power of 2.
#endif

#if RBUF_SIZE < 2
#error RBUF_SIZE is too small.  It must be larger than 1.
#elif ((RBUF_SIZE & (RBUF_SIZE-1)) != 0)
#error RBUF_SIZE must be a power of 2.
#endif

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
struct buf_st {
  unsigned int in;          /* Next In Index */
  unsigned int out;         /* Next Out Index */
  char buf [RBUF_SIZE];     /* Buffer */
};

static struct buf_st rbuf = { 0, 0, };
#define SIO_RBUFLEN ((unsigned short)(rbuf.in - rbuf.out))

static struct buf_st tbuf = { 0, 0, };
#define SIO_TBUFLEN ((unsigned short)(tbuf.in - tbuf.out))

static unsigned int tx_restart = 1;   /* NZ if TX restart is required */

extern const int writeOffset;
extern int writePtr;
extern U8 Memory[MemorySize];           /* MSC Memory in RAM */

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
void sio_irq (void) __irq {
  volatile char dummy;
  volatile char IIR;
  struct buf_st *p;

  /*------------------------------------------------
  Repeat while there is at least one interrupt source.
  ------------------------------------------------*/
  while (((IIR = U1IIR) & 0x01) == 0) {
     switch (IIR & 0x0E) {
       case 0x06: /* Receive Line Status */
         dummy = U1LSR;  /* Just clear the interrupt source */
         break;

       case 0x04: /* Receive Data Available */
       case 0x0C: /* Character Time-Out */
         p = &rbuf;

         //if (((p->in - p->out) & ~(RBUF_SIZE-1)) == 0) {
           //p->buf [p->in & (RBUF_SIZE-1)] = U1RBR;
					 dummy = U1RBR;
					 RxByte(dummy);
		   		 //Memory[writeOffset + writePtr++] = p->buf[p->in & (RBUF_SIZE-1)];	// write received text to internal txt file
           //p->in++;
         //}
				 
         break;

       case 0x02: /* THRE Interrupt */
         p = &tbuf;

         if (p->in != p->out) {
           U1THR = p->buf [p->out & (TBUF_SIZE-1)];
           p->out++;
           tx_restart = 0;
         }
         else {
           tx_restart = 1;
         }
         break;

       case 0x00: /* Modem Interrupt */
         dummy = U1MSR;  /* Just clear the interrupt source */
         break;

       default:
         break;
     }
  }

  VICVectAddr = 0; /* Acknowledge Interrupt */
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
void com_initialize (void) {
  volatile char dummy;

  /*------------------------------------------------
  Clear com buffer indexes.
  ------------------------------------------------*/
  tbuf.in = 0;
  tbuf.out = 0;
  tx_restart = 1;

  rbuf.in = 0;
  rbuf.out = 0;

  /*------------------------------------------------
  Setup serial port registers.
  ------------------------------------------------*/
  PINSEL0 |= 0x40000000;               /* Enable TxD1 */
  PINSEL1 |= 0x00000001;               /* Enable RxD1 */

  U1LCR = 0x03;            /* 8 bits, no Parity, 1 Stop bit */
  U1IER = 0;               /* Disable UART1 Interrupts */

  VICVectAddr7 = (unsigned long)sio_irq;
  VICVectCntl7 = 15;       /* use it for UART1 Interrupt */
  VICIntEnable = 1 << 7;   /* Enable UART1 Interrupt */

  com_baudrate (115200);   /* setup for 115200 baud (14,4MHz) */
  /*** Note that with the PLL and VPB setup the pclk is 14,4MHz. ***/
  /*** This does NOT generate nice baudrates!!! ***/
  /*** Most connection problems are baudrate mismatches. ***/
  /*** Symptoms we've seen include reception on PC but no ***/
  /*** reception on the target system. ***/

  dummy = U1IIR;   /* Read IrqID - Required to Get Interrupts Started */
  U1IER = 3;       /* Enable UART1 RX and THRE Interrupts */
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
void com_baudrate (unsigned int baudrate) {
  unsigned long DLreload;

  /*** Note that the pclk is 14,4MHz. ***/
  DLreload = ((14400000UL / 16UL) + (baudrate-1)) / baudrate;

  U1LCR |= 0x80;           /* Set DLAB */
  U1DLL = DLreload;
  U1DLM = (DLreload >> 8);
  U1LCR &= ~0x80;          /* Clear DLAB */
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
int com_putchar (int c) {	   
  struct buf_st *p = &tbuf;

  /*------------------------------------------------
  If the buffer is full, return an error value.
  ------------------------------------------------*/
  if (SIO_TBUFLEN >= TBUF_SIZE)
    return (-1);

  /*------------------------------------------------
  Add the data to the transmit buffer.  If the
  transmit interrupt is disabled, then enable it.
  ------------------------------------------------*/
  if (tx_restart)	{
    tx_restart = 0;
    U1THR = c;
  }
  else {
    p->buf [p->in & (TBUF_SIZE - 1)] = c;
    p->in++;
  }

  return (0);
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
int com_getchar (void) {
  struct buf_st *p = &rbuf;

  if (SIO_RBUFLEN == 0)
    return (-1);

  return (p->buf [(p->out++) & (RBUF_SIZE - 1)]);
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

