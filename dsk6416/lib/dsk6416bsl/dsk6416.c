/*
 *  Copyright 2003 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ======== dsk6416.c ========
 *  DSK6416 board initializion implementation.
 */

#include <csl.h>
#include <csl_emif.h>
#include <csl_emifa.h>
#include <csl_emifb.h>
#include <dsk6416.h>

/*
 *    6416 DSK Version Table
 *
 *    Board Rev  CPLD Rev  Vesion  Features
 *       3          2         1    600 MHz 6416, 100 MHz EMIF
 *       4          3         2    720 MHz 6416, 120 MHz EMIF
 *       5          4         3    1 GHz 6416T, 120 MHz EMIF
 */

Int16 DSK6416_version;
static Uint16 DSK6416_usecdelay;

/* Initialize the board APIs */
void DSK6416_init()
{
    /* EMIFA settings for 600/100 MHz operation */
    EMIFA_Config emifaCfg0v1 = {
        EMIFA_FMKS(GBLCTL, EK2RATE, FULLCLK)    |
        EMIFA_FMKS(GBLCTL, EK2HZ, CLK)          |
        EMIFA_FMKS(GBLCTL, EK2EN, ENABLE)       |
        EMIFA_FMKS(GBLCTL, BRMODE, MRSTATUS)    |
        EMIFA_FMKS(GBLCTL, NOHOLD, DISABLE)     |
        EMIFA_FMKS(GBLCTL, EK1HZ, HIGHZ)        |
        EMIFA_FMKS(GBLCTL, EK1EN, ENABLE)       |
        EMIFA_FMKS(GBLCTL, CLK4EN, ENABLE)      |
        EMIFA_FMKS(GBLCTL, CLK6EN, DISABLE),
        
        EMIFA_FMKS(CECTL, WRSETUP, DEFAULT)    |
        EMIFA_FMKS(CECTL, WRSTRB, DEFAULT)     |
        EMIFA_FMKS(CECTL, WRHLD, DEFAULT)      |
        EMIFA_FMKS(CECTL, RDSETUP, DEFAULT)    |
        EMIFA_FMKS(CECTL, TA, DEFAULT)         |
        EMIFA_FMKS(CECTL, RDSTRB, DEFAULT)     |
        EMIFA_FMKS(CECTL, MTYPE, SDRAM64)      |
        EMIFA_FMKS(CECTL, RDHLD, DEFAULT),
        
        EMIFA_FMKS(CECTL, WRSETUP, DEFAULT)    |
        EMIFA_FMKS(CECTL, WRSTRB, DEFAULT)     |
        EMIFA_FMKS(CECTL, WRHLD, DEFAULT)      |
        EMIFA_FMKS(CECTL, RDSETUP, DEFAULT)    |
        EMIFA_FMKS(CECTL, TA, DEFAULT)         |
        EMIFA_FMKS(CECTL, RDSTRB, DEFAULT)     |
        EMIFA_FMKS(CECTL, MTYPE, DEFAULT)      |
        EMIFA_FMKS(CECTL, RDHLD, DEFAULT),
        
        EMIFA_FMKS(CECTL, WRSETUP, OF(2))      |
        EMIFA_FMKS(CECTL, WRSTRB, OF(10))      |
        EMIFA_FMKS(CECTL, WRHLD, OF(2))        |
        EMIFA_FMKS(CECTL, RDSETUP, OF(2))      |
        EMIFA_FMKS(CECTL, TA, OF(2))           |
        EMIFA_FMKS(CECTL, RDSTRB, OF(10))      |
        EMIFA_FMKS(CECTL, MTYPE, ASYNC32)      |
        EMIFA_FMKS(CECTL, RDHLD, OF(2)),

        EMIFA_FMKS(CECTL, WRSETUP, OF(2))      |
        EMIFA_FMKS(CECTL, WRSTRB, OF(10))      |
        EMIFA_FMKS(CECTL, WRHLD, OF(2))        |
        EMIFA_FMKS(CECTL, RDSETUP, OF(2))      |
        EMIFA_FMKS(CECTL, TA, OF(2))           |
        EMIFA_FMKS(CECTL, RDSTRB, OF(10))      |
        EMIFA_FMKS(CECTL, MTYPE, ASYNC32)      |
        EMIFA_FMKS(CECTL, RDHLD, OF(2)),
        
        EMIFA_FMKS(SDCTL, SDBSZ, 4BANKS)       |
        EMIFA_FMKS(SDCTL, SDRSZ, 11ROW)        |
        EMIFA_FMKS(SDCTL, SDCSZ, 8COL)         |
        EMIFA_FMKS(SDCTL, RFEN, ENABLE)        |
        EMIFA_FMKS(SDCTL, INIT, YES)           |
        EMIFA_FMKS(SDCTL, TRCD, OF(1))         |
        EMIFA_FMKS(SDCTL, TRP, OF(1))          |
        EMIFA_FMKS(SDCTL, TRC, OF(5))          |
        EMIFA_FMKS(SDCTL, SLFRFR, DISABLE),
        
        EMIFA_FMKS(SDTIM, XRFR, OF(0))         |
        EMIFA_FMKS(SDTIM, PERIOD, OF(1560)),
        
        EMIFA_FMKS(SDEXT, WR2RD, OF(0))        |
        EMIFA_FMKS(SDEXT, WR2DEAC, OF(2))      |
        EMIFA_FMKS(SDEXT, WR2WR, OF(1))        |
        EMIFA_FMKS(SDEXT, R2WDQM, OF(1))       |
        EMIFA_FMKS(SDEXT, RD2WR, OF(0))        |
        EMIFA_FMKS(SDEXT, RD2DEAC, OF(1))      |
        EMIFA_FMKS(SDEXT, RD2RD, OF(0))        |
        EMIFA_FMKS(SDEXT, THZP, OF(2))         |
        EMIFA_FMKS(SDEXT, TWR, OF(1))          |
        EMIFA_FMKS(SDEXT, TRRD, OF(0))         |
        EMIFA_FMKS(SDEXT, TRAS, OF(4))         |
        EMIFA_FMKS(SDEXT, TCL, OF(1)),         
        
        EMIFA_CESEC_DEFAULT,
        EMIFA_CESEC_DEFAULT,
        EMIFA_CESEC_DEFAULT,
        EMIFA_CESEC_DEFAULT
    };
    
    /* EMIFB settings for 600/100 MHz operation */
    EMIFB_Config emifbCfg0v1 = {
        EMIFB_FMKS(GBLCTL, EK2RATE, FULLCLK)    |
        EMIFB_FMKS(GBLCTL, EK2HZ, CLK)          |
        EMIFB_FMKS(GBLCTL, EK2EN, DISABLE)      |
        EMIFB_FMKS(GBLCTL, BRMODE, MRSTATUS)    |
        EMIFB_FMKS(GBLCTL, NOHOLD, DISABLE)     |
        EMIFB_FMKS(GBLCTL, EK1HZ, HIGHZ)        |
        EMIFB_FMKS(GBLCTL, EK1EN, ENABLE),
        
        EMIFB_FMKS(CECTL, WRSETUP, OF(0))      |
        EMIFB_FMKS(CECTL, WRSTRB, OF(8))       |
        EMIFB_FMKS(CECTL, WRHLD, OF(2))        |
        EMIFB_FMKS(CECTL, RDSETUP, OF(0))      |
        EMIFB_FMKS(CECTL, TA, OF(2))           |
        EMIFB_FMKS(CECTL, RDSTRB, OF(8))       |
        EMIFB_FMKS(CECTL, MTYPE, ASYNC8)       |
        EMIFB_FMKS(CECTL, RDHLD, OF(0)),
        
        EMIFB_FMKS(CECTL, WRSETUP, OF(0))      |
        EMIFB_FMKS(CECTL, WRSTRB, OF(8))       |
        EMIFB_FMKS(CECTL, WRHLD, OF(2))        |
        EMIFB_FMKS(CECTL, RDSETUP, OF(0))      |
        EMIFB_FMKS(CECTL, TA, OF(2))           |
        EMIFB_FMKS(CECTL, RDSTRB, OF(8))       |
        EMIFB_FMKS(CECTL, MTYPE, ASYNC8)       |
        EMIFB_FMKS(CECTL, RDHLD, OF(0)),
        
        EMIFB_FMKS(CECTL, WRSETUP, DEFAULT)    |
        EMIFB_FMKS(CECTL, WRSTRB, DEFAULT)     |
        EMIFB_FMKS(CECTL, WRHLD, DEFAULT)      |
        EMIFB_FMKS(CECTL, RDSETUP, DEFAULT)    |
        EMIFB_FMKS(CECTL, TA, DEFAULT)         |
        EMIFB_FMKS(CECTL, RDSTRB, DEFAULT)     |
        EMIFB_FMKS(CECTL, MTYPE, DEFAULT)      |
        EMIFB_FMKS(CECTL, RDHLD, DEFAULT),

        EMIFB_FMKS(CECTL, WRSETUP, DEFAULT)    |
        EMIFB_FMKS(CECTL, WRSTRB, DEFAULT)     |
        EMIFB_FMKS(CECTL, WRHLD, DEFAULT)      |
        EMIFB_FMKS(CECTL, RDSETUP, DEFAULT)    |
        EMIFB_FMKS(CECTL, TA, DEFAULT)         |
        EMIFB_FMKS(CECTL, RDSTRB, DEFAULT)     |
        EMIFB_FMKS(CECTL, MTYPE, DEFAULT)      |
        EMIFB_FMKS(CECTL, RDHLD, DEFAULT),
        
        EMIFB_FMKS(SDCTL, SDBSZ, DEFAULT)      |
        EMIFB_FMKS(SDCTL, SDRSZ, DEFAULT)      |
        EMIFB_FMKS(SDCTL, SDCSZ, DEFAULT)      |
        EMIFB_FMKS(SDCTL, RFEN, DEFAULT)       |
        EMIFB_FMKS(SDCTL, INIT, DEFAULT)       |
        EMIFB_FMKS(SDCTL, TRCD, DEFAULT)       |
        EMIFB_FMKS(SDCTL, TRP, DEFAULT)        |
        EMIFB_FMKS(SDCTL, TRC, DEFAULT),
        
        EMIFB_FMKS(SDTIM, XRFR, DEFAULT)       |
        EMIFB_FMKS(SDTIM, PERIOD, DEFAULT),
        
        EMIFB_FMKS(SDEXT, WR2RD, DEFAULT)      |
        EMIFB_FMKS(SDEXT, WR2DEAC, DEFAULT)    |
        EMIFB_FMKS(SDEXT, WR2WR, DEFAULT)      |
        EMIFB_FMKS(SDEXT, R2WDQM, DEFAULT)     |
        EMIFB_FMKS(SDEXT, RD2WR, DEFAULT)      |
        EMIFB_FMKS(SDEXT, RD2DEAC, DEFAULT)    |
        EMIFB_FMKS(SDEXT, RD2RD, DEFAULT)      |
        EMIFB_FMKS(SDEXT, THZP, DEFAULT)       |
        EMIFB_FMKS(SDEXT, TWR, DEFAULT)        |
        EMIFB_FMKS(SDEXT, TRRD, DEFAULT)       |
        EMIFB_FMKS(SDEXT, TRAS, DEFAULT)       |
        EMIFB_FMKS(SDEXT, TCL, DEFAULT),         

        EMIFB_CESEC_DEFAULT,
        EMIFB_CESEC_DEFAULT,
        EMIFB_CESEC_DEFAULT,
        EMIFB_CESEC_DEFAULT
    };
    
    /* EMIFA settings for 720/120 MHz operation */
    EMIFA_Config emifaCfg0v2 = {
        EMIFA_FMKS(GBLCTL, EK2RATE, FULLCLK)    |
        EMIFA_FMKS(GBLCTL, EK2HZ, CLK)          |
        EMIFA_FMKS(GBLCTL, EK2EN, ENABLE)       |
        EMIFA_FMKS(GBLCTL, BRMODE, MRSTATUS)    |
        EMIFA_FMKS(GBLCTL, NOHOLD, DISABLE)     |
        EMIFA_FMKS(GBLCTL, EK1HZ, HIGHZ)        |
        EMIFA_FMKS(GBLCTL, EK1EN, ENABLE)       |
        EMIFA_FMKS(GBLCTL, CLK4EN, ENABLE)      |
        EMIFA_FMKS(GBLCTL, CLK6EN, DISABLE),
        
        EMIFA_FMKS(CECTL, WRSETUP, DEFAULT)    |
        EMIFA_FMKS(CECTL, WRSTRB, DEFAULT)     |
        EMIFA_FMKS(CECTL, WRHLD, DEFAULT)      |
        EMIFA_FMKS(CECTL, RDSETUP, DEFAULT)    |
        EMIFA_FMKS(CECTL, TA, DEFAULT)         |
        EMIFA_FMKS(CECTL, RDSTRB, DEFAULT)     |
        EMIFA_FMKS(CECTL, MTYPE, SDRAM64)      |
        EMIFA_FMKS(CECTL, RDHLD, DEFAULT),
        
        EMIFA_FMKS(CECTL, WRSETUP, DEFAULT)    |
        EMIFA_FMKS(CECTL, WRSTRB, DEFAULT)     |
        EMIFA_FMKS(CECTL, WRHLD, DEFAULT)      |
        EMIFA_FMKS(CECTL, RDSETUP, DEFAULT)    |
        EMIFA_FMKS(CECTL, TA, DEFAULT)         |
        EMIFA_FMKS(CECTL, RDSTRB, DEFAULT)     |
        EMIFA_FMKS(CECTL, MTYPE, DEFAULT)      |
        EMIFA_FMKS(CECTL, RDHLD, DEFAULT),
        
        EMIFA_FMKS(CECTL, WRSETUP, OF(2))      |
        EMIFA_FMKS(CECTL, WRSTRB, OF(12))      |
        EMIFA_FMKS(CECTL, WRHLD, OF(2))        |
        EMIFA_FMKS(CECTL, RDSETUP, OF(2))      |
        EMIFA_FMKS(CECTL, TA, OF(2))           |
        EMIFA_FMKS(CECTL, RDSTRB, OF(12))      |
        EMIFA_FMKS(CECTL, MTYPE, ASYNC32)      |
        EMIFA_FMKS(CECTL, RDHLD, OF(2)),

        EMIFA_FMKS(CECTL, WRSETUP, OF(2))      |
        EMIFA_FMKS(CECTL, WRSTRB, OF(12))      |
        EMIFA_FMKS(CECTL, WRHLD, OF(2))        |
        EMIFA_FMKS(CECTL, RDSETUP, OF(2))      |
        EMIFA_FMKS(CECTL, TA, OF(2))           |
        EMIFA_FMKS(CECTL, RDSTRB, OF(12))      |
        EMIFA_FMKS(CECTL, MTYPE, ASYNC32)      |
        EMIFA_FMKS(CECTL, RDHLD, OF(2)),
        
        EMIFA_FMKS(SDCTL, SDBSZ, 4BANKS)       |
        EMIFA_FMKS(SDCTL, SDRSZ, 11ROW)        |
        EMIFA_FMKS(SDCTL, SDCSZ, 8COL)         |
        EMIFA_FMKS(SDCTL, RFEN, ENABLE)        |
        EMIFA_FMKS(SDCTL, INIT, YES)           |
        EMIFA_FMKS(SDCTL, TRCD, OF(1))         |
        EMIFA_FMKS(SDCTL, TRP, OF(1))          |
        EMIFA_FMKS(SDCTL, TRC, OF(5))          |
        EMIFA_FMKS(SDCTL, SLFRFR, DISABLE),

        EMIFA_FMKS(SDTIM, XRFR, OF(0))         |
        EMIFA_FMKS(SDTIM, PERIOD, OF(1872)),
        
        EMIFA_FMKS(SDEXT, WR2RD, OF(1))        |
        EMIFA_FMKS(SDEXT, WR2DEAC, OF(3))      |
        EMIFA_FMKS(SDEXT, WR2WR, OF(1))        |
        EMIFA_FMKS(SDEXT, R2WDQM, OF(3))       |
        EMIFA_FMKS(SDEXT, RD2WR, OF(2))        |
        EMIFA_FMKS(SDEXT, RD2DEAC, OF(3))      |
        EMIFA_FMKS(SDEXT, RD2RD, OF(1))        |
        EMIFA_FMKS(SDEXT, THZP, OF(2))         |
        EMIFA_FMKS(SDEXT, TWR, OF(2))          |
        EMIFA_FMKS(SDEXT, TRRD, OF(0))         |
        EMIFA_FMKS(SDEXT, TRAS, OF(6))         |
        EMIFA_FMKS(SDEXT, TCL, OF(1)),         
        
        EMIFA_CESEC_DEFAULT,
        EMIFA_CESEC_DEFAULT,
        EMIFA_CESEC_DEFAULT,
        EMIFA_CESEC_DEFAULT
    };
    
    /* EMIFB settings for 720/120 MHz operation */
    EMIFB_Config emifbCfg0v2 = {
        EMIFB_FMKS(GBLCTL, EK2RATE, FULLCLK)    |
        EMIFB_FMKS(GBLCTL, EK2HZ, CLK)          |
        EMIFB_FMKS(GBLCTL, EK2EN, DISABLE)      |
        EMIFB_FMKS(GBLCTL, BRMODE, MRSTATUS)    |
        EMIFB_FMKS(GBLCTL, NOHOLD, DISABLE)     |
        EMIFB_FMKS(GBLCTL, EK1HZ, HIGHZ)        |
        EMIFB_FMKS(GBLCTL, EK1EN, ENABLE),
        
        EMIFB_FMKS(CECTL, WRSETUP, OF(0))      |
        EMIFB_FMKS(CECTL, WRSTRB, OF(10))      |
        EMIFB_FMKS(CECTL, WRHLD, OF(2))        |
        EMIFB_FMKS(CECTL, RDSETUP, OF(0))      |
        EMIFB_FMKS(CECTL, TA, OF(2))           |
        EMIFB_FMKS(CECTL, RDSTRB, OF(10))      |
        EMIFB_FMKS(CECTL, MTYPE, ASYNC8)       |
        EMIFB_FMKS(CECTL, RDHLD, OF(0)),
        
        EMIFB_FMKS(CECTL, WRSETUP, OF(0))      |
        EMIFB_FMKS(CECTL, WRSTRB, OF(10))      |
        EMIFB_FMKS(CECTL, WRHLD, OF(2))        |
        EMIFB_FMKS(CECTL, RDSETUP, OF(0))      |
        EMIFB_FMKS(CECTL, TA, OF(2))           |
        EMIFB_FMKS(CECTL, RDSTRB, OF(10))      |
        EMIFB_FMKS(CECTL, MTYPE, ASYNC8)       |
        EMIFB_FMKS(CECTL, RDHLD, OF(0)),
        
        EMIFB_FMKS(CECTL, WRSETUP, DEFAULT)    |
        EMIFB_FMKS(CECTL, WRSTRB, DEFAULT)     |
        EMIFB_FMKS(CECTL, WRHLD, DEFAULT)      |
        EMIFB_FMKS(CECTL, RDSETUP, DEFAULT)    |
        EMIFB_FMKS(CECTL, TA, DEFAULT)         |
        EMIFB_FMKS(CECTL, RDSTRB, DEFAULT)     |
        EMIFB_FMKS(CECTL, MTYPE, DEFAULT)      |
        EMIFB_FMKS(CECTL, RDHLD, DEFAULT),

        EMIFB_FMKS(CECTL, WRSETUP, DEFAULT)    |
        EMIFB_FMKS(CECTL, WRSTRB, DEFAULT)     |
        EMIFB_FMKS(CECTL, WRHLD, DEFAULT)      |
        EMIFB_FMKS(CECTL, RDSETUP, DEFAULT)    |
        EMIFB_FMKS(CECTL, TA, DEFAULT)         |
        EMIFB_FMKS(CECTL, RDSTRB, DEFAULT)     |
        EMIFB_FMKS(CECTL, MTYPE, DEFAULT)      |
        EMIFB_FMKS(CECTL, RDHLD, DEFAULT),
        
        EMIFB_FMKS(SDCTL, SDBSZ, DEFAULT)      |
        EMIFB_FMKS(SDCTL, SDRSZ, DEFAULT)      |
        EMIFB_FMKS(SDCTL, SDCSZ, DEFAULT)      |
        EMIFB_FMKS(SDCTL, RFEN, DEFAULT)       |
        EMIFB_FMKS(SDCTL, INIT, DEFAULT)       |
        EMIFB_FMKS(SDCTL, TRCD, DEFAULT)       |
        EMIFB_FMKS(SDCTL, TRP, DEFAULT)        |
        EMIFB_FMKS(SDCTL, TRC, DEFAULT),
        
        EMIFB_FMKS(SDTIM, XRFR, DEFAULT)       |
        EMIFB_FMKS(SDTIM, PERIOD, DEFAULT),
        
        EMIFB_FMKS(SDEXT, WR2RD, DEFAULT)      |
        EMIFB_FMKS(SDEXT, WR2DEAC, DEFAULT)    |
        EMIFB_FMKS(SDEXT, WR2WR, DEFAULT)      |
        EMIFB_FMKS(SDEXT, R2WDQM, DEFAULT)     |
        EMIFB_FMKS(SDEXT, RD2WR, DEFAULT)      |
        EMIFB_FMKS(SDEXT, RD2DEAC, DEFAULT)    |
        EMIFB_FMKS(SDEXT, RD2RD, DEFAULT)      |
        EMIFB_FMKS(SDEXT, THZP, DEFAULT)       |
        EMIFB_FMKS(SDEXT, TWR, DEFAULT)        |
        EMIFB_FMKS(SDEXT, TRRD, DEFAULT)       |
        EMIFB_FMKS(SDEXT, TRAS, DEFAULT)       |
        EMIFB_FMKS(SDEXT, TCL, DEFAULT),         

        EMIFB_CESEC_DEFAULT,
        EMIFB_CESEC_DEFAULT,
        EMIFB_CESEC_DEFAULT,
        EMIFB_CESEC_DEFAULT
    };
    
    /* Configure EMIFB for failsafe operation at 120MHz */
    EMIFB_config(&emifbCfg0v2);
    
    if (DSK6416_getVersion() == 1)
    {
        /* Initialize EMIFA */
        EMIFA_config(&emifaCfg0v1);

        /* Initialize EMIFB */
        EMIFB_config(&emifbCfg0v1);
        
        /* Set reference for software timing loops */
        DSK6416_usecdelay = 21;
    } else
    {
        /* Initialize EMIFA for 120 MHz operation, EMIFB is already set */
        EMIFA_config(&emifaCfg0v2);
        
        /* Set reference for software timing loops */
        if (DSK6416_getVersion() == 2)
            DSK6416_usecdelay = 29;
        else
            DSK6416_usecdelay = 41;
    }

    /* Set CPLD registers to default state */
    DSK6416_rset(DSK6416_USER_REG, 0);
    DSK6416_rset(DSK6416_DC_REG,   0);
    DSK6416_rset(DSK6416_MISC,     0);
}

