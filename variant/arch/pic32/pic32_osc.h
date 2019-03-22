/*
 * Neon
 * Copyright (C)  2018  REAL-TIME CONSULTING
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
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Oscillator module for PIC32
 *
 *  @addtogroup  port
 *  @{ */

/** @defgroup    port_pic32_osc Oscillator module for PIC32
 *  @brief       Oscillator module for PIC32.
 *  @{ */

#ifndef NEON_PIC32_OSC_H_
#define NEON_PIC32_OSC_H_

#include <stdint.h>

#include "board_variant/board.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#if !defined(PIC32_EXT_PRI_CLOCK_HZ)
#error "PIC32 based board needs to declare the primary clock frequency in PIC32_EXT_CLOCK"
#endif

#if !defined(PIC32_EXT_SEC_CLOCK_HZ)
#error "PIC32 based board needs to declare the secondary clock frequency in PIC32_EXT_SEC_CLOCK"
#endif
    
enum pic32_osc_source
{
    /*  Primary Oscillator with PLL module (XTPLL, HSPLL or ECPLL) */
    PIC32_OSC_SOURCE_PRIPLL,
};

uint32_t pic32_osc_get_sysclk_hz(void);
uint32_t pic32_osc_get_pbclk_hz(void);
void pic32_osc_new_source(enum pic32_osc_source source);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC32_OSC_H_ */
