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

enum np_testsuite_state
{
    NP_TESTSUITE_STATE_INIT,
    NP_TESTSUITE_STATE_EXPECT,
    NP_TESTSUITE_STATE_ACTUAL,
    NP_TESTSUITE_STATE_EVALUATE,
};

struct np_testsuite_context
{
    struct np_testsuite_fixture * fixture;
    const struct np_testsuite_test * test;
    struct np_testsuite_test_case
    {
        union np_testsuite_test_val actual;
        union np_testsuite_test_val expected;
        enum np_testsuite_type type;
    } test_case;
    enum np_testsuite_state state;
    uint32_t total_tests;
    uint32_t total_failed_tests;
    uint32_t total_asserts;
    bool should_exit;
};

static struct np_testsuite_context g_np_testsuite_context;

static void testsuite_test_failed(uint32_t line)
{
    nlogger_err("Test FAILED at %s() in %s:%u\n", 
        g_np_testsuite_context.test->name, 
        g_np_testsuite_context.test->file, line);
}

void np_testsuite_print_overview(void)
{
	if (g_np_testsuite_context.total_failed_tests != 0u) {
		nlogger_info("\n\n  Total tests  : %u\n  Total FAILED : %u\n"
			"  Total asserts: %u\n",
			g_np_testsuite_context.total_tests,
			g_np_testsuite_context.total_failed_tests,
			g_np_testsuite_context.total_asserts);
	} else {
		nlogger_info("\n\n  Total tests  : %u\n"
			"  Total asserts: %u\n\n  OK\n",
			g_np_testsuite_context.total_tests,
			g_np_testsuite_context.total_asserts);
	}
}

bool np_testsuite_expect(union np_testsuite_test_val * value, enum np_testsuite_type type, uint32_t line)
{
	if ((g_np_testsuite_context.state != NP_TESTSUITE_STATE_INIT) &&
		(g_np_testsuite_context.state != NP_TESTSUITE_STATE_EVALUATE)) {
        testsuite_test_failed(line);
		nlogger_err("%s\n", "Didn't finish previous evaluation.");
		g_np_testsuite_context.should_exit = true;
		return true;
	}
	g_np_testsuite_context.state = NP_TESTSUITE_STATE_EXPECT;
	g_np_testsuite_context.test_case.type = type;

	switch (type) {
        case NP_TESTSUITE_TYPE_BOOL:
            g_np_testsuite_context.test_case.expected.b = value->b;
            g_np_testsuite_context.test_case.actual.b = !value->b;
            break;
        case NP_TESTSUITE_TYPE_UINT:
            g_np_testsuite_context.test_case.expected.ui = value->ui;
            g_np_testsuite_context.test_case.actual.ui = ~value->ui;
            break;
        case NP_TESTSUITE_TYPE_INT:
            g_np_testsuite_context.test_case.expected.si = value->si;
            g_np_testsuite_context.test_case.actual.si = ~value->si;
            break;
        case NP_TESTSUITE_TYPE_PTR:
            g_np_testsuite_context.test_case.expected.ptr = value->ptr;
            g_np_testsuite_context.test_case.actual.ptr = NULL;
            break;
	}
	return false;
}

bool np_testsuite_actual(union np_testsuite_test_val * value, enum np_testsuite_type type, uint32_t line)
{
    if (g_np_testsuite_context.state != NP_TESTSUITE_STATE_EXPECT) {
        testsuite_test_failed(line);
		nlogger_err("%s\n", "Didn't specified the expected value.");
		g_np_testsuite_context.should_exit = true;
		return true;
    }

    if (g_np_testsuite_context.test_case.type != type) {
        const char * expected_type;
        switch (g_np_testsuite_context.test_case.type) {
            case NP_TESTSUITE_TYPE_BOOL:
                expected_type = "NP_TESTSUITE_TYPE_BOOL";
                break;
            case NP_TESTSUITE_TYPE_UINT:
                expected_type = "NP_TESTSUITE_TYPE_UINT";
                break;
            case NP_TESTSUITE_TYPE_INT:
                expected_type = "NP_TESTSUITE_TYPE_INT";
                break;
            case NP_TESTSUITE_TYPE_PTR:
                expected_type = "NP_TESTSUITE_TYPE_PTR";
                break;
        }
        testsuite_test_failed(line);
		nlogger_err("MACRO TYPE MISMATCH!\n"
            "  Expected type (%s)\n"
            "  Actual   type (%s)\n", expected_type, type);
		g_np_testsuite_context.should_exit = true;
		return true;
    }
    g_np_testsuite_context.state = NP_TESTSUITE_STATE_ACTUAL;

	switch (type) {
        case NP_TESTSUITE_TYPE_BOOL:
            g_np_testsuite_context.test_case.actual.b = value->b;
            break;
        case NP_TESTSUITE_TYPE_UINT:
            g_np_testsuite_context.test_case.actual.ui = value->ui;
            break;
        case NP_TESTSUITE_TYPE_INT:
            g_np_testsuite_context.test_case.actual.si = value->si;
            break;
        case NP_TESTSUITE_TYPE_PTR:
            g_np_testsuite_context.test_case.actual.ptr = value->ptr;
            break;
	}
    return false;
}

