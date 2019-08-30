/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @defgroup   neon_impl Neon implementation
 *  @brief      Neon implementation
 *  @{ *//*==================================================================*/

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "neon.h"

/*===========================================================================*/
/** @defgroup   nport_impl Port generic implementation
 *  @brief      Port generic implementation
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   nconfig_impl Configuration module implementation
 *  @brief      Configuration module implementation
 *  @{ *//*==================================================================*/

#if (NCONFIG_EPA_INSTANCES > NBITARRAY_X_MAX_SIZE)
# error "The limit of maximum EPA instances has been exceeded!"
#endif

#if (NCONFIG_EPA_INSTANCES > NEPA_PRIO_MAX)
# error "The limit of maximum EPA priorities has been exceeded!"
#endif

const struct nconfig_entry * nconfig_record_fetch(uint8_t idx)
{
    static const struct nconfig_entry record[] =
    {
        [NCONFIG_ENTRY_ENABLE_DEBUG] =
		{
			"NCONFIG_ENABLE_DEBUG",
			NCONFIG_ENABLE_DEBUG
		},
        [NCONFIG_ENTRY_ENABLE_LOGGER] =
        {
			"NCONFIG_ENABLE_LOGGER",
			NCONFIG_ENABLE_LOGGER
        },
        [NCONFIG_ENTRY_LOGGER_BUFFER_SIZE] =
        {
			"NCONFIG_LOGGER_BUFFER_SIZE",
			NCONFIG_STDIO_OUTPUT_BUFFER_SIZE
        },
        [NCONFIG_ENTRY_LOGGER_LEVEL] =
        {
			"NCONFIG_LOGGER_LEVEL",
			NCONFIG_LOGGER_LEVEL
        },
        [NCONFIG_ENTRY_EPA_INSTANCES] =
        {
			"NCONFIG_EPA_INSTANCES",
			NCONFIG_EPA_INSTANCES
        },
        [NCONFIG_ENTRY_EPA_USE_HSM] =
        {
			"NCONFIG_EPA_USE_HSM",
			NCONFIG_EPA_USE_HSM
        },
        [NCONFIG_ENTRY_EPA_HSM_LEVELS] =
        {
			"NCONFIG_EPA_HSM_LEVELS",
			NCONFIG_EPA_HSM_LEVELS
        },
        [NCONFIG_ENTRY_SYS_EXITABLE_SCHEDULER] =
        {
			"NCONFIG_SYS_EXITABLE_SCHEDULER",
			NCONFIG_SYS_EXITABLE_SCHEDULER
        },
        [NCONFIG_ENTRY_EVENT_USE_DYNAMIC] =
        {
			"NCONFIG_EVENT_USE_DYNAMIC",
			NCONFIG_EVENT_USE_DYNAMIC
        },
        [NCONFIG_ENTRY_SCHEDULER_PRIORITIES] =
        {
			"NCONFIG_SCHEDULER_PRIORITIES",
			NCONFIG_SCHEDULER_PRIORITIES
        },
        [NCONFIG_ENTRY_USE_EXCLUSIVE_ACCESS] =
        {
			"NCONFIG_USE_EXCLUSIVE_ACCESS",
			NCONFIG_USE_EXCLUSIVE_ACCESS
        },
    };

    if (idx >= NBITS_ARRAY_SIZE(record)) {
        return NULL;
    }
    return &record[idx];
}

/** @} *//*==================================================================*/
/** @defgroup   ndebug_impl Debug implementation
 *  @brief      Debug implementation
 *  @{ *//*==================================================================*/

#if (NCONFIG_ENABLE_DEBUG == 1)

volatile const char * l_text;
volatile const char * l_file;
volatile const char * l_func;
volatile uint32_t     l_line;

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
    nlogger_err(
            "\r\nFAILED ASSERTION at:\r\n file: %s\r\n func: %s()\r\n line: %u",
            file,
    		func,
            line);
    nlogger_err("Expression that failed:\r\n '%s'", text);
    nlogger_err("Build details:\r\n %s - %s", 
            nsys_build_date, 
            nsys_build_time);
    nlogger_err("Platform:\r\n %s", nsys_platform_id);
    nlogger_flush();
    narch_cpu_stop();
}
#endif

