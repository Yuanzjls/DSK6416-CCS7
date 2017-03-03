/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_flash_checksum.c ========
 *  DSK6416_FLASH_checksum() implementation
 */
 
#include <std.h>
#include <csl.h>

#include <dsk6416.h>
#include <dsk6416_flash.h>

/* Calculate the checksum of a data range in Flash */
Uint32 DSK6416_FLASH_checksum(Uint32 start, Uint32 length)
{
    Int16 i;
    Uint8 *pdata;
    Uint32 checksum;
    
    /* Establish source and destination */
    pdata = (Uint8 *)start;
    
    /* Calculate checksum by adding each word to the total */
    checksum = 0;
    for (i = 0; i < length; i++)
    {
        checksum += *pdata++;
    }
    
    return checksum;
}
