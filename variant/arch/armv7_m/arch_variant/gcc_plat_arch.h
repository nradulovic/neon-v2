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
 *  @brief       GCC platform supported by architecture header
 *
 *  @addtogroup  port
 *  @{
 */
/** @defgroup    port_armv7_m_variant_arch_common GCC platform supported by architecture
 *  @brief       GCC platform supported by architecture
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_ARMV7_M_ARCH_VARIANT_GCC_PLAT_ARCH_H_
#define NEON_ARMV7_M_ARCH_VARIANT_GCC_PLAT_ARCH_H_

#include <stdint.h>

#include "port/nport_platform.h"
#include "common_plat_arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   ARMv7-M_variant_arch_cpu_gcc Architecture CPU (ARMv7-M) operations (GCC specific)
 *  @brief      Architecture CPU (ARMv7-M) operations (GCC specific)
 *  @{
 */

NPLATFORM_INLINE
uint_fast8_t narch_log2(narch_uint x)
{
    uint_fast8_t clz;

    __asm__ __volatile__ (
        "@  ncore_log2                                      \n"
        "   clz    %0, %1                                   \n"
        : "=r"(clz)
        : "r"(x));

    return (31u - clz);
}

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_ARMV7_M_ARCH_VARIANT_GCC_PLAT_ARCH_H_ */
