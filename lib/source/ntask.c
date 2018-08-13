
#include "bits/nbits.h"
#include "bits/nbits_bitarray.h"
#include "error/nerror.h"
#include "queue/nqueue_pqueue.h"
#include "task/ntask_fiber.h"
#include "task/ntask.h"

struct task_ready_queue
{
    struct nbitarray prio_group;
    struct npqueue group_lists[NBITARRAY_BITS];
};

static struct task_ready_queue g_task_ready_queue;

struct np_thread_dispatch ng_thread_dispatch;

void ntask_init(struct ntask * task, task_fn * fn, void * arg, 
        uint_fast8_t prio)
{
    static bool is_initialized = false;

    if (is_initialized == false) {
        is_initialized = true;
        nbitarray_init(&g_task_ready_queue.prio_group);

        for (uint32_t i; i < NBITARRAY_BITS; i++) {
            npqueue_init(&g_task_ready_queue.group_lists[i]);
        }
    }

    if (prio >= NBITS_ARRAY_SIZE(g_task_ready_queue.group_lists)) {
        nerror = -EOBJ_INVALID;
        return;
    }
    nfiber_init(&task->fiber);
    npqueue_node_init(&task->pnode, prio);
    task->fn = fn;
    task->arg = arg;
    task->state = NFIBER_TERMINATED;
}

void ntask_ready(struct ntask * task)
{
    uint_fast8_t prio;

    prio = npqueue_node_priority(&task->pnode);
    nbitarray_set(&g_task_ready_queue.prio_group, prio);
    npqueue_insert(&g_task_ready_queue.group_lists[prio], &task->pnode);
    task->state = NTASK_READY;
}

struct ntask * ntask_block(struct ntask * task)
{
    uint_fast8_t prio;

    prio = npqueue_node_priority(&task->pnode);
    npqueue_remove(&task->pnode);

    if (npqueue_is_empty(&g_task_ready_queue.group_lists[prio])) {
        nbitarray_clear(&g_task_ready_queue.prio_group, prio);
    }
    task->state = NTASK_BLOCKED;

    return (task);
}
