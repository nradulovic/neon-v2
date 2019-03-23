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

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>

#define NEON_C_SOURCE
#include "neon.h"

/*===========================================================================*/
/** @defgroup   nconfig_impl Configuration module implementation
 *  @brief      Configuration module implementation
 *  @{ *//*==================================================================*/

#if (NCONFIG_EPA_INSTANCES > NBITARRAY_X_MAX_SIZE)
# error "The limit of maximum EPA instances has been exceeded!"
#endif

#if (NCONFIG_EPA_INSTANCES > NEPA_PRIO_MAX)
# error "The limit of maximum EPA priorities has been exceeded!"
#endif

const uint32_t nconfig_compiled_id = NCONFIG_ID;

/** @} *//*==================================================================*/
/** @defgroup   nbits_impl Bit operations module implementation
 *  @brief      Bit operations module implementation
 *  @{ *//*==================================================================*/

const uint32_t g_np_bits_right_mask[33] =
{
    [ 0] = 0x00000000u,
    [ 1] = 0x00000001u,
    [ 2] = 0x00000003u,
    [ 3] = 0x00000007u,
    [ 4] = 0x0000000fu,
    [ 5] = 0x0000001fu,
    [ 6] = 0x0000003fu,
    [ 7] = 0x0000007fu,
    [ 8] = 0x000000ffu,
    [ 9] = 0x000001ffu,
    [10] = 0x000003ffu,
    [11] = 0x000007ffu,
    [12] = 0x00000fffu,
    [13] = 0x00001fffu,
    [14] = 0x00003fffu,
    [15] = 0x00007fffu,
    [16] = 0x0000ffffu,
    [17] = 0x0001ffffu,
    [18] = 0x0003ffffu,
    [19] = 0x0007ffffu,
    [20] = 0x000fffffu,
    [21] = 0x001fffffu,
    [22] = 0x003fffffu,
    [23] = 0x007fffffu,
    [24] = 0x00ffffffu,
    [25] = 0x01ffffffu,
    [26] = 0x03ffffffu,
    [27] = 0x07ffffffu,
    [28] = 0x0fffffffu,
    [29] = 0x1fffffffu,
    [30] = 0x3fffffffu,
    [31] = 0x7fffffffu,
    [32] = 0xffffffffu
};

uint32_t nbits_ftou32(float val)
{
    uint32_t retval;

    memcpy(&retval, &val, sizeof(retval));

    return retval;
}

float nbits_u32tof(uint32_t val)
{
    float retval;

    memcpy(&retval, &val, sizeof(retval));

    return retval;
}

/*
 * 1. Set group value
 * 2. Set group indicator.
 */
void nbitarray_x_set(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
	pos = bit & (NARCH_DATA_WIDTH - 1u);           /* bit % NARCH_DATA_WIDTH */

    array[group + 1u] |= narch_exp2(pos);                               /* 1 */
    array[0] |= narch_exp2(group);                                      /* 2 */
}

void nbitarray_x_clear(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
	pos = bit & (NARCH_DATA_WIDTH - 1u);           /* bit % NARCH_DATA_WIDTH */

    array[group + 1u] &= ~narch_exp2(pos);                              /* 1 */

    if (array[group + 1u] == 0u) {
        array[0] &= ~narch_exp2(group);                                 /* 2 */
    }
}

#if (NEON_HAS_BITARRAY_X_ATOMICS == 1)
/*
 * It is safe to have two independent atomic operations when we first set group
 * value and then set group indicator bit. Even when we are interrupted right
 * in between the calls, the consistency of the array is sustained because
 * group indicator is set after group value.
 *
 * 1. Set group value
 * 2. Set group indicator.
 */
void nbitarray_x_set_atomic(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
	pos = bit & (NARCH_DATA_WIDTH - 1u);           /* bit % NARCH_DATA_WIDTH */

	narch_atomic_set_bit(&array[group + 1u], pos);                      /* 1 */
    narch_atomic_set_bit(&array[0], group);                             /* 2 */
}

