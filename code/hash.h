/**
 * Copyright (C) 2011 Joao Paulo de Souza Medeiros
 *
 * Author(s): Joao Paulo de Souza Medeiros <ignotus21@gmail.com>
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

#ifndef CLADS_HASH_H
#define CLADS_HASH_H

#include "clads.h"
#include "list.h"

#define CLADS_HASH_INITIAL_TABLE_SIZE   2


typedef struct clads_hash_node
{
    clads_id_type key;
    void *info;
} clads_hash_node_type;

typedef struct clads_hash
{
    clads_list_type **table;
    clads_size_type size;
    clads_size_type n_node;
    clads_bool_type is_set;
    /*
     * This is the hash function
     */
    clads_size_type (*f_hash)(clads_size_type, clads_id_type);
} clads_hash_type;


/**
 *
 */
clads_hash_node_type *
clads_hash_node_new(void);

/**
 *
 */
void
clads_hash_node_initialize(clads_hash_node_type *n);

/**
 *
 */
void
clads_hash_node_finalize(clads_hash_node_type *n);

/**
 *
 */
void
clads_hash_initialize(clads_hash_type *h);

/**
 *
 */
void
clads_hash_finalize(clads_hash_type *h);

/**
 *
 */
clads_bool_type
clads_hash_insert(clads_hash_type *h,
                  clads_hash_node_type *n);

/**
 *
 */
clads_bool_type
clads_hash_remove(clads_hash_type *h,
                  clads_hash_node_type *n);

/**
 *
 */
clads_hash_node_type *
clads_hash_search(clads_hash_type *h,
                  clads_id_type key);

/**
 *
 */
clads_hash_node_type *
clads_hash_search_by_info(clads_hash_type *h,
                          void *info);

#endif
