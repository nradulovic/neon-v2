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

#include "pic32_osc.h"
#include "neon.h"

#define INTERNAL_FRC_HZ                        8000000ul
#define INTERNAL_LPRC_HZ                       31250ul

static const uint32_t pllodiv_frcdiv_pbdiv[8] =
{
    1u, 2u, 4u, 8u, 16u, 32u, 64u, 256u
};
    
uint32_t pic32_osc_get_sysclk_hz(void)
{
    static const uint32_t pllmult[8] =
    {
        15u, 16u, 17u, 18u, 19u, 20u, 21u, 24u
    };
    static const uint32_t pllidiv[8] =
    {
        1u, 2u, 3u, 4u, 5u, 6u, 10u, 12u
    };
    uint32_t sysclk_hz;
    
    switch (OSCCONbits.COSC & 0x7u) {
        case 0u:
            /* Internal Fast RC (FRC) Oscillator */
            sysclk_hz = INTERNAL_FRC_HZ;
            break;
        case 1u:
            /* Internal Fast RC Oscillator with PLL module via Postscaler 
             * (FRCPLL) 
             */
            sysclk_hz = (INTERNAL_FRC_HZ / pllidiv[DEVCFG2bits.FPLLIDIV]) 
                    * pllmult[OSCCONbits.PLLMULT] 
                    / pllodiv_frcdiv_pbdiv[OSCCONbits.PLLODIV];
            break;
        case 2u:
            /* Primary Oscillator (XT, HS or EC) */
            NASSERT(PIC32_EXT_PRI_CLOCK_HZ != 0);
            sysclk_hz = PIC32_EXT_PRI_CLOCK_HZ;
            break;
        case 3u:
            /* Primary Oscillator with PLL module (XTPLL, HSPLL or ECPLL) */
            NASSERT(PIC32_EXT_PRI_CLOCK_HZ != 0);
            sysclk_hz = 
                    (PIC32_EXT_PRI_CLOCK_HZ / pllidiv[DEVCFG2bits.FPLLIDIV]) 
                    * pllmult[OSCCONbits.PLLMULT]
                    / pllodiv_frcdiv_pbdiv[OSCCONbits.PLLODIV];
            break;
        case 4u:
            /* Secondary Oscillator (SOSC) */
            NASSERT(PIC32_EXT_SEC_CLOCK_HZ != 0);
            sysclk_hz = PIC32_EXT_SEC_CLOCK_HZ;
            break;
        case 5u:
            /* Internal Low-Power RC (LPRC) Oscillator */
            sysclk_hz = INTERNAL_LPRC_HZ;
            break;
        case 6u:
            /* Internal Fast RC (FRC) Oscillator divided by 16 */
            sysclk_hz = INTERNAL_FRC_HZ / 16u;
            break;
        case 7u:
            /* Internal Fast RC (FRC) Oscillator divided by OSCCON<FRCDIV> 
             * bits 
             */
            sysclk_hz = INTERNAL_FRC_HZ 
                / pllodiv_frcdiv_pbdiv[OSCCONbits.FRCDIV];
            break;
    }
    return sysclk_hz;
}

uint32_t pic32_osc_get_pbclk_hz(void)
{
    return pic32_osc_get_sysclk_hz() / pllodiv_frcdiv_pbdiv[OSCCONbits.PBDIV];
}