void nbitarray_x_clear_atomic(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t pos;
    narch_uint group_val_c;
    narch_uint group_val_n;

	group = bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
	pos = bit & (NARCH_DATA_WIDTH - 1u);           /* bit % NARCH_DATA_WIDTH */

    do {
        group_val_c = array[group + 1u];
        group_val_n = group_val_c & ~narch_exp2(pos);

        if (group_val_n == 0u) {
            narch_atomic_clear_bit(&array[0], group);
        } else {
            narch_atomic_set_bit(&array[0], group);
        }
    } while (!narch_compare_and_swap(
            &array[group + 1],
            group_val_c,
            group_val_n));
}
#endif /* (NEON_HAS_BITARRAY_X_ATOMICS == 1) */

uint_fast8_t nbitarray_x_msbs(const nbitarray_x * array)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = narch_log2(array[0]);
	pos = narch_log2(array[group + 1u]);

	return (uint_fast8_t)(group * (uint_fast8_t)NARCH_DATA_WIDTH + pos);
}

bool nbitarray_x_is_set(const nbitarray_x * array, uint_fast8_t bit)
{
    uint_fast8_t group;
	uint_fast8_t pos;

	group = bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
	pos = bit & (NARCH_DATA_WIDTH - 1u);           /* bit % NARCH_DATA_WIDTH */

    return !!(array[group + 1u] & narch_exp2(pos));
}

/** @} *//*==================================================================*/
/** @defgroup   nqueue_lqueue_impl Lightweight queue module implementation
 *  @brief      Lightweight queue module implementation
 *  @{ *//*==================================================================*/

void np_lqueue_super_init(struct np_lqueue_super * lqs, uint8_t elements)
{
    lqs->u.m.head = 0u;
    lqs->u.m.tail = 1u;
    lqs->u.m.empty = elements;
    lqs->u.m.mask = elements - 1u;
}

int_fast8_t np_lqueue_super_head(const struct np_lqueue_super * qb)
{
    int_fast8_t real_head;

    real_head = qb->u.m.head;
    real_head++;
    real_head &= qb->u.m.mask;

    return real_head;
}

int_fast8_t np_lqueue_super_tail(const struct np_lqueue_super * qb)
{
    int_fast8_t real_tail;

    real_tail = qb->u.m.tail;
    real_tail--;
    real_tail &= qb->u.m.mask;

    return real_tail;
}

#if defined(NLQUEUE_IDX_FIFO_ATOMIC)
int_fast8_t nlqueue_super_idx_fifo_atomic(struct np_lqueue_super * qb)
{
    int_fast8_t retval;
    struct np_lqueue_super qc;
    struct np_lqueue_super qn;

    do {
        qc.u.ui = qb->u.ui;
        qn.u.ui = qc.u.ui;
        retval = nlqueue_super_idx_fifo(&qn);
    } while (!narch_compare_and_swap(&qb->u.ui, qc.u.ui, qn.u.ui));
    return retval;
}
#endif

#if defined(NLQUEUE_IDX_LIFO_ATOMIC)
int32_t nlqueue_super_idx_lifo_atomic(struct np_lqueue_super * qb)
{
    int32_t retval;
    struct np_lqueue_super qc;
    struct np_lqueue_super qn;

    do {
        qc.u.ui = qb->u.ui;
        qn.u.ui = qc.u.ui;
        retval = nlqueue_super_idx_lifo(&qn);
    } while (!narch_compare_and_swap(&qb->u.ui, qc.u.ui, qn.u.ui));

    return retval;
}
#endif

#if defined(NLQUEUE_IDX_GET_ATOMIC)
int_fast8_t nlqueue_super_idx_get_atomic(struct np_lqueue_super * qb)
{
    int_fast8_t retval;
    struct np_lqueue_super qc;
    struct np_lqueue_super qn;

    do {
        qc.u.ui = qb->u.ui;
        qn.u.ui = qc.u.ui;
        retval = nlqueue_super_idx_get(&qn);
    } while (!narch_compare_and_swap(&qb->u.ui, qc.u.ui, qn.u.ui));

    return retval;
}
#endif

/** @} *//*==================================================================*/
/** @defgroup   nqueue_pqueue_impl Priority sorted queue module implementation
 *  @brief      Priority sorted queue module implementation
 *  @{ *//*==================================================================*/

