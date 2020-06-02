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
 *  @brief       Architecture header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_arch Architecture
 *  @brief       Architecture
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NK_ALLOCATOR_H_
#define NK_ALLOCATOR_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void * nk_allocator__alloc(size_t size);

void * nk_allocator__alloc_safe(size_t size);

void nk_allocator__free(void * mem);

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NK_ALLOCATOR_H_ */
