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


#ifndef NEON_MODULE_TASK_H_
#define NEON_MODULE_TASK_H_

#include "configs/nconfig_default.h"
#include "bits/nbits.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief  	The highest task priority value.
 *
 *  The task with this priority has the highest urgency to be selected and
 *  dispatched by scheduler.
 */
#define NTASK_PRIO_MAX          255

/** @brief		The lowest task priority value
 */
#define NTASK_PRIO_MIN          0

/** @brief		The current thread.
 */
#define ncurrent                ntask_current()

/** @brief		The current thread error.
 */
#define nerror                  ncurrent->tls.error

struct ntask;

/** @brief		Task function pointer
 */
typedef void (ntask_fn)(void * arg);

enum ntask_state
{
    NTASK_UNINITIALIZED         = 0,
    NTASK_DORMANT               = 251,
    NTASK_READY                 = 252,
    NTASK_CANCELLED             = 253,
    NTASK_BLOCKED               = 254
};

/** @brief      Task ready/wait queue
 */
struct ntask_queue
{
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
    nbitarray_s bitarray;
#else
    nbitarray_x bitarray[NBITARRAY_DEF(NCONFIG_TASK_INSTANCES)];
#endif
};

struct ntask * ntask_current(void);

/** @brief		Create a task instance
 *  @param      fn
 *  			Pointer to task function. See @ref ntask_fn.
 *  @param		arg
 *  			Task function argument.
 *  @param		prio
 *  			Priority of the task. Minimum priority is @ref NTASK_PRIO_MIN
 *  			and maximum priority @ref NTASK_PRIO_MAX.
 *
 *  @pre		Pointer @a fn != NULL.
 *  @pre		Priority @a prio range ``(NTASK_PRIO_MIN, NTASK_PRIO_MAX]``
 *
 *  Create and initialize the task with given attributes. The task is allocated
 *  from internal task pool which size is defined with
 *  @ref NCONFIG_TASK_INSTANCES. When a task is created it is transitioned in
 *  to state @ref NTASK_DORMANT.
 */
struct ntask * ntask_create(ntask_fn * fn, void * arg, uint_fast8_t prio);

/** @brief		Delete the task instance.
 *  @param		task
 *  			Task structure.
 */
void ntask_delete(struct ntask * task);

/** @brief 		Start a task
 *  @param		task
 *  			Task structure.
 *
 *  When a task is started its state is changed to @ref NTASK_READY.
 */
void ntask_start(struct ntask * task);

void ntask_stop(struct ntask * task);

void ntask_schedule(void);

enum ntask_state ntask_state(const struct ntask * task);

void ntask_queue_ready(struct ntask_queue * queue);

void ntask_queue_block(struct ntask_queue * queue);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TASK_H_ */