/** @} *//*==================================================================*/
/** @defgroup   nerror_impl Error handling implementation
 *  @brief      Error handling implementation
 *  @{ *//*==================================================================*/

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

/** @} *//*==================================================================*/
/** @defgroup   nlist_sll_impl Singly linked list implementation
 *  @brief      Singly linked list implementation
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   nlist_dll_impl Doubly linked list implementation
 *  @brief      Doubly linked list implementation
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   nlqueue_impl Lightweight queue implementation
 *  @brief      Lightweight queue implementation
 *  @{ *//*==================================================================*/

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

/** @} *//*==================================================================*/
/** @defgroup   npqueue_impl Priority sorted queue implementation
 *  @brief      Priority sorted queue implementation
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
/** @defgroup   bits_bitarray_s_impl Simple bit array implementation
 *  @brief      Simple bit array implementation.
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   bits_bitarray_x_impl Extended bit array implementation
 *  @brief      Extended bit array implementation.
 *  @{ *//*==================================================================*/

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
/** @defgroup   nstdio_impl Standard IO implementation
 *  @brief      Standard IO implementation
 *  @{ *//*==================================================================*/

#if (NBOARD_USES_STD_STREAM > 0) && (NBOARD_USES_STD_STREAM < 16)
#include "neon_uart.h"

#if (NBOARD_USES_STD_STREAM == 1)
#define NUART_ID                        NUART_ID_1
#define NSTREAM_ISR_CALLBACK                       nuart_callback_1
#elif (NBOARD_USES_STD_STREAM == 2)
#define NUART_ID                        NUART_ID_2
#define NSTREAM_ISR_CALLBACK                       nuart_callback_2
#elif (NBOARD_USES_STD_STREAM == 5)
#define NUART_ID                        NUART_ID_5
#define NSTREAM_ISR_CALLBACK                       nuart_callback_5
#else
#define NUART_ID                        NUART_ID_15
#define NSTREAM_ISR_CALLBACK                       nuart_callback_15
#endif
    
#define NSTREAM_INIT()                  nuart_init(NUART_ID, NULL)
   
#define NSTREAM_IS_INITIALIZED()        nuart_is_initialized(NUART_ID)
    
#define NSTREAM_SEND(buffer, size)      nuart_send(NUART_ID, (buffer), (size))

#define NSTREAM_SEND_BYTE(byte)         nuart_send_byte(NUART_ID, (byte))

#define NSTREAM_RECEIVE_BYTE()          nuart_receive_byte(NUART_ID)

#elif (NBOARD_USES_STD_STREAM >= 16) && (NBOARD_USES_STD_STREAM < 32)
#elif (NBOARD_USES_STD_STREAM >= 32) && (NBOARD_USES_STD_STREAM < 48)
#endif

struct nstdio_buff nstdio_buff;

#if !defined(NSTREAM_RECEIVE_BYTE)
#define NSTREAM_RECEIVE_BYTE()			getchar()
#endif

#if !defined(NSTREAM_SEND_BYTE)
#define NSTREAM_SEND_BYTE(c)			putchar(c)
#endif

#if !defined(NSTREAM_IS_INITIALIZED)
#define NSTREAM_IS_INITIALIZED()		true
#endif

void nstdio_putc(struct nstdio_buff * buff, uint8_t c)
{
    static bool is_initialized;
    
    if (!is_initialized) {
        is_initialized = true;
        NLQUEUE_INIT(&buff->out);
    }
    NLQUEUE_PUT_FIFO(&buff->out, c);
}

uint8_t nstdio_getc(struct nstdio_buff * buff)
{
    return NSTREAM_RECEIVE_BYTE();
}

bool nstdio_flush(struct nstdio_buff * buff)
{
    if (!NSTREAM_IS_INITIALIZED()) {
        return false;
    }
    while (!NLQUEUE_IS_EMPTY(&buff->out)) {
        char c;
        
        c = NLQUEUE_GET(&buff->out);
        NSTREAM_SEND_BYTE(c);
    }
    
    return true;
}

/** @} *//*==================================================================*/
/** @defgroup   nlogger_x_impl Extended logger module implementation
 *  @brief      Extended logger module implementation
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   nmem_pool_impl Memory pool implementation
 *  @brief      Memory pool implementation
 *  @{ *//*==================================================================*/

