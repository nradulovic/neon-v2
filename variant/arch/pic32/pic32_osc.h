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

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t g_osc_pbclk;
extern uint32_t g_osc_sysclk;


#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC32_OSC_H_ */
