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
 *  @brief       OS support
 *
 *  @addtogroup  os
 *  @{
 */
/** @defgroup    os_none Barebone support (no OS)
 *  @brief       Barebone support (no OS)
 *  @{
 */

#ifndef NEON_OS_VARIANT_NONE_H_
#define NEON_OS_VARIANT_NONE_H_

#include "arch_variant/arch.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define NOS_CRITICAL_DECL(name)                                             \
        NARCH_ISR_STATE_DECL(name);

#define NOS_CRITICAL_LOCK(local_state)                                      \
        NARCH_ISR_LOCK(local_state)
#define NOS_CRITICAL_UNLOCK(local_state)                                    \
        NARCH_ISR_UNLOCK(local_state)

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_OS_VARIANT_NONE_H_ */
