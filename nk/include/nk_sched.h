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

#include "nk_bitarray.h"

#ifdef __cplusplus
extern "C" {
#endif

struct nk_task__cb;

struct nk_ready_queue__indefinite
{
	struct nk_bitarray__indefinite * bitarray;
	struct nk_task__cb * task_cb;
};

#define NK_READY_QUEUE__DEFINITE_T(no_tasks) \
		{ \
			struct nk_sched__indefinite__ready_queue indefinite; \
			struct /* unnamed */ NK_BITARRAY__DEFINITE(no_tasks) bitarray; \
			struct nk_task__cb * task_cb[no_tasks]; \
		}

#define NK_READY_QUEUE__TO_INDEFINITE(rq) \
		(&(rq)->indefinite)

#define NK_READY_QUEUE__DEFINITE_INIT(rqd) \
		nk_ready_queue__indefinite__init(	\
				NK_READY_QUEUE__TO_INDEFINITE(rqd), \
				&(rqd)->bitarray, 			\
				&(rqd)->task_cb[0])

void nk_ready_queue__indefinite__init(
		struct nk_ready_queue__indefinite * rq,
		struct nk_bitarray__indefinite * bitarray,
		struct nk_task__cb * task_cb);

void nk_ready_queue__indefinite__ready(
		struct nk_ready_queue__indefinite * rq,
		struct nk_task__cb * task_cb,
		uint_fast8_t prio);

void nk_ready_queue__indefinite__block(
		struct nk_ready_queue__indefinite * rq,
		uint_fast8_t prio);

struct nk_task__cb * nk_ready_queue__indefinite__get(
		const struct nk_ready_queue__indefinite * rq);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NK_SCHED_H_ */
