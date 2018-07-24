
#include "task/ntask.h"

void ntask_init(struct ntask * task, task_fn * fn, void * arg, 
        uint_fast8_t prio)
{
    nfiber_init(&task->fiber);
    npqueue_node_init(&task->pnode, prio);
    task->fn = fn;
    task->arg = arg;
    task->state = NFIBER_TERMINATED;
}

void ntask_ready(struct ntask * task)
{
}

struct ntask * ntask_block(struct ntask * task)
{
}
