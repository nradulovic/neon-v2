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
 *  @brief       Variant architecture for PIC32 header
 *
 *  @addtogroup  port
 *  @{ */

/** @defgroup    port_pic18_variant_arch Variant architecture for PIC32
 *  @brief       Variant architecture for PIC32.
 *  @{ */

#ifndef NEON_PIC32_COMMON_H_
#define NEON_PIC32_COMMON_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    
struct __attribute__((packed , aligned(4))) pic32_periph_reg
{
    volatile uint32_t reg;
    volatile uint32_t clr;
    volatile uint32_t set;
    volatile uint32_t inv;
};

#define pic32_periph_access(base)                                           \
        ((struct pic32_periph_reg *)(base))

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC32_COMMON_H_ */
