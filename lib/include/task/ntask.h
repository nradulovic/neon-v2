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

#define NTASK_QUEUE_SB 1
#define NTASK_QUEUE_FB 2
#define NTASK_QUEUE_DB 3
#define NTASK_QUEUE_SQ 4
#define NTASK_BITMAP_X 1
#define NTASK_BITMAP_S 2

#if ((NCONFIG_TASK_SCHED_RR == 1) && \
     (NCONFIG_TASK_PRIO_GROUPS == NCONFIG_TASK_PRIO_LEVELS))
#define NTASK_RDY_QUEUE_TYPE    NTASK_QUEUE_FB
#elif ((NCONFIG_TASK_SCHED_RR == 1) && \
       (NCONFIG_TASK_PRIO_GROUPS != NCONFIG_TASK_PRIO_LEVELS))
#define NTASK_RDY_QUEUE_TYPE    NTASK_QUEUE_SB
#elif ((NCONFIG_TASK_SCHED_PRIO == 1) && \
       (NCONFIG_TASK_PRIO_GROUPS == NCONFIG_TASK_PRIO_LEVELS))
#define NTASK_RDY_QUEUE_TYPE    NTASK_QUEUE_DB
#else
#error "Invalid configuration."
#endif

#if ((NCONFIG_TASK_SCHED_RR == 1) || (NCONFIG_TASK_PRIO_GROUPS > 32))
#define NTASK_WAIT_QUEUE_TYPE   NTASK_QUEUE_SQ
#elif (NCONFIG_TASK_SCHED_PRIO == 1)
#define NTASK_WAIT_QUEUE_TYPE   NTASK_QUEUE_DB
#else
#error "Invalid configuration."
#endif

#if (NCONFIG_TASK_PRIO_GROUPS > NARCH_DATA_WIDTH)
#define NTASK_BITMAP_TYPE       NTASK_BITMAP_X
#else
#define NTASK_BITMAP_TYPE       NTASK_BITMAP_S
#endif

struct ntask;

typedef void (task_fn)(struct ntask * task, void * arg);

enum ntask_state
{
    NTASK_UNINITIALIZED         = 0,
    NTASK_DORMANT               = 1,
    NTASK_READY                 = 2,
    NTASK_BLOCKED               = 3
};

/** @brief      Task ready queue
 */
struct ntask_rdy_queue
{
#if ((NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB))
    struct npqueue_sentinel sentinel[NCONFIG_TASK_PRIO_GROUPS];
#endif
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
    nbitarray_x bitarray[NBITARRAY_DEF(NCONFIG_TASK_PRIO_GROUPS)];
#else
    nbitarray_s bitarray[1];
#endif
};

/**
 * @brief       Task priority queue
 */
struct ntask_wait_queue
{
#if (NTASK_WAIT_QUEUE_TYPE == NTASK_QUEUE_SQ)
    struct npqueue_sentinel sentinel;
#else
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
    nbitarray_x bitarray[NBITARRAY_DEF(NCONFIG_TASK_PRIO_GROUPS)];
#else
    nbitarray_s bitarray[1];
#endif
#endif
};

struct ntask
{
#if ((NTASK_WAIT_QUEUE_TYPE == NTASK_QUEUE_SQ) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB))
    struct npqueue node;
#else
    uint_fast8_t prio;
#endif
    task_fn * fn;
    void * arg;
    enum ntask_state state;
    struct ntask_local_storage
    {
        uint32_t error;
    } tls;
};

struct ntask_schedule
{
    struct ntask * current;
    struct ntask_rdy_queue queue;
    struct ntask_wait_queue dormant;
    bool switch_pending;
#if (NCONFIG_TASK_SCHED_RR == 1)
    bool should_shift;
#endif
};

extern struct ntask_schedule g_task_schedule;

void ntask_init(struct ntask * task, task_fn * fn, void * arg, 
        uint_fast8_t prio);

void ntask_term(struct ntask * task);

#define ntask_state(a_task)  (a_task)->state

#if ((NTASK_WAIT_QUEUE_TYPE == NTASK_QUEUE_SQ) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB))
#define ntask_priority(a_task)   npqueue_priority(&(a_task)->node)
#else
#define ntask_priority(a_task)  (a_task)->prio
#endif

void ntask_looper(void);

/** @brief      Do the scheduling and return if task switch is needed.
 *  @return     Is task switching needed?
 *  @retval     true - Task switching is needed.
 *  @retval     false - Task switching is not needed.
 */
#define ntask_schedule()        g_task_schedule.switch_pending

void ntask_ready(struct ntask_wait_queue * queue, struct ntask * task);

void ntask_block(struct ntask_wait_queue * queue, struct ntask * task);

#define ntask_terminate(a_task)    											\
	ntask_block(&g_task_schedule.dormant, (a_task))

#define ncurrent                g_task_schedule.current
#define nerror                  ncurrent->tls.error

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TASK_H_ */
