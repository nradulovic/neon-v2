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

#include <stdio.h>
#include <stdarg.h>

#include "nlogger_x.h"

struct nlogger_instance p_nlogger_global =
{
    .level = NLOGGER_LEVEL_INFO
};

void p_nlogger_x_print(struct nlogger_instance * instance, uint8_t level, 
    const char * msg, ...)
{
    if (instance->level >= level) {
        va_list args;
        va_start(args, msg);
        vprintf(msg, args);
        va_end(args);
    }
}

void p_nlogger_x_set_level(struct nlogger_instance * instance, uint8_t level)
{
    instance->level = level;
}
