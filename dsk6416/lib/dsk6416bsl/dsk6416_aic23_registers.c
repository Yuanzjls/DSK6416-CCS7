/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416_aic23_registers.c ========
 *  DSK6416_AIC23_rset() and DSK6416_AIC23_rget() implementation
 */
#include <dsk6416.h>
#include <dsk6416_aic23.h>

/* Internal codec state used to simulate read/write functionality */
static DSK6416_AIC23_Config codecstate = DSK6416_AIC23_DEFAULTCONFIG;

/*
 *  ======== DSK6416_AIC23_rset ========
 *  Set codec register regnum to value regval
 */
void DSK6416_AIC23_rset(DSK6416_AIC23_CodecHandle hCodec, Uint16 regnum, Uint16 regval)
{
    /* Mask off lower 9 bits */
    regval &= 0x1ff;
    
    /* Wait for XRDY signal before writing data to DXR */
    while (!MCBSP_xrdy(DSK6416_AIC23_CONTROLHANDLE));
    
    /* Write 16 bit data value to DXR */
    MCBSP_write(DSK6416_AIC23_CONTROLHANDLE, (regnum << 9) | regval);
    
    /* Save register value if regnum is in range */
    if (regnum < DSK6416_AIC23_NUMREGS)
        codecstate.regs[regnum] = regval;
        
    /* Wait for XRDY, state machine will not update until next McBSP clock */
    while (MCBSP_xrdy(DSK6416_AIC23_CONTROLHANDLE));

}

/*
 *  ======== DSK6416_AIC23_rget ========
 *  Return value of codec register regnum
 */
Uint16 DSK6416_AIC23_rget(DSK6416_AIC23_CodecHandle hCodec, Uint16 regnum)
{
    if (regnum < DSK6416_AIC23_NUMREGS)
        return codecstate.regs[regnum];
    else
        return 0;    
}

/*
 *  ======== DSK6416_AIC23_config ========
 *  Set the default codec register config values
 */
void DSK6416_AIC23_config(DSK6416_AIC23_CodecHandle hCodec, DSK6416_AIC23_Config *Config)
{
    int i;
    
    /* Use default parameters if none are given */
    if (Config == NULL)
    	Config = &codecstate;
    	
    /* Configure power down register first */
    DSK6416_AIC23_rset(hCodec, DSK6416_AIC23_POWERDOWN,
        Config -> regs[DSK6416_AIC23_POWERDOWN]);
    
    /* Assign each register */
    for (i = 0; i < DSK6416_AIC23_NUMREGS; i++)
        if (i != DSK6416_AIC23_POWERDOWN)
            DSK6416_AIC23_rset(hCodec, i, Config -> regs[i]);
}
