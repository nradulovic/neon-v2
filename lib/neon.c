/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @defgroup   neon_impl Neon implementation
 *  @brief      Neon implementation
 *  @{ *//*==================================================================*/

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "neon.h"

/** @} *//*==================================================================*/
/** @defgroup   nepa_impl Event Processing Agent (EPA) implementation
 *  @brief      Event Processing Agent (EPA) implementation
 *  @{ *//*==================================================================*/

#define epa_from_prio(ctx, a_prio)      (&(ctx)->mempool[(a_prio)])

#define prio_from_epa(a_epa)            ((a_epa)->task.prio)

#if (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE)

#define prio_queue_insert(a_queue, a_prio)                                  \
        nbitarray_s_set(&(a_queue)->bitarray, (a_prio))

#define prio_queue_remove(a_queue, a_prio)                                  \
        nbitarray_s_clear(&(a_queue)->bitarray, (a_prio))

#define prio_queue_get_highest(a_queue)                                     \
        nbitarray_s_msbs(&(a_queue)->bitarray)

#define prio_queue_is_set(a_queue, a_prio)                                  \
        nbitarray_s_is_set(&(a_queue)->bitarray, (a_prio))

#else /* (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE) */

#define prio_queue_insert(a_queue, a_prio)                                  \
        nbitarray_x_set(&(a_queue)->bitarray[0], (a_prio))

#define prio_queue_remove(a_queue, a_prio)                                  \
        nbitarray_x_clear(&(a_queue)->bitarray[0], (a_prio))

#define prio_queue_get_highest(a_queue)                                     \
        nbitarray_x_msbs(&(a_queue)->bitarray[0])

#define prio_queue_is_set(a_queue, a_prio)                                  \
        nbitarray_x_is_set(&(a_queue)->bitarray[0], (a_prio))
#endif /* (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE) */

static void task_init(struct ntask * task, uint_fast8_t prio)
{
    task->prio = prio;
}

static void equeue_init(struct nequeue * equeue)
{
    NREQUIRE((equeue->np_lq_storage != NULL) && (equeue->super.empty != 0u));
    NREQUIRE((equeue->super.head = 0u) && (equeue->super.tail == 1u));
    NPLATFORM_UNUSED_ARG(equeue);
}

nerror nepa_send_signal(struct nepa * epa, uint_fast16_t signal)
{
    return nepa_send_event(epa, &g_events[signal]);
}

nerror nepa_send_event(struct nepa * epa, const struct nevent * event)
{
    struct nos_critical local;
    int_fast8_t idx;
    nerror error;

    NREQUIRE(NSIGNATURE_OF(epa) == NSIGNATURE_EPA);

    event_ref_up(event);
    NOS_CRITICAL_LOCK(&local);
    idx = NLQUEUE_IDX_FIFO(&epa->equeue);

    if (idx >= 0) {
        NLQUEUE_IDX_REFERENCE(&epa->equeue, idx) = event;
        //prio_queue_insert(&epa->scheduler->ready, prio_from_epa(epa));
        NOS_CRITICAL_UNLOCK(&local);
        error = EOK;
    } else {
        NOS_CRITICAL_UNLOCK(&local);
        /* Undo the event_ref_up step from above.
         */
        event_ref_down(event);
        error = -EOBJ_INVALID;
    }
    
    return error;
}

/** @} *//*==================================================================*/
/** @defgroup   nscheduler_impl Scheduler implementation
 *  @brief      Scheduler implementation
 *  @{ *//*==================================================================*/

static void schedule_initialize_epas(
        struct nscheduler * schedule, 
        const struct nepa * const * epa_registry)
{
   
}

bool nscheduler_is_started(struct nscheduler * scheduler)
{
    return !!scheduler->current;
}

void nscheduler_task_init(
        struct nscheduler * scheduler, 
        struct nscheduler_task * task,
        task_fn * fn,
        void * arg,
        uint8_t prio)
{
}

void nscheduler_task_ready(struct nscheduler_task * task)
{

}

void nscheduler_task_block(struct nscheduler_task * task)
{

}

/*
 * 1. If no ready task is set then set the default idle task.
 */
NPLATFORM_NORETURN(void nscheduler_start(
        struct nscheduler * scheduler, 
        const struct nepa * const * epa_registry))
{
    schedule_initialize_epas(scheduler, epa_registry);

    while (true) {
     
    }
}

/** @} *//*==================================================================*/
/** @defgroup   nsys System module
 *  @brief      System module
 *  @{ *//*==================================================================*/

/** @brief      Idle EPA Event queue
 */
static struct epa_queue_idle nevent_queue(2) g_epa_queue_idle;

static nsm_action idle_state_init(struct nsm *, const struct nevent *);

static nsm_action idle_state_init(struct nsm * sm, const struct nevent * event)
{
    NPLATFORM_UNUSED_ARG(sm);
    NPLATFORM_UNUSED_ARG(event);

    return nsm_event_ignored();
}

const char * const nsys_build_date = NPLATFORM_DATE;
const char * const nsys_build_time = NPLATFORM_TIME;
const char * const nsys_platform_id = NPLATFORM_ID;
const char * const nsys_platform_version = NPLATFORM_VERSION;

const struct nepa nsys_epa_idle = NEPA_INITIALIZER(
            &g_epa_queue_idle, 
            NEPA_FSM_TYPE, 
            idle_state_init, 
            NULL);

void nsys_init(void)
{
    nboard_init();
    nstdio_flush(&nstdio_buff);
}

/** @} */
/** @} */
