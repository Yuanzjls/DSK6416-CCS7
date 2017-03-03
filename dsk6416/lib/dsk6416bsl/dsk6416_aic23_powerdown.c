/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_aic23_powerDown.c ========
 *  DSK6416_AIC23_powerDown() implementation
 */
 
#include <dsk6416.h>
#include <dsk6416_aic23.h>

/*
 *  ======== DSK6416_AIC23_powerDown ========
 *  Enable/disable powerdown modes for the DAC and ADC codec subsections
 */
void DSK6416_AIC23_powerDown(DSK6416_AIC23_CodecHandle hCodec, Uint16 sect)
{
    /* Write to codec register */
    DSK6416_AIC23_rset(hCodec, DSK6416_AIC23_POWERDOWN,
        (DSK6416_AIC23_rget(hCodec, DSK6416_AIC23_POWERDOWN) & 0xff00) | (sect & 0xff));
}
