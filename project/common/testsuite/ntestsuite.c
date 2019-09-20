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
#include <stdio.h>

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

void ntestsuite_run_tests(ntestsuite_fn * const * array)
{
    while (*array) {
        (*array)();
        array++;
    }
    printf("\nTotal tests: %u\nOK\n\n",
            g_np_testsuite_context.total_tests);
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
        g_np_testsuite_context.fixture.setup();
    }
    test->test_fn();
    if (g_np_testsuite_context.fixture.teardown) {
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
        printf("\nTest FAILED at %s() in %s:%u\n",
                g_np_testsuite_context.test->name,
                g_np_testsuite_context.fixture.name,
                line);
        
        switch (g_np_testsuite_context.test_case.type) {
            case NP_TESTSUITE_TYPE_BOOL:
                printf("Expected: %u\nActual  : %u",
                        g_np_testsuite_context.test_case.expected.b,
                        actual.b);
                break;
            case NP_TESTSUITE_TYPE_UINT:
                printf("Expected: %u\nActual  : %u",
                        g_np_testsuite_context.test_case.expected.ui,
                        actual.ui);
                break;
            case NP_TESTSUITE_TYPE_INT:
                printf("Expected: %d\nActual  : %d",
                        g_np_testsuite_context.test_case.expected.si,
                        actual.si);
                break;
            case NP_TESTSUITE_TYPE_PTR:
                printf("Expected: %p\nActual  : %p",
                        g_np_testsuite_context.test_case.expected.ptr,
                        actual.ptr);
                break;
            case NP_TESTSUITE_TYPE_STR:
                printf("Expected: %s\nActual   : %s",
                        g_np_testsuite_context.test_case.expected.str,
                        actual.str);
                break;
            case NP_TESTSUITE_TYPE_NOT_BOOL:
                printf("Unexpected: %u\nActual    : %u",
                        g_np_testsuite_context.test_case.expected.b,
                        actual.b);
                break;
            case NP_TESTSUITE_TYPE_NOT_UINT:
                printf("Unexpected: %u\nActual    : %u",
                        g_np_testsuite_context.test_case.expected.ui,
                        actual.ui);
                break;
            case NP_TESTSUITE_TYPE_NOT_INT:
                printf("Unexpected: %d\nActual    : %d",
                        g_np_testsuite_context.test_case.expected.si,
                        actual.si);
                break;
            case NP_TESTSUITE_TYPE_NOT_PTR:
                printf("Unexpected: %p\nActual    : %p",
                        g_np_testsuite_context.test_case.expected.ptr,
                        actual.ptr);
                break;
            case NP_TESTSUITE_TYPE_NOT_STR:
                printf("Unexpected: %s\nActual    : %s",
                        g_np_testsuite_context.test_case.expected.str,
                        actual.str);
                break;
        }
	
	while (true) {
		;
	}
    }
}