void npqueue_sentinel_shift(struct npqueue_sentinel * sentinel)
{
    struct npqueue * next = npqueue_next(sentinel);

    nlist_dll_remove(&sentinel->list);
    nlist_dll_add_before(&next->list, &sentinel->list);
}

struct npqueue * npqueue_init(struct npqueue * node, uint_fast8_t priority)
{
    nlist_dll_init(&node->list);
    npqueue_priority_set(node, priority);

    return (node);
}

void npqueue_term(struct npqueue * node)
{
    npqueue_priority_set(node, 0);
    nlist_dll_init(&node->list);
}

void npqueue_insert_sort(struct npqueue_sentinel * sentinel,
        struct npqueue * node)
{
    struct nlist_dll * current_list;

    for (NLIST_DLL_EACH(current_list, &sentinel->list)) {
        struct npqueue * current = npqueue_from_list(current_list);

        if (current->priority < node->priority) {
            break;
        }
    }
    nlist_dll_add_after(current_list, &node->list);
}

/** @} *//*==================================================================*/
/** @defgroup   nlogger_x_impl Extended logger module implementation
 *  @brief      Extended logger module implementation
 *  @{ *//*==================================================================*/

#include "neon_uart.h"

#if (NCONFIG_ENABLE_LOGGER == 1)
static struct logger_q nlqueue(char, NCONFIG_LOGGER_BUFFER_SIZE) g_logger_q;
#endif

static void logger_init(void)
{
    NLQUEUE_INIT(&g_logger_q);
}

struct nlogger_instance np_logger_global =
{
    .level = NLOGGER_LEVEL_INFO
};


void np_logger_x_print(struct nlogger_instance * instance, uint8_t level,
    const char * msg, ...)
{
    if (instance->level >= level) {
        char buffer[83];
        int retval;

        va_list args;
        va_start(args, msg);
        retval = vsnprintf(buffer, sizeof(buffer), msg, args);
        va_end(args);

        if (retval > 0) {
            if (retval >= (sizeof(buffer) - 2)) {
                buffer[sizeof(buffer) - 1] = '\r';
                buffer[sizeof(buffer) - 2] = '\n';
                retval = sizeof(buffer);
            }
            nuart_send_sync(NUART_ID_5, buffer, retval);
        }
    }
}

void np_logger_x_set_level(struct nlogger_instance * instance, uint8_t level)
{
    instance->level = level;
}

void np_logger_x_set_drain(struct nlogger_instance * instance)
{

}

/** @} *//*==================================================================*/
/** @defgroup   nlogger_impl Basic logger module implementation
 *  @brief      Basic logger module implementation
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   nevent_impl Event implementation
 *  @brief      Event implementation
 *  @{ *//*==================================================================*/



/** @} *//*==================================================================*/
/** @defgroup   nstate_machine_processor_impl State machine processor module implementation
 *  @brief      State machine processor module implementation
 *  @{ *//*==================================================================*/

#if (NCONFIG_EVENT_USE_EVENT_X == 1)
#define NSMP_EVENT(event)               make_event(&g_smp_events[(event)])
#else
#define NSMP_EVENT(event)               make_signal(event)
#endif

#if (NCONFIG_EVENT_USE_EVENT_X == 1)
NPLATFORM_INLINE
struct nevent make_event(const struct nevent_x * event_x)
{
    struct nevent event;

    event.u.x = event_x;

    return event;
}
#else
NPLATFORM_INLINE
struct nevent make_signal(uint_fast8_t signal)
{
    struct nevent event;

    event.u.signal = signal;

    return event;
}
#endif


/*
 * NOTE: We don't use indexed initialisation here, so it must be ensured that
 *       the order of events in this array match the enumerator nsmp_events.
 */
#if (NCONFIG_EVENT_USE_EVENT_X == 1)
static const struct nevent_x g_smp_events[4] =
{
    NEVENT_X_INITIALIZER(NSM_SUPER, sizeof(struct nevent)),
    NEVENT_X_INITIALIZER(NSM_ENTRY, sizeof(struct nevent)),
    NEVENT_X_INITIALIZER(NSM_EXIT,  sizeof(struct nevent)),
    NEVENT_X_INITIALIZER(NSM_INIT,  sizeof(struct nevent))
};
#endif

