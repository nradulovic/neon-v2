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
	uint_fast8_t prio;
    ntask_fn * fn;
    void * arg;
    enum ntask_state state;
    struct ntask_local_storage
    {
        uint32_t error;
    } tls;
    NSIGNATURE_DECLARE
};


/** @brief		Scheduler context structure
 */
struct ntask_schedule
{
	struct ntask * current;         /**< Speed optimization, current thread. */
    struct ntask * sentinel[NCONFIG_TASK_INSTANCES]; /**< Sentinels to threads. */
    struct ntask_queue ready;		/**< Ready queue */
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

static struct ntask g_task_mempool[NCONFIG_TASK_INSTANCES];

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

	group = (uint_fast8_t)((bit / 32) + 1u);
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

void nfiber_task_create(struct nfiber_task ** fiber, nfiber_fn * fn, void * arg,
    uint_fast8_t prio)
{
}

void nfiber_task_delete(struct nfiber_task * fiber)
{
}

static void np_fiber_task_dispatch(struct ntask * task, void * arg)
{
}

static struct ntask * alloc_task(struct ntask * mempool)
{
	struct ntask * task;

	task = NULL;

	for (uint16_t i = 0u; i < NCONFIG_TASK_INSTANCES; i++) {
		task = &mempool[i];

		if (task->state == NTASK_UNINITIALIZED) {
			break;
		}
	}

	return task;
}

static struct ntask * find_task_with_prio(struct ntask * mempool,
		uint_fast8_t prio)
{
    for (uint16_t i = 0u; i < NCONFIG_TASK_INSTANCES; i++) {
    	struct ntask * task;

        task = &mempool[i];

        if (task->state == NTASK_UNINITIALIZED) {
        	break;
        }
        if (task->prio == prio) {
            return task;
        }
    }
    return NULL;
}

static void register_tasks(struct ntask_schedule * ctx, struct ntask * mempool)
{
    uint_fast8_t abs_prio;

    abs_prio = 0u;

    for (uint16_t prio = NTASK_PRIO_MIN; prio <= NTASK_PRIO_MAX; prio++) {
        struct ntask * task;

        task = find_task_with_prio(mempool, (uint_fast8_t)prio);

        if (task) {
            ctx->sentinel[abs_prio++] = task;
        }
    }
}

static void prioritize_tasks(struct ntask_schedule * ctx)
{
    for (uint16_t i = 0u; i < NCONFIG_TASK_INSTANCES; i++) {
    	struct ntask * task;

    	task = ctx->sentinel[i];

    	if (task == NULL) {
			break;
		}
        task->prio = (uint_fast8_t)i;
    }
}

static void dispatch(struct ntask * task)
{
    task->fn(task->arg);
}

#define task_from_prio(ctx, prio)		(ctx)->sentinel[prio]

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
    struct ntask * task;

    NREQUIRE(fn != NULL);
    NREQUIRE(g_task_schedule.current == NULL);
    NREQUIRE(find_task_with_prio(&g_task_mempool[0], prio) == NULL);

    task = alloc_task(&g_task_mempool[0]);

	NENSURE(task != NULL);
    NOBLIGATION(NSIGNATURE_IS(task, NSIGNATURE_THREAD));

    task->prio = prio;
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

        /* Insert to ready queue only if scheduler has been already started. */
    if (ctx->current) {
                                               /* Insert task to ready queue */
    	queue_insert(&ctx->ready, task->prio);
    }
                                                        /* Update task state */
    task->state = NTASK_READY;
}

/*
 * 1. If a task is in ready queue then just remove it from the queue.
 * 2. If a task is blocked (waiting on something) it will be invoked with
 *    current state set to NTASK_CANCELED so blocking code can distinguish this
 *    use case and unblock the task in order to terminate itself.
 * 3. If a task is already canceled then just do nothing.
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
            if (ctx->current) {                                         /* 1 */
            	queue_remove(&ctx->ready, task->prio);
            }
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
 */
void ntask_schedule(void)
{
    struct ntask_schedule * ctx = &g_task_schedule;

                           /* Calculate relative priority and sort the tasks */
    register_tasks(ctx, &g_task_mempool[0]);
    prioritize_tasks(ctx);

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
        ctx->current = task_from_prio(ctx, prio);
                                                       /* Execute the thread */
        dispatch(ctx->current);
    }
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
    uint_fast8_t prio = ctx->current->prio;

                                             /* Remove task from ready queue */
    queue_remove(&ctx->ready, prio);
                                                /* Insert task to wait queue */
    queue_insert(queue, prio);
                                                        /* Update task state */
    ctx->current->state = NTASK_BLOCKED;
}
