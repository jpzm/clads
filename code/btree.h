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

#ifndef CLADS_BTREE_H
#define CLADS_BTREE_H

#include "clads.h"


/**
 *
 */
typedef struct clads_btree_node
{
    struct clads_btree_node *parent;
    void *info;
    struct clads_btree_node *lchild;
    struct clads_btree_node *rchild;
} clads_btree_node_type;

/**
 * Tree structure
 */
typedef struct clads_btree
{
    clads_btree_node_type *root;
    clads_size_type n_node;
    /*
     * This function tell if two nodes have the same information
     * (i.e. are equal).
     */
    clads_order_type (*f_compare)(void *, void *);
} clads_btree_type;


/**
 * Initialize a given tree node
 */
inline void
clads_btree_initialize(clads_btree_type *t);

/**
 * Finalize a given tree node
 */
inline void
clads_btree_finalize(clads_btree_type *t);

/**
 * Initialize a given tree
 */
inline void
clads_btree_initialize(clads_btree_type *t);

/**
 * Finalize a given tree
 */
inline void
clads_btree_finalize(clads_btree_type *t);

/**
 * Creates a copy of a tree.
 */
int
clads_btree_copy(const clads_btree_type *ta,
                 clads_btree_type *tb);

/**
 * Initialize a given tree node
 */
inline void
clads_btree_node_initialize(clads_btree_node_type *n);

/**
 * Finalize a given tree node
 */
inline void
clads_btree_node_finalize(clads_btree_node_type *n);

/**
 *
 */
clads_btree_node_type *
clads_btree_insert(clads_btree_type *t,
                   clads_btree_node_type *n);

/**
 *
 */
clads_btree_node_type *
clads_btree_remove(clads_btree_type *t,
                   clads_btree_node_type *n);

/**
 *
 */
clads_btree_node_type *
clads_btree_search(clads_btree_type *t,
                   void *info);


#endif
