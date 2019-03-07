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

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>

#include "neon.h"

struct ntask
{
    ntask_fn *                  fn;             /**< Task function */
    void *                      arg;            /**< Task arguments */
    enum ntask_state            state;          /**< Task state */
    struct ntask_local_storage
    {
        enum nerror_id              error;      /**< Error indicator from last 
                                                 *   function call */
    }                           tls;            /**< Task Local Storage or 
                                                 *   TLS */
    NSIGNATURE_DECLARE
};


/** @brief		Scheduler context structure
 */
struct schedule
{
	ntask_id                    current;        /**< Speed optimization, 
                                                 *   current thread. */
   
    /** @brief      Task ready/wait queue
     */
    struct ntask_queue
    {
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
        nbitarray_s bitarray;
#else
        nbitarray_x bitarray[NBITARRAY_DEF(NCONFIG_TASK_INSTANCES)];
#endif
    }                           ready;          /**< Ready queue */
    struct nepa
    {
        struct ntask                task;
        struct np_lqueue_base *     evt_q;
        nepa_state *                state;
        void *                      ws;
    }                           mempool[NCONFIG_TASK_INSTANCES];
};

const uint32_t nbits_right_mask[33] =
{
    [ 0] = 0x00000000u,
    [ 1] = 0x00000001u,
    [ 2] = 0x00000003u,
    [ 3] = 0x00000007u,
    [ 4] = 0x0000000fu,
    [ 5] = 0x0000001fu,
    [ 6] = 0x0000003fu,
    [ 7] = 0x0000007fu,
    [ 8] = 0x000000ffu,
    [ 9] = 0x000001ffu,
    [10] = 0x000003ffu,
    [11] = 0x000007ffu,
    [12] = 0x00000fffu,
    [13] = 0x00001fffu,
    [14] = 0x00003fffu,
    [15] = 0x00007fffu,
    [16] = 0x0000ffffu,
    [17] = 0x0001ffffu,
    [18] = 0x0003ffffu,
    [19] = 0x0007ffffu,
    [20] = 0x000fffffu,
    [21] = 0x001fffffu,
    [22] = 0x003fffffu,
    [23] = 0x007fffffu,
    [24] = 0x00ffffffu,
    [25] = 0x01ffffffu,
    [26] = 0x03ffffffu,
    [27] = 0x07ffffffu,
    [28] = 0x0fffffffu,
    [29] = 0x1fffffffu,
    [30] = 0x3fffffffu,
    [31] = 0x7fffffffu,
    [32] = 0xffffffffu
};

/** @brief		Scheduler context
 */
static struct schedule g_task_schedule;

#if (NCONFIG_TASK_INSTANCES > NBITARRAY_X_MAX_SIZE)
# error "The limit of maximum task instances has been exceeded!"
#endif

#if (NCONFIG_TASK_INSTANCES > NTASK_PRIO_MAX)
# error "The limit of maximum task priorities has been exceeded!"
#endif

#if (NCONFIG_EXITABLE_SCHEDULER == 1)
static bool should_exit = false;
#endif

struct nlogger_instance p_nlogger_global =
{
    .level = NLOGGER_LEVEL_INFO
};

const uint32_t nconfig_compiled_id = NCONFIG_ID;

uint32_t nbits_ftou32(float val)
{
    uint32_t retval;

    memcpy(&retval, &val, sizeof(retval));

    return retval;
}

float nbits_u32tof(uint32_t val)
{
    float retval;

    memcpy(&retval, &val, sizeof(retval));

    return retval;
}

void nbitarray_x_set(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = (uint_fast8_t)((bit / NARCH_DATA_WIDTH) + 1u);
	pos = bit % NARCH_DATA_WIDTH;
	array[group] |= 0x1u << pos;
	array[0] |= 0x1u << (group - 1u);
}

void nbitarray_x_clear(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = bit / NARCH_DATA_WIDTH;
	pos = bit % NARCH_DATA_WIDTH;

	array[group + 1u] &= ~(0x1u << pos);

	if (array[group + 1u] == 0u) {
        array[0] &= ~(0x1u << group);
	}
}

uint_fast8_t nbitarray_x_msbs(const nbitarray_x * array)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = narch_log2(array[0]);
	pos = narch_log2(array[group + 1u]);

	return (uint_fast8_t)(group * (uint_fast8_t)NARCH_DATA_WIDTH + pos);
}

void p_nlogger_x_print(struct nlogger_instance * instance, uint8_t level,
    const char * msg, ...)
{
    if (instance->level >= level) {
        va_list args;
        va_start(args, msg);
        vprintf(msg, args);
        va_end(args);
    }
}

void p_nlogger_x_set_level(struct nlogger_instance * instance, uint8_t level)
{
    instance->level = level;
}

void np_lqueue_base_init(struct np_lqueue_base * qb, uint8_t elements)
{
    qb->head = 0u;
    qb->tail = 0u;
    qb->empty = elements;
    qb->mask = (uint_fast8_t)(elements - 1u);
}

uint32_t np_lqueue_base_put_fifo(struct np_lqueue_base * qb)
{
    qb->tail--;
    qb->tail &= qb->mask;
    qb->empty--;

    return (qb->tail);
}

uint32_t np_lqueue_base_put_lifo(struct np_lqueue_base * qb)
{
    uint32_t retval;

    retval = qb->head++;
    qb->head &= qb->mask;
    qb->empty--;

    return (retval);
}

