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
 *  @brief       PIC32MX Clicker board
 *
 *  @addtogroup  board
 *  @{
 */
/** @defgroup    board_pic32mx_clicker PIC32MX Clicker board
 *  @brief       PIC32MX Clicker board
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_BOARD_VARIANT_PIC32MX_CLICKER_H_
#define NEON_BOARD_VARIANT_PIC32MX_CLICKER_H_

#include "mcu_variant/mcu.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NMCU_PIC32MX534F064H
#error "PIC32MX Clicker board uses PIC32MX534F064H"
#endif
    
#define NBOARD_PIC32MX_CLICKER
    
#define PIC32_BOARD_OSC_PRI_CLOCK_HZ    8000000ul
#define PIC32_BOARD_OSC_SEC_CLOCK_HZ    32768ul
#define PIC32_BOARD_UART_5_ISR_PRIO     PIC32MX_CLICKER_UART_ISR_PRIO
    
#define PIC32MX_CLICKER_UART            NUART_ID_5
#define PIC32MX_CLICKER_UART_CONTROL    0 /* Async mode, 8n1 */
#define PIC32MX_CLICKER_UART_BAUDRATE   115200
#define PIC32MX_CLICKER_UART_ISR_PRIO   3
    
#define NBOARD_USES_UART_5              1

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_BOARD_VARIANT_PIC32MX_CLICKER_H_ */
