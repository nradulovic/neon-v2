/*
 * main.c
 *
 *  Created on: Aug 27, 2019
 *      Author: nenad
 */

#include "neon.h"
#include "ntestsuite.h"

#if defined(NEON_TEST_NPORT)
#include "test_nport.h"
#endif

#if defined(NEON_TEST_NBITS)
#include "test_nbits.h"
#endif

#if defined(NEON_TEST_NLIST_SLL)
#include "test_nlist_sll.h"
#endif

#if defined(NEON_TEST_NLIST_DLL)
#include "test_nlist_dll.h"
#endif

#if defined(NEON_TEST_NLQUEUE)
#include "test_nlqueue.h"
#endif

int main(void)
{
	static ntestsuite_fn * const tests[] =
	{
#if defined(NEON_TEST_NPORT)
		test_exec_nport,
#endif
#if defined(NEON_TEST_NBITS)
		test_exec_nbits,
#endif
#if defined(NEON_TEST_NLIST_SLL)
		test_exec_nlist_sll,
#endif
#if defined(NEON_TEST_NLIST_DLL)
		test_exec_nlist_dll,
#endif
#if defined(NEON_TEST_NLQUEUE)
		test_exec_nlqueue,
#endif
		NULL
	};
	ntestsuite_run_tests(tests);

	return 0;
}
