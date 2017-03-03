/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_flash_write.c ========
 *  DSK6416_FLASH_write() implementation
 */

#include <std.h>
#include <csl.h>

#include <dsk6416.h>
#include <dsk6416_flash.h>

/* Write data to a data range in Flash */
void DSK6416_FLASH_write(Uint32 src, Uint32 dst, Uint32 length)
{
    volatile Uint8 *psrc, *pdst;
    Uint32 i, delay;
    
    /* Establish source and destination */
    psrc = (volatile Uint8 *)src;
    pdst = (volatile Uint8 *)dst; 
    for (i = 0; i < length; i++)
    {
        /* Program one 8-bit word */
        *((volatile Uint8 *)DSK6416_FLASH_CTLAAA) = 0xaa;
        *((volatile Uint8 *)DSK6416_FLASH_CTL555) = 0x55;
        *((volatile Uint8 *)DSK6416_FLASH_CTLAAA) = 0xa0;
        *pdst = *psrc;
        
        /* Wait a short amount of time */
        for (delay = 0; delay < 4; delay++);
        
        /* Wait for operation to complete */
        while(1)
            if (*pdst == *psrc)
                break;
                
        pdst++;
        psrc++;
    }
    
    /* Put back in read mode */
    *((volatile Uint16 *)DSK6416_FLASH_BASE) = 0xf0;    
}
