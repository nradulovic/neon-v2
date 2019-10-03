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
 *  @brief       Variant architecture for ARMv71 header
 *
 *  @addtogroup  port
 *  @{
 */
/** @defgroup    port_armv71_variant_arch Variant architecture for ARMv71
 *  @brief       Variant architecture for ARMv71.
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_ARM71_ARCH_VARIANT_ARCH_H_
#define NEON_ARM71_ARCH_VARIANT_ARCH_H_

#include <stdint.h>

#define NARCH_ID "armv7_m"
#define NARCH_DATA_WIDTH 32 /* sizeof(narch_uint) * 8 */
#define NARCH_ARMV71 1

typedef uint32_t narch_uint;

NPLATFORM_INLINE
void narch_set_bit(narch_uint * u32, uint_fast8_t bit)
{
    *u32 |= (narch_uint)1u << bit;
}

NPLATFORM_INLINE
void narch_clear_bit(narch_uint * u32, uint_fast8_t bit)
{
    *u32 &= ~((narch_uint)1u << bit);
}

NPLATFORM_INLINE
narch_uint narch_exp2(uint_fast8_t x)
{
    return (0x1u << x);
}

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_ARM71_ARCH_VARIANT_ARCH_H_ */
