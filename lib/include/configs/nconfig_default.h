/*
 * Neon
 * Copyright (C)  2018  REAL-TIME CONSULTING
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NEON_CONFIG_DEFAULT_H_
#define NEON_CONFIG_DEFAULT_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NCONFIG_PROJECT_CONFIG)
#include "neon_config.h"
#endif

#ifndef NCONFIG_ENABLE_LOGGER
#define NCONFIG_ENABLE_LOGGER 0
#endif
    
#ifndef NCONFIG_ENABLE_DEBUG
#define NCONFIG_ENABLE_DEBUG 1
#endif

#ifndef NCONFIG_FIBER_INSTANCES
#define NCONFIG_FIBER_INSTANCES 32
#endif

#ifndef NCONFIG_TASK_INSTANCES
#define NCONFIG_TASK_INSTANCES 8
#endif

#ifndef NCONFIG_EPA_INSTANCES
#define NCONFIG_EPA_INSTANCES 32
#endif

#ifndef NCONFIG_TASK_INSTANCES
#define NCONFIG_TASK_INSTANCES 32
#endif

#ifndef NCONFIG_TASK_PRIO_GROUPS
#define NCONFIG_TASK_PRIO_GROUPS 32
#endif

#ifndef NCONFIG_TASK_PRIO_GROUPS
#define NCONFIG_TASK_PRIO_GROUPS 32
#endif

#ifndef NCONFIG_TASK_SCHED_RR
#define NCONFIG_TASK_SCHED_RR 1
#endif

#ifndef NCONFIG_TASK_SCHED_PRIO
#define NCONFIG_TASK_SCHED_PRIO 0
#endif

#ifndef NCONFIG_TESTSUITE_STOP_ON_ERROR
#define NCONFIG_TESTSUITE_STOP_ON_ERROR 0
#endif

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_CONFIG_DEFAULT_H_ */
