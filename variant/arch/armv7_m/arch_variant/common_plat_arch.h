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
 *  @brief       Common part of all platforms supported by architecture header
 *
 *  @addtogroup  port
 *  @{
 */
/** @defgroup    port_armv7_m_variant_arch_common Common part of all platforms supported by architecture
 *  @brief       Common part of all platforms supported by architecture
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_ARMV7_M_ARCH_VARIANT_COMMON_PLAT_ARCH_H_
#define NEON_ARMV7_M_ARCH_VARIANT_COMMON_PLAT_ARCH_H_

#include <stdint.h>
#include "port/nport_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   ARMv7-M_variant_arch_cpu Architecture CPU (ARMv7-M) operations
 *  @brief      Architecture CPU (ARMv7-M) operations.
 *  @{
 */

#define NARCH_ID "armv7_m"
#define NARCH_DATA_WIDTH 32 /* sizeof(narch_uint) * 8 */
#define NARCH_ARMV7_M 1

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
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_ARMV7_M_ARCH_VARIANT_COMMON_PLAT_ARCH_H_ */
