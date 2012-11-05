/*----------------------------------------------------------------------------
 *      Name:    LCD.H
 *      Purpose: LCD module 2x16 driver function definitions
 *      Rev.:    V1.00 / 24-may-2007
 *----------------------------------------------------------------------------
 *      This file is part of the uVision/ARM development tools.
 *      This software may only be used under the terms of a valid, current,
 *      end user licence from KEIL for a compatible version of KEIL software
 *      development tools. Nothing else gives you the right to use it.
 *
 *      Copyright (c) 2005-2007 Keil Software.
 *---------------------------------------------------------------------------*/


extern void LCD_init (void);
extern void LCD_load (unsigned char *fp, unsigned int cnt);
extern void LCD_gotoxy (unsigned int x, unsigned int y);
extern void LCD_cls (void);
extern void LCD_cur_off (void);
extern void LCD_on (void);
extern void LCD_putc (unsigned char c);
extern void LCD_puts (unsigned char *sp);
extern void LCD_bargraph (unsigned int val, unsigned int size);
extern void putScreen (int *index);

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

