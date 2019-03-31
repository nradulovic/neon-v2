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
/** @defgroup   ndebug_impl Debug module implementation
 *  @brief      Debug module implementation
 *  @{ *//*==================================================================*/

volatile const char * l_text;
volatile const char * l_file;
volatile const char * l_func;
volatile uint32_t     l_line;

#if 0
NPLATFORM_NORETURN(void nassert(
        const char * text,
        const char * file,
        const char * func,
        uint32_t line))
{
    l_text = text;
    l_file = file;
    l_func = func;
    l_line = line;
    nlogger_err("Failed assert %s at %s:%u in %s\n\r",
                text,
    		func,
                line,
                file);
    NARCH_DISABLE_INTERRUPTS();
    narch_cpu_stop();
}
#endif

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

void np_lqueue_super_init(struct nlqueue * lqs, uint8_t elements)
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
/** @defgroup   nmem_pool)impl Memory pool implementation
 *  @brief      Memory pool implementation
 *  @{ *//*==================================================================*/

void np_mem_pool_init(
        struct nmem_pool * pool,
        void * storage,
        size_t storage_size,
        uint32_t elements)
{

    size_t element_size = storage_size / elements;
    char * current_element;

    nlist_sll_init(&pool->next);
    pool->free = elements;
    current_element = storage;

    for (uint32_t i = 0u; i < elements; i++) {
        struct nlist_sll * current_list = (struct nlist_sll *)current_element;
        nlist_sll_init(current_list);
        nlist_sll_add_before(&pool->next, current_list);
        current_element += element_size;
    }
}

void * np_mem_pool_alloc(struct nmem_pool * pool)
{
    void * retval = NULL;
    NCRITICAL_STATE_DECL(local)

    NCRITICAL_LOCK(&local, NULL);
    if (pool->free != 0u) {
        pool->free--;
        retval = nlist_sll_next(&pool->next);
        nlist_sll_remove_from(&pool->next);
    }
    NCRITICAL_UNLOCK(&local, NULL);

    return retval;
}

void np_mem_pool_free(struct nmem_pool * pool, void * mem)
{
    struct nlist_sll * current = mem;
    NCRITICAL_STATE_DECL(local)

    nlist_sll_init(current);
    NCRITICAL_LOCK(&local, NULL);
    pool->free++;
    nlist_sll_add_after(&pool->next, current);
    NCRITICAL_UNLOCK(&local, NULL);
}

/** @} *//*==================================================================*/
/** @defgroup   nlogger_x_impl Extended logger module implementation
 *  @brief      Extended logger module implementation
 *  @{ *//*==================================================================*/

#include "neon_uart.h"

#if (NCONFIG_ENABLE_LOGGER == 1)
struct logger_line
{
    uint_fast8_t size;
    char text[NCONFIG_LOGGER_LINE_SIZE];
} data;

struct logger_pool
        npool(struct logger_line, NCONFIG_LOGGER_BUFFER_LINES);
struct logger_queue
        nlqueue(struct logger_line *, NCONFIG_LOGGER_BUFFER_LINES);

static struct logger_pool  g_logger_pool;
static struct logger_queue g_logger_queue;
static struct logger_line * g_current;

static void logger_send_callback(void)
{
    np_mem_pool_free(NMEM_POOL(&g_logger_pool), g_current);
}

static void logger_init(void)
{
    nuart_init(NUART_ID_5, (nuart_callback *)logger_send_callback);
    NMEM_POOL_INIT(&g_logger_pool);
    NLQUEUE_INIT(&g_logger_queue);
}

bool nlogger_flush(void)
{
    NCRITICAL_STATE_DECL(local)
    struct logger_line * line;

    if (!nuart_is_initialized(NUART_ID_5)) {
        return false;
    }
    NCRITICAL_LOCK(&local, NULL);
    while (!NLQUEUE_IS_EMPTY(&g_logger_queue)) {
        line = NLQUEUE_GET(&g_logger_queue);
        NCRITICAL_UNLOCK(&local, NULL);

        if (line->size == 0) {
            continue;
        }
        while (!nuart_is_idle(NUART_ID_5)) {
            narch_cpu_idle();
        }
        g_current = line;
        nuart_send(NUART_ID_5, &line->text[0], line->size);
        NCRITICAL_LOCK(&local, NULL);
    }
    NCRITICAL_UNLOCK(&local, NULL);
    return true;
}

