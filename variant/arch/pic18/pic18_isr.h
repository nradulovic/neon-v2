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
 *  @brief       Interrupt module for PIC18 series
 *
 *  @addtogroup  port
 *  @{ */

/** @defgroup    port_pic18_isr Interrupt module for PIC18 series
 *  @brief       Interrupt module for PIC18 series
 *  @{ */

#ifndef NEON_PIC18_ISR_H_
#define NEON_PIC18_ISR_H_

#include <stdint.h>

#include "board_variant/board.h"

#ifdef __cplusplus
extern "C" {
#endif

void pic18_isr_init(void);

void pic18_isr_high_app(void);
void pic18_isr_low_app(void);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC18_ISR_H_ */
