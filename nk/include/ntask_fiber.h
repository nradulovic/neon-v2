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
 *  @brief       Task Fiber header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_fiber Task Fiber
 *  @brief       Task Fiber
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_TASK_FIBER_H_
#define NEON_TASK_FIBER_H_

#include <stdint.h>

/*---------------------------------------------------------------------------*/
/** @defgroup   fiber_ctx Fiber context macros
 *  @brief      Fiber context macros.
 *  @note       These macros are not part of the public API.
 *  @{
 */

/** @brief      Initialize the fiber context.
 *  @hideinitializer
 *  @notapi
 */
#define NP_FIBER_CTX_INIT(ctx)              *(ctx) = 0;

/** @brief      Retrieve previously saved context.
 *  @hideinitializer
 *  @notapi
 */
#define NP_FIBER_CTX_BEGIN(ctx)             switch(*(ctx)) { case 0:

/** @brief      Save the context.
 *  @hideinitializer
 *  @notapi
 */
#define NP_FIBER_CTX_SAVE(ctx, r, offset)                                   \
    *(ctx) = __LINE__ + offset; return (r); case __LINE__ + offset:

/** @brief      End the current execution context.
 *  @hideinitializer
 *  @notapi
 */
#define NP_FIBER_CTX_END(ctx, r)                                            \
    *(ctx) = __LINE__; case __LINE__: ; default: ;} return (r)

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

#define NFIBER_UNINITIALIZED                0u
#define NFIBER_TERMINATED                   1u
#define NFIBER_YIELDED                      2u
#define NFIBER_WAITING                      3u

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
 *
 *  @hideinitializer
 */
#define nfiber_init(fb)                      NP_FIBER_CTX_INIT(&(fb)->ctx)

/** @} */
/*---------------------------------------------------------------------------*/
/** @name       Declaration and definition
 *  @{
 */

/** @brief      Declaration of a fiber.
 *
 *  This macro is used to declare a fiber. All fibers must be declared with
 *  this macro.
 *
 *  @param      fiber_proto
 *              The name and arguments of the C function implementing the
 *              fiber.
 *
 *  @hideinitializer
 */
#define NFIBER(fiber_proto) uint_fast8_t fiber_proto

/** @brief      Declare the start of a fiber inside the C function.
 *
 *  This macro is used to declare the starting point of a fiber. It should be
 *  placed at the start of the function in which the fiber runs. All C
 *  statements above the NFIBER_BEGIN() invokation will be executed each time
 *  the fiber is scheduled.
 *
 *  @param      fb
 *              A pointer to the fiber control structure.
 *
 *  @hideinitializer
 */
#define NFIBER_BEGIN(fb)                                                    \
    do {                                                                    \
        struct nfiber * np_lfb = (fb);                                      \
        NP_FIBER_CTX_BEGIN(&np_lfb->ctx)

/** @brief      Declare the end of a fiber.
 *
 *  This macro is used for declaring that a fiber ends. It must always be used
 *  together with a matching NFIBER_BEGIN() macro.
 *
 *  @hideinitializer
 */
#define NFIBER_END()                                                        \
        NP_FIBER_CTX_END(&np_lfb->ctx, NFIBER_TERMINATED);                  \
    } while (0)

/** @} */
/*---------------------------------------------------------------------------*/
/** @name Exiting and restarting
 *  @{
 */

/**
 * Exit the fiber.
 *
 * This macro causes the fiber to exit. If the fiber was
 * spawned by another fiber, the parent fiber will become
 * unblocked and can continue to run.
 *
 * \hideinitializer
 */
#define nfiber_exit()    			                                        \
    NP_FIBER_CTX_SAVE(&np_lfb->ctx, NFIBER_TERMINATED, 2000u);

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
 * \param fiber_fn The call to the C function implementing the fiber to
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
 * \param condition The condition.
 *
 * \hideinitializer
 */
#define nfiber_wait_until(condition)                                        \
    while (!(condition)) {    			                                    \
        NP_FIBER_CTX_SAVE(&np_lfb->ctx, NFIBER_WAITING, 0u);    		    \
    }

/**
 * Block and wait while condition is true.
 *
 * This function blocks and waits while condition is true. See
 * PT_WAIT_UNTIL().
 *
 * \param cond The condition.
 *
 * \hideinitializer
 */
#define nfiber_wait_while(cond)         nfiber_wait_until(!(cond))

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
 * \param fiber_fn The child fiber with arguments
 *
 * \hideinitializer
 */
#define nfiber_call(fiber_fn)                                               \
    nfiber_wait_until(nfiber_dispatch(fiber_fn) == NFIBER_TERMINATED)

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
 * \hideinitializer
 */
#define nfiber_yield()    	                                                \
        NP_FIBER_CTX_SAVE(&np_lfb->ctx, NFIBER_YIELDED, 1000u)

#define nfiber_block()                                                      \
        NP_FIBER_CTX_SAVE(&np_lfb->ctx, NFIBER_WAITING, 2000u)

/** @} */

#endif /* NEON_TASK_FIBER_H_ */