bool nlogger_print(const char * msg, ...)
{
    NCRITICAL_STATE_DECL(local)
    struct logger_line * line;
    uint_fast8_t empty;
    int retval;

    line = np_mem_pool_alloc(NMEM_POOL(&g_logger_pool));

    if (line == NULL) {
        return false;
    }

    va_list args;
    va_start(args, msg);
    retval = vsnprintf(
            &line->text[0],
            sizeof(line->text),
            msg,
            args);
    va_end(args);

    line->size = 0;

    if (retval < 0) {
        np_mem_pool_free(NMEM_POOL(&g_logger_pool), line);
        return false;
    }
    if ((size_t)retval >= sizeof(line->text)) {
        retval  = sizeof(line->text);
        line->text[sizeof(line->text) - 3u] = '>';
        line->text[sizeof(line->text) - 2u] = '\r';
        line->text[sizeof(line->text) - 1u] = '\n';
    }
    line->size = retval;

    NCRITICAL_LOCK(&local, NULL);
    NLQUEUE_PUT_FIFO(&g_logger_queue, line);
    NCRITICAL_UNLOCK(&local, NULL);

    empty = NLQUEUE_EMPTY(&g_logger_queue);

    if (empty <= (NLQUEUE_SIZE(&g_logger_queue) / 2)) {
        return nlogger_flush();
    }
    return true;
}
#endif /* (NCONFIG_ENABLE_LOGGER == 1) */

/** @} *//*==================================================================*/
/** @defgroup   nlogger_impl Basic logger module implementation
 *  @brief      Basic logger module implementation
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   nevent_impl Event implementation
 *  @brief      Event implementation
 *  @{ *//*==================================================================*/

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
static inline
bool event_ref_down(const struct nevent * event)
{
    bool retval;

    if (event->pool != NULL) {
        struct nevent * l_event = (struct nevent *)event;
        l_event->ref--;
        retval = !(l_event->ref == 0u);
    } else {
        retval = false;
    }
    return retval;
}
#else
#define event_ref_down(a_event)
#endif

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
void event_ref_up(const struct nevent * event)
{
    if (event->pool != NULL) {
        struct nevent * l_event = (struct nevent *)event;

        l_event->ref++;
    }
}
#else
#define event_ref_up(a_event)
#endif

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
void event_delete(const struct nevent * event)
{
    if (event_ref_down(event)) {
        np_mem_pool_free(event->pool, (void *)event);
    }
}
#else
#define event_delete(a_event)
#endif

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
void * nevent_create(struct nmem_pool * pool, uint_fast16_t id)
{
    struct nevent * event;

    event = np_mem_pool_alloc(pool);

    if (event == NULL) {
        return NULL;
    }
    event->id = id;
    event->ref = 0u;
    event->pool = pool;

    return event;
}
#endif

/** @} *//*==================================================================*/
/** @defgroup   nstate_machine_processor_impl State machine processor module implementation
 *  @brief      State machine processor module implementation
 *  @{ *//*==================================================================*/

#define sm_event(event)                 &g_sm_events[(event)]

static const struct nevent g_sm_events[4] =
{
    NEVENT_INITIALIZER(NSM_SUPER),
    NEVENT_INITIALIZER(NSM_ENTRY),
    NEVENT_INITIALIZER(NSM_EXIT),
    NEVENT_INITIALIZER(NSM_INIT)
};

#if (NCONFIG_EPA_USE_HSM == 1)
void sm_dispatch(struct nsm * sm, const struct nevent * event)
{
    sm->type.dispatch(sm, event);
}
#else
#define sm_dispatch(a_sm, a_event)      sm_fsm_dispatch((a_sm), (a_event))
#endif

static void sm_init(struct nsm * sm)
{
    NREQUIRE(sm->state != NULL);

#if (NCONFIG_EPA_USE_HSM == 1)
    if (sm->type.id == NEPA_FSM_TYPE) {
        sm->type.dispatch = fsm_dispatch;
    } else {
        sm->type.dispatch = hsm_dispatch;
    }
#endif
    NPLATFORM_UNUSED_ARG(sm);
}

static nsm_action sm_fsm_dispatch(struct nsm * sm, const struct nevent * event)
{
    nsm_action                  ret;
    nstate_fn *                 current_state;

    current_state = sm->state;

    while ((ret = current_state(sm, event)) == NP_SMP_TRANSIT_TO) {
        ret = current_state(sm, sm_event(NSM_EXIT));
        NREQUIRE((ret == NACTION_IGNORED) || (ret == NACTION_HANDLED));
        current_state = sm->state;
        ret = current_state(sm, sm_event(NSM_ENTRY));
        NREQUIRE((ret == NACTION_IGNORED) || (ret == NACTION_HANDLED));
        event = sm_event(NSM_INIT);
    }
    NREQUIRE(ret != NP_SMP_SUPER_STATE);
    sm->state = current_state;

    return ret;
}

/** @} *//*==================================================================*/
/** @defgroup   nepa_impl Event Processing Agent (EPA) module implementation
 *  @brief      Event Processing Agent (EPA) module implementation
 *  @{ *//*==================================================================*/

/** @brief		Scheduler context structure
 */
static struct nepa_schedule
{
    struct nepa *               current;        /**< Speed optimization,
                                                 *   current thread priority. */
    struct nepa_queue
    {
#if (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE)
        nbitarray_s                 bitarray;   /**< Simple bit array is used
                                                 * when small number of task
                                                 * is used. */
#else
        nbitarray_x                 bitarray
                [NBITARRAY_DEF(NCONFIG_EPA_INSTANCES)];
#endif
    }                           ready;          /**< Ready queue */
#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
    volatile bool               should_exit;
#endif
} g_epa_schedule;

