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

#include "arch_variant/arch.h"

void narch_cpu_stop(void)
{
    for (;;);
}

narch_uint narch_exp2(uint_fast8_t x)
{
    return ((narch_uint)0x1u << x);
}

uint_fast8_t narch_log2(narch_uint x)
{
    static const uint_fast8_t log2_table[256] =
    {
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
        0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
#undef LT
    };
    
    return log2_table[x];
}
