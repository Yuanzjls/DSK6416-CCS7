/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_flash_erase.c ========
 *  DSK6416_FLASH_erase() implementation
 */
 
#include <std.h>
#include <csl.h>

#include <dsk6416.h>
#include <dsk6416_flash.h>

#define DSK6416_FLASH_SECTORS       11

/* Constant table containing end address of each sector */
static Uint32 sector_end[DSK6416_FLASH_SECTORS] = {
    DSK6416_FLASH_BASE + 0x00ffff, /* Sector 0  */
    DSK6416_FLASH_BASE + 0x01ffff, /* Sector 1  */
    DSK6416_FLASH_BASE + 0x02ffff, /* Sector 2  */
    DSK6416_FLASH_BASE + 0x03ffff, /* Sector 3  */
    DSK6416_FLASH_BASE + 0x04ffff, /* Sector 4  */
    DSK6416_FLASH_BASE + 0x05ffff, /* Sector 5  */
    DSK6416_FLASH_BASE + 0x06ffff, /* Sector 6  */
    DSK6416_FLASH_BASE + 0x077fff, /* Sector 7  */
    DSK6416_FLASH_BASE + 0x079fff, /* Sector 8  */
    DSK6416_FLASH_BASE + 0x07bfff, /* Sector 9  */
    DSK6416_FLASH_BASE + 0x07ffff  /* Sector 10 */
};


/* Erase a segment of Flash memory */
void DSK6416_FLASH_erase(Uint32 start, Uint32 length)
{
    Int16 i;
    volatile Uint8 *pdata;
    Uint32 sector_base, end, delay;
    
    /* Calculate extents of range to erase */
    end = start + length - 1;
    
    /* Walk through each sector, erase any sectors within range */
    sector_base = DSK6416_FLASH_BASE;
    for (i = 0; i < DSK6416_FLASH_SECTORS; i++)
    {
        if ((start <= sector_base) && (sector_end[i] <= end))
        {
            /* Start sector erase sequence */
            *((volatile Uint8 *)DSK6416_FLASH_CTLAAA) = 0xaa;
            *((volatile Uint8 *)DSK6416_FLASH_CTL555) = 0x55;
            *((volatile Uint8 *)DSK6416_FLASH_CTLAAA) = 0x80;
            *((volatile Uint8 *)DSK6416_FLASH_CTLAAA) = 0xaa;
            *((volatile Uint8 *)DSK6416_FLASH_CTL555) = 0x55;
            
            /* Start erase at sector address */
            pdata = (Uint8 *)sector_end[i];
            *pdata = 0x30;
            
            for (delay = 0; delay < 100; delay++);
            
            /* Wait for erase to complete */
            while (1)
                if (*pdata & 0x80)
                    break;
                    
            /* Put back in read mode */
            *((volatile Uint8 *)DSK6416_FLASH_BASE) = 0xf0;                    
        }
        
        /* Advance to next sector */
        sector_base = sector_end[i] + 1;
    }
}