void nmem_pool_init(
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

void * nmem_pool_alloc(struct nmem_pool * pool)
{
    void * retval = NULL;
    struct nos_critical local;

    NOS_CRITICAL_LOCK(&local);
    if (pool->free != 0u) {
        pool->free--;
        retval = nlist_sll_next(&pool->next);
        nlist_sll_remove_from(&pool->next);
    }
    NOS_CRITICAL_UNLOCK(&local);

    return retval;
}

void nmem_pool_free(struct nmem_pool * pool, void * mem)
{
    struct nlist_sll * current = mem;
    struct nos_critical local;

    NOS_CRITICAL_LOCK(&local);
    pool->free++;
    nlist_sll_add_before(&pool->next, current);
    NOS_CRITICAL_UNLOCK(&local);
}

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
        nmem_pool_free(event->pool, (void *)event);
    }
}
#else
#define event_delete(a_event)
#endif

#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
void * nevent_create(struct nmem_pool * pool, uint_fast16_t id)
{
    struct nevent * event;

    event = nmem_pool_alloc(pool);

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
/** @defgroup   nsm_impl State machine implementation
 *  @brief      State machine implementation
 *  @{ *//*==================================================================*/

#define sm_event(event)                 &g_events[(event)]

static const struct nevent g_events[] =
{
    [NSM_SUPER] = NEVENT_INITIALIZER(NSM_SUPER),
    [NSM_ENTRY] = NEVENT_INITIALIZER(NSM_ENTRY),
    [NSM_EXIT] = NEVENT_INITIALIZER(NSM_EXIT),
    [NSM_INIT] = NEVENT_INITIALIZER(NSM_INIT),
    
    [NSIGNAL_RETRIGGER] = NEVENT_INITIALIZER(NSIGNAL_RETRIGGER),
    [NSIGNAL_AFTER] = NEVENT_INITIALIZER(NSIGNAL_AFTER),
    [NSIGNAL_EVERY] = NEVENT_INITIALIZER(NSIGNAL_EVERY),
    
    [NEVENT_NULL] = NEVENT_INITIALIZER(NEVENT_NULL),
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
/** @defgroup   nepa_impl Event Processing Agent (EPA) implementation
 *  @brief      Event Processing Agent (EPA) implementation
 *  @{ *//*==================================================================*/

#define epa_from_prio(ctx, a_prio)      (&(ctx)->mempool[(a_prio)])

#define prio_from_epa(a_epa)            ((a_epa)->task.prio)

#if (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE)

#define prio_queue_insert(a_queue, a_prio)                                  \
        nbitarray_s_set(&(a_queue)->bitarray, (a_prio))

#define prio_queue_remove(a_queue, a_prio)                                  \
        nbitarray_s_clear(&(a_queue)->bitarray, (a_prio))

#define prio_queue_get_highest(a_queue)                                     \
        nbitarray_s_msbs(&(a_queue)->bitarray)

#define prio_queue_is_set(a_queue, a_prio)                                  \
        nbitarray_s_is_set(&(a_queue)->bitarray, (a_prio))

#else /* (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE) */

#define prio_queue_insert(a_queue, a_prio)                                  \
        nbitarray_x_set(&(a_queue)->bitarray[0], (a_prio))

#define prio_queue_remove(a_queue, a_prio)                                  \
        nbitarray_x_clear(&(a_queue)->bitarray[0], (a_prio))

#define prio_queue_get_highest(a_queue)                                     \
        nbitarray_x_msbs(&(a_queue)->bitarray[0])

#define prio_queue_is_set(a_queue, a_prio)                                  \
        nbitarray_x_is_set(&(a_queue)->bitarray[0], (a_prio))
#endif /* (NCONFIG_EPA_INSTANCES <= NBITARRAY_S_MAX_SIZE) */

static void task_init(struct ntask * task, uint_fast8_t prio)
{
    task->prio = prio;
}

static void equeue_init(struct nequeue * equeue)
{
    NREQUIRE((equeue->np_lq_storage != NULL) && (equeue->super.empty != 0u));
    NREQUIRE((equeue->super.head = 0u) && (equeue->super.tail == 1u));
    NPLATFORM_UNUSED_ARG(equeue);
}

nerror nepa_send_signal(struct nepa * epa, uint_fast16_t signal)
{
    return nepa_send_event(epa, &g_events[signal]);
}

nerror nepa_send_event(struct nepa * epa, const struct nevent * event)
{
    struct nos_critical local;
    int_fast8_t idx;
    nerror error;

    NREQUIRE(NSIGNATURE_OF(epa) == NSIGNATURE_EPA);

    event_ref_up(event);
    NOS_CRITICAL_LOCK(&local);
    idx = NLQUEUE_IDX_FIFO(&epa->equeue);

    if (idx >= 0) {
        NLQUEUE_IDX_REFERENCE(&epa->equeue, idx) = event;
        //prio_queue_insert(&epa->scheduler->ready, prio_from_epa(epa));
        NOS_CRITICAL_UNLOCK(&local);
        error = EOK;
    } else {
        NOS_CRITICAL_UNLOCK(&local);
        /* Undo the event_ref_up step from above.
         */
        event_ref_down(event);
        error = -EOBJ_INVALID;
    }
    
    return error;
}

/** @} *//*==================================================================*/
/** @defgroup   nscheduler_impl Scheduler implementation
 *  @brief      Scheduler implementation
 *  @{ *//*==================================================================*/

static void schedule_initialize_epas(
        struct nscheduler * schedule, 
        const struct nepa * const * epa_registry)
{
   
}

bool nscheduler_is_started(struct nscheduler * scheduler)
{
    return !!scheduler->current;
}

void nscheduler_task_init(
        struct nscheduler * scheduler, 
        struct nscheduler_task * task,
        task_fn * fn,
        void * arg,
        uint8_t prio)
{
}

void nscheduler_task_ready(struct nscheduler_task * task)
{

}

void nscheduler_task_block(struct nscheduler_task * task)
{

}

/*
 * 1. If no ready task is set then set the default idle task.
 */
#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
void nscheduler_start(
        struct nscheduler * scheduler,
        const struct nepa * const * epa_registry)
#else
NPLATFORM_NORETURN(void nscheduler_start(
        struct nscheduler * scheduler, 
        const struct nepa * const * epa_registry))
#endif
{
    schedule_initialize_epas(scheduler, epa_registry);

#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
                                    /* While there are ready tasks in system */
    while (!should_exit) {
#else
    while (true) {
#endif
     
    }

#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
    for (uint_fast8_t prio = 0u; prio < NCONFIG_EPA_INSTANCES; prio) {
        struct ntask * task;

        task = epa_from_prio(scheduler, prio);

        ntask_stop(task);
    }

    for (uint_fast8_t prio = 0u; prio < NCONFIG_EPA_INSTANCES; prio) {
        struct ntask * task;

        task = epa_from_prio(scheduler, prio);

        ntask_delete(task);
    }
#endif
}

#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
void nscheduler_stop(struct nscheduler * scheduler)
{
    scheduler->should_exit = true;
}
#endif

/** @} *//*==================================================================*/
/** @defgroup   nsys System module
 *  @brief      System module
 *  @{ *//*==================================================================*/

/** @brief      Idle EPA Event queue
 */
static struct epa_queue_idle nevent_queue(2) g_epa_queue_idle;

static nsm_action idle_state_init(struct nsm *, const struct nevent *);

static nsm_action idle_state_init(struct nsm * sm, const struct nevent * event)
{
    NPLATFORM_UNUSED_ARG(sm);
    NPLATFORM_UNUSED_ARG(event);

    return nsm_event_ignored();
}

const char * const nsys_build_date = NPLATFORM_DATE;
const char * const nsys_build_time = NPLATFORM_TIME;
const char * const nsys_platform_id = NPLATFORM_ID;
const char * const nsys_platform_version = NPLATFORM_VERSION;

const struct nepa nsys_epa_idle = NEPA_INITIALIZER(
            &g_epa_queue_idle, 
            NEPA_FSM_TYPE, 
            idle_state_init, 
            NULL);

void nsys_init(void)
{
    nboard_init();
    nstdio_flush(&nstdio_buff);
}

/** @} */
/** @} */
