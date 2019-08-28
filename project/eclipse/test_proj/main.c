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
		NULL
	};
	ntestsuite_run_tests(tests);

	return 0;
}
