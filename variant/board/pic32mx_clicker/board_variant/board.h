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
    
#define PIC32MX_CLICKER_USE_UART        1
    
#define PIC32MX_CLICKER_UART            g_uart_5
#define PIC32MX_CLICKER_UART_CONTROL    NUART_COMMAND_SETUP  /* Async mode, 8n1 */
#define PIC32MX_CLICKER_UART_BAUDRATE   0
#define PIC32MX_CLICKER_UART_CONFIG     g_uart_5_board_config

#define PIC32MX_CLICKER_EXT_CLOCK       8000000ul
    
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_BOARD_VARIANT_PIC32MX_CLICKER_H_ */
