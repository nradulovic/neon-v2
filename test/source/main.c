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

#include "test_narch.h"
#include "test_nlist_sll.h"
#include "test_nlist_dll.h"
#include "test_ndebug_enabled.h"
#include "test_ndebug_disabled.h"
#include "test_nbits.h"
#include "test_nbits_bitarray.h"
#include "test_nqueue_lqueue.h"
#include "test_nqueue_pqueue.h"
#include "test_nos.h"
#include "test_nthread_fiber.h"

int main(void)
{
    NTESTSUITE_PRINT_HEADER();
    test_narch();
    test_nlist_sll();
    test_nlist_dll();
    test_ndebug_enabled();
    test_ndebug_disabled();
    test_nbits();
    test_nbits_bitarray();
    test_nqueue_lqueue();
    test_nqueue_pqueue();
    test_nos();
    test_nthread_fiber();
    NTESTSUITE_PRINT_OVERVIEW();
    
    return 0;
}
