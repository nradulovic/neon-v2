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

#include "sys/nport.h"
#include "sys/nconfig.h"
#include "sys/nbitarray_s.h"
#include "sys/nepa.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/** @brief		Scheduler context structure
 */
struct nscheduler
{
    struct nepa *               current;        /**< Speed optimization,
                                                 *   current thread priority. */
    struct nepa_queue
    {
#if (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE)
        nbitarray_s                 bitarray;   /**< Simple bit array is used
                                                 * when small number of task
                                                 * is used. */
#else
        nbitarray_x                 bitarray
                [NBITARRAY_X_DEF(NCONFIG_EPA_INSTANCES)];
#endif
    }                           ready;          /**< Ready queue */
#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
    volatile bool               should_exit;
#endif
    struct nepa                 mempool[NCONFIG_EPA_INSTANCES];
};

struct nscheduler_task
{
    struct nscheduler * scheduler;
    uint_fast8_t prio;
    void (* task_fn)(struct nscheduler_task *, void *);
    void * arg;
};

#define nscheduler_current(scheduler)  (scheduler)->current

bool nscheduler_is_started(struct nscheduler * scheduler);

void nscheduler_task_init(struct nscheduler_task * task);

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