/* Read an 8-bit value from a CPLD register */
Uint8 DSK6416_rget(Int16 regnum)
{
    Uint8 *pdata;
    
    /* Return lower 8 bits of register */
    pdata = (Uint8 *)(DSK6416_CPLD_BASE + regnum);
    return *pdata;
}

/* Write an 8-bit value to a CPLD register */
void DSK6416_rset(Int16 regnum, Uint8 regval)
{
    Uint8 *pdata;
    
    /* Write lower 8 bits of register */
    pdata = (Uint8 *)(DSK6416_CPLD_BASE + regnum);
    *pdata = regval;
}

/* Spin in a delay loop for delay iterations */
void DSK6416_wait(Uint32 delay)
{
    volatile Uint32 i, n;
    
    n = 0;
    for (i = 0; i < delay; i++)
    {
        n = n + 1;
    }
}

/* Spin in a delay loop for delay microseconds */
void DSK6416_waitusec(Uint32 delay)
{
    DSK6416_wait(delay * DSK6416_usecdelay);
}

/* Get the DSK version */
Int16 DSK6416_getVersion()
{
    DSK6416_version = 1;

    /* Check board revision */
    if ((DSK6416_rget(DSK6416_VERSION) & 0x7) == 5)
        DSK6416_version = 3;
    if ((DSK6416_rget(DSK6416_VERSION) & 0x7) == 4)
    {
        /* Check state of 600 MHz / 720 MHz config switch */
        if ((DSK6416_rget(DSK6416_MISC) & 0x10) == 0)
            DSK6416_version = 1;
        else
            DSK6416_version = 2;
    }
    
    return DSK6416_version;
}

