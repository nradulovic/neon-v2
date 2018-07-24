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
#include "task/ntask.h"
#include "test_ntask.h"

static struct ntask g_task_init;
static struct ntask g_task_yield;

static NTASK(task_init_fn(struct ntask * task, void * arg))
{
    (void)arg;

	NTASK_BEGIN(task);
	NTASK_END();
}

static NTASK(task_yield_fn(struct ntask * task, void * arg))
{
    (void)arg;

	NTASK_BEGIN(task);
    ntask_yield();
	NTASK_END();
}

static void test_init(void)
{
    NTESTSUITE_EXPECT_UINT(NTASK_DORMANT);
    ntask_init(&g_task_init, task_init_fn, NULL, 0);
    NTESTSUITE_ACTUAL_UINT(ntask_state(&g_task_init));
    NTESTSUITE_EVALUATE();
}

static void test_priority(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    ntask_init(&g_task_init, task_init_fn, NULL, 1);
    NTESTSUITE_ACTUAL_UINT(ntask_priority(&g_task_init));
    NTESTSUITE_EVALUATE();
}

static void test_yield(void)
{
    NTESTSUITE_EXPECT_UINT(NTASK_READY);
    ntask_init(&g_task_yield, task_yield_fn, NULL, 0);
    ntask_dispatch(&g_task_yield);
    NTESTSUITE_ACTUAL_UINT(ntask_state(&g_task_yield));
    NTESTSUITE_EVALUATE();
}

void test_ntask(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);

    NTESTSUITE_RUN(none, test_init);
    NTESTSUITE_RUN(none, test_priority);
    NTESTSUITE_RUN(none, test_yield);
    NTESTSUITE_PRINT_RESULTS(none);   
}


