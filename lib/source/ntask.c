
#include "port/nport_arch.h"
#include "port/nport_platform.h"
#include "bits/nbits.h"
#include "error/nerror.h"
#include "task/ntask.h"
#include "mem/nmem_pool.h"

struct ntask
{
	uint_fast8_t prio;
    task_fn * fn;
    void * arg;
    enum ntask_state state;
    struct ntask_local_storage
    {
        uint32_t error;
    } tls;
};


struct ntask_schedule g_task_schedule;

#define NMEM_DEFINE(array) \
	.free = (struct nlist_sll *)array,

static struct ntask task_mempool_storage[NCONFIG_TASK_INSTANCES];
static struct nmem_pool task_mempool;

struct ntask * ntask_create(task_fn * fn, void * arg, uint_fast8_t prio)
{
	struct ntask_schedule * ctx = &g_task_schedule;
    struct ntask * task;

    if (nmem_pool_is_initialized(&task_mempool) == false) {
    	nmem_pool_init(&task_mempool,
    			task_mempool_storage,
    			sizeof(task_mempool_storage),
				sizeof(task_mempool_storage[0]));
    }
    task = nmem_pool_alloc(&task_mempool);

    task->prio = prio;
    task->fn = fn;
    task->arg = arg;
    task->state = NTASK_DORMANT;

    return task;
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
