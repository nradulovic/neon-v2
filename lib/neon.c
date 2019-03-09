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
    ntask_fn * fn;
    void * arg;
    enum ntask_state state;
    struct ntask_local_storage
    {
        enum nerror_id error;
    } tls;
    NSIGNATURE_DECLARE
};


/** @brief		Scheduler context structure
 */
struct ntask_schedule
{
	uint_fast8_t current_prio;     /**< Speed optimization, current thread priority. */
    struct ntask mempool[NCONFIG_TASK_INSTANCES];     /**< Thread instances. */
    struct ntask_queue ready;		/**< Ready queue */
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
static struct ntask_schedule g_task_schedule;

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

struct nlist_dll * nlist_dll_init(struct nlist_dll * node)
{
    node->next = node;
    node->prev = node;

    return (node);
}

struct nlist_dll * nlist_dll_add_after(struct nlist_dll * current,
        struct nlist_dll * node)
{
    node->next          = current;
    node->prev          = current->prev;
    current->prev->next = node;
    current->prev       = node;

    return (node);
}

struct nlist_dll * nlist_dll_add_before(struct nlist_dll * current,
        struct nlist_dll * node)
{
    node->prev          = current;
    node->next          = current->next;
    current->next->prev = node;
    current->next       = node;

    return (node);
}

void nlist_dll_remove(struct nlist_dll * node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

struct nlist_sll * nlist_sll_init(struct nlist_sll * node)
{
    node->next = node;

    return (node);
}

/*
 * NOTE:
 * This function is not inlined since doing so would generate bigger executable
 * by around 200bytes (gcc-arm-none-eabi, 4.9.3, all optimizations) per each
 * library user.
 */
struct nlist_sll * nlist_sll_prev(struct nlist_sll * const node)
{
    struct nlist_sll * tmp = node;

    while (tmp->next != node) {
        tmp = tmp->next;
    }
    return (tmp);
}

void nlist_sll_add_after(struct nlist_sll * current, struct nlist_sll * node)
{
    struct nlist_sll * prev = nlist_sll_prev(current);

    node->next = prev->next;
    prev->next = node;
}

struct nlist_sll * nlist_sll_add_before(struct nlist_sll * current,
        struct nlist_sll * node)
{
    node->next = current->next;
    current->next = node;

    return (node);
}

void nlist_sll_remove(struct nlist_sll * node)
{
    struct nlist_sll * prev = nlist_sll_prev(node);

    nlist_sll_remove_from(prev, node);
}

void nlist_sll_remove_from(struct nlist_sll * prev, struct nlist_sll * node)
{
    prev->next = node->next;
    node->next = node;
}

bool nlist_sll_is_empty(const struct nlist_sll * node)
{
    return (!!(node->next == node));
}

void npqueue_sentinel_shift(struct npqueue_sentinel * sentinel)
{
    struct npqueue * next = npqueue_next(sentinel);

    nlist_dll_remove(&sentinel->list);
    nlist_dll_add_before(&next->list, &sentinel->list);
}

struct npqueue * npqueue_init(struct npqueue * node, uint_fast8_t priority)
{
    nlist_dll_init(&node->list);
    npqueue_priority_set(node, priority);

    return (node);
}

void npqueue_term(struct npqueue * node)
{
    npqueue_priority_set(node, 0);
    nlist_dll_init(&node->list);
}

void npqueue_insert_sort(struct npqueue_sentinel * sentinel,
        struct npqueue * node)
{
    struct nlist_dll * current_list;

    for (NLIST_DLL_EACH(current_list, &sentinel->list)) {
        struct npqueue * current = npqueue_from_list(current_list);

        if (current->priority < node->priority) {
            break;
        }
    }
    nlist_dll_add_after(current_list, &node->list);
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

/*===========================================================================*/
/*
 * Fiber task implementation
 */
/*===========================================================================*/

struct nfiber_task * nfiber_task_create(struct nfiber_task * fiber, 
        nfiber_fn * fn, 
        void * arg,
        uint_fast8_t prio)
{
}

void nfiber_task_delete(struct nfiber_task * fiber)
{
}

static void np_fiber_task_dispatch(struct ntask * task, void * arg)
{
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

static inline 
void dispatch(struct ntask * task)
{
    task->fn(task->arg);
}

#define task_from_prio(ctx, prio)		(&(ctx)->mempool[prio])

#define prio_from_task(ctx, task)       ((task) - &(ctx)->mempool[0])

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

struct ntask * ntask_create(ntask_fn * fn, void * arg, uint_fast8_t prio)
{
    struct ntask_schedule * ctx = &g_task_schedule;
    struct ntask * task;

    NREQUIRE(fn != NULL);
    NREQUIRE(prio < NCONFIG_TASK_INSTANCES);

    task = task_from_prio(ctx, prio);

    NREQUIRE(NSIGNATURE_OF(task) != NSIGNATURE_THREAD);
    NOBLIGATION(NSIGNATURE_IS(task, NSIGNATURE_THREAD));

    task->fn = fn;
    task->arg = arg;
    task->state = NTASK_DORMANT;

    return task;
}

void ntask_delete(struct ntask * task)
{
	NREQUIRE(NSIGNATURE_OF(task) == NSIGNATURE_THREAD);
	NREQUIRE(task->state == NTASK_DORMANT);
    task->state = NTASK_UNINITIALIZED;
    NOBLIGATION(NSIGNATURE_IS(task, ~NSIGNATURE_THREAD));
}


void ntask_start(struct ntask * task)
{
    struct ntask_schedule * ctx = &g_task_schedule;

    NREQUIRE(NSIGNATURE_OF(task) == NSIGNATURE_THREAD);
    NREQUIRE(task->state == NTASK_DORMANT);

                                               /* Insert task to ready queue */
    queue_insert(&ctx->ready, prio_from_task(ctx, task));
                                                        /* Update task state */
    task->state = NTASK_READY;
}

/*
 * 1. If a task is in ready queue then just remove it from the queue.
 * 2. If a task is blocked (waiting on something) it will be invoked with
 *    current state set to NTASK_CANCELED so blocking code can distinguish this
 *    use case and unblock the task in order to terminate itself.
 * 3. If a task is already cancelled then just do nothing.
 * 4. The task state is updated to NTASK_DORMANT.
 */
void ntask_stop(struct ntask * task)
{
	NREQUIRE(NSIGNATURE_OF(task) == NSIGNATURE_THREAD);
	NREQUIRE(task->state != NTASK_UNINITIALIZED);
	NREQUIRE(task->state != NTASK_DORMANT);

    switch (task->state) {
        case NTASK_READY: {
            struct ntask_schedule * ctx = &g_task_schedule;
                  /* Remove from ready queue only if scheduler has been already
                   * started.
                   */
            queue_remove(&ctx->ready, prio_from_task(ctx, task));       /* 1 */
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

static void idle_task(void * arg)
{
    /* */
}

/*
 */
void ntask_schedule(void)
{
    struct ntask_schedule * ctx = &g_task_schedule;

    ntask_start(ntask_create(idle_task, NULL, 0));
    
#if (NCONFIG_EXITABLE_SCHEDULER == 1)
                                    /* While there are ready tasks in system */
    while (!should_exit) {
#else
    while (true) {
#endif
        uint_fast8_t prio;
                                                    /* Get the highest level */
        prio = queue_get_highest(&ctx->ready);
                                                       /* Fetch the new task */
        ctx->current_prio = prio;
                                                       /* Execute the thread */
        dispatch(task_from_prio(ctx, prio));
    }
    
#if (NCONFIG_EXITABLE_SCHEDULER == 1)
    for (uint_fast8_t prio = 0u; prio < NCONFIG_TASK_INSTANCES; prio) {
        struct ntask * task;
        
        task = task_from_prio(ctx, prio);
        
        ntask_stop(task);
    }
    
    for (uint_fast8_t prio = 0u; prio < NCONFIG_TASK_INSTANCES; prio) {
        struct ntask * task;
        
        task = task_from_prio(ctx, prio);
        
        ntask_delete(task);
    }
#endif
}

enum ntask_state ntask_state(const struct ntask * task)
{
	NREQUIRE(NSIGNATURE_OF(task) == NSIGNATURE_THREAD);

	return task->state;
}

void ntask_queue_ready(struct ntask_queue * queue)
{
    struct ntask_schedule * ctx = &g_task_schedule;
    uint_fast8_t prio;

    				   /* Find the most high priority task in the wait queue */
    prio = queue_get_highest(queue);
    										  /* Remove task from wait queue */
    queue_remove(queue, prio);
                                               /* Insert task to ready queue */
    queue_insert(&ctx->ready, prio);
                                                        /* Update task state */
    task_from_prio(ctx, prio)->state = NTASK_READY;
}

void ntask_queue_block(struct ntask_queue * queue)
{
    struct ntask_schedule * ctx = &g_task_schedule;
    uint_fast8_t prio = ctx->current_prio;

                                             /* Remove task from ready queue */
    queue_remove(&ctx->ready, prio);
                                                /* Insert task to wait queue */
    queue_insert(queue, prio);
                                                        /* Update task state */
    task_from_prio(ctx, prio)->state = NTASK_BLOCKED;
}
