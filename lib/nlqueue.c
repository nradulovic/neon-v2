/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   nlqueue_impl Lightweight queue implementation
 *  @brief      Lightweight queue implementation
 *  @{ *//*==================================================================*/

#include "core/nlqueue.h"

void np_lqueue_super_init(struct nlqueue * lqs, uint16_t elements)
{
    lqs->head = 0u;
    lqs->tail = 1u;
    lqs->empty = elements;
    lqs->mask = elements - 1u;
}

int_fast8_t np_lqueue_super_head(const struct nlqueue * qb)
{
    int_fast8_t real_head;

    real_head = qb->head;
    real_head++;
    real_head &= qb->mask;

    return real_head;
}

int_fast8_t np_lqueue_super_tail(const struct nlqueue * qb)
{
    int_fast8_t real_tail;

    real_tail = qb->tail;
    real_tail--;
    real_tail &= qb->mask;

    return real_tail;
}

/** @} */
