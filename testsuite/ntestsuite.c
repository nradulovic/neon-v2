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

#include <string.h>

#include "ntestsuite.h"

struct np_testsuite_context
{
    const struct np_testsuite_test * test;
    struct np_testsuite_fixture
    {
        void (* setup)(void);
        void (* teardown)(void);
        const char * name;
        const char * file;
        uint8_t total;
    } fixture;
    struct np_testsuite_test_case
    {
        union np_testsuite_test_val expected;
        enum np_testsuite_type type;
    } test_case;
    uint16_t total_tests;
};

static struct np_testsuite_context g_np_testsuite_context;

void np_testsuite_print_overview(void)
{
    nlogger_info("\n\r\n\r  Total  %u\n\r", g_np_testsuite_context.total_tests);
}

void np_testsuite_print_results(void)
{
    nlogger_info("  Total  %u\n\r", g_np_testsuite_context.fixture.total);
}

void np_testsuite_set_fixture(
        void (* setup)(void),
        void (* teardown)(void),
        const char * name,
        const char * file)
{
    g_np_testsuite_context.fixture.setup = setup;
    g_np_testsuite_context.fixture.teardown = teardown;
    g_np_testsuite_context.fixture.name = name;
    g_np_testsuite_context.fixture.file = file;
    g_np_testsuite_context.fixture.total = 0u;
}

void np_testsuite_expect(union np_testsuite_test_val value, enum np_testsuite_type type)
{
	g_np_testsuite_context.test_case.type = type;
    g_np_testsuite_context.test_case.expected = value;
}

void np_testsuite_run(const struct np_testsuite_test * test)
{
	g_np_testsuite_context.test = test;
    if (g_np_testsuite_context.fixture.total == 0u) {
        nlogger_info("Test %s:%s\n\r",
                g_np_testsuite_context.fixture.file,
                g_np_testsuite_context.fixture.name);
    }
	g_np_testsuite_context.total_tests++;
	g_np_testsuite_context.fixture.total++;

	if (g_np_testsuite_context.fixture.setup) {
		nlogger_debug("D: Setup fixture %s for test %s.\n\r",
                g_np_testsuite_context.fixture.name,
				test->name);
		g_np_testsuite_context.fixture.setup();
	}
    test->test_fn();
	if (g_np_testsuite_context.fixture.teardown) {
		nlogger_debug("D: Teardown fixture %s for test %s\n\r",
				g_np_testsuite_context.fixture.name,
				test->name);
		g_np_testsuite_context.fixture.teardown();
	}
}

void np_testsuite_actual(uint32_t line, union np_testsuite_test_val actual)
{
    bool should_block = false;

    switch (g_np_testsuite_context.test_case.type) {
        case NP_TESTSUITE_TYPE_BOOL:
            if (actual.b !=
                g_np_testsuite_context.test_case.expected.b) {
                nlogger_err("  Expected: %u\n\r  Actual  : %u\n\r",
                        g_np_testsuite_context.test_case.expected.b,
                        actual.b);
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_UINT:
            if (actual.ui !=
                g_np_testsuite_context.test_case.expected.ui) {
                nlogger_err("  Expected: %u\n\r  Actual  : %u\n\r",
                        g_np_testsuite_context.test_case.expected.ui,
                        actual.ui);
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_INT:
            if (actual.si !=
                g_np_testsuite_context.test_case.expected.si) {
        		nlogger_err("  Expected: %d\n\r  Actual  : %d\n\r",
                        g_np_testsuite_context.test_case.expected.si,
                        actual.si);
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_PTR:
            if (actual.ptr !=
                g_np_testsuite_context.test_case.expected.ptr) {
                nlogger_err("  Expected: %p\n\r  Actual  : %p\n\r",
                        g_np_testsuite_context.test_case.expected.ptr,
                        actual.ptr);
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_STR:
            if (strcmp(actual.str,
                g_np_testsuite_context.test_case.expected.str) != 0) {
                nlogger_err("  Expected : %s\n\r  Actual   : %s\n\r",
                        g_np_testsuite_context.test_case.expected.str,
                        actual.str);
                should_block = true;
            }
            break;
    }
    if (should_block) {
        (void)line; /* Suppress compiler warning when nlogger is not enabled. */
                /*
                 * When nlogger is not enabled, all the arguments which are
                 * normally used by nlogger will not be used. This will make
                 * the compiler complain about unused variables.
                 */
        nlogger_err("Test FAILED at %s() in %s:%u\n\r",
            g_np_testsuite_context.test->name,
            g_np_testsuite_context.fixture.file, line);
        narch_cpu_stop();
    }
}
