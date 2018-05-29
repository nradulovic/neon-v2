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
 *  @brief       Testsuite header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_testsuite Testsuite
 *  @brief       Testsuite.
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_TESTSUITE_H_
#define NEON_MODULE_TESTSUITE_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include "logger/nlogger.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (NLOGGER_IS_ENABLED == 0)
#error "Module nlogger must be enabled for ntestsuite."
#endif

#define NTESTSUITE_ASSERT(expr)                                             \
    if (p_ntestsuite_context.should_exit) {                                 \
        return;                                                             \
    }                                                                       \
    if (!(expr)) {                                                          \
        p_ntestsuite_context.should_exit = true;                            \
        return;                                                             \
    }

#define NTESTSUITE_PRINT_RESULTS()                                          \
    if (p_ntestsuite_failed_tests != 0u) {                                  \
        nlogger_info("Test %s:%s\n  Total  %u\n  FAILED %u\n",              \
            NPLATFORM_FILE, NPLATFORM_FUNC, p_ntestsuite_tests,             \
            p_ntestsuite_failed_tests);                                     \
    } else {                                                                \
        nlogger_info("Test %s:%s\n  Total %u\n  OK\n",                      \
                NPLATFORM_FILE, NPLATFORM_FUNC,                             \
                p_ntestsuite_tests);                                        \
    }                                                                       \
    p_ntestsuite_tests = 0u;                                                \
    p_ntestsuite_failed_tests = 0u;

#define NTESTSUITE_ASSERT_EQUAL_INT(expected, actual)                       \
    P_NTESTSUITE_ASSERT_EQUAL(expected, actual, int32_t, d,                 \
            P_NTESTSUITE_CNV_NONE, P_NTESTSUITE_CMP_PLAIN)

#define NTESTSUITE_ASSERT_EQUAL_UINT(expected, actual)                      \
    P_NTESTSUITE_ASSERT_EQUAL(expected, actual, uint32_t, u,                \
            P_NTESTSUITE_CNV_NONE, P_NTESTSUITE_CMP_PLAIN)

#define NTESTSUITE_ASSERT_EQUAL_PTR(expected, actual)                       \
    P_NTESTSUITE_ASSERT_EQUAL(expected, actual, void *, p,                  \
            P_NTESTSUITE_CNV_NONE, P_NTESTSUITE_CMP_PLAIN)

#define NTESTSUITE_ASSERT_EQUAL_BOOL(expected, actual)                      \
    P_NTESTSUITE_ASSERT_EQUAL(expected, actual, bool, s,                    \
            P_NTESTSUITE_CNV_BOOL, P_NTESTSUITE_CMP_PLAIN)

#define NTESTSUITE_ASSERT_EQUAL_STRING(expected, actual)                    \
    P_NTESTSUITE_ASSERT_EQUAL(expected, actual, const char *, s,            \
            P_NTESTSUITE_CNV_NONE, P_NTESTSUITE_CMP_STRING)

#define NTESTSUITE_RUN(a_fixture, function)                                 \
    p_ntestsuite_context.fixture = &a_fixture;                              \
    p_ntestsuite_context.should_exit = false;                               \
    if (a_fixture.setup) {                                                  \
        nlogger_debug("D: Setup fixture %s for test %s\n", a_fixture.name,  \
            # function);                                                    \
        a_fixture.setup();                                                  \
    }                                                                       \
    if (p_ntestsuite_context.should_exit == true) {                         \
        nlogger_err("Failed to setup fixture %s for test %s() at %s:%s\n",  \
                a_fixture.name, # function, NPLATFORM_FILE,                 \
                NPLATFORM_LINE);                                            \
    } else {                                                                \
        function();                                                         \
    }                                                                       \
    if (a_fixture.teardown) {                                               \
        nlogger_debug("D: Teardown fixture %s for test %s\n",               \
                a_fixture.name, # function);                                \
        a_fixture.teardown();                                               \
    }

#define NTESTSUITE_FIXTURE(a_name, a_setup, a_teardown)                     \
    static const struct p_ntestsuite_fixture a_name = {                     \
        .name = # a_name,                                                   \
        .setup = a_setup,                                                   \
        .teardown = a_teardown,                                             \
    }

#define P_NTESTSUITE_CMP_PLAIN(a, b)        ((a) != (b))
#define P_NTESTSUITE_CMP_STRING(a, b)       (strlen(a) != strlen(b))

#define P_NTESTSUITE_CNV_BOOL(a_bool)       (a_bool) ? "true" : "false"
#define P_NTESTSUITE_CNV_NONE(a_val)        (a_val)

#define P_NTESTSUITE_PRINT_LOCATION()                                       \
    nlogger_err("Test FAILED at %s() in %s:%u\n",                           \
            NPLATFORM_FUNC, NPLATFORM_FILE,                                 \
            NPLATFORM_LINE);                                                \

#define P_NTESTSUITE_ASSERT_EQUAL(expected, actual, type, format, cnv, compare)\
    do {                                                                    \
        if (p_ntestsuite_context.should_exit) {                             \
            return;                                                         \
        }                                                                   \
        type _expected = (type)(expected);                                  \
        type _actual = (type)(actual);                                      \
        p_ntestsuite_tests++;                                               \
        if (compare((_actual), (_expected))) {                              \
            p_ntestsuite_failed_tests++;                                    \
            P_NTESTSUITE_PRINT_LOCATION();                                  \
            nlogger_err("  Comparing: %s and %s\n", # expected, # actual);  \
            nlogger_err("  Expected : %" # format  "\n  Actual   : %"       \
                    # format "\n", cnv(_expected), cnv(_actual));           \
            p_ntestsuite_context.should_exit = true;                        \
            return;                                                         \
        }                                                                   \
    } while (0)

struct p_ntestsuite_fixture
{
    const char * name;
    void (* setup)(void);
    void (* teardown)(void);
};

struct p_ntestsuite_context
{
    const struct p_ntestsuite_fixture * fixture;
    bool should_exit;
};

extern uint32_t p_ntestsuite_tests;
extern uint32_t p_ntestsuite_failed_tests;
extern struct p_ntestsuite_context p_ntestsuite_context;

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TESTSUITE_H_ */
