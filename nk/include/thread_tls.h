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
 *  @brief       Thread Local Storage (TLS)
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_thread_tls Thread Local Storage (TLS)
 *  @brief       Thread Local Storage.
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_THREAD_TLS_H_
#define NEON_THREAD_TLS_H_

#include <stdint.h>
#include "nthread_dispatch.h"

#ifdef __cplusplus
extern "C" {
#endif

struct nthread_tls
{
    int32_t error;
}

NPLATFORM_INLINE
struct nthread_tls * ng_tls(void)
{
    return (ng_current->tls);
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_THREAD_TLS_H_ */
