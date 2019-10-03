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
/** @defgroup   nerror Error
 *  @brief      Error
 *  @{
 */

#ifndef NEON_ERROR_H_
#define NEON_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Error identifiers.
 */
enum nerror_id
{
    EOK,                                    /**< No error. */
    EOBJ_INVALID,                           /**< Invalid object error.        */
    EOBJ_INITIALIZED,                       /**< Object was already 
                                             *   initialized. */
    EARG_OUTOFRANGE,                        /**< Argument is out of range.    */
};

typedef enum nerror_id nerror;

enum nexception_id
{
	NEXCEPTION_RUNTIME
};

void nexception_raise(enum nexception_id nexception_id);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_ERROR_H_ */
