
#include "port/nport_arch.h"
#include "port/nport_platform.h"
#include "bits/nbits.h"
#include "error/nerror.h"
#include "task/ntask.h"
#include "debug/ndebug.h"

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


struct ntask_schedule g_task_schedule;

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
    struct ntask_schedule * ctx = &g_task_schedule;
    struct ntask * task;

    NREQUIRE(fn != NULL);
    NREQUIRE(ctx->current == NULL);
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

