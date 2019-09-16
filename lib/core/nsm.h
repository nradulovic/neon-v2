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
/** @defgroup   nsm State machine
 *  @brief      State machine
 *  @{
 */

#ifndef NEON_SM_H_
#define NEON_SM_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       Get the state machine workspace pointer
 */
#define nsm_wspace(sm)                  ((sm)->wspace)

/**
 * @brief       State machine action, given event was handled.
 * @return      Actions enumerator @ref NACTION_HANDLED.
 */
#define nsm_event_handled()             (NACTION_HANDLED)

/**
 * @brief       State machine action, given event was ignored.
 * @return      Actions enumerator @ref NACTION_IGNORED.
 */
#define nsm_event_ignored()             (NACTION_IGNORED)

/**
 * @brief       State machine action, state is returning its super state
 * @param       sm
 *              Pointer to the state machine
 * @param       state_ptr
 *              State function pointer to super state
 * @return      Actions enumerator @ref NP_SMP_SUPER_STATE.
 */
#define nsm_super_state(sm, state_ptr)                                      \
        ((sm)->state = (state_ptr), NP_SMP_SUPER_STATE)

/**
 * @brief       State machine action, state machine wants to transit to new
 *              state
 * @param       sm
 *              Pointer to the state machine
 * @param       state_ptr
 *              State function pointer to new state
 * @return      Actions enumerator @ref NP_SMP_TRANSIT_TO.
 */
#define nsm_transit_to(sm, state_ptr)                                       \
        ((sm)->state = (state_ptr), NP_SMP_TRANSIT_TO)

/** @brief      State machine event identifications
 */
enum nsm_event
{
    NSM_SUPER,                              /**<@brief Get the state super 
                                             *         state.
                                             */
    NSM_ENTRY,                              /**<@brief Process state entry.   */
    NSM_EXIT,                               /**<@brief Process state exit.    */
    NSM_INIT,                               /**<@brief Process state init.    */
    NSIGNAL_RETRIGGER,
    NSIGNAL_AFTER,
    NSIGNAL_EVERY,
    NEVENT_NULL,                            /**<@brief NULL event.            */
    
    NEVENT_USER_ID
};

/** @brief      Returned actions enumerator
 *  
 * This enumerator is for internal use only. It defines what actions should 
 * dispatcher execute for the given state machine.
 * 
 * @note        Do not use this enumerator directly, but use the appropriate
 *              naction_*() function.
 * @notapi
 */
typedef enum np_sm_action
{
    NP_SMP_SUPER_STATE  = 0u,               /**< Returns super state          */
    NP_SMP_TRANSIT_TO   = 1u,               /**< Transit to a state           */
    NACTION_HANDLED     = 2u,               /**< Event is handled             */
    NACTION_IGNORED     = 3u,               /**< Event is ignored             */
} nsm_action;

/** @brief      EPA state machine type
 *  
 *  There are two different state machine types: a Finite State Machine (FSM)
 *  and a Hierarchical State Machine. FSM is a subclass of a HSM, as it has only
 *  one level of hierarchy.
 */
enum nepa_type
{
    NEPA_FSM_TYPE,                          /**<@brief Finite State Machine.  */
    NEPA_HSM_TYPE                           /**<@brief Hierarchical State
                                             *         Machine.
                                             */
};

struct nsm;
struct nevent;



/** @brief      State function prototype.
 * 
 *  Each state machine state is described by a single state function. A state
 *  will receive a state machine which is being executed and an event which
 *  needs to be processed by the state function.
 * 
 *  @param      sm
 *              Pointer to state machine being executed
 *  @param      event
 *              Pointer to event that has been dispatched to the state machine
 *  @return     Action enumerator of the specified state. Action enumerator can
 *              be one of the following:
 *              - @ref NP_SMP_SUPER_STATE - state is returning its super state
 *              - @ref NP_SMP_TRANSIT_TO - state machine wants to transit to
 *                  new state
 *              - @ref NACTION_HANDLED - given event was handled
 *              - @ref NACTION_IGNORED - given event was ignored
 * @note        Do not use return enumerator directly but use the appropriate
 *              naction_*() function.
 */
typedef nsm_action (nstate_fn)(struct nsm *, const struct nevent *);

/** @brief      State machine structure
 */
struct nsm
{
#if (NCONFIG_SM_USE_HSM == 1)
    union nsm_type
    {
        nstate_fn *                 dispatch;   /**< Dispatch function. */
        enum nepa_type              id;         /**< EPA type ID. */
    }                       type;               /**< SM type information. */
#endif
    nstate_fn *                 state;          /**< Current state. */
    void *                      ws;             /**< Pointer to workspace. */
};

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_SM_H_ */
