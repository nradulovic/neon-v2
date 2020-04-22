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
#include <stdbool.h>

#include "nport_platform.h"
#include "nk_arch.h"
#include "nlogger.h"

#if defined(NEON_APP_CONFIG)
#include "neon_app_config.h"
#else
#include "default_config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define NTESTSUITE_PRINT_RESULTS(a_fixture)                                 \
	np_testsuite_print_results(&(a_fixture))

#define NTESTSUITE_PRINT_OVERVIEW()                                         \
	np_testsuite_print_overview()

#define NTESTSUITE_PRINT_HEADER()                                           \
    nlogger_info("Build info: %s - %s\n", NPLATFORM_DATE, NPLATFORM_TIME);  \
    nlogger_info("Port platform ID: %s\n", nplatform_id);                   \
    nlogger_info("Port platform build: %s\n", nplatform_build);


#define NTESTSUITE_EXPECT_UINT(a_number)                                    \
    do {\
        union np_testsuite_test_val val; \
        val.ui = (a_number); \
        np_testsuite_expect(val, NP_TESTSUITE_TYPE_UINT); \
    } while (0)

#define NTESTSUITE_EXPECT_INT(a_number)                                     \
    do {\
        union np_testsuite_test_val val; \
        val.si = (a_number); \
	    np_testsuite_expect(val, NP_TESTSUITE_TYPE_INT); \
    } while (0)

#define NTESTSUITE_EXPECT_PTR(a_pointer)                                    \
    do {\
        union np_testsuite_test_val val; \
        val.ptr = (a_pointer); \
        np_testsuite_expect(val, NP_TESTSUITE_TYPE_PTR); \
    } while (0)

#define NTESTSUITE_EXPECT_BOOL(a_bool)                                      \
    do {\
        union np_testsuite_test_val val; \
        val.b = (a_bool); \
	    np_testsuite_expect(val, NP_TESTSUITE_TYPE_BOOL); \
    } while (0)
    
#define NTESTSUITE_ACTUAL_UINT(a_number)                                       \
    do {\
        union np_testsuite_test_val val; \
        val.ui = (a_number); \
	    NP_TESTSUITE_EVALUATE(val); \
    } while (0)

#define NTESTSUITE_ACTUAL_INT(a_number)                                        \
    do {\
        union np_testsuite_test_val val; \
        val.si = (a_number); \
	    NP_TESTSUITE_EVALUATE(val); \
    } while (0)
                
#define NTESTSUITE_ACTUAL_PTR(a_pointer)                                        \
    do {\
        union np_testsuite_test_val val; \
        val.ptr = (a_pointer); \
        NP_TESTSUITE_EVALUATE(val); \
    } while (0)

#define NTESTSUITE_ACTUAL_BOOL(a_bool)                                       \
    do {\
        union np_testsuite_test_val val; \
        val.b = (a_bool); \
        NP_TESTSUITE_EVALUATE(val); \
    } while (0)

#if (!NTESTSUITE_STOP_ON_ERROR)
#define NTESTSUITE_FIXTURE(a_name, a_setup, a_teardown)                     \
    struct np_testsuite_fixture a_name = {                                  \
        .setup = a_setup,                                                   \
        .teardown = a_teardown,                                             \
        .name = # a_name,                                                   \
        .total = 0u,                                                        \
        .failed = 0u,                                                       \
    }
#else
#define NTESTSUITE_FIXTURE(a_name, a_setup, a_teardown)                     \
    struct np_testsuite_fixture a_name = {                                  \
        .setup = a_setup,                                                   \
        .teardown = a_teardown,                                             \
    }
#endif

#define NTESTSUITE_EVALUATE()
    
#if (!NTESTSUITE_STOP_ON_ERROR)
#define NP_TESTSUITE_EVALUATE(val)                                               \
        if (np_testsuite_actual(NPLATFORM_LINE, (val))) { \
            return; \
        }
#else
#define NP_TESTSUITE_EVALUATE(val)                                               \
        if (np_testsuite_actual(NPLATFORM_LINE, (val))) { \
            narch_cpu_stop(); \
        }
#endif

enum np_testsuite_type
{
    NP_TESTSUITE_TYPE_UINT,
    NP_TESTSUITE_TYPE_INT,
    NP_TESTSUITE_TYPE_PTR,
    NP_TESTSUITE_TYPE_BOOL
};

struct np_testsuite_fixture
{
    void (* setup)(void);
    void (* teardown)(void);
    const char * name;
    uint8_t total;
    uint8_t failed;
};

#define NTESTSUITE_TEST(test_name) \
static void test_name(void); \
static struct np_testsuite_test testsuite_ ## test_name = { \
	.test_fn = test_name, \
	.name = # test_name, \
	.file = NPLATFORM_FILE, \
};\
static void test_name(void)

struct np_testsuite_test
{
	void (*test_fn)(void);
	const char * name;
	const char * file;
};

union np_testsuite_test_val
{
	uint32_t ui;
	int32_t si;
	void * ptr;
	bool b;
};

#define NTESTSUITE_RUN(fixture, test) \
		np_testsuite_run(&(fixture), &(testsuite_ ## test))

void np_testsuite_print_overview(void);

void np_testsuite_print_results(const struct np_testsuite_fixture * fixture);

void np_testsuite_run(struct np_testsuite_fixture * fixture,
		const struct np_testsuite_test * test);
void np_testsuite_expect(union np_testsuite_test_val value, enum np_testsuite_type type);

bool np_testsuite_actual(uint32_t line, union np_testsuite_test_val value);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TESTSUITE_H_ */
