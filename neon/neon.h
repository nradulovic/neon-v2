/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup    neon Neon API
 *  @brief       Neon API
 *  @{
 */

#ifndef NEON_H_
#define NEON_H_

#include "core/nport.h"
#include "core/nconfig.h"
#include "core/nerror.h"
#include "core/nbits.h"
#include "core/nlist_sll.h"
#include "core/nlist_dll.h"
#include "core/nlqueue.h"
#include "core/npqueue.h"
#include "core/nbitarray.h"
#include "core/nstdio.h"
#include "core/nlogger.h"
#include "core/nmempool.h"
#include "core/nevent.h"
#include "core/nsm.h"
#include "core/nepa.h"
#include "core/nscheduler.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Defines system Idle EPA description
 */
extern const struct nepa nsys_epa_idle;

/** @brief      System initialization function
 * 
 *  This function will initialize all modules of Neon library package.
 */
void nsys_init(void);

/** @brief      Returns the pointer to currently executed EPA.
 *  
 *  @param      a_scheduler
 *              A pointer to scheduler context structure.
 */
#define nsys_current(a_scheduler)       nscheduler_current(a_scheduler)

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* NEON_H_ */
