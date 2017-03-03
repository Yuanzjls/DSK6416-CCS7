/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_aic23_mute.c ========
 *  DSK6416_AIC23_mute() implementation
 */
 
#include <dsk6416.h>
#include <dsk6416_aic23.h>

/*
 *  ======== DSK6416_AIC23_mute ========
 *  Enable/disable codec mute mode
 */
void DSK6416_AIC23_mute(DSK6416_AIC23_CodecHandle hCodec, Int16 mode)
{
    int regval;
    
    /* Enable mute if mode is true */
    regval = (mode) ? 0x08 : 0x00;
    
    /* Write to codec registers (left and right) */
    DSK6416_AIC23_rset(hCodec, DSK6416_AIC23_DIGPATH,
        (DSK6416_AIC23_rget(hCodec, DSK6416_AIC23_DIGPATH) & 0xfff7) | regval);
}
