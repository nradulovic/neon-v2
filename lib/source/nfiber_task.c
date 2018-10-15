
#include "fiber/nfiber_task.h"

void nfiber_task_create(struct nfiber_task ** fiber, nfiber_fn * fn, void * arg,
    uint_fast8_t prio)
{
}

void nfiber_task_delete(struct nfiber_task * fiber)
{
}

void np_fiber_task_dispatch(struct ntask * task, void * arg)
{
    struct nfiber_task * fiber_task;

    fiber_task = NPLATFORM_CONTAINER_OF(task, struct nfiber_task, task);

    switch (fiber_task->fiber_fn(&fiber_task->fiber, arg)) {
        case NFIBER_YIELDED:
	    case NFIBER_BLOCKED:
            break;
       	case NFIBER_TERMINATED:
       		ntask_terminate(task);
            break;
    }
}

