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
 *  @brief       PIC32 UART specifics
 *
 *  @addtogroup  port
 *  @{ */

/** @defgroup    port_pic32_uart PIC32 UART specifics
 *  @brief       PIC32 UART specifics
 *  @{ */

#ifndef NEON_PIC32_UART_H_
#define NEON_PIC32_UART_H_

#include <stdint.h>

#include "neon_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

struct pic32_uart_board_config
{
    uint8_t e_isr_prio;
    uint8_t rx_isr_prio;
    uint8_t tx_isr_prio;
};

#if (NBOARD_USES_UART_5 == 1)
extern const struct pic32_uart_board_config PIC32_UART_5_BOARD_CONFIG;
#endif

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC32_UART_H_ */
