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

#ifndef CLADS_TREE_H
#define CLADS_TREE_H

#include "clads.h"


/**
 *
 */
typedef struct clads_tree_node
{
    struct clads_tree_node *parent;
    clads_addr_type info;
    struct clads_tree_node *lchild;
    struct clads_tree_node *rchild;
    clads_size_type height;
} clads_tree_node_type;

/**
 * Tree structure
 */
typedef struct clads_tree
{
    clads_tree_node_type *root;
    clads_size_type n_node;
    clads_bool_type is_set;
    /*
     * This function tell if two nodes have the same information
     * (i.e. are equal).
     */
    clads_order_type (*f_compare)(clads_addr_type, clads_addr_type);
} clads_tree_type;


/**
 * Creating a new tree node
 */
clads_tree_node_type *
clads_tree_node_new(clads_void_type);

/**
 * Initialize a given tree node
 */
inline clads_void_type
clads_tree_node_initialize(clads_tree_node_type *t);

/**
 * Finalize a given tree node
 */
inline clads_void_type
clads_tree_node_finalize(clads_tree_node_type *t);

/**
 * Initialize a given tree
 */
inline clads_void_type
clads_tree_initialize(clads_tree_type *t);

/**
 * Finalize a given tree
 */
inline clads_void_type
clads_tree_finalize(clads_tree_type *t);

/**
 * Creates a copy of a tree.
 */
int
clads_tree_copy(const clads_tree_type *ta,
                clads_tree_type *tb);

/**
 * Initialize a given tree node
 */
inline clads_void_type
clads_tree_node_initialize(clads_tree_node_type *n);

/**
 * Finalize a given tree node
 */
inline clads_void_type
clads_tree_node_finalize(clads_tree_node_type *n);

/**
 *
 */
clads_tree_node_type *
clads_tree_insert(clads_tree_type *t,
                  clads_tree_node_type *n);

/**
 *
 */
clads_tree_node_type *
clads_tree_remove(clads_tree_type *t,
                  clads_tree_node_type *n);

/**
 *
 */
clads_tree_node_type *
clads_tree_search(clads_tree_type *t,
                  clads_addr_type info);

/**
 *
 */
clads_tree_node_type *
clads_tree_minimun(clads_tree_type *t);

/**
 *
 */
clads_tree_node_type *
clads_tree_minimun_from_node(clads_tree_type *t,
                             clads_tree_node_type *n);

/**
 *
 */
clads_tree_node_type *
clads_tree_maximun(clads_tree_type *t);

/**
 *
 */
clads_tree_node_type *
clads_tree_maximun_from_node(clads_tree_type *t,
                             clads_tree_node_type *n);


#endif
