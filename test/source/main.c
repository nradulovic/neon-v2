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

#include "test_narch.h"
#include "test_nbits.h"
#include "test_nbits_bitarray.h"
#include "test_ndebug_disabled.h"
#include "test_ndebug_enabled.h"
#include "test_nk_list.h"
#include "test_nk_queue.h"
#include "test_nqueue_pqueue.h"
#include "test_ntask.h"
#include "test_ntask_fiber.h"
#include "ntestsuite.h"

int main(void)
{
    test_narch();
    test_nk_list();
    test_ndebug_enabled();
    test_ndebug_disabled();
    test_nbits();
    test_nbits_bitarray();
    test_nk_queue();
    //test_nqueue_pqueue();
    test_ntask_fiber();
    test_ntask();
    
    return 0;
}
