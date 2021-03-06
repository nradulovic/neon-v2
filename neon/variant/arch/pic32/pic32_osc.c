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

static const uint16_t pllodiv_frcdiv_pbdiv[8] =
{
    1u, 2u, 4u, 8u, 16u, 32u, 64u, 256u
};

uint32_t pic32_osc_get_sysclk_hz(void)
{
    static const uint8_t pllmult[8] =
    {
        15u, 16u, 17u, 18u, 19u, 20u, 21u, 24u
    };
    static const uint8_t pllidiv[8] =
    {
        1u, 2u, 3u, 4u, 5u, 6u, 10u, 12u
    };
    uint32_t sysclk_hz = 0u;

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
            sysclk_hz = PIC32_BOARD_OSC_PRI_CLOCK_HZ;
            break;
        case 3u:
            /* Primary Oscillator with PLL module (XTPLL, HSPLL or ECPLL) */
            sysclk_hz =
                    (PIC32_BOARD_OSC_PRI_CLOCK_HZ / pllidiv[DEVCFG2bits.FPLLIDIV])
                    * pllmult[OSCCONbits.PLLMULT]
                    / pllodiv_frcdiv_pbdiv[OSCCONbits.PLLODIV];
            break;
        case 4u:
            /* Secondary Oscillator (SOSC) */
            sysclk_hz = PIC32_BOARD_OSC_SEC_CLOCK_HZ;
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


void pic32_osc_new_source(enum pic32_osc_source source)
{
    nlogger_info("PIC32 OSC: Setting clock source to %d", source);

    SYSKEY = 0x00000000;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;
    switch (source) {
        case PIC32_OSC_SOURCE_PRIPLL:
            OSCCONbits.NOSC = 0x3u;
            break;
        default:
            return;
    }
    OSCCONbits.OSWEN = 1u;
    SYSKEY = 0x00000000;

    while (OSCCONbits.OSWEN == 1);

    nlogger_info("PIC32 OSC: CPU clock %uHz", pic32_osc_get_sysclk_hz());
    nlogger_info("PIC32 OSC: PB  clock %uHz", pic32_osc_get_pbclk_hz());
}