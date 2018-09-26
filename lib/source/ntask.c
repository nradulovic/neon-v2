
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

