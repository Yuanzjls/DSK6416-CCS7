/*
 *  Copyright 2002 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */
 
/*
 *  ======== dsk6416_led.c ========
 *  LED module for the DSK6416
 */
 
#include <csl.h>

#include "dsk6416.h"
#include "dsk6416_led.h"

static Int16 ledstate;

void DSK6416_LED_init()
{
    /* Turn all LEDs off */
    ledstate = 0;
    DSK6416_rset(DSK6416_USER_REG, ledstate);
}

void DSK6416_LED_off(Uint32 ledNum)
{
    /* Check bounds for ledNum */
    if (ledNum >= 4)
        return;
       
    /* Clear the LED bit */
    ledstate &= ~(1 << ledNum);
    DSK6416_rset(DSK6416_USER_REG, ledstate);
}

void DSK6416_LED_on(Uint32 ledNum)
{
    /* Check bounds for ledNum */
    if (ledNum >= 4)
        return;
        
    /* Set the LED bit */
    ledstate |= 1 << ledNum;
    DSK6416_rset(DSK6416_USER_REG, ledstate);
}

void DSK6416_LED_toggle(Uint32 ledNum)
{
    /* Check bounds for ledNum */
    if (ledNum >= 4)
        return;
        
    /* Toggle the LED bit */
    if ((DSK6416_rget(DSK6416_USER_REG) & (1 << ledNum)) == 0)
        DSK6416_LED_on(ledNum);
    else
        DSK6416_LED_off(ledNum);
}


