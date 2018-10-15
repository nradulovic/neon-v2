
#include "port/nport_arch.h"
#include "port/nport_platform.h"
#include "bits/nbits.h"
#include "error/nerror.h"
#include "task/ntask.h"

struct ntask_schedule g_task_schedule;

#if ((NTASK_WAIT_QUEUE_TYPE == NTASK_QUEUE_SQ) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB))
static struct ntask * task_from_node(struct npqueue * node)
{
    return NPLATFORM_CONTAINER_OF(node, struct ntask, node);
}
#endif

void ntask_init(struct ntask * task, task_fn * fn, void * arg, 
        uint_fast8_t prio)
{
    struct ntask_schedule * ctx = &g_task_schedule;
    static bool is_initialized = false;

    if (!is_initialized) {
        is_initialized = true;

#if ((NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB))
        for (uint32_t i = 0u; i < NBITS_ARRAY_SIZE(ctx->queue.sentinel); i++) {
            npqueue_sentinel_init(&ctx->queue.sentinel[i]);
        }
#else

#endif
    }

    /* Adjust priority now according to avaialable priority groups or levels.
     */
#if ((NTASK_WAIT_QUEUE_TYPE == NTASK_QUEUE_SQ) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB))
    npqueue_init(&task->node, prio);
#else
    task->prio = prio;
#endif
    task->fn = fn;
    task->arg = arg;
    task->state = NTASK_DORMANT;
}

void ntask_term(struct ntask * task)
{
    task->state = NTASK_UNINITIALIZED;
}

void ntask_looper(void)
{
    struct ntask_schedule * ctx = &g_task_schedule;
                                    /* While there are ready tasks in system */
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
    while (!nbitarray_x_is_empty(&ctx->queue.bitarray[0])) {
#else
    while (!nbitarray_s_is_empty(&ctx->queue.bitarray[0])) {
#endif
        uint_fast8_t prio;
                                                    /* Get the highest level */
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
        prio = nbitarray_x_msbs(&ctx->queue.bitarray[0]);
#else
        prio = nbitarray_s_msbs(&ctx->queue.bitarray[0]);
#endif
                                                       /* Fetch the new task */
#if ((NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB))
        ctx->current = task_from_node(
                npqueue_sentinel_head(&ctx->queue.sentinel[prio]));
#else
#endif
                                              /* Round-robin for other tasks */
#if (NCONFIG_TASK_SCHED_RR == 1)
        if (ctx->should_shift) {
            ctx->should_shift = false;
            npqueue_sentinel_shift(&ctx->queue.sentinel[prio]);
        }
#endif
                                                       /* Execute the thread */
        ctx->current->fn(ctx->current, ctx->current->arg);
    }
}

void ntask_ready(struct ntask_wait_queue * queue, struct ntask * task)
{
    struct ntask_schedule * ctx = &g_task_schedule;
    uint_fast8_t prio = ntask_priority(task);

    if (prio > ntask_priority(ctx->current)) {
        ctx->switch_pending = true;
    }
    task->state = NTASK_READY;

    /* Remove task from wait queue */
#if (NTASK_WAIT_QUEUE_TYPE == NTASK_QUEUE_SQ)
    (void)queue;
    npqueue_remove(&task->node);
#else
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
    nbitarray_x_clear(&queue->bitarray[0], prio);
#else
    nbitarray_s_clear(&queue->bitarray[0], prio);
#endif
#endif

    /* Insert task to ready queue */
#if (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB)
    npqueue_insert_sort(&ctx->queue.sentinel[prio], &task->node);
#elif (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB)
    npqueue_insert_fifo(&ctx->queue.sentinel[prio], &task->node);
#endif
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
    nbitarray_x_set(&ctx->queue.bitarray[0], prio);
#else
    nbitarray_s_set(&ctx->queue.bitarray[0], prio);
#endif
}

void ntask_block(struct ntask_wait_queue * queue, struct ntask * task)
{
    struct ntask_schedule * ctx = &g_task_schedule;
    uint_fast8_t prio = ntask_priority(task);
    
    ctx->switch_pending = true;
    task->state = NTASK_BLOCKED;

    /* Remove task from ready queue */
#if ((NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_SB) || \
     (NTASK_RDY_QUEUE_TYPE == NTASK_QUEUE_FB)) 
    npqueue_remove(&task->node);
    
    if (npqueue_sentinel_is_empty(&ctx->queue.sentinel[prio])) {
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
        nbitarray_x_clear(&ctx->queue.bitarray[0], prio);
#else
        nbitarray_s_clear(&ctx->queue.bitarray[0], prio);
#endif
    }
#else
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
    nbitarray_x_clear(&ctx->queue.bitarray[0], prio);
#else
    nbitarray_s_clear(&ctx->queue.bitarray[0], prio);
#endif
#endif

    /* Insert task to wait queue */
#if (NTASK_WAIT_QUEUE_TYPE == NTASK_QUEUE_SQ)
    npqueue_insert_sort(&queue->sentinel, &task->node);
#else
#if (NTASK_BITMAP_TYPE == NTASK_BITMAP_X)
    nbitarray_x_set(&queue->bitarray[0], prio);
#else
    nbitarray_s_set(&queue->bitarray[0], prio);
#endif
#endif
}
