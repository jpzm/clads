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

#include "tree.h"


clads_order_type
clads_tree_default_f_compare(void *a,
                             void *b)
{
    /*
     * As default threat as integer values.
     */
    if (*((int *) a) == *((int *) b))
        return equal;
    if (*((int *) a) < *((int *) b))
        return less;
    return more;
}

void
clads_tree_node_initialize(clads_tree_node_type *n)
{
    n->parent = NULL;
    n->info = NULL;
    n->l_child = malloc(sizeof(clads_list_type));
    clads_list_initialize(n->l_child);
}

void
clads_tree_node_finalize(clads_tree_node_type *n)
{
    if (n != NULL)
    {
        /*
         * Finalize the children first.
         */
        clads_list_node_type *e = n->l_child->head;

        while (e != NULL)
        {
            clads_tree_node_finalize((clads_tree_node_type *) e->info);

            e = e->next;
        }

        clads_list_finalize(n->l_child);

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
clads_tree_initialize(clads_tree_type *t)
{
    t->root = NULL;
    t->n_node = 0;
    t->f_compare = &clads_tree_default_f_compare;
}

void
clads_tree_finalize(clads_tree_type *t)
{
    if (t != NULL)
        clads_tree_node_finalize(t->root);
#if CLADS_DEBUG
    else
        printf("W. [TREE] Trying to finalize a NULL pointer.\n");
#endif
}

int
clads_tree_copy(const clads_tree_type *ta,
                clads_tree_type *tb)
{
    // TODO
    return 0;
}

clads_tree_node_type *
clads_tree_insert(clads_tree_type *t,
                  clads_tree_node_type *p,
                  clads_tree_node_type *n)
{
    clads_list_node_type *e;

    /*
     * Check if the parent exists or is NULL.
     */
    if (p == NULL && t->root == NULL)
    {
        t->root = n;
        t->n_node++;

        return n;
    }

    if (p != NULL && clads_tree_search_node(t, p->info))
    {
        n->parent = p;

        if (p != NULL)
        {
            e = clads_list_node_new();
            e->info = (void *) n;
            clads_list_insert(p->l_child, e);
        }
        else
            t->root = n;

        t->n_node++;

        return n;
    }

    return NULL;
}

clads_tree_node_type *
clads_tree_search_node_from(clads_tree_type *t,
                            clads_tree_node_type *r,
                            void *info)
{
    clads_tree_node_type *n, *a;
    clads_list_node_type *l;

    /*
     * Checking for current node
     */
    if (t->f_compare(r->info, info) == equal)
        return r;

    /*
     * Recurssion over children
     */
    l = r->l_child->head;
    a = NULL;

    while (l != NULL && a == NULL)
    {
        n = (clads_tree_node_type *) l->info;
        a = clads_tree_search_node_from(t, n, info);
        l = l->next;
    }

    return a;
}

clads_tree_node_type *
clads_tree_search_node(clads_tree_type *t,
                       void *info)
{
    return clads_tree_search_node_from(t, t->root, info);
}
