/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    SERIAL.C
 *      Purpose: Interrupt controlled and event driven serial IO
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <LPC23xx.H>                 /* LPC23xx definitions                  */
#include <RTL.h>                     /* RTX kernel functions & defines       */
#include <stdio.h>

#define  CTRL_Q  0x11                /* Control+Q character code             */
#define  CTRL_S  0x13                /* Control+S character code             */

static BIT sendstop;                 /* flag: marks XOFF character           */
static char recbuf[256];
static U8 ridx;
static U8 widx;

OS_TID wr_task;
OS_TID rd_task;

/*----------------------------------------------------------------------------
 *       fputc:  event driven putchar function
 *---------------------------------------------------------------------------*/
int fputc (int c, FILE *f) {
  wr_task = os_tsk_self ();          /* identify task for serial interrupt   */
  os_evt_clr (0x0100, wr_task); 
  if (c == '\n') {                   /* expand new line character:           */
    U1THR = (char)'\r';
    os_evt_wait_or (0x0100, 0xffff); /* wait till character transmited       */
  }
  U1THR = (char)c;                   /* transmit a character                 */
  os_evt_wait_or (0x0100, 0xffff);   /* wait till character transmited       */
  return (c);                        /* return character: ANSI requirement   */
}

/*----------------------------------------------------------------------------
 *       getkey:  event driven getkey function
 *---------------------------------------------------------------------------*/
int getkey (void) {
  if (ridx == widx) {
    rd_task = os_tsk_self ();
    os_evt_clr (0x0100, rd_task);
    os_evt_wait_or (0x0100, 0xffff); /* wait till character received         */
  }
  return (recbuf[ridx++]);
}


/*----------------------------------------------------------------------------
 *       serial:  serial receive and transmit interrupt
 *---------------------------------------------------------------------------*/
void int_serial (void) __irq {
  U8 c;

  if ((U1IIR & 0x0E) == 0x04) {       /* Receive interrupt                   */
    c = (char) U1RBR;                 /* read character                      */
    switch (c)  {                     /* process character                   */
      case CTRL_S:
        sendstop = __TRUE;            /* if Control+S stop transmission      */
        goto ack;

      case CTRL_Q:
        sendstop = __FALSE;           /* if Control+Q start transmission     */
        break;

      default:                        /* send character to a mailbox         */
        recbuf[widx++] = c;
        isr_evt_set (0x0100, rd_task);/* set event character received        */
        goto ack;
    }
  }
                                      /* Transmit interrupt                  */
  if (!sendstop)  {                   /* if not Control+S received           */
    isr_evt_set (0x0100, wr_task);    /* Go on, set event transmit ready     */
  }
ack:
  VICVectAddr = 0;                    /* Acknowledge Interrupt               */
}

/*----------------------------------------------------------------------------
 *       serial_init: initialize serial interface
 *---------------------------------------------------------------------------*/
void serial_init (void) {

  PINSEL0 &= ~0xC0000000;
  PINSEL0 |=  0x40000000;             /* Enable TxD1 pin                     */
  PINSEL1 &= ~0x00000003;
  PINSEL1 |=  0x00000001;             /* Enable RxD1 pin                     */

  U1LCR = 0x83;                       /* 8 bits, no Parity, 1 Stop bit       */
  U1DLL = 3;                          /* 115200 Baud Rate @ 12MHz PCLK Clock */
  U1FDR = 0x67;                       /* Fractional Divider                  */
  U1LCR = 0x03;                       /* DLAB = 0                            */
  U1IER = 0x03;                       /* Enable RDA and THRE interrupts      */

  VICVectAddr7 = (U32)int_serial;     /* Set Interrupt Vector                */
  VICVectCntl7 = 7;                   /* use it for UART1 Interrupt          */
  VICIntEnable  = (1  << 7);          /* Enable Interrupt                    */

  sendstop = __FALSE;                 /* CtrlQ not received                  */
  ridx = widx = 0;                    /* clear buffer indexes                */
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
