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

#include "test_ntask.h"
#include "ntask.h"
#include "ntestsuite.h"

static struct nk_sched__task_cb * g_task_create;
static struct nk_sched__task_cb * g_task_yield;

static NTASK(task_create_fn(struct nk_sched__task_cb * task, void * arg))
{
    (void)arg;

    NTASK_BEGIN(task);
    NTASK_END();
}

static NTASK(task_yield_fn(struct nk_sched__task_cb * task, void * arg))
{
    (void)arg;

    NTASK_BEGIN(task);
    ntask_yield();
    NTASK_END();
}

static void test_init_state(void)
{
    NTESTSUITE_EXPECT_UINT(NTASK_DORMANT);
    ntask_create(&g_task_create, task_create_fn, NULL, 0);
    NTESTSUITE_ACTUAL_UINT(ntask_state(g_task_create));
}

static void test_init_priority(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    ntask_create(&g_task_create, task_create_fn, NULL, 1);
    NTESTSUITE_ACTUAL_UINT(ntask_priority(g_task_create));
}

static void test_yield(void)
{
    NTESTSUITE_EXPECT_UINT(NTASK_DORMANT);
    ntask_create(&g_task_yield, task_yield_fn, NULL, 2);
    ntask_ready(g_task_yield);
    ntask_schedule();
    NTESTSUITE_ACTUAL_UINT(ntask_state(g_task_yield));
}

void test_ntask(void)
{
	static const struct nk_testsuite_test none_tests[] =
	{
		NK_TESTSUITE_TEST(test_init_state),
		NK_TESTSUITE_TEST(test_init_priority),
		NK_TESTSUITE_TEST(test_yield),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(NULL, NULL, NK_TESTSUITE_FIXTURE_NAME(none));
	nk_testsuite_run_tests(none_tests);
}


