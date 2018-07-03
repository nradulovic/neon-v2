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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "testsuite/ntestsuite.h"
#include "task/ntask.h"
#include "test_ntask.h"

static void test_ntask_init(void);

static NTASK(my_task_fn(struct ntask * ts));

static NTASK(my_task_fn(struct ntask * ts))
{

}

static void test_ntask_init(void)
{
	struct ntask my_task;


}

void test_nos(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_RUN(none, test_ntask_init);
    NTESTSUITE_PRINT_RESULTS(none);
}


