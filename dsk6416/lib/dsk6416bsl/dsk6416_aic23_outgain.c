/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_aic23_setfreq.c ========
 *  DSK6416_AIC23_setFreq() implementation
 */
 
#include <dsk6416.h>
#include <dsk6416_aic23.h>

/*
 *  ======== DSK6416_AIC23_outGain ========
 *  Set the output gain on the codec
 */
void DSK6416_AIC23_outGain(DSK6416_AIC23_CodecHandle hCodec, Uint16 outGain)
{
    /* Write to codec registers (left and right) */
    DSK6416_AIC23_rset(hCodec, DSK6416_AIC23_LEFTHPVOL, 
        (DSK6416_AIC23_rget(hCodec, DSK6416_AIC23_LEFTHPVOL) & 0xff80) | (outGain & 0x7f));
    DSK6416_AIC23_rset(hCodec, DSK6416_AIC23_RIGHTHPVOL, 
        (DSK6416_AIC23_rget(hCodec, DSK6416_AIC23_RIGHTHPVOL) & 0xff80) | (outGain & 0x7f));
}

