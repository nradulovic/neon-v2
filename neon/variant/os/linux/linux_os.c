/*
 * linux_os.c
 *
 *  Created on: Aug 27, 2019
 *      Author: nenad
 */

#include "core/nport.h"

#include <pthread.h>

static pthread_mutex_t g_nglobal_mutex = PTHREAD_MUTEX_INITIALIZER;

void nos_critical_lock(struct nos_critical * lock)
{
    NPLATFORM_UNUSED_ARG(lock);
    pthread_mutex_lock(&g_nglobal_mutex);
}

void nos_critical_unlock(struct nos_critical * lock)
{
    NPLATFORM_UNUSED_ARG(lock);
	pthread_mutex_unlock(&g_nglobal_mutex);
}
