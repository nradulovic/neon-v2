
/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
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
 *  @brief       Platform header for common GCC definitions.
 *
 *  @addtogroup  mod_platform
 *  @{
 */
/** @defgroup    platform_gcc_common Common GCC Platform definitions
 *  @brief       Common GCC Platform definitions
 *  @{
 */
/*---------------------------------------------------------------------------*/

#ifndef NEON_GCC_VARIANT_GCC_COMMON_H_
#define NEON_GCC_VARIANT_GCC_COMMON_H_

#define GCC_VERSION                                                         \
    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#if GCC_VERSION < 40900
#error "GCC_VARIANT: Your compiler is too old - please upgrade it."
#endif

#if (defined(__STDC_VERSION__))
#if (__STDC_VERSION__ >= 201112L)
#include "../../../../../kernel/va_include/nport/platform_gcc/variant/gcc_c11.h"
#elif (__STDC_VERSION__ >= 199901L)
#include "variant/gcc_c99.h"
#elif (__STDC_VERSION__ >= 199409L)
#include "variant/gcc_c89.h"
#else
#error "GCC VARIANT: Define either C89, C99, or C11 C standard."
#endif
#else
#error "GCC_VARIANT: Unsupported compiler mode."
#endif

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------------------------------------------------------*/

#define NPLATFORM_FILE                  __FILE__

#define NPLATFORM_LINE                  __LINE__

#define NPLATFORM_NAKED(x)              __attribute__((naked)) x

#define NPLATFORM_UNUSED(y)             __attribute__((unused)) y

#define NPLATFORM_NORETURN(x)           __attribute__((noreturn)) x

#define NPLATFORM_PACKED(x)             __attribute__((packed)) x

#define NPLATFORM_ALIGN(align, x)       __attribute__((aligned (align))) x

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_GCC_VARIANT_GCC_COMMON_H_ */
