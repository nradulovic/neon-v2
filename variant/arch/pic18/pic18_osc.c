/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <xc.h>

#include "pic18_osc.h"

#include "neon.h"

#define INTERNAL_FRC_HZ                        8000000ul
#define INTERNAL_LFINTOSC_HZ                   31000ul

static uint32_t hfintosc(void)
{
    static const uint32_t hfintosc_hz[] =
    {
        1000000u,
        2000000u,
        4000000u,
        8000000u,
        12000000u,
        16000000u,
        32000000u,
        48000000u,
        64000000u,
    };
    return hfintosc_hz[OSCFRQbits.HFFRQ];
}

uint32_t pic18_osc_get_sysclk_hz(void)
{
    uint32_t sysclk_hz = 0u;
    
    switch (OSCCON2bits.COSC) {
#if (PIC18_BOARD_OSC_PRI_CLOCK_HZ != 0)
        case 2:
            sysclk_hz = PIC18_BOARD_OSC_PRI_CLOCK_HZ << 2;
            break;
#endif
#if (PIC18_BOARD_OSC_SEC_CLOCK_HZ != 0)
        case 4:
            sysclk_hz = PIC18_BOARD_OSC_SEC_CLOCK_HZ;
            break;
#endif 
        case 5:
            sysclk_hz = INTERNAL_LFINTOSC_HZ;
            break;
        case 6:
            sysclk_hz = hfintosc();
            break;
#if (PIC18_BOARD_OSC_PRI_CLOCK_HZ != 0)
        case 7:
            sysclk_hz = PIC18_BOARD_OSC_PRI_CLOCK_HZ;
            break;
#endif
        default:
            return 0;
    }
    sysclk_hz >>= OSCCON2bits.CDIV;

    return sysclk_hz;
}

uint32_t pic18_osc_get_pbclk_hz(void)
{
    return hfintosc();
}

void pic18_osc_new_source(enum pic18_osc_source source)
{
    nlogger_info("PIC18 OSC: Setting clock source to %d", source);

    switch (source) {
#if (PIC18_BOARD_OSC_PRI_CLOCK_HZ != 0)
        case PIC18_OSC_SOURCE_PRIPLL:
            OSCENbits.EXTOEN = 1;
            
            while (OSCSTATbits.EXTOR == 0);
            OSCCON1bits.NOSC = 7;
            break;
#endif
        default:
            return;
    }
    
    while (OSCCON3bits.ORDY == 0);

    nlogger_info("PIC18 OSC: CPU clock %uHz", pic18_osc_get_sysclk_hz());
    nlogger_info("PIC18 OSC: PB  clock %uHz", pic18_osc_get_pbclk_hz());
}