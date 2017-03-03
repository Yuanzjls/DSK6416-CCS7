/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */
 
/*
 *  ======== dsk6416_dip.c ========
 *  DIP switch module for the DSK6416
 */

#include <csl.h>

#include <dsk6416.h>
#include <dsk6416_dip.h>

void DSK6416_DIP_init()
{
}

Uint32 DSK6416_DIP_get(Uint32 dipNum)
{
    /* Check bounds for dipNum */
    if (dipNum >= 4)
        return 0;
        
    /* Read DIP switch */
    if ((DSK6416_rget(DSK6416_USER_REG) & (0x10 << dipNum)) == 0)
        return 0;
    else
        return 1;
}

