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
    NP_TESTSUITE_ASSERT_EQUAL(expected, actual, int32_t, d,                 \
            NP_TESTSUITE_CNV_NONE, NP_TESTSUITE_CMP_PLAIN)

#define NTESTSUITE_ASSERT_EQUAL_UINT(expected, actual)                      \
    NP_TESTSUITE_ASSERT_EQUAL(expected, actual, uint32_t, u,                \
            NP_TESTSUITE_CNV_NONE, NP_TESTSUITE_CMP_PLAIN)

#define NTESTSUITE_ASSERT_EQUAL_PTR(expected, actual)                       \
    NP_TESTSUITE_ASSERT_EQUAL(expected, actual, void *, p,                  \
            NP_TESTSUITE_CNV_NONE, NP_TESTSUITE_CMP_PLAIN)

#define NTESTSUITE_ASSERT_EQUAL_BOOL(expected, actual)                      \
    NP_TESTSUITE_ASSERT_EQUAL(expected, actual, bool, s,                    \
            NP_TESTSUITE_CNV_BOOL, NP_TESTSUITE_CMP_PLAIN)

#define NTESTSUITE_ASSERT_EQUAL_STRING(expected, actual)                    \
    NP_TESTSUITE_ASSERT_EQUAL(expected, actual, const char *, s,            \
            NP_TESTSUITE_CNV_NONE, NP_TESTSUITE_CMP_STRING)

