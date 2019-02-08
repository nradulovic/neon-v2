
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

#if (NCONFIG_TASK_INSTANCES > NBITARRAY_MAX_SIZE)
# error "The limit of maximum task instances has been exceeded!
#endif

#if (NCONFIG_TASK_INSTANCES > NTASK_PRIO_MAX)
# error "The limit of maximum task priorities has been exceeded!"
#endif

static struct ntask task_mempool_storage[NCONFIG_TASK_INSTANCES];
static struct nmem_pool task_mempool;
#if (NCONFIG_EXITABLE_SCHEDULER == 1)
static bool should_exit = false;
#endif

static struct ntask * find_task_with_prio(uint_fast8_t prio)
{
    struct ntask * task;
    size_t tasks;

    tasks = nmem_pool_instances(&task_mempool);

    for (size_t i = 0u; i < tasks; i++) {
        task = nmem_pool_by_idx(&task_mempool, i);

        if (task->prio == prio) {
            return task;
        }
    }
    return NULL;
}

static void sort_tasks(struct ntask_schedule * ctx)
{
    uint32_t i;
    uint32_t abs_prio;

    abs_prio = 0u;

    for (int16_t rel_prio = NTASK_PRIO_MIN; 
         rel_prio <= NTASK_PRIO_MAX; 
         rel_prio++) {
        struct ntask * task;

        task = find_task_with_prio(rel_prio);

        if (task) {
            ctx->sentinel[abs_prio] = task;
            abs_prio++;
        }
    }
}

static void exchange_tasks_prio(struct ntask_schedule * ctx)
{
    size_t tasks;

    tasks = nmem_pool_instances(&task_mempool);

    for (int16_t abs_prio = 0u; abs_prio < tasks; abs_prio++) {
        ctx->sentinel[abs_prio]->prio = abs_prio;
    }
}

static struct ntask * task_from_prio(struct ntask_schedule * ctx, 
        uint_fast8_t prio)
{
    return ctx->sentinel[prio];
}

static void dispatch(struct ntask * task)
{
    task->fn(task->arg);
}

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
    if (ctx->current) {
        return NULL;
    }
    if (find_task_with_prio(prio)) {
        return NULL;
    }
    task = nmem_pool_alloc(&task_mempool);
    task->prio = prio;
    task->fn = fn;
    task->arg = arg;
    task->state = NTASK_DORMANT;

    return task;
}

void ntask_delete(struct ntask * task)
{
    task->state = NTASK_UNINITIALIZED;
}


void ntask_start(struct ntask * task)
{
    struct ntask_schedule * ctx = &g_task_schedule;

    /* Insert task to ready queue */
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
    nbitarray_s_set(&ctx->ready.bitarray, task->prio);
#else
    nbitarray_x_set(&ctx->ready.bitarray[0], task->prio);
#endif

    /* Update task state */
    task->state = NTASK_READY;
}

void ntask_stop(struct ntask * task)
{
    switch (task->state) {
        case NTASK_UNINITIALIZED: {
            /* error */
            return;
        }
        case NTASK_DORMANT: {
            /* error */
            return;
        }
        case NTASK_READY: {
            struct ntask_schedule * ctx = &g_task_schedule;

            /* Remove task from ready queue */
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
            nbitarray_s_clear(&ctx->ready.bitarray, prio);
#else
            nbitarray_x_clear(&ctx->ready.bitarray[0], prio);
#endif
            break;
        }
        case NTASK_CANCELLED: {
            /* It can happen, no error, just exit. */
            return;
        }
        case NTASK_BLOCKED: {
            task->state = NTASK_CANCELLED;
            /* Give the task a chance to cancel itself. */
            dispatch(task);
            break;
        }
    }

    /* Update task state */
    task->state = NTASK_DORMANT;
}

void ntask_schedule(void)
{
    struct ntask_schedule * ctx = &g_task_schedule;

    /* Calculate relative priority and sort the tasks */
    sort_tasks(ctx);
    exchange_tasks_prio(ctx);

#if (NCONFIG_EXITABLE_SCHEDULER == 1)
                                    /* While there are ready tasks in system */
    while (!should_exit) {
#else
    while (true) {
#endif
        uint_fast8_t prio;
                                                    /* Get the highest level */
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
        prio = nbitarray_s_msbs(&ctx->queue.bitarray);
#else
        prio = nbitarray_x_msbs(&ctx->queue.bitarray[0]);
#endif
                                                       /* Fetch the new task */
        ctx->current = task_from_prio(prio);
                                                       /* Execute the thread */
        dispatch(ctx->current);
    }
}

void ntask_ready(struct ntask_queue * queue)
{
    struct ntask_schedule * ctx = &g_task_schedule;
    uint_fast8_t prio;

    /* Find the most high priority task in the wait queue */
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
    prio = nbitarray_s_msbs(&queue->bitarray);
#else
    prio = nbitarray_x_msbs(&queue->bitarray[0]);
#endif

    /* Remove task from wait queue */
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
    nbitarray_s_clear(&queue->bitarray, prio);
#else
    nbitarray_x_clear(&queue->bitarray[0], prio);
#endif

    /* Insert task to ready queue */
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
    nbitarray_s_set(&ctx->ready.bitarray, prio);
#else
    nbitarray_x_set(&ctx->ready.bitarray[0], prio);
#endif

    /* Update task state */
    task_from_prio(prio)->state = NTASK_READY;
}

void ntask_block(struct ntask_wait_queue * queue)
{
    struct ntask_schedule * ctx = &g_task_schedule;
    uint_fast8_t prio = ctx->current->prio;
    
    /* Remove task from ready queue */
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
    nbitarray_s_clear(&ctx->ready.bitarray, prio);
#else
    nbitarray_x_clear(&ctx->ready.bitarray[0], prio);
#endif

    /* Insert task to wait queue */
#if (NCONFIG_TASK_INSTANCES <= NBITARRAY_S_MAX_SIZE)
    nbitarray_x_set(&queue->bitarray[0], prio);
#else
    nbitarray_s_set(&queue->bitarray[0], prio);
#endif
    /* Update task state */
    ctx->current->state = NTASK_BLOCKED;
}

