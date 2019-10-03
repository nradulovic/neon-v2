/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   nevent_impl Event implementation
 *  @brief      Event implementation
 *  @{ *//*==================================================================*/

#include "core/nevent.h"
#include "core/nmempool.h"

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
void * nevent_create(struct nmem_pool * pool, uint_fast16_t id)
{
    struct nevent * event;

    event = nmem_pool_alloc(pool);

    if (event == NULL) {
        return NULL;
    }
    event->id = id;
    event->ref = 0u;
    event->pool = pool;

    return event;
}
#endif

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
void event_delete(const struct nevent * event)
{
    if (event_ref_down(event)) {
        nmem_pool_free(event->pool, (void *)event);
    }
}
#endif

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
void event_ref_up(const struct nevent * event)
{
    if (event->pool != NULL) {
        struct nevent * l_event = (struct nevent *)event;

        l_event->ref++;
    }
}
#endif

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
static inline
bool event_ref_down(const struct nevent * event)
{
    bool retval;

    if (event->pool != NULL) {
        struct nevent * l_event = (struct nevent *)event;
        l_event->ref--;
        retval = !(l_event->ref == 0u);
    } else {
        retval = false;
    }
    return retval;
}
#endif

/** @} */
