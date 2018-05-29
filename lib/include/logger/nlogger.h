/*
 * Neon
 * Copyright (C)  2017  Nenad Radulovic
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Logger header
 *
 *  @addtogroup  module
 *  @{
 */
/** @defgroup    mod_logger Logging facility
 *  @brief       Logging facility
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_LOGGER_H_
#define NEON_MODULE_LOGGER_H_

#include "nlogger_x.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   loggerid Logger identification information
 *  @brief      Logger identification macros.
 *  @{
 */
#ifndef NLOGGER_ID
#define NLOGGER_ID              "unknown"
#endif

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   loggerlevels Logger levels
 *  @brief      Logger levels.
 *  @{
 */

/** @brief      Logger levels
 *  @details    Default log level is @ref NLOGGER_LVL_DEBUG.
 */
enum nlogger_levels
{
    NLOGGER_LEVEL_DEBUG = 4,
    NLOGGER_LEVEL_INFO = 3,
    NLOGGER_LEVEL_WARN = 2,
    NLOGGER_LEVEL_ERR = 1
};

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   loggerprinters Logger printers
 *  @brief      Logger printers.
 *  @{
 */

/** @brief      Log a debug message.
 */
#define nlogger_debug(msg, ...)                                             \
        nlogger_x_debug(NULL, msg, __VA_ARGS__)

/** @brief      Log a informational message.
 */
#define nlogger_info(msg, ...)                                              \
        nlogger_x_info(NULL, msg, __VA_ARGS__)

/** @brief      Log a warning message.
 */
#define nlogger_warn(msg, ...)                                              \
        nlogger_x_warn(NULL, msg, __VA_ARGS__)

/** @brief      Log a error message.
 */
#define nlogger_err(msg, ...)                                               \
        nlogger_x_err(NULL, msg, __VA_ARGS__)

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_LOGGER_H_ */
