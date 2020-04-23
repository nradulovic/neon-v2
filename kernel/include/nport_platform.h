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
 *  @brief       Platform header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_platform Platform
 *  @brief       Platform
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_PLATFORM_H_
#define NEON_MODULE_PLATFORM_H_

#include "../../kernel/va_include/nport/platform_gcc/variant/platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   platformid Platform identification information
 *  @brief      Port compiler identification macros.
 *  @{
 */
#define NPLATFORM_ID            "gcc"

/** @brief      Each port defines a macro named NPLATFORM_xxx.
 *  
 *  For example, the GCC based compilers will define 'NPLATFORM_GCC'. ARM
 *  based compilers will define NPLATFORM_ARM.
 */
#define NPLATFORM_xxx

extern const char * nplatform_id;
extern const char * nplatform_build;

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   platform_compiler Platform compiler macros
 *  @brief      Port compiler helper macros.
 *  @{
 */

/** @brief      Compiler directive to inline a function.
 *  @note       This macro is usually defined in port.
 */
#ifndef NPLATFORM_INLINE
#define NPLATFORM_INLINE        static inline
#endif

#ifndef NPLATFORM_INLINE_ALWAYS
#define NPLATFORM_INLINE_ALWAYS NPLATFORM_INLINE
#endif

/**@brief       Cast a member of a structure out to the containing structure
 * @param       ptr
 *              the pointer to the member.
 * @param       type
 *              the type of the container struct this is embedded in.
 * @param       member
 *              the name of the member within the struct.
 */
#ifndef NPLATFORM_CONTAINER_OF
#define NPLATFORM_CONTAINER_OF(ptr, type, member)                      \
    ((type *)((char *)ptr - offsetof(type, member)))
#endif

/**@brief       Provides function name for assert macros
 */
#ifndef NPLATFORM_FUNC
#define NPLATFORM_FUNC             "unknown"
#endif

/**@brief       Provides the free file's name which is being compiled
 */
#ifndef NPLATFORM_FILE
#define NPLATFORM_FILE             "unknown"
#endif

/**@brief       Provides the free source line
 */
#ifndef NPLATFORM_LINE
#define NPLATFORM_LINE             0
#endif

/**@brief       Omit function prologue/epilogue sequences
 * @note        Using this macro when the compiler feature is not supported
 *              will generate compilation error.
 */
#ifndef NPLATFORM_NAKED
#define NPLATFORM_NAKED(x)              __provoke_error__ x
#endif

#ifndef NPLATFORM_UNUSED
#define NPLATFORM_UNUSED(y)             __provoke_error__ y
#endif

/**@brief       Declare a function that will never return
 */
#ifndef NPLATFORM_NORETURN
#define NPLATFORM_NORETURN(x)           x
#endif

#ifndef NPLATFORM_PACKED
#define NPLATFORM_PACKED(x)             __provoke_error__ x
#endif

/**@brief       This attribute specifies a minimum alignment (in bytes) for
 *              variables of the specified type.
 */
#ifndef NPLATFORM_ALIGN
#define NPLATFORM_ALIGN(align, x)       __provoke_error__ x
#endif

/**@brief       Prevent the compiler from merging or refetching accesses.
 * @details     The compiler is also forbidden from reordering successive
 *              instances of NPLATFORM_ACCESS_ONCE(), but only when the 
 *              compiler is aware of some particular ordering.  One way to make
 *              the compiler aware of ordering is to put the two invocations of
 *              NPLATFORM_ACCESS_ONCE() in different C statements.
 */
#ifndef NPLATFORM_ACCESS_ONCE
#define NPLATFORM_ACCESS_ONCE(x)        (*(volatile typeof(x) *)&(x))
#endif

/** @brief      Returns current date.
 */
#ifndef NPLATFORM_DATE
#define NPLATFORM_DATE                  __DATE__
#endif

/** @brief      Returns current time.
 */
#ifndef NPLATFORM_TIME
#define NPLATFORM_TIME                  __TIME__
#endif

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_PLATFORM_H_ */
