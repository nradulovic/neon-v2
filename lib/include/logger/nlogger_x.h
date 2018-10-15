/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
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
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Extended Logger header
 *
 *  @addtogroup  module
 *  @{
 */
/** @defgroup    mod_logger Extended Logging facility
 *  @brief       Extended Logging facility
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_LOGGER_X_H_
#define NEON_MODULE_LOGGER_X_H_

#include <stdint.h>

#include "logger/nlogger.h"
#include "list/nlist_sll.h"
#include "configs/default_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   loggerprinters Logger printers
 *  @brief      Logger printers.
 *  @{
 */

#if defined(NCONFIG_ENABLE_LOGGER) && (NCONFIG_ENABLE_LOGGER == 1)
#define NLOGGER_IS_ENABLED 1
#else
/** @brief      Macro that returns current nlogger configuration
 */
#define NLOGGER_IS_ENABLED 0
#endif

#define NLOGGER_INITIALIZER(a_name) {.name = a_name}

/** @brief      Log a debug message.
 */
#define nlogger_x_debug(instance, msg, ...)                                 \
        nlogger_x_print(instance, NLOGGER_LEVEL_DEBUG, msg, __VA_ARGS__)

/** @brief      Log an informational message.
 */
#define nlogger_x_info(instance, msg, ...)                                  \
        nlogger_x_print(instance, NLOGGER_LEVEL_INFO, msg, __VA_ARGS__)

/** @brief      Log a warning message.
 */
#define nlogger_x_warn(instance, msg, ...)                                  \
        nlogger_x_print(instance, NLOGGER_LEVEL_WARN, msg, __VA_ARGS__)

/** @brief      Log an error message.
 */
#define nlogger_x_err(instance, msg, ...)                                   \
        nlogger_x_print(instance, NLOGGER_LEVEL_ERR, msg, __VA_ARGS__)

#if (NLOGGER_IS_ENABLED == 1)
#define nlogger_x_print(instance, level, msg, ...)                          \
    do {                                                                    \
        struct nlogger_instance * _instance = (instance);                   \
        p_nlogger_x_print(!_instance ? &p_nlogger_global : _instance, level,\
                msg, __VA_ARGS__);                                          \
    } while (0)
#else
#define nlogger_x_print(instance, level, msg, ...)
#endif

#if (NLOGGER_IS_ENABLED == 1)
#define nlogger_x_set_level(instance, level)                                \
    do {                                                                    \
        struct nlogger_instance * _instance = (instance);                   \
        p_nlogger_x_set_level(!_instance ? &p_nlogger_global : _instance,   \
                (level));                                                   \
    } while (0)
#else
#define nlogger_x_set_level(instance, level)
#endif

struct nlogger_instance
{
    struct nlist_sll list;
    const char * name;
    uint8_t level;
};

extern struct nlogger_instance p_nlogger_global;

void p_nlogger_x_print(struct nlogger_instance * instance, 
        uint8_t level, const char * msg, ...);
void p_nlogger_x_set_level(struct nlogger_instance * instance, uint8_t level);

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_LOGGER_X_H_ */
