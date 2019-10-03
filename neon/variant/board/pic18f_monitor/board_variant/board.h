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
 *  @brief       PIC18F Monitor board
 *
 *  @addtogroup  board
 *  @{
 */
/** @defgroup    board_pic18f_monitor PIC18F Monitor board
 *  @brief       PIC18F Monitor board
 *  @{
 */

#ifndef NEON_BOARD_VARIANT_PIC18F_MONITOR_H_
#define NEON_BOARD_VARIANT_PIC18F_MONITOR_H_

#include "mcu_variant/mcu.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PIC18F46K40_MCU
#error "PIC18F Monitor board uses PIC18F46K40"
#endif
    
#define PIC18_BOARD_OSC_PRI_CLOCK_HZ    8000000
#define PIC18_BOARD_OSC_SEC_CLOCK_HZ    0
    
#define NBOARD_USES_UART_1              1
#define NBOARD_USES_STD_STREAM          1

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_BOARD_VARIANT_PIC18F_MONITOR_H_ */
