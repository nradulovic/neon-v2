/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   nsm_impl State machine implementation
 *  @brief      State machine implementation
 *  @{ *//*==================================================================*/

#include <stddef.h>

#include "core/nsm.h"
#include "core/nevent.h"
#include "core/nport.h"

#define sm_event(event)                 &g_events[(event)]

static const struct nevent g_events[] =
{
    [NSM_SUPER] = NEVENT_INITIALIZER(NSM_SUPER),
    [NSM_ENTRY] = NEVENT_INITIALIZER(NSM_ENTRY),
    [NSM_EXIT] = NEVENT_INITIALIZER(NSM_EXIT),
    [NSM_INIT] = NEVENT_INITIALIZER(NSM_INIT),
    
    [NSIGNAL_RETRIGGER] = NEVENT_INITIALIZER(NSIGNAL_RETRIGGER),
    [NSIGNAL_AFTER] = NEVENT_INITIALIZER(NSIGNAL_AFTER),
    [NSIGNAL_EVERY] = NEVENT_INITIALIZER(NSIGNAL_EVERY),
    
    [NEVENT_NULL] = NEVENT_INITIALIZER(NEVENT_NULL),
};

static nsm_action sm_fsm_dispatch(struct nsm * sm, const struct nevent * event)
{
    nsm_action                  ret;
    nstate_fn *                 current_state;

    current_state = sm->state;

    while ((ret = current_state(sm, event)) == NP_SMP_TRANSIT_TO) {
        ret = current_state(sm, sm_event(NSM_EXIT));
        current_state = sm->state;
        ret = current_state(sm, sm_event(NSM_ENTRY));
        event = sm_event(NSM_INIT);
    }
    sm->state = current_state;

    return ret;
}

void sm_init(struct nsm * sm)
{
#if (NCONFIG_EPA_USE_HSM == 1)
    if (sm->type.id == NEPA_FSM_TYPE) {
        sm->type.dispatch = fsm_dispatch;
    } else {
        sm->type.dispatch = hsm_dispatch;
    }
#endif
    NPLATFORM_UNUSED_ARG(sm);
}

nsm_action sm_dispatch(struct nsm * sm, const struct nevent * event)
{
#if (NCONFIG_EPA_USE_HSM == 1)
	return sm->type.dispatch(sm, event);
#else
	return sm_fsm_dispatch(sm, event);
#endif
}

/** @} */
