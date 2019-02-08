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

#include <stdint.h>
#include <stdbool.h>

#include "configs/default_config.h"
#include "queue/nqueue_pqueue.h"
#include "bits/nbits.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NTASK_PRIO_MAX          255
#define NTASK_PRIO_MIN          0

#define ncurrent                g_task_schedule.current

#define nerror                  ncurrent->tls.error

struct ntask;

typedef void (task_fn)(void * arg);

enum ntask_state
{
    NTASK_UNINITIALIZED         = 0,
    NTASK_DORMANT               = 1,
    NTASK_READY                 = 2,
    NTASK_CANCELLED             = 3,
    NTASK_BLOCKED               = 4
};

/** @brief      Task ready queue
 */
struct ntask_queue
{
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
    nbitarray_s bitarray;
#else
    nbitarray_x bitarray[NBITARRAY_DEF(NCONFIG_TASK_INSTANCES)];
#endif
};

struct ntask_schedule
{
    struct ntask_queue ready;
    struct ntask * current; /* Speed optimization, a pointer pointing to msbs
                               of the ready queue. */
    struct ntask * sentinel[NCONFIG_TASK_INSTANCES];
};

extern struct ntask_schedule g_task_schedule;

struct ntask * ntask_create(task_fn * fn, void * arg, uint_fast8_t prio);

void ntask_delete(struct ntask * task);

void ntask_start(struct ntask * task);

void ntask_stop(struct ntask * task);

void ntask_schedule(void);

void ntask_ready(struct ntask_queue * queue);

void ntask_block(struct ntask_queue * queue);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TASK_H_ */
