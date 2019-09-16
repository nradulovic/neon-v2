/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @addtogroup neon
 *  @{
 */
/** @defgroup   nscheduler Scheduler
 *  @brief      Scheduler
 *  @{
 */

#ifndef NEON_SCHEDULER_H_
#define NEON_SCHEDULER_H_

#include <stdbool.h>
#include <stdint.h>

#include "core/nport.h"
#include "core/nconfig.h"
#include "core/nbitarray_s.h"
#include "core/nbitarray_x.h"
#include "core/nlist_dll.h"
#include "core/nepa.h"

#ifdef __cplusplus
extern "C" {
#endif
    
struct nscheduler_task;

typedef void (task_fn)(struct nscheduler_task *, void *);

/** @brief		Scheduler context structure
 */
struct nscheduler
{
    struct nscheduler_task *        current;    /**< Speed optimization,
                                                 *   current thread priority. */
    struct nscheduler_queue
    {
#if (NARCH_DATA_WIDTH < NCONFIG_SCHEDULER_PRIORITIES)
        nbitarray_x                 bitarray
                [NBITARRAY_X_DEF(NCONFIG_SCHEDULER_PRIORITIES)];
        
#else
        nbitarray_s                 bitarray;   /**< Simple bit array is used
                                                 * when small number of task
                                                 * is used. */
#endif
        struct nlist_dll * levels[NCONFIG_SCHEDULER_PRIORITIES];
    }                           ready;          /**< Ready queue */
#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
    volatile bool               should_exit;
#endif
};

struct nscheduler_task
{
    struct nlist_dll queue;
    struct nscheduler * scheduler;
    uint_fast8_t prio;
    task_fn * fn;
    void * arg;
};

#define nscheduler_current(scheduler)  (scheduler)->current

bool nscheduler_is_started(struct nscheduler * scheduler);

void nscheduler_task_init(
        struct nscheduler * scheduler, 
        struct nscheduler_task * task,
        task_fn * fn,
        void * arg,
        uint8_t prio);

void nscheduler_task_ready(struct nscheduler_task * task);

void nscheduler_task_block(struct nscheduler_task * task);

/** @brief      Start executing Event Processing Agents
 *  
 *  This function will execute the list EPA in @a epa_registry. This is just a
 *  registry of EPAs that application wants to execute.
 * 
 *  The behaviour of this function is modified by:
 *  - NCONFIG_SYS_EXITABLE_SCHEDULER
 *              When this argument is set to enabled (1) the scheduler can be
 *              terminated with a call to @ref nscheduler_stop function. In
 *              that case the event processing loop will stop and the function
 *              will return.
 *              When this argument is set to disabled (0) then the scheduler
 *              loop can not be exited, in other words, the function is compiled
 *              as infinite loop.
 * 
 *  @param      epa_registry
 *              A registry of EPAs that application wants to be executed.
 */
#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1) || defined(__DOXYGEN__)
void nscheduler_start(
        struct nscheduler * scheduler,
        const struct nepa * const * epa_registry);
#else
NPLATFORM_NORETURN(void nscheduler_start(
        struct nscheduler * scheduler, 
        const struct nepa * const * epa_registry));
#endif

/** @brief      Stop the execution of scheduler and return to main function.
 *  
 *  This function will create a request to the scheduler to stop the execution.
 *  The scheduler will exit at next iteration of schedule process.
 * 
 *  @note       This function is not available when configuration option
 *              @ref NCONFIG_SYS_EXITABLE_SCHEDULER is disabled (0).
 */
#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1) || defined(__DOXYGEN__)
void nscheduler_stop(struct nscheduler * scheduler);
#endif

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_SCHEDULER_H_ */
