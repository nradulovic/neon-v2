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
    uint32_t control_code;
    uint32_t arg;
    uint8_t isr_vector_prio;
};

extern const struct pic32_uart_board_config g_pic32_uart_5_board_config;

void pic32_uart_init(void);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC32_UART_H_ */
