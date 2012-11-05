/*----------------------------------------------------------------------------
 *      Name:    LCD.C
 *      Purpose: LCD module 2x16 driver for ST7066 controller
 *      Rev.:    V1.00 / 24-may-2007
 *----------------------------------------------------------------------------
 *      This file is part of the uVision/ARM development tools.
 *      This software may only be used under the terms of a valid, current,
 *      end user licence from KEIL for a compatible version of KEIL software
 *      development tools. Nothing else gives you the right to use it.
 *
 *      Copyright (c) 2005-2007 Keil Software.
 *---------------------------------------------------------------------------*/

#include <LPC23xx.H>                    /* LPC23xx definitions               */
#include "LCD.h"

#define MCB2300_V1                      /* First version of MCB2300          */

#define IO1DIR    IODIR1
#define IO1SET    IOSET1
#define IO1CLR    IOCLR1
#define IO1PIN    IOPIN1

/* LCD IO definitions */
#ifdef MCB2300_V1
 #define LCD_E     0xC0000000           /* Enable control pin                */
 #define LCD_RW    0x20000000           /* Read/Write control pin            */
 #define LCD_RS    0x10000000           /* Data/Instruction control          */
 #define LCD_CTRL  0xF0000000           /* Control lines mask                */
 #define LCD_DATA  0x0F000000           /* Data lines mask                   */
#else
 #define LCD_E     0x80000000           /* Enable control pin                */
 #define LCD_RW    0x20000000           /* Read/Write control pin            */
 #define LCD_RS    0x10000000           /* Data/Instruction control          */
 #define LCD_CTRL  0xB0000000           /* Control lines mask                */
 #define LCD_DATA  0x0F000000           /* Data lines mask                   */
#endif

/* Local variables */
static unsigned int lcd_ptr;

