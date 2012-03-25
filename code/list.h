/**
 * Copyright (C) 2011-2012 Joao Paulo de Souza Medeiros
 *
 * Author(s): Joao Paulo de Souza Medeiros <jpsm1985@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef CLADS_LIST_H
#define CLADS_LIST_H

#include "clads.h"


typedef struct clads_list_node
{
    struct clads_list_node *prev;
    clads_addr_type info;
    struct clads_list_node *next;
} clads_list_node_type;

typedef struct clads_list
{
    clads_list_node_type *head;
    clads_list_node_type *tail;
    clads_list_node_type *iter;
    clads_bool_type do_free_info;
    /*
     * This flag indicates to `clads_list_insert' function to not insert
     * duplicated nodes.
     * But, this flag do not change `clads_list_push' and `clads_list_enqueue'
     * functions behaviour.
     */
    clads_bool_type is_set;
    /*
     * This function tell if two nodes have the same information
     * (i.e. are equal).
     */
    clads_order_type (*f_compare)(struct clads_list *,
                                  clads_addr_type,
                                  clads_addr_type);
    /*
     * This function creates a copy of node's information.
     */
    clads_addr_type (*f_copy)(clads_addr_type);
    /*
     * Used by external programs to store extra information (e.g. bindings).
     */
    clads_addr_type more;
} clads_list_type;


/**
 *
 */
clads_list_node_type *
clads_list_node_new(clads_void_type);

/**
 *
 */
clads_void_type
clads_list_node_initialize(clads_list_node_type *n);

/**
 *
 */
clads_void_type
clads_list_node_finalize(clads_list_node_type *n,
                         clads_bool_type do_free_info);

/**
 *
 */
clads_void_type
clads_list_initialize(clads_list_type *l);

/**
 *
 */
clads_void_type
clads_list_finalize(clads_list_type *l);

/**
 *
 */
clads_list_type *
clads_list_copy(clads_list_type *l);

/**
 *
 */
clads_size_type
clads_list_size(clads_list_type *l);

/**
 *
 */
clads_bool_type
clads_list_is_empty(clads_list_type *l);

/**
 *
 */
clads_bool_type
clads_list_insert(clads_list_type *l,
                  clads_list_node_type *x);

/**
 *
 */
clads_bool_type
clads_list_remove(clads_list_type *l,
                  clads_list_node_type *x);

/**
 *
 */
clads_list_node_type *
clads_list_search(clads_list_type *l,
                  clads_addr_type info);

/**
 *
 */
clads_bool_type
clads_list_push(clads_list_type *l,
                clads_list_node_type *x);

/**
 *
 */
clads_list_node_type *
clads_list_pop(clads_list_type *l);

/**
 *
 */
clads_bool_type
clads_list_enqueue(clads_list_type *l,
                   clads_list_node_type *x);

/**
 *
 */
clads_list_node_type *
clads_list_dequeue(clads_list_type *l);

/**
 *
 */
clads_list_node_type *
clads_list_next(clads_list_type *l);

#endif
