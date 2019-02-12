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
#include "main.h"

static void task_fn(void * arg);

static void task_fn(void * arg)
{
	(void)arg;
}

NTESTSUITE_TEST(test_init_state)
{
	struct ntask * task;

	task = ntask_create(task_fn, NULL, 1);

	NTESTSUITE_EXPECT_UINT(NTASK_DORMANT);
	NTESTSUITE_ACTUAL_UINT(ntask_state(task));
}

NTESTSUITE_TEST(test_start_state)
{
	struct ntask * task;

	task = ntask_create(task_fn, NULL, 2);

	NTESTSUITE_EXPECT_UINT(NTASK_DORMANT);
	NTESTSUITE_ACTUAL_UINT(ntask_state(task));
}

NTESTSUITE_TEST(test_yield)
{
}

void test_exec(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);

    NTESTSUITE_RUN(none, test_init_state);
    NTESTSUITE_RUN(none, test_start_state);
    NTESTSUITE_RUN(none, test_yield);
    NTESTSUITE_PRINT_RESULTS(none);
}


