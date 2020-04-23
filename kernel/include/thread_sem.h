
#ifndef NEON_THREAD_SEM_H_
#define NEON_THREAD_SEM_H_

#include "../../kernel/include/nport_platform.h"
#include "../../kernel/include/nqueue_pqueue.h"
#include "../../kernel/include/ntask.h"

enum nsem_state
{
    NSEM_STATE_INIT,
    NSEM_STATE_ACTIVE = 0x1,
    NSEM_STATE_INACTIVE = 0x2,
    NSEM_STATE_TERMINATED = 0xDEADC0DE,
};

struct nsem
{
    int32_t count;
    struct npqueue queue;
    enum nsem_state state;
};

/**
 * Initialize a semaphore
 *
 * This macro initializes a semaphore with a value for the
 * counter. Internally, the semaphores use an "unsigned int" to
 * represent the counter, and therefore the "count" argument should be
 * within range of an unsigned int.
 *
 * \param s (struct nsem *) A pointer to the nsem struct
 * representing the semaphore
 *
 * \param c (unsigned int) The initial count of the semaphore.
 * \hideinitializer
 */
NPLATFORM_INLINE
void nsem_init(struct nsem * sem, uint32_t count)
{
    sem->count = count;
    npqueue_init(&sem->queue);
    sem->state = NSEM_STATE_ACTIVE;
}

/**
 * Wait for a semaphore
 *
 * This macro carries out the "wait" operation on the semaphore. The
 * wait operation causes the protothread to block while the counter is
 * zero. When the counter reaches a value larger than zero, the
 * protothread will continue.
 *
 * \param pt (struct pt *) A pointer to the protothread (struct pt) in
 * which the operation is executed.
 *
 * \param s (struct nsem *) A pointer to the nsem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define nsem_wait(s)            nfiber_wait_while(np_sem_wait(s))

#define nerror ((struct nthread_tls * )pt_tls)->error

NPLATFORM_INLINE
bool np_sem_wait(struct nsem * sem)
{
    bool is_switch_pending = false;
    
    switch (sem->state) {
        case NSEM_STATE_ACTIVE:
        case NSEM_STATE_INACTIVE:
            break;
        case NSEM_STATE_TERMINATED:
            nerror = -ESTD_ABORT;
            return (is_switch_pending);
        default:
            nerror = -ESTD_INVAL;
            return (is_switch_pending);
    }
    
    if (sem->count > 0) {
        sem->count--;
    } else {
        /* TODO:
         * Insert current thread to this semaphore and then make it blocked.
         */
        is_switch_pending = true;
    }
    return (is_switch_pending);
}

struct nthread_tls
{
    int32_t error;
};


/**
 * Signal a semaphore
 *
 * This macro carries out the "signal" operation on the semaphore. The
 * signal operation increments the counter inside the semaphore, which
 * eventually will cause waiting protothreads to continue executing.
 *
 * \param pt (struct pt *) A pointer to the protothread (struct pt) in
 * which the operation is executed.
 *
 * \param s (struct nsem *) A pointer to the nsem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define PT_SEM_SIGNAL(s)                                                    \
    do {                                                                    \
        struct nsem * l_npt_sem = (s);                                    \
        l_npt_sem->count++; \
        if (l_npt_sem->count > 1) {                                        \
        }                                                                   \
        if (false/* Ask scheduler should we yield */) \
        PT_YIELD();                                                         \
    } while (0)

#endif /* NEON_THREAD_SEM_H_ */

/** @} */
/** @} */
   
