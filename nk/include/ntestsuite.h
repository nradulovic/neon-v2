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
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Testsuite header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_testsuite Testsuite
 *  @brief       Testsuite.
 *
 *  @{
 */

#ifndef NEON_MODULE_TESTSUITE_H_
#define NEON_MODULE_TESTSUITE_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NK_TESTSUITE_TEST(test_name)                                        \
	{       																\
    	.test_fn = test_name,                                 				\
    	.name = # test_name                                                 \
    }

#define NK_TESTSUITE_TEST_TERMINATE()										\
	{																		\
		.test_fn = NULL,													\
		.name = NULL														\
	}

#define NTESTSUITE_EXPECT_UINT(a_number)                                    \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.ui = (a_number);                                                \
        np_testsuite_expect(val, NP_TESTSUITE_TYPE_UINT);                   \
    } while (0)

#define NTESTSUITE_EXPECT_INT(a_number)                                     \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.si = (a_number);                                                \
	    np_testsuite_expect(val, NP_TESTSUITE_TYPE_INT);                    \
    } while (0)

#define NTESTSUITE_EXPECT_PTR(a_pointer)                                    \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.ptr = (a_pointer);                                              \
        np_testsuite_expect(val, NP_TESTSUITE_TYPE_PTR);                    \
    } while (0)
    
#define NTESTSUITE_EXPECT_STR(a_string)                                     \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.str = (a_string);                                               \
        np_testsuite_expect(val, NP_TESTSUITE_TYPE_STR);                    \
    } while (0)

#define NTESTSUITE_EXPECT_BOOL(a_bool)                                      \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.b = (a_bool);                                                   \
	    np_testsuite_expect(val, NP_TESTSUITE_TYPE_BOOL);                   \
    } while (0)

#define NTESTSUITE_NOT_EXPECT_UINT(a_number)                                \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.ui = (a_number);                                                \
        np_testsuite_expect(val, NP_TESTSUITE_TYPE_NOT_UINT);               \
    } while (0)

#define NTESTSUITE_NOT_EXPECT_INT(a_number)                                 \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.si = (a_number);                                                \
	    np_testsuite_expect(val, NP_TESTSUITE_TYPE_NOT_INT);                \
    } while (0)

#define NTESTSUITE_NOT_EXPECT_PTR(a_pointer)                                \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.ptr = (a_pointer);                                              \
        np_testsuite_expect(val, NP_TESTSUITE_TYPE_NOT_PTR);                \
    } while (0)
    
#define NTESTSUITE_NOT_EXPECT_STR(a_string)                                 \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.str = (a_string);                                               \
        np_testsuite_expect(val, NP_TESTSUITE_TYPE_NOT_STR);                \
    } while (0)

#define NTESTSUITE_NOT_EXPECT_BOOL(a_bool)                                  \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.b = (a_bool);                                                   \
	    np_testsuite_expect(val, NP_TESTSUITE_TYPE_NOT_BOOL);               \
    } while (0)
    
#define NTESTSUITE_ACTUAL_UINT(a_number)                                    \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.ui = (a_number);                                                \
	    np_testsuite_actual(__LINE__, (val));                         \
    } while (0)

#define NTESTSUITE_ACTUAL_INT(a_number)                                     \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.si = (a_number);                                                \
	    np_testsuite_actual(__LINE__, (val));                         \
    } while (0)
                
#define NTESTSUITE_ACTUAL_PTR(a_pointer)                                    \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.ptr = (a_pointer);                                              \
        np_testsuite_actual(__LINE__, (val));                         \
    } while (0)
    
#define NTESTSUITE_ACTUAL_STR(a_string)                                     \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.str = (a_string);                                               \
        np_testsuite_actual(__LINE__, (val));                         \
    } while (0)
    
#define NTESTSUITE_ACTUAL_BOOL(a_bool)                                      \
    do {                                                                    \
        union np_testsuite_test_val val;                                    \
        val.b = (a_bool);                                                   \
        np_testsuite_actual(__LINE__, (val));                         \
    } while (0)

#define NK_TESTSUITE_FIXTURE_NAME(a_name)									\
		__FILE__ ":" # a_name

enum np_testsuite_type
{
    NP_TESTSUITE_TYPE_UINT,
    NP_TESTSUITE_TYPE_INT,
    NP_TESTSUITE_TYPE_PTR,
    NP_TESTSUITE_TYPE_BOOL,
    NP_TESTSUITE_TYPE_STR,
    NP_TESTSUITE_TYPE_NOT_UINT,
    NP_TESTSUITE_TYPE_NOT_INT,
    NP_TESTSUITE_TYPE_NOT_PTR,
    NP_TESTSUITE_TYPE_NOT_BOOL,
    NP_TESTSUITE_TYPE_NOT_STR,
};

struct nk_testsuite_test
{
	void (*test_fn)(void);
	const char * name;
};

union np_testsuite_test_val
{
	uint32_t ui;
	int32_t si;
	const void * ptr;
    const char * str;
	bool b;
};


void nk_testsuite_run_tests(const struct nk_testsuite_test * array);

void nk_testsuite_set_fixture(
        void (* setup)(void),
        void (* teardown)(void),
        const char * name);

void np_testsuite_expect(
        union np_testsuite_test_val value, 
        enum np_testsuite_type type);

void np_testsuite_actual(uint32_t line, union np_testsuite_test_val value);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_MODULE_TESTSUITE_H_ */