static void sm_fsm_dispatch(struct nsm * sm, struct nevent event)
{
    naction                     ret;
    nstate_fn *                 current_state;

    current_state = sm->state;

    while ((ret = current_state(sm, event)) == NP_SMP_TRANSIT_TO) {
#if (NDEBUG_IS_ENABLED == 1)
        ret = current_state(sm, NSMP_EVENT(NSM_EXIT));
        NREQUIRE((ret == NACTION_IGNORED) || (ret == NACTION_HANDLED));
#else
        (void)current_state(sm, NSMP_EVENT(NSM_EXIT));
#endif
        current_state = sm->state;
#if (NDEBUG_IS_ENABLED == 1)
        ret = current_state(sm, NSMP_EVENT(NSM_ENTRY));
        NREQUIRE((ret == NACTION_IGNORED) || (ret == NACTION_HANDLED));
#else
        (void)current_state(sm, NSMP_EVENT(NSM_ENTRY));
#endif
        event = NSMP_EVENT(NSM_INIT);
    }
    NREQUIRE(ret != NP_SMP_SUPER_STATE);
    sm->state = current_state;
}

/** @} *//*==================================================================*/
/** @defgroup   nepa_impl Event Processing Agent (EPA) module implementation
 *  @brief      Event Processing Agent (EPA) module implementation
 *  @{ *//*==================================================================*/

/** @brief		Scheduler context structure
 */
static struct nepa_schedule
{
	struct nepa * current;                      /**< Speed optimization,
                                                 *   current thread priority. */
    struct nepa_queue
    {
#if (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE)
        nbitarray_s bitarray;                   /**< Simple bit array is used
                                                 * when small number of task
                                                 * is used. */
#else
        nbitarray_x bitarray[NBITARRAY_DEF(NCONFIG_EPA_INSTANCES)];
#endif
    } ready;                                    /**< Ready queue */
#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
    bool should_exit = false;
#endif
    struct nepa mempool[NCONFIG_EPA_INSTANCES]; /**< EPA instances. */
} g_epa_schedule;



static naction default_idle_epa(struct nsm * sm, struct nevent event)
{
    NPLATFORM_UNUSED_ARG(sm);
    NPLATFORM_UNUSED_ARG(event);

    return NACTION_HANDLED;
}

#define epa_from_prio(a_ctx, a_prio)    (&(a_ctx)->mempool[a_prio])

#if (NCONFIG_MEM_OPTIMIZATION == 0)
#define prio_from_epa(a_ctx, a_epa)     ((a_epa)->task.prio)
#else
#define prio_from_epa(a_ctx, a_epa)     ((a_epa) - &(a_ctx)->mempool[0])
#endif

#if (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE)

#if (NEON_HAS_BITARRAY_S_ATOMICS == 1)
#define HAS_QUEUE_ATOMICS               1
#define PRIO_QUEUE_INSERT_ATOMIC(a_queue, a_prio)                           \
        nbitarray_s_set_atomic(&(a_queue)->bitarray, (a_prio))

#define PRIO_QUEUE_REMOVE_ATOMIC(a_queue, a_prio)                           \
        nbitarray_s_clear_atomic(&(a_queue)->bitarray, (a_prio))
#else
#define HAS_QUEUE_ATOMICS               0
#endif /* (NEON_HAS_BITARRAY_S_ATOMICS == 1) */

#define PRIO_QUEUE_INSERT(a_queue, a_prio)                                  \
        nbitarray_s_set(&(a_queue)->bitarray, (a_prio))

#define PRIO_QUEUE_REMOVE(a_queue, a_prio)                                       \
        nbitarray_s_clear(&(a_queue)->bitarray, (a_prio))

#define PRIO_QUEUE_GET_HIGHEST(a_queue)                                     \
        nbitarray_s_msbs(&(a_queue)->bitarray)

#define PRIO_QUEUE_IS_SET(a_queue, a_prio)                                  \
        nbitarray_s_is_set(&(a_queue)->bitarray, (a_prio))
#else /* (NEON_HAS_BITARRAY_S_ATOMICS == 1) */

#if (NEON_HAS_BITARRAY_X_ATOMICS == 1)
#define HAS_QUEUE_ATOMICS               1
#define PRIO_QUEUE_INSERT_ATOMIC(a_queue, a_prio)                                \
        nbitarray_x_set_atomic(&(a_queue)->bitarray[0], (a_prio))

