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
 *  @brief       Thread Fiber header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_fiber Thread Fiber
 *  @brief       Thread Fiber
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_THREAD_FIBER_H_
#define NEON_THREAD_FIBER_H_

#include <stdint.h>
#include "port/nport_platform.h"

/*---------------------------------------------------------------------------*/
/** @defgroup   fiber_ctx Fiber context macros
 *  @brief      Fiber context macros.
 *  @note       These macros are not part of the public API.
 *  @{
 */

/** @brief      Initialize the fiber context.
 *  @notapi
 */
#define NP_FIBER_CTX_INIT(ctx)              *(ctx) = 0;

/** @brief      Retrieve previously saved context.
 *  @notapi
 */
#define NP_FIBER_CTX_BEGIN(ctx)             switch(*(ctx)) { case 0:

/** @brief      Save the context.
 *  @notapi
 */
#define NP_FIBER_CTX_SAVE(ctx, r, offset)                                   \
    *(ctx) = __LINE__ + offset; return (r); case __LINE__ + offset:

/** @brief      End the current execution context.
 *  @notapi
 */
#define NP_FIBER_CTX_END(ctx, r)                                            \
    *(ctx) = __LINE__; case __LINE__: ;} return (r)

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   fiber_decl Fiber declarations
 *  @brief      Fiber declarations.
 *  @{
 */

/** @brief      Fiber control structure.
 */
struct nfiber
{
    uint32_t ctx;
};

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   fiber_state Fiber states
 *  @brief      Fiber states.
 *  @{
 */

#define NFIBER_YIELDED                      0
#define NFIBER_WAITING                      1
#define NFIBER_TERMINATED                   2

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   fiber_init Fiber initialization
 *  @brief      Fiber initialization.
 *  @{
 */

/** @brief      Initialize a fiber.
 *
 *  Initializes a fiber. Initialization must be done prior to starting to
 *  execute the fiber.
 *
 *  @param      fb
 *              A pointer to the fiber control structure.
 */
NPLATFORM_INLINE
void nfiber_init(struct nfiber * fb)
{
    NP_FIBER_CTX_INIT(&fb->ctx);
}

/** @} */

/**
 * \name Declaration and definition
 * @{
 */

/**
 * Declaration of a fiber.
 *
 * This macro is used to declare a fiber. All fibers must
 * be declared with this macro.
 *
 * \param name_args The name and arguments of the C function
 * implementing the fiber.
 *
 * \hideinitializer
 */
#define NFIBER(name_args) uint_fast8_t name_args

/**
 * Declare the start of a fiber inside the C function
 * implementing the fiber.
 *
 * This macro is used to declare the starting point of a
 * fiber. It should be placed at the start of the function in
 * which the fiber runs. All C statements above the PT_BEGIN()
 * invokation will be executed each time the fiber is scheduled.
 *
 * \param pt A pointer to the fiber control structure.
 *
 * \hideinitializer
 */
#define NFIBER_BEGIN(fb)                    NP_FIBER_CTX_BEGIN(&(fb)->ctx)

/**
 * Declare the end of a fiber.
 *
 * This macro is used for declaring that a fiber ends. It must
 * always be used together with a matching PT_BEGIN() macro.
 *
 * \param pt A pointer to the fiber control structure.
 *
 * \hideinitializer
 */
#define NFIBER_END(fb)                                                      \
    NP_FIBER_CTX_END(&(fb)->ctx, NFIBER_TERMINATED)

/** @} */

/**
 * \name Exiting and restarting
 * @{
 */

/**
 * Exit the fiber.
 *
 * This macro causes the fiber to exit. If the fiber was
 * spawned by another fiber, the parent fiber will become
 * unblocked and can continue to run.
 *
 * \param pt A pointer to the fiber control structure.
 *
 * \hideinitializer
 */
#define NFIBER_EXIT(fb)				\
    NP_FIBER_CTX_SAVE(&(fb)->ctx, NFIBER_TERMINATED, 2000u);

/** @} */

/**
 * \name Calling a fiber
 * @{
 */

/**
 * Schedule a fiber.
 *
 * This function shedules a fiber. The return value of the
 * function is non-zero if the fiber is running or zero if the
 * fiber has exited.
 *
 * \param f The call to the C function implementing the fiber to
 * be scheduled
 *
 * \hideinitializer
 */
#define nfiber_dispatch(fiber_fn)    fiber_fn

/** @} */

/**
 * \name Blocked wait
 * @{
 */

/**
 * Block and wait until condition is true.
 *
 * This macro blocks the fiber until the specified condition is
 * true.
 *
 * \param pt A pointer to the fiber control structure.
 * \param condition The condition.
 *
 * \hideinitializer
 */
#define NFIBER_WAIT_UNTIL(fb, condition)	        \
  do {						\
    while (!(condition)) {				\
        NP_FIBER_CTX_SAVE(&(fb)->ctx, NFIBER_WAITING, 0u);			\
    }						\
  } while(0)

/**
 * Block and wait while condition is true.
 *
 * This function blocks and waits while condition is true. See
 * PT_WAIT_UNTIL().
 *
 * \param pt A pointer to the fiber control structure.
 * \param cond The condition.
 *
 * \hideinitializer
 */
#define NFIBER_WAIT_WHILE(fb, cond)  NFIBER_WAIT_UNTIL((fb), !(cond))

/** @} */


/**
 * \name Hierarchical fibers
 * @{
 */

/**
 * Block and wait until a child fiber completes.
 *
 * This macro schedules a child fiber. The current fiber
 * will block until the child fiber completes.
 *
 * \note The child fiber must be manually initialized with the
 * PT_INIT() function before this function is used.
 *
 * \param pt A pointer to the fiber control structure.
 * \param thread The child fiber with arguments
 *
 * \sa PT_SPAWN()
 *
 * \hideinitializer
 */
#define NFIBER_WAIT(fb, fiber_fn)                                           \
    NFIBER_WAIT_UNTIL((fb), nfiber_dispatch(fiber_fn) == NFIBER_TERMINATED)

/** @} */

/**
 * \name Yielding from a fiber
 * @{
 */

/**
 * Yield from the current fiber.
 *
 * This function will yield the fiber, thereby allowing other
 * processing to take place in the system.
 *
 * \param pt A pointer to the fiber control structure.
 *
 * \hideinitializer
 */
#define NFIBER_YIELD(fb)		                                            \
        NP_FIBER_CTX_SAVE(&(fb)->ctx, NFIBER_YIELDED, 1000u)

#define NP_FIBER_EXEC(fb, preexec, condition, postexec, offset) \
    do { \
        if (preexec) { \
            do { \
                NP_FIBER_CTX_SAVE(&(fb)->ctx, NFIBER_WAITING, offset); \
            } while (!condition); \
            postexec; \
        } \
    } while (0)

/** @} */

#endif /* NEON_THREAD_FIBER_H_ */