void np_testsuite_run(struct np_testsuite_fixture * fixture,
		const struct np_testsuite_test * test)
{
	if (fixture->total == 0u) {
		nlogger_info("Test %s:%s:%s\n", test->file, test->name, fixture->name);
	}
	g_np_testsuite_context.should_exit = false;
	g_np_testsuite_context.total_tests++;
	g_np_testsuite_context.fixture = fixture;
	g_np_testsuite_context.fixture->total++;
	g_np_testsuite_context.test = test;

	if (fixture->setup) {
		nlogger_debug("D: Setup fixture %s for test %s.\n", fixture->name,
				test->name);
		fixture->setup();
	}
    test->test_fn();
	if (g_np_testsuite_context.should_exit == true) {
		g_np_testsuite_context.total_failed_tests++;
		g_np_testsuite_context.fixture->failed++;
	}
	if (fixture->teardown) {
		nlogger_debug("D: Teardown fixture %s for test %s\n",
				fixture->name,
				test->name);
		fixture->teardown();
	}
}

void np_testsuite_print_results(const struct np_testsuite_fixture * fixture)
{
	if (fixture->failed != 0u) {
		nlogger_info("  Total  %u\n  FAILED %u\n", fixture->total,
				fixture->failed);
	} else {
		nlogger_info("  Total %u  OK\n", fixture->total);
	}
}

bool np_testsuite_evaluate(uint32_t line)
{
    if (g_np_testsuite_context.state != NP_TESTSUITE_STATE_ACTUAL) {
        testsuite_test_failed(line);
		nlogger_err("%s\n", "Didn't specified the actual value.");
		g_np_testsuite_context.should_exit = true;
		return true;
    }
    g_np_testsuite_context.state = NP_TESTSUITE_STATE_EVALUATE;
    g_np_testsuite_context.total_asserts++;

    switch (g_np_testsuite_context.test_case.type) {
        case NP_TESTSUITE_TYPE_BOOL:
            if (g_np_testsuite_context.test_case.actual.b !=
                g_np_testsuite_context.test_case.expected.b) {
                testsuite_test_failed(line);
		        nlogger_err("  Expected : %s\n"
                            "  Actual   : %s\n", 
                            g_np_testsuite_context.test_case.expected.b ?
                                "true" : "false",
                            g_np_testsuite_context.test_case.actual.b ?
                                "true" : "false");
                return true;
            }
            break;
        case NP_TESTSUITE_TYPE_UINT:
            if (g_np_testsuite_context.test_case.actual.ui !=
                g_np_testsuite_context.test_case.expected.ui) {
                testsuite_test_failed(line);
		        nlogger_err("  Expected : %u\n"
                            "  Actual   : %u\n", 
                            g_np_testsuite_context.test_case.expected.ui,
                            g_np_testsuite_context.test_case.actual.ui);
                return true;
            }
            break;
        case NP_TESTSUITE_TYPE_INT:
            if (g_np_testsuite_context.test_case.actual.si !=
                g_np_testsuite_context.test_case.expected.si) {
                testsuite_test_failed(line);
		        nlogger_err("  Expected : %d\n"
                            "  Actual   : %d\n", 
                            g_np_testsuite_context.test_case.expected.si,
                            g_np_testsuite_context.test_case.actual.si);
                return true;
            }
            break;
        case NP_TESTSUITE_TYPE_PTR:
            if (g_np_testsuite_context.test_case.actual.si !=
                g_np_testsuite_context.test_case.expected.si) {
                testsuite_test_failed(line);
		        nlogger_err("  Expected : %p\n"
                            "  Actual   : %p\n", 
                            g_np_testsuite_context.test_case.expected.ptr,
                            g_np_testsuite_context.test_case.actual.ptr);
                return true;
            }
            break;
    }
    return false;
}
