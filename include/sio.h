/*----------------------------------------------------------------------------
 *      Name:    sio.h
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
#ifndef LPC2300_SIO_H
#define LPC2300_SIO_H

void com_initialize (void);

void com_baudrate (unsigned int baudrate);

int com_putchar (int c);

int com_getchar (void);

#endif

