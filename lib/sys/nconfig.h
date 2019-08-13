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
/** @defgroup   nconfig Compile time configuration
 *  @brief      Compile time configuration
 *  @{
 */

#ifndef NEON_CONFIG_H_
#define NEON_CONFIG_H_

#include <stdint.h>

#include "sys/nport.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Use "neon_config.h" file to customize various modules  of the Neon
 * library. Each project should have its own configuration file.
 */
#if defined(NCONFIG_PROJECT_CONFIG)
#include "neon_config.h"
#endif

/** @brief      Configure if debug module is enabled.
 * 
 *  This macro defines if Neon should be compiled with debug support. If this
 *  module is not enabled all API calls will be replaced by preprocessor to 
 *  empty macros thus not consuming RAM or ROM memory. Debug component also uses
 *  logger component. If logger is not enabled then debug module will only stop
 *  the execution of the application in case of failed assertion.
 *
 *  When this macro is set to '1' the module is enabled, when the macro is set
 *  to '0' the module is disabled. Using any other value is undefined
 *  behaviour.
 * 
 *  Default value is 0 (debug not enabled).
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_ENABLE_DEBUG)
#define NCONFIG_ENABLE_DEBUG            0
#endif

/** @brief      Configure if logger module is enabled.
 * 
 *  This macro defines if Neon should be compiled with logger support. If this
 *  module is not enabled all API calls will be replaced by preprocessor with
 *  empty macros thus not consuming any RAM or ROM memory.
 *
 *  When this macro is set to '1' the module is enabled, when the macro is set
 *  to '0' the module is disabled. Using any other value is undefined
 *  behaviour.
 * 
 *  Default value is 1 (logger enabled).
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_ENABLE_LOGGER)
#define NCONFIG_ENABLE_LOGGER           1
#endif

/** @brief      Configure logger module buffer size (in bytes).
 * 
 *  The logger module uses a buffer to store messages while stream interface is
 *  busy or still not avaialable (during boot process). When the stream 
 *  interface becomes available all the messages in buffer will be flushed from
 *  buffer.
 * 
 *  The value of this macro should be bigger then 10 (or 10 bytes). The maximum 
 *  value of the macro is not defined, but it should not be bigger then a few 
 *  kilobytes.
 * 
 *  Default value is 1024 (use 1kB for the buffer).
 * 
 *  @note       This configuration option is ignored when 
 *              @ref NCONFIG_ENABLE_LOGGER is not enabled.
 * 
 *  @note       If new buffer size is smaller than the default size then during 
 *              boot process (before stream is initialized) a few logger 
 *              messages could be lost.
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_LOGGER_BUFFER_SIZE)
#define NCONFIG_LOGGER_BUFFER_SIZE      1024
#endif
    
/** @brief      Configure the logger level.
 * 
 *  The logger supports a few logger levels, see @ref Logger levels for more
 *  details. Default logger level is @ref NLOGGER_LEVEL_INFO (3).
 * 
 *  The value of this macro should be in range @ref NLOGGER_LEVEL_ERR (1) up
 *  to @ref NLOGGER_LEVEL_DEBUG (4). Using any other value is undefined
 *  behaviour.
 * 
 *  Default value is NLOGGER_LEVEL_INFO (equal to number 3).
 * 
 *  @note       This configuration option is ignored when
 *              @ref NCONFIG_ENABLE_LOGGER is not enabled.
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_LOGGER_LEVEL)
#define NCONFIG_LOGGER_LEVEL            NLOGGER_LEVEL_INFO
#endif

/** @brief      Configure how many EPA Instances are used by application.
 * 
 *  Neon uses static allocation for all instances of EPA objects. Therefore, for
 *  optimal memory usage each application configuration file should specify
 *  exact number of needed EPA instances. This number will then be used to 
 *  statically allocate the instances.
 * 
 *  Neon defines a number of intrisic system EPA objects (idle EPA, deferred 
 *  ISR EPA, ...). Please, take these system EPA objects into account when 
 *  calculating how much EPA instances are needed.
 * 
 *  Minimum value of this macro should be 2 (at least IDLE EPA and one 
 *  application EPA).
 * 
 *  Default value is 8 (supporting up to 8 EPA instances).
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_EPA_INSTANCES)
#define NCONFIG_EPA_INSTANCES           8
#endif
    
/** @brief      Configure whether to support HSM state machines or not.
 * 
 *  As stated in more detail in @ref nepa section, there are two classes of
 *  state machines: Finite State Machine (FSM) and Hierarchical State Machine.
 *  
 *  In application which use exclusively FSM this configuration option should
 *  be disabled to allow for certain speed and size optimizations. If an
 *  application uses at least one HSM then this option needs to be enabled.
 *  
 *  When this macro is set to '1' the HSM dispatcher will be compiled, when the 
 *  macro is set to '0' the HSM dispatcher will not be compiled, therefore not
 *  supporting HSM type EPA class. Using any other value is undefined behaviour.
 * 
 *  Default value is 0 (don't support HSM EPA class).
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_EPA_USE_HSM)
#define NCONFIG_EPA_USE_HSM             0
#endif
    
/** @brief      Configure the hierarchical levels of HSM dispatcher.
 * 
 *  Each HSM is characterized by the number of levels of its hierarchy. The
 *  HSM dispatch uses this configuration option to configure itself for maximum
 *  HSM level allowable.
 * 
 *  Set this value to maximum value of hierarchy level of all HSMs used in an
 *  application. When this value is set to 1 it means that application does not
 *  need HSM at all (disable the NCONFIG_EPA_USE_HSM). Using values smaller than
 *  2 is undefined behaviour.
 * 
 *  Default value is 8 (8 hierarchical levels).
 * 
 *  @note       This configuration option is ignored when 
 *              @ref NCONFIG_EPA_USE_HSM is not enabled.
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_EPA_HSM_LEVELS)
#define NCONFIG_EPA_HSM_LEVELS          8
#endif

/** @brief      Configure if loop scheduler should be exitable.
 * 
 *  Normally, in an embedded applications once a loop scheduler is started it is
 *  never stopped. In this case one can rely on this fact and produce more
 *  optimized code (acquire and never release a resource, do not compile exit
 *  or terminate functions...). However, if there is a need to eventually exit
 *  from loop scheduler (for example in a Linux application) then this 
 *  configuration option should be enabled.
 * 
 *  Default value is 0 (exit from scheduler is not enabled).
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_SYS_EXITABLE_SCHEDULER)
#define NCONFIG_SYS_EXITABLE_SCHEDULER  0
#endif
    
/** @brief      Enable or disable dynamic event.
 * 
 *  Dynamic events can be deleted once they are processed. For more details on
 *  dynamic events see @ref nevent section. In case the application needs this 
 *  functionality then enable this macro.
 * 
 *  When this macro is set to '1' the option is enabled, when the macro is set
 *  to '0' the option is disabled. Using any other value is undefined
 *  behaviour.
 * 
 *  Default value is 0 (debug not enabled).
 * 
 *  @hideinitializer
 */
#if !defined(NCONFIG_EVENT_USE_DYNAMIC)
#define NCONFIG_EVENT_USE_DYNAMIC       0
#endif
    
#if !defined(NCONFIG_USE_EXCLUSIVE_ACCESS) 
#define NCONFIG_USE_EXCLUSIVE_ACCESS    0
#endif

#define NCONFIG_ENABLE_DEBUG_BIT        31
#define NCONFIG_ENABLE_LOGGER_BIT       30
#define NCONFIG_EPA_USE_HSM_BIT         16
#define NCONFIG_EPA_HSM_LEVELS_BIT      12
#define NCONFIG_SYS_EXITABLE_SCHEDULER_BIT  9
#define NCONFIG_EVENT_USE_DYNAMIC_BIT   8
    
    
extern const uint32_t nconfig_configuration;

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_CONFIG_H_ */
