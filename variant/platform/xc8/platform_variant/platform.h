/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Platform header for common XC8 definitions.
 *
 *  @addtogroup  mod_platform
 *  @{
 */
/** @defgroup    platform_xc8_common Common XC8 Platform definitions
 *  @brief       Common XC8 Platform definitions
 *  @{
 */

#ifndef NEON_VA_INCLUDE_NPORT_PLATFORM_XC8_VARIANT_PLATFORM
#define NEON_VA_INCLUDE_NPORT_PLATFORM_XC8_VARIANT_PLATFORM

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#define NPLATFORM_ID                    "xc8"
    
#define NPLATFORM_DATE                  __DATE__
    
#define NPLATFORM_TIME                  __TIME__

#define NPLATFORM_FILE                  __FILE__

#define NPLATFORM_LINE                  __LINE__
    
#define NPLATFORM_FUNC                  __func__
    
#define NPLATFORM_UNUSED_ARG(x)         (void)x

#define NPLATFORM_NAKED(x)              __attribute__((naked)) x

#define NPLATFORM_UNUSED(y)             __attribute__((unused)) y

#define NPLATFORM_NORETURN(x)           __attribute__((noreturn)) x

#define NPLATFORM_PACKED(x)             __attribute__((packed)) x

#define NPLATFORM_ALIGN(align, x)       __attribute__((aligned (align))) x

#define NPLATFORM_INLINE        		static inline

#define NPLATFORM_INLINE_ALWAYS 		NPLATFORM_INLINE
    
#define NPLATFORM_BROKEN_INLINE         1

#define NPLATFORM_CONTAINER_OF(ptr, type, member)                      \
    ((type *)((char *)ptr - offsetof(type, member)))
    
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_VA_INCLUDE_NPORT_PLATFORM_XC8_VARIANT_PLATFORM */
