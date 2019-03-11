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

#ifndef NEON_ARCH_VARIANT_PIC32_H_
#define NEON_ARCH_VARIANT_PIC32_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NARCH_ID                        "pic32"
#define NARCH_DATA_WIDTH                32 /* sizeof(narch_uint) * 8 */
#define NARCH_PIC32                     1

typedef uint32_t narch_uint;

/* TODO: Use static assert to compare NARCH_DATA_WIDTH and sizeof(narch_uint) */

static inline
narch_uint narch_exp2(uint_fast8_t x)
{
    return ((narch_uint)0x1u << x);
}

static inline
uint_fast8_t narch_log2(narch_uint x)
{
    return __builtin_clz(x) + 1u;
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_ARCH_VARIANT_PIC32_H_ */
