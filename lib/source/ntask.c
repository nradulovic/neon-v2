
#include "port/nport_arch.h"
#include "bits/nbits.h"
#include "bits/nbits_bitarray.h"
#include "configs/default_config.h"
#include "queue/nqueue_pqueue.h"
#include "error/nerror.h"
#include "task/ntask_fiber.h"
#include "task/ntask.h"

static struct task_ready_queue
{
    struct ntask * current;
    struct nbitarray group;
    struct npqueue * groups[NCONFIG_TASK_PRIORITIES];
} g_task_ready_queue;

#if (NCONFIG_TASK_INSTANCES != 0)
static struct ntask g_task_pool[NCONFIG_TASK_INSTANCES];
#endif

static struct ntask * task_from_node(struct npqueue * node)
{
    return NPLATFORM_CONTAINER_OF(node, struct ntask, node);
}

struct ntask * alloc_task(void)
{
#if (NCONFIG_TASK_INSTANCES != 0)
    struct ntask * task = &g_task_pool[0];

    for (uint8_t i = 0u; i < NBITS_ARRAY_SIZE(g_task_pool); i++) {
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
        rq->current = task_from_node(rq->groups[prio]);
                                              /* Round-robin for other tasks */
        rq->groups[prio] = npqueue_next(&rq->current->node);
                                                       /* Execute the thread */
        rq->current->state = nfiber_dispatch(
                rq->current->fn(rq->current, rq->current->arg)); 
    }
}

void ntask_ready(struct ntask * task)
{
    uint_fast8_t prio = npqueue_priority(&task->node);
    struct task_ready_queue * rq = &g_task_ready_queue;

    if (rq->groups[prio] == NULL) {
        rq->groups[prio] = &task->node;
        nbitarray_set(&rq->group, prio);
    } else {
        npqueue_insert_fifo(rq->groups[prio], &task->node);
    }
    task->state = NTASK_READY;
}

void ntask_block(struct ntask * task)
{
    if (npqueue_is_last(&task->node)) {
        uint_fast8_t prio = npqueue_priority(&task->node);
        struct task_ready_queue * rq = &g_task_ready_queue;
        
        rq->groups[prio] = NULL;
        nbitarray_clear(&rq->group, prio);
    } else {
        npqueue_remove(&task->node);
    }
    task->state = NTASK_BLOCKED;
}
