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
/** @defgroup   nevent Events
 *  @brief      Events
 *  @{
 */

#ifndef NEON_EVENT_H_
#define NEON_EVENT_H_

#include <stdint.h>

#include "sys/nconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NEVENT_INITIALIZER(a_id)                                            \
        {                                                                   \
            .id = (a_id),                                                   \
        }

struct nmem_pool;

struct nevent
{
    uint16_t id;
#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
    uint16_t ref;
    struct nmem_pool * pool;
#endif /* (NCONFIG_EVENT_USE_DYNAMIC == 1) */
};

void * nevent_create(struct nmem_pool * pool, uint_fast16_t id);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_EVENT_H_ */
