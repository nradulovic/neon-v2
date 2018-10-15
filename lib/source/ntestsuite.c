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

#include "testsuite/ntestsuite.h"

struct np_testsuite_context
{
    const struct np_testsuite_test * test;
    struct np_testsuite_test_case
    {
        union np_testsuite_test_val expected;
        enum np_testsuite_type type;
    } test_case;
#if (!NTESTSUITE_STOP_ON_ERROR)
    uint16_t total_tests;
    uint16_t total_failed_tests;
    bool should_exit;
#endif
};

static struct np_testsuite_context g_np_testsuite_context;

#if (!NTESTSUITE_STOP_ON_ERROR)
static void testsuite_test_failed(uint32_t line)
{
    (void)line; /* Suppress compiler warning when nlogger is not enabled. */
                /*
                 * When nlogger is not enabled, all the arguments which are 
                 * normally used by nlogger will not be used. This will make
                 * the compiler complain about unused variables.
                 */
    nlogger_err("Test FAILED at %s() in %s:%u\n", 
        g_np_testsuite_context.test->name, 
        g_np_testsuite_context.test->file, line);
}
#endif

#if (!NTESTSUITE_STOP_ON_ERROR)
void np_testsuite_print_overview(void)
{
	if (g_np_testsuite_context.total_failed_tests != 0u) {
		nlogger_info("\n\n  Total tests  : %u\n  Total FAILED : %u\n",
			g_np_testsuite_context.total_tests,
			g_np_testsuite_context.total_failed_tests);
	} else {
		nlogger_info("\n\n  Total tests  : %u\n",
			g_np_testsuite_context.total_tests);
	}
}
#endif

#if (!NTESTSUITE_STOP_ON_ERROR)
void np_testsuite_print_results(const struct np_testsuite_fixture * fixture)
{
	if (fixture->failed != 0u) {
		nlogger_info("  Total  %u\n  FAILED %u\n", fixture->total,
				fixture->failed);
	} else {
		nlogger_info("  Total %u  OK\n", fixture->total);
	}
}
#endif

void np_testsuite_expect(union np_testsuite_test_val value, enum np_testsuite_type type)
{
	g_np_testsuite_context.test_case.type = type;
    g_np_testsuite_context.test_case.expected = value;
}

void np_testsuite_run(struct np_testsuite_fixture * fixture,
		const struct np_testsuite_test * test)
{
	g_np_testsuite_context.test = test;
#if (!NTESTSUITE_STOP_ON_ERROR)
	g_np_testsuite_context.should_exit = false;
    if (fixture->total == 0u) {
        nlogger_info("Test %s:%s\n", test->file, fixture->name);
    }
	g_np_testsuite_context.total_tests++;
	fixture->total++;
#endif

	if (fixture->setup) {
		nlogger_debug("D: Setup fixture %s for test %s.\n", fixture->name,
				test->name);
		fixture->setup();
	}
    test->test_fn();
#if (!NTESTSUITE_STOP_ON_ERROR)
	if (g_np_testsuite_context.should_exit == true) {
		g_np_testsuite_context.total_failed_tests++;
		fixture->failed++;
	}
#endif
	if (fixture->teardown) {
		nlogger_debug("D: Teardown fixture %s for test %s\n",
				fixture->name,
				test->name);
		fixture->teardown();
	}
}

bool np_testsuite_actual(uint32_t line, union np_testsuite_test_val actual)
{
	bool retval = false;

#if (NTESTSUITE_STOP_ON_ERROR)
    (void)line;
#endif
    switch (g_np_testsuite_context.test_case.type) {
        case NP_TESTSUITE_TYPE_BOOL:
            if (actual.b !=
                g_np_testsuite_context.test_case.expected.b) {
#if (!NTESTSUITE_STOP_ON_ERROR)
                testsuite_test_failed(line);
#endif
		        nlogger_err("  Expected : %s\n"
                            "  Actual   : %s\n",
                            g_np_testsuite_context.test_case.expected.b ?
                                "true" : "false",
                            actual.b ?
                                "true" : "false");
		        retval = true;
            }
            break;
        case NP_TESTSUITE_TYPE_UINT:
            if (actual.ui !=
                g_np_testsuite_context.test_case.expected.ui) {
#if (!NTESTSUITE_STOP_ON_ERROR)
                testsuite_test_failed(line);
#endif
		        nlogger_err("  Expected : %u\n"
                            "  Actual   : %u\n",
                            g_np_testsuite_context.test_case.expected.ui,
                            actual.ui);
		        retval = true;
            }
            break;
        case NP_TESTSUITE_TYPE_INT:
            if (actual.si !=
                g_np_testsuite_context.test_case.expected.si) {
#if (!NTESTSUITE_STOP_ON_ERROR)
                testsuite_test_failed(line);
#endif
		        nlogger_err("  Expected : %d\n"
                            "  Actual   : %d\n",
                            g_np_testsuite_context.test_case.expected.si,
                            actual.si);
		        retval = true;
            }
            break;
        case NP_TESTSUITE_TYPE_PTR:
            if (actual.ptr !=
                g_np_testsuite_context.test_case.expected.ptr) {
#if (!NTESTSUITE_STOP_ON_ERROR)
                testsuite_test_failed(line);
#endif
		        nlogger_err("  Expected : %p\n"
                            "  Actual   : %p\n",
                            g_np_testsuite_context.test_case.expected.ptr,
                            actual.ptr);
		        retval = true;
            }
            break;
    }
#if (!NTESTSUITE_STOP_ON_ERROR)
    g_np_testsuite_context.should_exit = retval;
#endif
    return retval;
}
