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

#include "nk_arch.h"

void nk_arch_stop(void)
{
    for (;;);
}

void nk_arch_set_bit(uint32_t * u32, uint_fast8_t bit)
{
    *u32 |= (uint32_t)1u << bit;
}

void nk_arch_clear_bit(uint32_t * u32, uint_fast8_t bit)
{
    *u32 &= ~((uint32_t)1u << bit);
}

uint32_t nk_arch_exp2(uint_fast8_t x)
{
    return ((uint32_t)0x1u << x);
}

uint_fast8_t nk_arch_log2(uint32_t x)
{
    static const uint_fast8_t log2_table[256] =
    {
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
        0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
#undef LT
    };
    uint8_t tt;
    
    tt = x >> 24u;

    if (tt) {
        return 24u + log2_table[tt];
    }
    
    tt = x >> 16u;

    if (tt) {
        return 16u + log2_table[tt];
    }
    
    tt = x >> 8u;

    if (tt) {
        return 8u + log2_table[tt];
    }
    
    return log2_table[x];
}