#define NTESTSUITE_RUN(a_fixture, function)                                 \
    p_ntestsuite_context.fixture = &a_fixture;                              \
    if (p_ntestsuite_context.fixture->total == 0u) {                        \
        nlogger_info("Test %s:%s:%s\n",                                     \
            NPLATFORM_FILE, NPLATFORM_FUNC, a_fixture.name);                \
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

#define NTESTSUITE_ERROR(fmt, ...)                                          \
    do {                                                                    \
        NP_TESTSUITE_PRINT_LOCATION();                                      \
        nlogger_err(fmt "\n", __VA_ARGS__);                                 \
        p_ntestsuite_context.should_exit = true;                            \
        return;                                                             \
    } while (0)

#define NTESTSUITE_EXPECT_UINT(a_number)                                    \
    do {                                                                    \
        p_ntestsuite_context.test_case.expected.ui = (a_number);                               \
        p_ntestsuite_context.test_case.actual.ui = ~(a_number);                                \
        p_ntestsuite_context.test_case.type = TEST_CASE_UINT;                                  \
    } while (0u)

#define NTESTSUITE_EXPECT_INT(a_number)                                     \
    do {                                                                    \
        p_ntestsuite_context.test_case.expected.i = (a_number);                                \
        p_ntestsuite_context.test_case.actual.i = ~(a_number);                                 \
        p_ntestsuite_context.test_case.type = TEST_CASE_INT;                                   \
    } while (0u)

#define NTESTSUITE_EXPECT_PTR(a_pointer)                                    \
    do {                                                                    \
        p_ntestsuite_context.test_case.expected.ptr = (a_pointer);                             \
        p_ntestsuite_context.test_case.actual.ptr = NULL;                                      \
        p_ntestsuite_context.test_case.type = TEST_CASE_PTR;                                   \
    } while (0u)

#define NTESTSUITE_EXPECT_BOOL(a_bool)                                      \
    do {                                                                    \
        p_ntestsuite_context.test_case.expected.b = (a_bool);                                  \
        p_ntestsuite_context.test_case.actual.b = !(a_bool);                                   \
        p_ntestsuite_context.test_case.type = TEST_CASE_BOOL;                                  \
    } while (0u)
    
#define NTESTSUITE_ACTUAL_UINT(a_val)                                       \
    do {                                                                    \
        NP_TESTSUITE_TEST_CASE_VALIDATE_TYPE(TEST_CASE_UINT);                                    \
        p_ntestsuite_context.test_case.actual.ui = (a_val);                                    \
    } while (0)

#define NTESTSUITE_ACTUAL_INT(a_val)                                        \
    do {                                                                    \
        NP_TESTSUITE_TEST_CASE_VALIDATE_TYPE(TEST_CASE_INT);                                     \
        p_ntestsuite_context.test_case.actual.i = (a_val);                                     \
    } while (0)
                
#define NTESTSUITE_ACTUAL_PTR(a_val)                                        \
    do {                                                                    \
        NP_TESTSUITE_TEST_CASE_VALIDATE_TYPE(TEST_CASE_PTR);                                     \
        p_ntestsuite_context.test_case.actual.ptr = (a_val);                                   \
    } while (0)

#define NTESTSUITE_ACTUAL_BOOL(a_val)                                       \
    do {                                                                    \
        NP_TESTSUITE_TEST_CASE_VALIDATE_TYPE(TEST_CASE_BOOL);                                    \
        p_ntestsuite_context.test_case.actual.b = (a_val);                                     \
    } while (0)

#define NTESTSUITE_EVALUATE()                                               \
    do {                                                                    \
        switch (p_ntestsuite_context.test_case.type) {                                         \
            case TEST_CASE_UINT:                                            \
                NTESTSUITE_ASSERT_EQUAL_UINT(p_ntestsuite_context.test_case.expected.ui,       \
                        p_ntestsuite_context.test_case.actual.ui);                             \
                break;                                                      \
            case TEST_CASE_INT:                                             \
                NTESTSUITE_ASSERT_EQUAL_INT(p_ntestsuite_context.test_case.expected.i,         \
                        p_ntestsuite_context.test_case.actual.i);                              \
                break;                                                      \
            case TEST_CASE_PTR:                                             \
                NTESTSUITE_ASSERT_EQUAL_PTR(p_ntestsuite_context.test_case.expected.ptr,       \
                        p_ntestsuite_context.test_case.actual.ptr);                            \
                break;                                                      \
            case TEST_CASE_BOOL:                                            \
                NTESTSUITE_ASSERT_EQUAL_BOOL(p_ntestsuite_context.test_case.expected.b,        \
                        p_ntestsuite_context.test_case.actual.b);                              \
                break;                                                      \
        }                                                                   \
    } while (0)

#define NP_TESTSUITE_CMP_PLAIN(a, b)        ((a) != (b))
#define NP_TESTSUITE_CMP_STRING(a, b)       (strlen(a) != strlen(b))

#define NP_TESTSUITE_CNV_BOOL(a_bool)       (a_bool) ? "true" : "false"
#define NP_TESTSUITE_CNV_NONE(a_val)        (a_val)

#define NP_TESTSUITE_PRINT_LOCATION()                                       \
    nlogger_err("Test FAILED at %s() in %s:%u\n",                           \
            NPLATFORM_FUNC, NPLATFORM_FILE,                                 \
            NPLATFORM_LINE);                                                \

#define NP_TESTSUITE_ASSERT_EQUAL(expect, actual, type, format, cnv, compare)\
    do {                                                                    \
        if (p_ntestsuite_context.should_exit) {                             \
            return;                                                         \
        }                                                                   \
        type _expected = (type)(expect);                                    \
        type _actual = (type)(actual);                                      \
        p_ntestsuite_context.total_asserts++;                               \
        if (compare((_actual), (_expected))) {                              \
            NTESTSUITE_ERROR(                                               \
                "  Expected : %" #format "\n  Actual   : %" #format "\n",   \
                cnv(_expected), cnv(_actual));                              \
            NP_TESTSUITE_PRINT_LOCATION();                                  \
        }                                                                   \
    } while (0)

#define NP_TESTSUITE_TEST_CASE_VALIDATE_TYPE(a_type)                        \
    if (p_ntestsuite_context.test_case.type != (a_type)) {                  \
        const char * expected_type;                                         \
        switch (p_ntestsuite_context.test_case.type) {                      \
            case TEST_CASE_UINT:                                            \
                expected_type = "TEST_CASE_UINT";                           \
                break;                                                      \
            case TEST_CASE_INT:                                             \
                expected_type = "TEST_CASE_INT";                            \
                break;                                                      \
            case TEST_CASE_PTR:                                             \
                expected_type = "TEST_CASE_PTR";                            \
                break;                                                      \
            case TEST_CASE_BOOL:                                            \
                expected_type = "TEST_CASE_BOOL";                           \
                break;                                                      \
        }                                                                   \
        NTESTSUITE_ERROR("MACRO TYPE MISMATCH!\n"                           \
            "  Expected type (%s)\n"                                        \
            "  Actual   type (%s)",                                         \
            expected_type, # a_type);                                       \
    }


enum p_ntestsuite_test_case_type
{
    TEST_CASE_UINT,
    TEST_CASE_INT,
    TEST_CASE_PTR,
    TEST_CASE_BOOL
};

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
    struct p_ntestsuite_test_case
    {
        union test_val
        {
            uint32_t ui;
            int32_t i;
            void * ptr;
            bool b;
        } actual, expected;
        enum p_ntestsuite_test_case_type type;
    } test_case;
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
