/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   nconfig_impl Configuration module implementation
 *  @brief      Configuration module implementation
 *  @{ *//*==================================================================*/

#include <stddef.h>

#include "core/nconfig.h"
#include "core/nbits.h"

const struct nconfig_entry * nconfig_record_fetch(enum nconfig_entry_id idx)
{
    static const struct nconfig_entry record[] =
    {
        [NCONFIG_ENTRY_ENABLE_DEBUG] =
		{
			"NCONFIG_ENABLE_DEBUG",
			NCONFIG_ENABLE_DEBUG
		},
        [NCONFIG_ENTRY_ENABLE_LOGGER] =
        {
			"NCONFIG_ENABLE_LOGGER",
			NCONFIG_ENABLE_LOGGER
        },
        [NCONFIG_ENTRY_LOGGER_BUFFER_SIZE] =
        {
			"NCONFIG_LOGGER_BUFFER_SIZE",
			NCONFIG_STDIO_OUTPUT_BUFFER_SIZE
        },
        [NCONFIG_ENTRY_LOGGER_LEVEL] =
        {
			"NCONFIG_LOGGER_LEVEL",
			NCONFIG_LOGGER_LEVEL
        },
        [NCONFIG_ENTRY_EPA_INSTANCES] =
        {
			"NCONFIG_EPA_INSTANCES",
			NCONFIG_EPA_INSTANCES
        },
        [NCONFIG_ENTRY_EPA_USE_HSM] =
        {
			"NCONFIG_EPA_USE_HSM",
			NCONFIG_EPA_USE_HSM
        },
        [NCONFIG_ENTRY_EPA_HSM_LEVELS] =
        {
			"NCONFIG_EPA_HSM_LEVELS",
			NCONFIG_EPA_HSM_LEVELS
        },
        [NCONFIG_ENTRY_SYS_EXITABLE_SCHEDULER] =
        {
			"NCONFIG_SYS_EXITABLE_SCHEDULER",
			NCONFIG_SYS_EXITABLE_SCHEDULER
        },
        [NCONFIG_ENTRY_EVENT_USE_DYNAMIC] =
        {
			"NCONFIG_EVENT_USE_DYNAMIC",
			NCONFIG_EVENT_USE_DYNAMIC
        },
        [NCONFIG_ENTRY_SCHEDULER_PRIORITIES] =
        {
			"NCONFIG_SCHEDULER_PRIORITIES",
			NCONFIG_SCHEDULER_PRIORITIES
        },
        [NCONFIG_ENTRY_USE_EXCLUSIVE_ACCESS] =
        {
			"NCONFIG_USE_EXCLUSIVE_ACCESS",
			NCONFIG_USE_EXCLUSIVE_ACCESS
        },
    };

    if (idx >= NBITS_ARRAY_SIZE(record)) {
        return NULL;
    }
    return &record[idx];
}

/** @} */
