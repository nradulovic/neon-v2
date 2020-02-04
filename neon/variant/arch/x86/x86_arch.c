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

#include <stdlib.h>

#include "core/nport.h"

const char * const narch_id = "x86";
const bool narch_has_atomics = false;

void narch_cpu_stop(void)
{
    exit(1);
}

uint32_t narch_exp2(uint_fast8_t x)
{
	return ((uint32_t)0x1u << x);
}

uint_fast8_t narch_log2(uint32_t x)
{
	return (31 - __builtin_clz(x));
}
