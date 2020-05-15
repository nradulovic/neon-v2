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

#include "test_nk_arch.h"
#include "test_nk_bits.h"
#include "test_nk_bitarray.h"
#include "test_nk_debug_disabled.h"
#include "test_nk_debug_enabled.h"
#include "test_nk_list.h"
#include "test_nk_queue.h"
#include "ntestsuite.h"

int main(void)
{
    test_nk_arch();
    test_nk_list();
    test_nk_debug_enabled();
    test_nk_debug_disabled();
    test_nk_bits();
    test_nk_bitarray();
    test_nk_queue();
    
    return 0;
}
