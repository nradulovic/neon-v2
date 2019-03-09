
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
 *  @brief       Platform header for common XC32 definitions.
 *
 *  @addtogroup  mod_platform
 *  @{
 */
/** @defgroup    platform_xc32_common Common XC32 Platform definitions
 *  @brief       Common XC32 Platform definitions
 *  @{
 */
/*---------------------------------------------------------------------------*/

#ifndef NEON_GCC_PLATFORM_VARIANT_PLATFORM_H_
#define NEON_GCC_PLATFORM_VARIANT_PLATFORM_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------------------------------------------------------*/

#define NPLATFORM_GCC					1

#define NPLATFORM_FILE                  __FILE__

#define NPLATFORM_LINE                  __LINE__

#define NPLATFORM_NAKED(x)              __attribute__((naked)) x

#define NPLATFORM_UNUSED(y)             __attribute__((unused)) y

#define NPLATFORM_NORETURN(x)           __attribute__((noreturn)) x

#define NPLATFORM_PACKED(x)             __attribute__((packed)) x

#define NPLATFORM_ALIGN(align, x)       __attribute__((aligned (align))) x

#define NPLATFORM_INLINE        		static inline

#define NPLATFORM_INLINE_ALWAYS 		NPLATFORM_INLINE

#define NPLATFORM_CONTAINER_OF(ptr, type, member)                      \
    ((type *)((char *)ptr - offsetof(type, member)))

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_GCC_PLATFORM_VARIANT_PLATFORM_H_ */
