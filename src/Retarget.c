/*----------------------------------------------------------------------------
 *      Name:    Retarget.c
 *      Purpose: 'Retarget' layer for target-dependent low level functions
 *      Version: V1.0
 *----------------------------------------------------------------------------
 *      This file is part of the uVision/ARM development tools.
 *      This software may only be used under the terms of a valid, current,
 *      end user licence from KEIL for a compatible version of KEIL software
 *      development tools. Nothing else gives you the right to use it.
 *
 *      Copyright (c) 2005-2007 Keil Software.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_misc.h>

#pragma import(__use_no_semihosting_swi)


extern int com_putchar (int c);
extern int com_getchar (void);


struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int ch, FILE *f) {
//  return (sendchar(ch));
  volatile unsigned int i;

  while (com_putchar (ch) != 0) {
    for (i=0; i<1000; i++) {
      /*** DO NOTHING ***/
    }
  }

  return (ch);
}

/*------------------------------------------------------------------------------
fgetc waits until a character is received from the serial port.  This may not
be the exact desired operation (for example if the buffer is empty, this
function hangs waiting for a character to be received).
------------------------------------------------------------------------------*/
int fgetc(FILE *f) {
  int ch;

  do {
    ch = com_getchar ();
  }
  while (ch == -1);

  return ((unsigned char) ch);
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int ch) {
  volatile unsigned int i;

  while (com_putchar (ch) != 0) {
    for (i=0; i<1000; i++) {
      /*** DO NOTHING ***/
    }
  }
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}
