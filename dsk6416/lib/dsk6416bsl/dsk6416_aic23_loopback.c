/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_aic23_loopback.c ========
 *  DSK6416_AIC23_loopback() implementation
 */
 
#include <dsk6416.h>
#include <dsk6416_aic23.h>

/*
 *  ======== DSK6416_AIC23_loopback ========
 *  Enable/disable codec loopback mode
 */
void DSK6416_AIC23_loopback(DSK6416_AIC23_CodecHandle hCodec, Int16 mode)
{
    int regval;
    
    /* Set bypass bit if mode is true */
    regval = (mode) ? 0x8 : 0x0;
    
    /* Write to codec register */
    DSK6416_AIC23_rset(hCodec, DSK6416_AIC23_ANAPATH,
        (DSK6416_AIC23_rget(hCodec, DSK6416_AIC23_ANAPATH) & 0xfff7 | regval));
}
