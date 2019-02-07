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
 *  @brief       Memory pools header
 *
 *  @addtogroup  mem
 *  @{
 */
/** @defgroup    mem_pool Memory pool
 *  @brief       Memory pool management
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NMEM_POOL_H_
#define NMEM_POOL_H_

#include "list/nlist_sll.h"

#ifdef __cplusplus
extern "C" {
#endif

struct nmem_pool
{
	struct nlist_sll * free;
};

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NMEM_POOL_H_ */
