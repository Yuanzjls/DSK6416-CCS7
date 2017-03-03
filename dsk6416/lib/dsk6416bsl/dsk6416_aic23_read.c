/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_aic23_read16.c ========
 *  DSK6416_AIC23_read() implementation
 */
 
#include <dsk6416.h>
#include <dsk6416_aic23.h>

/*
 *  ======== DSK6416_AIC23_read ========
 *  Read a 32-bit value from the codec
 */
Int16 DSK6416_AIC23_read(DSK6416_AIC23_CodecHandle hCodec, Uint32 *val)
{
    /* If McBSP doesn't have new data available, return false */
    if (!MCBSP_rrdy(DSK6416_AIC23_DATAHANDLE)) {
        return (FALSE);
    }

    /* Read the data */
    *val = MCBSP_read(DSK6416_AIC23_DATAHANDLE);

    /* Short delay for McBSP state machine to update */    
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    
    return (TRUE);
}