#define PRIO_QUEUE_REMOVE_ATOMIC(a_queue, a_prio)                                \
        nbitarray_x_clear_atomic(&(a_queue)->bitarray[0], (a_prio))
#else
#define HAS_QUEUE_ATOMICS               0
#endif /* (NEON_HAS_BITARRAY_X_ATOMICS == 1) */

#define queue_insert(a_queue, a_prio)                                       \
        nbitarray_x_set(&(a_queue)->bitarray[0], (a_prio))

#define PRIO_QUEUE_REMOVE(a_queue, a_prio)                                       \
        nbitarray_x_clear(&(a_queue)->bitarray[0], (a_prio))

#define PRIO_QUEUE_GET_HIGHEST(a_queue)                                          \
        nbitarray_x_msbs(&(a_queue)->bitarray[0])

#define PRIO_QUEUE_IS_SET(a_queue, a_prio)                                       \
        nbitarray_x_is_set(&(a_queue)->bitarray[0], (a_prio))
#endif



static void event_q_init(
        struct nevent_q * event_q,
        const struct nepa_define * define)
{
    NLQUEUE_INIT_DYNAMIC(event_q, define->event_q_size, define->event_q_storage);
}

static void sm_init(struct nsm * sm, const struct nepa_define * define)
{
#if (NCONFIG_EPA_USE_HSM == 1)
    sm->dispatch = define->type = NEPA_HSM_TYPE ? hsm_dispatch : fsm_dispatch;
#endif
    sm->state = define->init_state;
    sm->ws = define->ws;
}

#if (NCONFIG_MEM_OPTIMIZATION == 0)
static void task_init(struct ntask * task, uint_fast8_t prio)
{
    task->prio = prio;
}
#endif

struct nepa * nepa_create(
        uint_fast8_t prio,
        const struct nepa_define * define)
{
    struct nepa_schedule * ctx = &g_epa_schedule;
    struct nepa * epa;

    NREQUIRE(define != NULL);
    NREQUIRE(prio < NCONFIG_EPA_INSTANCES);

    epa = epa_from_prio(ctx, prio);

    NREQUIRE(NSIGNATURE_OF(epa) != NSIGNATURE_EPA);
    NOBLIGATION(NSIGNATURE_IS(epa, NSIGNATURE_EPA));

#if (NCONFIG_MEM_OPTIMIZATION == 0)
    task_init(&epa->task, prio);
#endif
    sm_init(&epa->sm, define);
    event_q_init(&epa->event_q, define);

    return epa;
}

void nepa_delete(struct nepa * epa)
{
	NREQUIRE(NSIGNATURE_OF(epa) == NSIGNATURE_EPA);
    NOBLIGATION(NSIGNATURE_IS(epa, ~NSIGNATURE_EPA));
    (void)epa;
}

/*
 *
 * 1. Insert EPA to priority queue 'ready'
 *    a) insert it in atomic mode
 *    b) insert it in plain mode protected by critical section macros
 *
 * NOTES:
 * 1. The bool 'pending' is true when a queue was empty before calling this
 *    function. It will trigger calling the queue_insert_atomic. In rare cases
 *    it can be set (false positive) when multiple nepa_send_event functions
 *    are called from different execution contexts. The single side effect would
 *    be that queue_insert_atomic is called multiple times, which is not
 *    dangerous, it only cost additional CPU execution time.
 */
