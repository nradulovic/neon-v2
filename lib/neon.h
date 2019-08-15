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

#include "sys/nport.h"
#include "sys/nconfig.h"
#include "sys/ndebug.h"
#include "sys/nerror.h"
#include "sys/nbits.h"
#include "sys/nlist_sll.h"
#include "sys/nlist_dll.h"
#include "sys/nlqueue.h"
#include "sys/npqueue.h"
#include "sys/nbitarray_s.h"
#include "sys/nbitarray_x.h"
#include "sys/nstdio.h"
#include "sys/nlogger.h"
#include "sys/nmempool.h"
#include "sys/nevent.h"
#include "sys/nsm.h"
#include "sys/nepa.h"
#include "sys/nscheduler.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Defines a constant string representing Neon build date.
 */
extern const char * const nsys_build_date;

/** @brief      Defines a constant string representing Neon build time.
 */
extern const char * const nsys_build_time;

/** @brief      Defines a constant string representing Neon build platform ID.
 */
extern const char * const nsys_platform_id;

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
