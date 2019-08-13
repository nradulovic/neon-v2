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
/** @defgroup   nlogger Logger
 *  @brief      Logger
 *  @{
 */

#ifndef NEON_LOGGER_H_
#define NEON_LOGGER_H_

#include <stdbool.h>

#include "sys/nconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @name       Logger levels
 *  @brief      Logger levels
 *  @details    Default log level is @ref NLOGGER_LEVEL_DEBUG.
 *  @{
 */

/** @brief      Logger messages with DEBUG importance.
 */
#define NLOGGER_LEVEL_DEBUG             4

/** @brief      Logger messages with INFO importance.
 */
#define NLOGGER_LEVEL_INFO              3

/** @brief      Logger messages with WARNing importance.
 */
#define NLOGGER_LEVEL_WARN              2

/** @brief      Logger message with ERRor importance.
 */
#define NLOGGER_LEVEL_ERR               1

/** @} */
/** @defgroup   loggerprinters Logger printers
 *  @brief      Logger printers.
 *  @{
 */

#if defined(NCONFIG_ENABLE_LOGGER) && (NCONFIG_ENABLE_LOGGER == 1)
/** @brief      Macro that returns current nlogger configuration
 */
#define NLOGGER_IS_ENABLED              1
#else
#define NLOGGER_IS_ENABLED              0
#endif

#if (NLOGGER_IS_ENABLED == 1) && \
    (NCONFIG_LOGGER_LEVEL >= 4) || defined(__DOXYGEN__)
/** @brief      Log a debug message.
 */
#define nlogger_debug(msg, ...)         nlogger_print(msg, __VA_ARGS__)
#else
#define nlogger_debug(msg, ...)
#endif

#if (NLOGGER_IS_ENABLED == 1) && \
    (NCONFIG_LOGGER_LEVEL >= 3) || defined(__DOXYGEN__)
/** @brief      Log an informational message.
 */
#define nlogger_info(msg, ...)          nlogger_print(msg, __VA_ARGS__)
#else
#define nlogger_info(msg, ...)
#endif

#if (NLOGGER_IS_ENABLED == 1) && \
    (NCONFIG_LOGGER_LEVEL >= 2) || defined(__DOXYGEN__)
/** @brief      Log a warning message.
 */
#define nlogger_warn(msg, ...)          nlogger_print(msg, __VA_ARGS__)
#else
#define nlogger_warn(msg, ...)
#endif

#if (NLOGGER_IS_ENABLED == 1) && \
    (NCONFIG_LOGGER_LEVEL >= 1) || defined(__DOXYGEN__)
/** @brief      Log an error message.
 */
#define nlogger_err(msg, ...)           nlogger_print(msg, __VA_ARGS__)
#else
#define nlogger_err(msg, ...)
#endif

#if (NCONFIG_ENABLE_LOGGER == 1) || defined(__DOXYGEN__)
bool nlogger_flush(void);
#else
#define nlogger_flush()
#endif

#if (NCONFIG_ENABLE_LOGGER == 1) || defined(__DOXYGEN__)
/** @brief      Print a formated string to a logger.
 */
bool nlogger_print(const char * msg, ...);
#else
#define nlogger_print(msg, ...)
#endif

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_LOGGER_H_ */
