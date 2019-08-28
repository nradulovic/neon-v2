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
    } fixture;
    struct np_testsuite_test_case
    {
        union np_testsuite_test_val expected;
        enum np_testsuite_type type;
    } test_case;
    uint16_t total_tests;
};

static struct np_testsuite_context g_np_testsuite_context;


static void print_header(void)
{
    const struct nconfig_entry * entry;
    uint8_t idx;

    nlogger_info("\nBuild info: %s %s (%s - %s)\n",
            nsys_platform_id,
			nsys_platform_version,
            nsys_build_date,
            nsys_build_time);

    idx = 0u;

    while ((entry = nconfig_record_fetch(idx++))) {
        nlogger_info("%s: %u\n", entry->name, entry->value);
    }
    nlogger_flush();
}

static void print_overview(void)
{
    nlogger_info("\nTotal tests: %u\nOK\n\n",
            g_np_testsuite_context.total_tests);
    nlogger_flush();
}

void ntestsuite_run_tests(ntestsuite_fn * const * array)
{
	nboard_init();
	print_header();

	while (*array) {
		(*array)();
		array++;
	}
	print_overview();
}

void np_testsuite_set_fixture(
        void (* setup)(void),
        void (* teardown)(void),
        const char * name)
{
    g_np_testsuite_context.fixture.setup = setup;
    g_np_testsuite_context.fixture.teardown = teardown;
    g_np_testsuite_context.fixture.name = name;
}

void np_testsuite_expect(
        union np_testsuite_test_val value, 
        enum np_testsuite_type type)
{
	g_np_testsuite_context.test_case.type = type;
    g_np_testsuite_context.test_case.expected = value;
}

void np_testsuite_run(const struct np_testsuite_test * test)
{
	g_np_testsuite_context.test = test;
	g_np_testsuite_context.total_tests++;

	if (g_np_testsuite_context.fixture.setup) {
		nlogger_debug("D: Setup fixture %s for test %s\n",
                g_np_testsuite_context.fixture.name,
				test->name);
		g_np_testsuite_context.fixture.setup();
	}
    test->test_fn();
	if (g_np_testsuite_context.fixture.teardown) {
		nlogger_debug("D: Teardown fixture %s for test %s\n",
				g_np_testsuite_context.fixture.name,
				test->name);
		g_np_testsuite_context.fixture.teardown();
	}
}

void np_testsuite_actual(uint32_t line, union np_testsuite_test_val actual)
{
    bool should_block = false;
    
    /* In case logging is disabled we need to tell compiler not to warn us 
     * about unused argument.
     */
    NPLATFORM_UNUSED_ARG(line); 

    switch (g_np_testsuite_context.test_case.type) {
        case NP_TESTSUITE_TYPE_BOOL:
            if (actual.b !=
                g_np_testsuite_context.test_case.expected.b) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_UINT:
            if (actual.ui !=
                g_np_testsuite_context.test_case.expected.ui) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_INT:
            if (actual.si !=
                g_np_testsuite_context.test_case.expected.si) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_PTR:
            if (actual.ptr !=
                g_np_testsuite_context.test_case.expected.ptr) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_STR:
            if (strcmp(actual.str,
                g_np_testsuite_context.test_case.expected.str) != 0) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_NOT_BOOL:
            if (actual.b ==
                g_np_testsuite_context.test_case.expected.b) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_NOT_UINT:
            if (actual.ui ==
                g_np_testsuite_context.test_case.expected.ui) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_NOT_INT:
            if (actual.si ==
                g_np_testsuite_context.test_case.expected.si) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_NOT_PTR:
            if (actual.ptr ==
                g_np_testsuite_context.test_case.expected.ptr) {
                should_block = true;
            }
            break;
        case NP_TESTSUITE_TYPE_NOT_STR:
            if (strcmp(actual.str,
                g_np_testsuite_context.test_case.expected.str) == 0) {
                should_block = true;
            }
            break;
    }
    
    if (should_block) {
        nlogger_err("\nTest FAILED at %s() in %s:%u\n",
                g_np_testsuite_context.test->name,
                g_np_testsuite_context.fixture.name,
                line);
        
        switch (g_np_testsuite_context.test_case.type) {
            case NP_TESTSUITE_TYPE_BOOL:
                nlogger_err("Expected: %u\nActual  : %u",
                        g_np_testsuite_context.test_case.expected.b,
                        actual.b);
                break;
            case NP_TESTSUITE_TYPE_UINT:
                nlogger_err("Expected: %u\nActual  : %u",
                        g_np_testsuite_context.test_case.expected.ui,
                        actual.ui);
                break;
            case NP_TESTSUITE_TYPE_INT:
                nlogger_err("Expected: %d\nActual  : %d",
                        g_np_testsuite_context.test_case.expected.si,
                        actual.si);
                break;
            case NP_TESTSUITE_TYPE_PTR:
                nlogger_err("Expected: %p\nActual  : %p",
                        g_np_testsuite_context.test_case.expected.ptr,
                        actual.ptr);
                break;
            case NP_TESTSUITE_TYPE_STR:
                nlogger_err("Expected: %s\nActual   : %s",
                        g_np_testsuite_context.test_case.expected.str,
                        actual.str);
                break;
            case NP_TESTSUITE_TYPE_NOT_BOOL:
                nlogger_err("Unexpected: %u\nActual    : %u",
                        g_np_testsuite_context.test_case.expected.b,
                        actual.b);
                break;
            case NP_TESTSUITE_TYPE_NOT_UINT:
                nlogger_err("Unexpected: %u\nActual    : %u",
                        g_np_testsuite_context.test_case.expected.ui,
                        actual.ui);
                break;
            case NP_TESTSUITE_TYPE_NOT_INT:
                nlogger_err("Unexpected: %d\nActual    : %d",
                        g_np_testsuite_context.test_case.expected.si,
                        actual.si);
                break;
            case NP_TESTSUITE_TYPE_NOT_PTR:
                nlogger_err("Unexpected: %p\nActual    : %p",
                        g_np_testsuite_context.test_case.expected.ptr,
                        actual.ptr);
                break;
            case NP_TESTSUITE_TYPE_NOT_STR:
                nlogger_err("Unexpected: %s\nActual    : %s",
                        g_np_testsuite_context.test_case.expected.str,
                        actual.str);
                break;
        }
        nlogger_flush();
        narch_cpu_stop();
    }
}
