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

#include "btree.h"


clads_order_type
clads_btree_default_f_compare(void *a,
                              void *b)
{
    /*
     * As default threat as integer values.
     */
    if (*CLADS_CAST(a, int *) > *CLADS_CAST(b, int *))
        return more;
    if (*CLADS_CAST(a, int *) < *CLADS_CAST(b, int *))
        return less;
    return equal;
}

void
clads_btree_node_initialize(clads_btree_node_type *n)
{
    n->parent = NULL;
    n->info = NULL;
    n->lchild = NULL;
    n->rchild = NULL;
}

void
clads_btree_node_finalize(clads_btree_node_type *n)
{
    if (n != NULL)
    {
        /*
         * Finalize the children first.
         */
        clads_btree_node_finalize(n->lchild);
        clads_btree_node_finalize(n->rchild);

        if (n->info != NULL)
            free((void *) n->info);

        n->info = NULL;
    }
#if CLADS_DEBUG
    else
        printf("W. [TREE] Trying to finalize a NULL pointer.\n");
#endif
}

void
clads_btree_initialize(clads_btree_type *t)
{
    t->root = NULL;
    t->n_node = 0;
    t->f_compare = &clads_btree_default_f_compare;
}

void
clads_btree_finalize(clads_btree_type *t)
{
    if (t != NULL)
        clads_btree_node_finalize(t->root);
#if CLADS_DEBUG
    else
        printf("W. [TREE] Trying to finalize a NULL pointer.\n");
#endif
}

int
clads_btree_copy(const clads_btree_type *ta,
                 clads_btree_type *tb)
{
    // TODO
    return 0;
}

clads_btree_node_type *
clads_btree_insert(clads_btree_type *t,
                   clads_btree_node_type *n)
{
    // TODO
    return NULL;
}

clads_btree_node_type *
clads_btree_remove(clads_btree_type *t,
                   clads_btree_node_type *n)
{
    // TODO
    return NULL;
}

clads_btree_node_type *
clads_btree_search(clads_btree_type *t,
                   void *info)
{
    // TODO
    return NULL;
}
