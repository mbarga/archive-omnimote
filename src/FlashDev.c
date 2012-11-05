/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright KEIL ELEKTRONIK GmbH 2003 - 2006                         */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.C:  Device Description for Philips LPC2xxx 512kB Flash    */
/*               using Flash Boot Loader with IAP                      */
/*                                                                     */
/***********************************************************************/

#include "FlashOS.h"        // FlashOS Structures


struct FlashDevice const FlashDevice  =  {
   FLASH_DRV_VERS,             // Driver Version, do not modify!
   "LPC2000 IAP2 512kB Flash", // Device Name 
   ONCHIP,                     // Device Type
   0x00000000,                 // Device Start Address
   0x0007D000,                 // Device Size without Boot Loader (500kB)
   1024,                       // Programming Page Size
   0,                          // Reserved, must be 0
   0xFF,                       // Initial Content of Erased Memory
   100,                        // Program Page Timeout 100 mSec
   3000,                       // Erase Sector Timeout 3000 mSec

// Specify Size and Address of Sectors
   0x001000, 0x000000,         // Sector Size  4kB ( 8 Sectors)
   0x008000, 0x008000,         // Sector Size 32kB (14 Sectors) 
   0x001000, 0x078000,         // Sector Size  4kB ( 5 Sectors)
   SECTOR_END
};
