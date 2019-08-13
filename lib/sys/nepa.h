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
/** @defgroup   nepa Event Processing Agent (EPA)
 *  @brief      Event Processing Agent (EPA)
 *  @{
 */

#ifndef NEON_EPA_H_
#define NEON_EPA_H_

#include <stdint.h>

#include "sys/nconfig.h"
#include "sys/ndebug.h"
#include "sys/nlqueue.h"
#include "sys/nsm.h"
#include "sys/nerror.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      The highest EPA priority value.
 *
 *  The EPA with this priority has the highest urgency to be selected and
 *  dispatched by scheduler.
 */
#define NEPA_PRIO_MAX                   255

/** @brief      The lowest EPA priority value
 *  @note       This priority level is reserved by Neon idle task.
 */
#define NEPA_PRIO_MIN                   0

/** @brief      Define a structure of an event queue of fixed size.
 * 
 *  This is a helper macro which is used to ease the process of defining an
 *  event queue. For example, if you want to declare an event queue of a size
 *  @a M you would use the macro in the following way:
 * 
 *  @code
 *  struct my_epa_queue nevent_queue(M);
 *  @endcode
 * 
 *  Then in the code you would create an instance of the structure:
 * 
 *  @code
 *  static struct my_epa_queue g_my_epa_queue_instance;
 *  @endcode
 * 
 *  @param      a_size
 *              Number of event this queue would hold.
 */
#define nevent_queue(a_size)                                                \
        nlqueue_dynamic_storage(const struct nevent *, a_size)

#if (NCONFIG_EPA_USE_HSM == 1) || defined(__DOXYGEN__)
/** @brief      Initialize an Event Processing Agent (EPA)
 *  
 *  Each EPA is described by an event queue, state machine type, initial state
 *  and a workspace storage.
 * 
 *  @param      a_queue
 *              Pointer to an event queue. See @ref nevent_queue on details how
 *              to define and instantiate a queue.
 *  @param      a_type_id
 *              Type of state machine, see @ref nepa_type for details.
 *  @param      a_init_state
 *              Initial state function of the state machine. For more details
 *              about state functions see @ref nstate_fn.
 *  @param      a_ws
 *              State machine workspace. A workspace pointer is just passed to
 *              state machine state functions. It is a void pointer, so any kind
 *              of additional data can be passed to the state functions.
 */
#define NEPA_INITIALIZER(a_queue, a_type_id, a_init_state, a_ws)            \
        {                                                                   \
            .sm =                                                           \
            {                                                               \
                .type =                                                     \
                {                                                           \
                    .id = (a_type_id),                                      \
                },                                                          \
                .state = (a_init_state),                                    \
                .ws = (a_ws),                                               \
            },                                                              \
            .equeue =                                                       \
            {                                                               \
                .super =                                                    \
                {                                                           \
                    .head = 0                                               \
                    .tail = 1,                                              \
                    .empty = NBITS_ARRAY_SIZE(&(a_queue)->np_lq_storage),   \
                    .mask = NBITS_ARRAY_SIZE(&(a_queue)->np_lq_storage) - 1u,     \
                },                                                          \
                .np_lq_storage = &(a_queue)->np_lq_storage[0],              \
            },                                                              \
        }
#else
#define NEPA_INITIALIZER(a_queue, a_type_id, a_init_state, a_ws)            \
        {                                                                   \
            .sm =                                                           \
            {                                                               \
                .state = (a_init_state),                                    \
                .ws = (a_ws),                                               \
            },                                                              \
            .equeue =                                                       \
            {                                                               \
                .super =                                                    \
                {                                                           \
                    .head = 0,                                              \
                    .tail = 1,                                              \
                    .empty = NBITS_ARRAY_SIZE((a_queue)->np_lq_storage),    \
                    .mask = NBITS_ARRAY_SIZE((a_queue)->np_lq_storage) - 1u,     \
                },                                                          \
                .np_lq_storage = &(a_queue)->np_lq_storage[0],              \
            },                                                              \
        }
#endif

struct nscheduler;

/** @brief      Event Processing Agent (EPA)
 */
struct nepa
{
    /** @brief  Scheduler which manages this EPA.
     */
    struct nscheduler *         scheduler;
    
    /** @brief  State machine instance.
     */
    struct nsm                  sm;             
    
    /** @brief  Task management instance.
     */
    struct ntask
    {
        uint_fast8_t                prio;
    }                           task;           
    /** @brief  Event queue.
     */
    struct nequeue nlqueue_dynamic(const struct nevent *)
                                equeue;         
    NSIGNATURE_DECLARE
};

nerror nepa_send_signal(struct nepa * epa, uint_fast16_t signal);

nerror nepa_send_event(struct nepa * epa, const struct nevent * event);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_EPA_H_ */
