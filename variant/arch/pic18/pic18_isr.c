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

#include <xc.h>

#include "pic18_isr.h"

void pic18_isr_init(void)
{
    /* Enable Interrupt Priority Vectors */
    INTCONbits.GIEL = 0;
    INTCONbits.GIEH = 0;
    INTCONbits.IPEN = 1;
}

void pic18_isr_enable(void)
{
    INTCONbits.GIEL = 1;
    INTCONbits.GIEH = 1;
}