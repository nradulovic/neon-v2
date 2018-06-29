
#ifndef NEON_THREAD_SEM_H_
#define NEON_THREAD_SEM_H_

#include "port/nport_platform.h"
#include "thread/nthread.h"

enum np_thread_sem_state
{
    NP_THREAD_SEM_STATE_INIT,
    NP_THREAD_SEM_STATE_ACTIVE,
    NP_THREAD_SEM_STATE_INACTIVE,
    NP_THREAD_SEM_STATE_TERMINATED
};

struct pt_sem
{
    int32_t count;
    enum np_thread_sem_state state;
};

/**
 * Initialize a semaphore
 *
 * This macro initializes a semaphore with a value for the
 * counter. Internally, the semaphores use an "unsigned int" to
 * represent the counter, and therefore the "count" argument should be
 * within range of an unsigned int.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \param c (unsigned int) The initial count of the semaphore.
 * \hideinitializer
 */
NPLATFORM_INLINE
void pt_sem_init(struct pt_sem * sem, uint32_t count)
{
    sem->count = count;
    sem->state = NP_THREAD_SEM_STATE_ACTIVE;
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
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define PT_SEM_WAIT(s)	\
    NP_FIBER_EXEC(np_pt_sem_wait_preexec(s), true, np_pt_sem_wait_postexec(s))

#define nerror ((struct nthread_tls * )pt_tls)->error

NPLATFORM_INLINE
bool np_pt_sem_wait(struct pt_sem * sem)
{
    bool is_switch_pending = false;
    
    if (false/*TODO: Maybe semaphore was deleted in the mean time? */) {
        nerror = -ESTD_ABORT;
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
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define PT_SEM_SIGNAL(s)                                                    \
    do {                                                                    \
        struct pt_sem * l_npt_sem = (s);                                    \
        l_npt_sem->count++; \
        if (l_npt_sem->count > 1) {                                        \
        }                                                                   \
        PT_YIELD();                                                         \
    } while (0)

#endif /* NEON_THREAD_SEM_H_ */

/** @} */
/** @} */
   
