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

#include "nbits.h"

#include "nlist_sll.h"

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

#include "nlist_dll.h"

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

    /* NOTE:
     * Next pointer must point to itself, since it may be checked by
     * nlist_dll_is_empty() function.
     */
    node->next = node;
    /* NOTE:
     * During debugging it is easier to catch errors with NULL pointer.
     */
    node->prev = NULL;
}

#include "nqueue_pqueue.h"

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

#include "nk_arch.h"
#include "nbits.h"
#include "nbits_bitarray.h"
#include "default_config.h"
#include "nqueue_pqueue.h"
#include "nerror.h"
#include "ntask_fiber.h"
#include "ntask.h"

static struct task_ready_queue
{
    struct ntask * current;
    bool should_shift;
    struct nbitarray group;
    struct npqueue_sentinel groups[NCONFIG_TASK_PRIORITIES];
} g_task_ready_queue;

static struct ntask * task_from_node(struct npqueue * node)
{
    return NPLATFORM_CONTAINER_OF(node, struct ntask, node);
}

static struct ntask * alloc_task(void)
{
#if (NCONFIG_TASK_INSTANCES != 0)
    static struct ntask task_pool[NCONFIG_TASK_INSTANCES];
    struct ntask * task = &task_pool[0];

    for (uint8_t i = 0u; i < NBITS_ARRAY_SIZE(task_pool); i++) {
        if (task->state == NTASK_UNINITIALIZED) {
            return task;
        }
        task++;
    }
    return NULL;
#else
    return malloc(sizeof(struct ntask));
#endif
}

static void rq_init(struct task_ready_queue * rq)
{
    nbitarray_init(&rq->group);

    for (uint32_t i = 0u; i < NCONFIG_TASK_PRIORITIES; i++) {
        npqueue_sentinel_init(&rq->groups[i]);
    }
}

static void rq_insert(struct ntask * task, struct task_ready_queue * rq)
{
    uint_fast8_t prio = npqueue_priority(&task->node);

    nbitarray_set(&rq->group, prio);
    npqueue_insert_fifo(&rq->groups[prio], &task->node);
}

static void rq_remove(struct ntask * task, struct task_ready_queue * rq)
{
    uint_fast8_t prio;
    
    npqueue_remove(&task->node);
    
    prio = npqueue_priority(&task->node);
    
    if (npqueue_sentinel_is_empty(&rq->groups[prio])) {
        nbitarray_clear(&rq->group, prio);
    }
}

void ntask_create(
        struct ntask ** task, 
        task_fn * fn, 
        void * arg, 
        uint_fast8_t prio)
{
    static bool is_initialized;
    struct ntask * l_task;

    if (!is_initialized) {
        is_initialized = true;
        rq_init(&g_task_ready_queue);
    }

    l_task = alloc_task();

    if (l_task == NULL) {
        nerror = -EOBJ_INVALID;
        return;
    }
    nfiber_init(&l_task->fiber);
    npqueue_init(&l_task->node, prio);
    l_task->fn = fn;
    l_task->arg = arg;
    l_task->state = NTASK_DORMANT;
    *task = l_task;
}

struct ntask * ntask_current(void)
{
    struct task_ready_queue * rq = &g_task_ready_queue;

    return rq->current;
}

void ntask_schedule(void)
{
    struct task_ready_queue * rq = &g_task_ready_queue;
                                    /* While there are ready tasks in system */
    while (!nbitarray_is_empty(&rq->group)) {
        uint_fast8_t prio;
                                                    /* Get the highest level */
        prio = nbitarray_msbs(&rq->group);
                                                       /* Fetch the new task */
        rq->current = task_from_node(npqueue_sentinel_head(&rq->groups[prio]));
                                              /* Round-robin for other tasks */
        if (rq->should_shift) {
            rq->should_shift = false;
            npqueue_sentinel_shift(&rq->groups[prio]);
        }
                                                       /* Execute the thread */
        rq->current->state = nfiber_dispatch(
                rq->current->fn(rq->current, rq->current->arg)); 

        if (rq->current->state == NTASK_DORMANT || 
            rq->current->state == NTASK_BLOCKED) {
            rq_remove(rq->current, rq);
        }
    }
}

void ntask_ready(struct ntask * task)
{
    rq_insert(task, &g_task_ready_queue);
    task->state = NTASK_READY;
}

