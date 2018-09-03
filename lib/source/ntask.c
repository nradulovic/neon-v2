
#include "port/nport_arch.h"
#include "bits/nbits.h"
#include "bits/nbits_bitarray.h"
#include "configs/default_config.h"
#include "queue/nqueue_pqueue.h"
#include "error/nerror.h"
#include "task/ntask_fiber.h"
#include "task/ntask.h"

struct task_ready_queue
{
    struct nbitarray group;
    struct npqueue groups[NCONFIG_TASK_PRIORITIES];
};

static struct task_ready_queue g_task_ready_queue;
static struct ntask g_task_pool[NCONFIG_TASK_INSTANCES];

struct ntask * ng_current_task;

static struct ntask * task_from_node(struct npqueue_node * node)
{
    return NPLATFORM_CONTAINER_OF(node, struct ntask, node);
}

struct ntask * alloc_task(void)
{
    struct ntask * task = &g_task_pool[0];

    for (uint8_t i = 0u; i < NBITS_ARRAY_SIZE(g_task_pool); i++) {
        if (task->state == NTASK_UNINITIALIZED) {
            return task;
        }
        task++;
    }
    return NULL;
}

void ntask_create(
        struct ntask ** task, 
        task_fn * fn, 
        void * arg, 
        uint_fast8_t prio)
{
    struct ntask * l_task;

    l_task = alloc_task();

    if (l_task == NULL) {
        nerror = -EOBJ_INVALID;
        return;
    }
    nfiber_init(&l_task->fiber);
    npqueue_node_init(&l_task->node, prio);
    l_task->fn = fn;
    l_task->arg = arg;
    l_task->state = NFIBER_TERMINATED;
    *task = l_task;
}

void ntask_schedule(void)
{
}

void ntask_dispatch(struct ntask * task)
{
    task->state = nfiber_dispatch(task->fn(task, task->arg)); 
}

void ntask_ready(struct ntask * task)
{
    uint_fast8_t prio = npqueue_node_priority(&task->node);
    
    nbitarray_set(&g_task_ready_queue.group, prio);
    npqueue_insert(&g_task_ready_queue.groups[prio], &task->node);
    task->state = NTASK_READY;
}

void ntask_block(void)
{
    uint_fast8_t prio = npqueue_node_priority(&ng_current_task->node);

    task_from_node(npqueue_remove_first(&g_task_ready_queue.groups[prio]))->state = NTASK_BLOCKED;
    
    if (npqueue_is_empty(&g_task_ready_queue.groups[prio])) {
        nbitarray_clear(&g_task_ready_queue.group, prio);
    }
}
