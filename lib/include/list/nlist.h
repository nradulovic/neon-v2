/*
 * Neon
 * Copyright (C)  2017  Nenad Radulovic
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Linked lists header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_list Linked lists
 *  @brief       Single Linked Lists (SLL) and Doubly Linked Lists (DLL).
 *
 *  There are three different linked lists:
 *  - single linked list `sll`
 *  - doubly linked list `dll`
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_LIST_H_
#define NEON_MODULE_LIST_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "port/nport_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Macro to get the pointer to structure which contains any struct
 *              of a list.
 *  @param[in]  ptr
 *              Pointer to structure/data that is containing a list structure.
 *  @param[in]  type
 *              Type of variable which contains a list structure.
 *  @param[in]  member
 *              Name of member in variable structure.
 *  @return     Pointer to container structure.
 *
 *  @code
 *  struct my_struct
 *  {
 *      char my_name[8];
 *      struct nlist_dll some_list;
 *      int some_stuff;
 *  };
 *
 *  struct nlist_dll * current_element;
 *  struct my_struct * current;
 *
 *  current = NLIST_ENTRY(current_element, struct my_struct, some_list);
 *  @endcode
 *  @mseffect
 */
#define NLIST_ENTRY(ptr, type, member)                                      \
    NPLATFORM_CONTAINER_OF(ptr, type, member)
    
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_LIST_H_ */