uint32_t np_lqueue_base_get(struct np_lqueue_base * qb)
{
    uint32_t retval;

    retval = qb->tail++;
    qb->tail &= qb->mask;
    qb->empty++;

    return (retval);
}

uint32_t np_lqueue_base_head(const struct np_lqueue_base * qb)
{
    uint32_t real_head;

    real_head = qb->head;
    real_head--;
    real_head &= qb->mask;

    return (real_head);
}

uint32_t np_lqueue_base_tail(const struct np_lqueue_base * qb)
{
    return (qb->tail);
}

static void dispatch(struct ntask * task)
{
    task->fn(task->arg);
}

#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)

#define queue_insert(queue, prio) \
    nbitarray_s_set(&(queue)->bitarray, (prio))

#define queue_remove(queue, prio) \
    nbitarray_s_clear(&(queue)->bitarray, (prio))

#define queue_get_highest(queue) \
	nbitarray_s_msbs(&(queue)->bitarray)

#else

#define queue_insert(queue, prio) \
    nbitarray_x_set(&(queue)->bitarray[0], (prio))

#define queue_remove(queue, prio) \
    nbitarray_x_clear(&(queue)->bitarray[0], (prio));

#define queue_get_highest(queue) \
	nbitarray_x_msbs(&(queue)->bitarray[0])

#endif

#define task_from_epa_id(epa_id) \
    (&g_task_schedule.mempool[epa_id].task)

static void task_init(ntask_fn * fn, void * arg, uint_fast8_t prio)
{
    struct ntask * task = task_from_epa_id(prio);
    
    task->fn = fn;
    task->arg = arg;
    task->state = NTASK_DORMANT;
    memset(&task->tls, 0, sizeof(task->tls));
}

static void task_terminate(ntask_id task_id)
{
    task_from_epa_id(task_id)->task.state = NTASK_UNINITIALIZED;
}

/*
 * 1. Insert the task to ready queue.
 * 2. Update the task state to NTASK_READY.
 */
static void task_start(ntask_id task_id)
{
    queue_insert(&g_task_schedule.ready, task_id);                      /* 1 */
    task_from_epa_id(task_id)->state = NTASK_READY;                     /* 2 */
}

/*
 * 1. If a task is in ready queue then just remove it from the queue.
 * 2. If a task is blocked (waiting on something) it will be invoked with
 *    current state set to NTASK_CANCELED so blocking code can distinguish this
 *    use case and unblock the task in order to terminate itself.
 * 3. If a task is already cancelled then just do nothing.
 * 4. The task state is updated to NTASK_DORMANT.
 */
static void task_stop(ntask_id task_id)
{
    struct ntask * task;
    
    NREQUIRE(task_id < NCONFIG_TASK_INSTANCES);
    
    task = task_from_epa_id(task_id);
    
	NREQUIRE(NSIGNATURE_OF(task) == NSIGNATURE_THREAD);
	NREQUIRE(task->state != NTASK_UNINITIALIZED);
	NREQUIRE(task->state != NTASK_DORMANT);

    switch (task->state) {
        case NTASK_READY: {
            queue_remove(&g_task_schedule.ready, task_id);              /* 1 */
            break;
        }
        case NTASK_BLOCKED: {
            task->state = NTASK_CANCELLED;                              /* 2 */
            dispatch(task);
            break;
        }
        default:
            return;                                                     /* 3 */
    }
    task->state = NTASK_DORMANT;                                        /* 4 */
}

/*
 * 1. Loop while the exit flag is not set (in case exitable scheduler is used)
 *    or loop forever.
 * 2. Get the highest priority level.
 * 3. Fetch the new task and make it as current.
 * 4. Execute the task function.
 */
void ntask_schedule(void)
{
#if (NCONFIG_EXITABLE_SCHEDULER == 1)
    while (!should_exit) {                                              /* 1 */
#else
    while (true) {                                                      /* 1 */
#endif
        struct schedule * ctx = &g_task_schedule;
        ntask_id task_id;

        task_id = queue_get_highest(&ctx->ready);                       /* 2 */
        ctx->current = task_id;                                         /* 3 */
        dispatch(&ctx->mempool[task_id]);                               /* 4 */
    }
}
    
enum nerror_id ntask_current(void)
{
    return g_task_schedule.mempool[g_task_schedule.current].tls.error;
}

enum ntask_state ntask_state(ntask_id task_id)
{
    NREQUIRE(task_id < NCONFIG_TASK_INSTANCES);
	NREQUIRE(NSIGNATURE_OF(&g_task_schedule.mempool[task_id]) == NSIGNATURE_THREAD);

	return g_task_schedule.mempool[task_id].state;
}

void ntask_ready(ntask_id task_id)
{
                                               /* Insert task to ready queue */
    queue_insert(&g_task_schedule.ready, task_id);
                                                        /* Update task state */
    g_task_schedule.mempool[task_id].state = NTASK_READY;
}

void ntask_block(ntask_id task_id)
{
    queue_remove(&g_task_schedule.ready, task_id);
    
    g_task_schedule.mempool[task_id].state = NTASK_BLOCKED;
}

void np_epa_init(void * ws, nepa_state * init_state, uint_fast8_t prio)
{
    
}