#define epa_from_prio(a_prio)           (g_nsys_epa_list[(a_prio)])

#define prio_from_epa(a_epa)            ((a_epa)->task.prio)

#if (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE)

#define prio_queue_insert(a_queue, a_prio)                                  \
        nbitarray_s_set(&(a_queue)->bitarray, (a_prio))

#define prio_queue_remove(a_queue, a_prio)                                       \
        nbitarray_s_clear(&(a_queue)->bitarray, (a_prio))

#define prio_queue_get_highest(a_queue)                                     \
        nbitarray_s_msbs(&(a_queue)->bitarray)

#define prio_queue_is_set(a_queue, a_prio)                                  \
        nbitarray_s_is_set(&(a_queue)->bitarray, (a_prio))

#else /* (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE) */

#define queue_insert(a_queue, a_prio)                                       \
        nbitarray_x_set(&(a_queue)->bitarray[0], (a_prio))

#define prio_queue_remove(a_queue, a_prio)                                       \
        nbitarray_x_clear(&(a_queue)->bitarray[0], (a_prio))

#define prio_queue_get_highest(a_queue)                                          \
        nbitarray_x_msbs(&(a_queue)->bitarray[0])

#define prio_queue_is_set(a_queue, a_prio)                                       \
        nbitarray_x_is_set(&(a_queue)->bitarray[0], (a_prio))
#endif /* (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE) */

static void task_init(struct ntask * task, uint_fast8_t prio)
{
    task->prio = prio;
}

static void equeue_init(struct nequeue * equeue)
{
    NREQUIRE((equeue->np_qb_buffer != NULL) && (equeue->super.empty != 0u));
    NREQUIRE((equeue->super.head = 0u) && (equeue->super.tail == 1u));
    NPLATFORM_UNUSED_ARG(equeue);
}

static void epa_init_all(void)
{
    for (uint_fast8_t prio = 0u; prio < NCONFIG_EPA_INSTANCES; prio++) {
        struct nepa * epa;

        epa = epa_from_prio(prio);

        if (epa != NULL) {
            sm_init(&epa->sm);
            task_init(&epa->task, prio);
            equeue_init(&epa->equeue);
            nepa_send_event(epa, sm_event(NSM_INIT));
        }
    }
}

struct nepa * nepa_current(void)
{
    return g_epa_schedule.current;
}

nerror nepa_send_signal(struct nepa * epa, uint_fast16_t signal)
{
    return EOK;
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
nerror nepa_send_event(struct nepa * epa, const struct nevent * event)
{
    NCRITICAL_STATE_DECL(local)
    int_fast8_t idx;
    nerror error = EOK;

    NREQUIRE(NSIGNATURE_OF(epa) == NSIGNATURE_EPA);

    event_ref_up(event);
    NCRITICAL_LOCK(&local, NULL);
    idx = nlqueue_super_idx_fifo(NLQUEUE(&epa->equeue));

    if (idx >= 0) {
        struct nepa_schedule * ctx = &g_epa_schedule;

        NLQUEUE_IDX_REFERENCE(&epa->equeue, idx) = event;
        prio_queue_insert(&ctx->ready, prio_from_epa(epa));
    } else {
        event_ref_down(event);
        error = -EOBJ_INVALID;
    }
    NCRITICAL_UNLOCK(&local, NULL);
    return error;
}


static nsm_action idle_state_init(struct nsm * sm, const struct nevent * event)
{
    NPLATFORM_UNUSED_ARG(sm);
    NPLATFORM_UNUSED_ARG(event);

    return nsm_event_handled();
}

static struct idle_epa_queue nevent_queue(2) idle_epa_queue;
struct nepa g_nsys_epa_idle = NEPA_INITIALIZER(
            &idle_epa_queue, NEPA_FSM_TYPE, idle_state_init, NULL);


void nsys_init(void)
{
#if (NCONFIG_ENABLE_LOGGER == 1)
    logger_init();
#endif
    nboard_init();
#if (NCONFIG_ENABLE_LOGGER == 1)
    nlogger_flush();
#endif
}

bool nsys_is_scheduler_started(void)
{
    return !!g_epa_schedule.current;
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
    struct nepa_schedule * ctx = &g_epa_schedule;

    epa_init_all();

#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
                                    /* While there are ready tasks in system */
    while (!should_exit) {
#else
    while (true) {
#endif
        struct nepa * epa;
        const struct nevent * event;
        uint_fast8_t prio;
                                                    /* Get the highest level */
        prio = prio_queue_get_highest(&ctx->ready);
                                                       /* Fetch the new task */
        epa = epa_from_prio(prio);
        ctx->current = epa;
        NCRITICAL_STATE_DECL(local)
        NCRITICAL_LOCK(&local, NULL);

        if (NLQUEUE_IS_FIRST(&epa->equeue)) {
            prio_queue_remove(&ctx->ready, prio);
        }
        event = NLQUEUE_GET(&epa->equeue);
        NCRITICAL_UNLOCK(&local, NULL);
                                                          /* Execute the EPA */
        sm_dispatch(&epa->sm, event);
        event_delete(event);
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

