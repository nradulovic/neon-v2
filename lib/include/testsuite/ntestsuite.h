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

#include "port/nport_platform.h"
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
    p_ntestsuite_context.total_asserts++;                                   \
    if (!(expr)) {                                                          \
        p_ntestsuite_context.should_exit = true;                            \
        nlogger_debug("D: Failed assert %s\n", # expr);                     \
        return;                                                             \
    }

#define NTESTSUITE_PRINT_RESULTS(a_fixture)                                 \
    if (a_fixture.failed != 0u) {                                           \
        nlogger_info("  Total  %u\n  FAILED %u\n",                          \
            a_fixture.total, a_fixture.failed);                             \
    } else {                                                                \
        nlogger_info("  Total %u  OK\n", a_fixture.total);                  \
    }

#define NTESTSUITE_PRINT_HEADER()                                           \
    nlogger_info("Build info: %s - %s\n", NPLATFORM_DATE, NPLATFORM_TIME);  \
    nlogger_info("Port platform ID: %s\n", nplatform_id);                   \
    nlogger_info("Port platform build: %s\n", nplatform_build);

#define NTESTSUITE_PRINT_OVERVIEW()                                         \
    if (p_ntestsuite_context.total_failed_tests != 0u) {                    \
        nlogger_info("\n\n  Total tests  : %u\n  Total FAILED : %u\n"       \
            "  Total asserts: %u\n",                                        \
            p_ntestsuite_context.total_tests,                               \
            p_ntestsuite_context.total_failed_tests,                        \
            p_ntestsuite_context.total_asserts);                            \
    } else {                                                                \
        nlogger_info("\n\n  Total tests  : %u\n"                            \
            "  Total asserts: %u\n\n  OK\n",                                \
            p_ntestsuite_context.total_tests,                               \
            p_ntestsuite_context.total_asserts);                            \
    }


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
    if (p_ntestsuite_context.fixture->total == 0u) {                        \
        nlogger_info("Test (%s) %s:%s\n",                                   \
            a_fixture.name, NPLATFORM_FILE, NPLATFORM_FUNC);                \
    }                                                                       \
    p_ntestsuite_context.should_exit = false;                               \
    p_ntestsuite_context.total_tests++;                                     \
    p_ntestsuite_context.fixture->total++;                                  \
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
    if (p_ntestsuite_context.should_exit) {                                 \
        p_ntestsuite_context.total_failed_tests++;                          \
        p_ntestsuite_context.fixture->failed++;                             \
    }                                                                       \
    if (a_fixture.teardown) {                                               \
        nlogger_debug("D: Teardown fixture %s for test %s\n",               \
                a_fixture.name, # function);                                \
        a_fixture.teardown();                                               \
    }

#define NTESTSUITE_FIXTURE(a_name, a_setup, a_teardown)                     \
    struct p_ntestsuite_fixture a_name = {                                  \
        .name = # a_name,                                                   \
        .setup = a_setup,                                                   \
        .teardown = a_teardown,                                             \
        .total = 0u,                                                        \
        .failed = 0u,                                                       \
    }

#define P_NTESTSUITE_CMP_PLAIN(a, b)        ((a) != (b))
#define P_NTESTSUITE_CMP_STRING(a, b)       (strlen(a) != strlen(b))

#define P_NTESTSUITE_CNV_BOOL(a_bool)       (a_bool) ? "true" : "false"
#define P_NTESTSUITE_CNV_NONE(a_val)        (a_val)

#define P_NTESTSUITE_PRINT_LOCATION()                                       \
    nlogger_err("Test FAILED at %s() in %s:%u\n",                           \
            NPLATFORM_FUNC, NPLATFORM_FILE,                                 \
            NPLATFORM_LINE);                                                \

#define P_NTESTSUITE_ASSERT_EQUAL(expect, actual, type, format, cnv, compare)\
    do {                                                                    \
        if (p_ntestsuite_context.should_exit) {                             \
            return;                                                         \
        }                                                                   \
        type _expected = (type)(expect);                                    \
        type _actual = (type)(actual);                                      \
        p_ntestsuite_context.total_asserts++;                              \
        if (compare((_actual), (_expected))) {                              \
            P_NTESTSUITE_PRINT_LOCATION();                                  \
            nlogger_err("  Comparing: %s and %s\n", # expect, # actual);    \
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
    uint32_t total;
    uint32_t failed;
};

struct p_ntestsuite_context
{
    struct p_ntestsuite_fixture * fixture;
    uint32_t total_tests;
    uint32_t total_failed_tests;
    uint32_t total_asserts;
    bool should_exit;
};

extern struct p_ntestsuite_context p_ntestsuite_context;

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TESTSUITE_H_ */