nerror nepa_send_event(struct nepa * epa, struct nevent event)
{
    struct nepa_schedule * ctx = &g_epa_schedule;
    nerror error;

    NREQUIRE(NSIGNATURE_OF(epa) == NSIGNATURE_EPA);

#if (NCONFIG_EVENT_USE_EVENT_X == 1)


#if defined(PRIO_QUEUE_INSERT_ATOMIC) && defined(NLQUEUE_IDX_FIFO_ATOMIC) \
    && defined(NLQUEUE_IS_FIRST_ATOMIC)
    {
        int_fast8_t idx;

        idx = NLQUEUE_IDX_FIFO_ATOMIC(&epa->event_q);

        if (idx >= 0) {
            NLQUEUE_IDX_REFERENCE(&epa->event_q, idx) = event;
                                                               /* See note 1 */
                                                                        /* 1a*/
            if (NLQUEUE_IS_FIRST_ATOMIC(&epa->event_q)) {
                PRIO_QUEUE_INSERT_ATOMIC(&ctx->ready, prio_from_epa(ctx, epa));
            }
            error = EOK;
        } else {
            error = -EOBJ_INVALID;
        }
    }
#else
    {
        NCRITICAL_STATE_DECL(local)
        int_fast8_t idx;

        NCRITICAL_LOCK(&local, NULL);
        idx = NLQUEUE_IDX_FIFO(&epa->event_q);

        if (idx >= 0) {
            NLQUEUE_IDX_REFERENCE(&epa->event_q, idx) = event;
            PRIO_QUEUE_INSERT(&ctx->ready, prio_from_epa(ctx, epa));
            error = EOK;
        } else {
            error = -EOBJ_INVALID;
        }
        NCRITICAL_UNLOCK(&local, NULL);
    }
#endif
#endif
    return error;
}

void nsys_init(void)
{
    logger_init();
    nboard_init();
}

void nsys_timer_isr(void)
{

}

/*
 * 1. If no ready task is set then set the default idle task.
 */
#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
void nsys_schedule_start(void)
#else
NPLATFORM_NORETURN(void nsys_schedule_start(void))
#endif
{
    static const struct nepa_define idle_epa = {
        .event_q_size = 0,
        .event_q_storage = NULL,
        .init_state = default_idle_epa,
        .type = NEPA_FSM_TYPE,
        .ws = NULL,
    };
    struct nepa_schedule * ctx = &g_epa_schedule;

    if (!PRIO_QUEUE_IS_SET(&ctx->ready, 0)) {                           /* 1 */
        nepa_create(0, &idle_epa);
    }

#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
                                    /* While there are ready tasks in system */
    while (!should_exit) {
#else
    while (true) {
#endif
        struct nepa * epa;
        struct nevent event;
        uint_fast8_t prio;
                                                    /* Get the highest level */
        prio = PRIO_QUEUE_GET_HIGHEST(&ctx->ready);
                                                       /* Fetch the new task */
        epa = epa_from_prio(ctx, prio);
        ctx->current = epa;

#if defined(NLQUEUE_IS_FIRST_ATOMIC) && defined(PRIO_QUEUE_REMOVE_ATOMIC) \
    && defined(NLQUEUE_IDX_GET_ATOMIC)
        if (NLQUEUE_IS_FIRST_ATOMIC(&epa->event_q)) {
            PRIO_QUEUE_REMOVE_ATOMIC(&ctx->ready, prio);
        }

        event = NLQUEUE_IDX_REFERENCE(
                &epa->event_q,
                NLQUEUE_IDX_GET_ATOMIC(&epa->event_q));
#else
        {
            NCRITICAL_STATE_DECL(local)
            NCRITICAL_LOCK(&local, NULL);

            if (NLQUEUE_IS_FIRST(&epa->event_q)) {
                PRIO_QUEUE_REMOVE(&ctx->ready, prio);
            }
            event = NLQUEUE_GET(&epa->event_q);
            NCRITICAL_UNLOCK(&local, NULL);
        }
#endif
                                                          /* Execute the EPA */
#if (NCONFIG_EPA_USE_HSM == 1)
        epa->dispatch.dispatch(&epa->sm, event);
#else
        sm_fsm_dispatch(&epa->sm, event);
#endif
    }

#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
    for (uint_fast8_t prio = 0u; prio < NCONFIG_EPA_INSTANCES; prio) {
        struct ntask * task;

        task = epa_from_prio(ctx, prio);

        ntask_stop(task);
    }

    for (uint_fast8_t prio = 0u; prio < NCONFIG_EPA_INSTANCES; prio) {
        struct ntask * task;

        task = epa_from_prio(ctx, prio);

        ntask_delete(task);
    }
#endif
}

#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
void ntask_schedule_stop(void)
{
    should_exit = true;
}
#endif

/** @} *//*==================================================================*/
/** @defgroup   nfiber_task_impl Fiber task implementation
 *  @brief      Fiber task implementation
 *  @{ *//*==================================================================*/

