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
 *  @brief       Task header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_task Task
 *  @brief       Task
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NK_SCHED_H_
#define NK_SCHED_H_

#include <stdint.h>

#include "nk_list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct nk_sched__task_cb;

typedef uint_fast8_t (nk_sched__task_fn)(void * ws, void * arg);

typedef uint_fast8_t nk_sched__task_prio;

struct nk_sched__task_cb;

struct nk_sched__task_cb
{
    struct nk_list__node node;
    nk_sched__task_fn * fn;
    void * tls;
    void * arg;
};

void nk_sched__task_init(
		struct nk_sched__task_cb * tcb,
		nk_sched__task_fn * task_fn,
		void * tls,
		void * arg);

void nk_sched__task_ready(struct nk_sched__task_cb * tcb);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NK_SCHED_H_ */