/* 8 user defined characters to be loaded into CGRAM (used for bargraph) */
static const unsigned char UserFont[8][8] = {
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
  { 0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10 },
  { 0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18 },
  { 0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C },
  { 0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E },
  { 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F },
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

/* Local Function Prototypes */
static void delay (unsigned int cnt);
static void lcd_write (unsigned int c);
static void lcd_write_4bit (unsigned int c);
static unsigned int  lcd_rd_stat (void);
static void lcd_wr_cmd (unsigned int c);
static void lcd_wr_data (unsigned int d);
static void lcd_wait_busy (void);

/*----------------------------------------------------------------------------
 * LCD Driver Interface Functions
 *---------------------------------------------------------------------------*/


/*--------------------------- delay -----------------------------------------*/

static void delay (unsigned int cnt) {
   /* Delay in while loop cycles. */

   while (cnt--);
}


/*--------------------------- lcd_write_4bit --------------------------------*/

static void lcd_write_4bit (unsigned int c) {
   /* Write a 4-bit command to LCD controller. */

   IO1DIR |= LCD_DATA | LCD_CTRL;
   IO1CLR  = LCD_RW   | LCD_DATA;
   IO1SET  = (c & 0xF) << 24;
   IO1SET  = LCD_E;
   delay (10);
   IO1CLR  = LCD_E;
   delay (10);
}


/*--------------------------- lcd_write -------------------------------------*/

static void lcd_write (unsigned int c) {
   /* Write data/command to LCD controller. */

   lcd_write_4bit (c >> 4);
   lcd_write_4bit (c);
}


/*--------------------------- lcd_rd_stat -----------------------------------*/

static unsigned int lcd_rd_stat (void) {
   /* Read status of LCD controller (ST7066) */
   unsigned int stat;

   IO1DIR &= ~LCD_DATA;
   IO1CLR  = LCD_RS;
   IO1SET  = LCD_RW;
   delay (10);
   IO1SET  = LCD_E;
   delay (10);
   stat    = (IO1PIN >> 20) & 0xF0;
   IO1CLR  = LCD_E;
   delay (10);
   IO1SET  = LCD_E;
   delay (10);
   stat   |= (IO1PIN >> 24) & 0xF;
   IO1CLR  = LCD_E;
   return (stat);
}


/*--------------------------- lcd_wait_busy ---------------------------------*/

static void lcd_wait_busy (void) {
   /* Wait until LCD controller (ST7066) is busy. */
   unsigned int stat;

   do {
      stat = lcd_rd_stat ();
   } while (stat & 0x80);               /* Wait for busy flag                */
}


/*--------------------------- lcd_wr_cmd ------------------------------------*/

static void lcd_wr_cmd (unsigned int c) {
   /* Write command to LCD controller. */

   lcd_wait_busy ();
   IO1CLR = LCD_RS;
   lcd_write (c);
}


/*--------------------------- lcd_wr_data -----------------------------------*/

static void lcd_wr_data (unsigned int d) {
   /* Write data to LCD controller. */

   lcd_wait_busy ();
   IO1SET = LCD_RS;
   lcd_write (d);
}


/*--------------------------- LCD_init --------------------------------------*/

void LCD_init (void) {
   /* Initialize the ST7066 LCD controller to 4-bit mode. */ 

   IO1DIR |= LCD_CTRL | LCD_DATA;
   IO1CLR  = LCD_RW   | LCD_RS   | LCD_DATA;

   lcd_write_4bit (0x3);                /* Select 4-bit interface            */
   delay (100000);
   lcd_write_4bit (0x3);
   delay (10000);
   lcd_write_4bit (0x3);
   lcd_write_4bit (0x2);

   lcd_wr_cmd (0x28);                   /* 2 lines, 5x8 character matrix     */
   lcd_wr_cmd (0x0e);                   /* Display ctrl:Disp/Curs/Blnk=ON    */
   lcd_wr_cmd (0x06);                   /* Entry mode: Move right, no shift  */

   LCD_load ((unsigned char *)&UserFont, sizeof (UserFont));
   LCD_cls ();
}


/*--------------------------- LCD_load --------------------------------------*/

void LCD_load (unsigned char *fp, unsigned int cnt) {
   /* Load user-specific characters into CGRAM */
   unsigned int i;

   lcd_wr_cmd (0x40);                   /* Set CGRAM address counter to 0    */
   for (i = 0; i < cnt; i++, fp++)  {
      lcd_wr_data (*fp);
   }
}

/*--------------------------- LCD_gotoxy ------------------------------------*/

void LCD_gotoxy (unsigned int x, unsigned int y) {
   /* Set cursor position on LCD display. Left corner: 1,1, right: 16,2 */
   unsigned int c;

   c = --x;
   if (--y) {
      c |= 0x40;
   }
   lcd_wr_cmd (c | 0x80);
   lcd_ptr = y*16 + x;
}


/*--------------------------- LCD_cls ---------------------------------------*/

void LCD_cls (void) {
   /* Clear LCD display, move cursor to home position. */

   lcd_wr_cmd (0x01);
   LCD_gotoxy (1,1);
}


/*--------------------------- LCD_cur_off------------------------------------*/

void LCD_cur_off (void) {
   /* Switch off LCD cursor. */

   lcd_wr_cmd (0x0c);
}


/*--------------------------- LCD_on ------ ---------------------------------*/

void LCD_on (void) {
   /* Switch on LCD and enable cursor. */

   lcd_wr_cmd (0x0e);
}


/*--------------------------- LCD_putc --------------------------------------*/

void LCD_putc (unsigned char c) { 
   /* Print a character to LCD at current cursor position. */

   if (lcd_ptr == 16) {
      lcd_wr_cmd (0xc0);
   }
   lcd_wr_data (c);
   lcd_ptr++;
}


/*--------------------------- LCD_puts --------------------------------------*/

void LCD_puts (unsigned char *sp) {
   /* Print a string to LCD display. */

   while (*sp) {
      LCD_putc (*sp++);
   }
}


/*--------------------------- LCD_bargraph ----------------------------------*/

void LCD_bargraph (unsigned int val, unsigned int size) {
   /* Print a bargraph to LCD display.  */
   /* - val:  value 0..100 %            */
   /* - size: size of bargraph 1..16    */
   unsigned int i;

   val = val * size / 20;               /* Display matrix 5 x 8 pixels       */
   for (i = 0; i < size; i++) {
      if (val > 5) {
         LCD_putc (5);
         val -= 5;
      }
      else {
         LCD_putc (val);
         break;
      }
   }
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

