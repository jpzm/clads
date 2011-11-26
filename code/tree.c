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


clads_bool_type
clads_tree_default_f_node_eq(clads_tree_node_type *a,
                             clads_tree_node_type *b)
{
    return a == b;
}

void
clads_tree_initialize(clads_tree_type *t)
{
    t->root = NULL;
    t->n_node = 0;
    t->f_node_eq = &clads_tree_default_f_node_eq;
}

void
clads_tree_finalize(clads_tree_type *t)
{
    clads_tree_node_finalize(t->root);
    free((void *) t);
}

int
clads_tree_copy(const clads_tree_type *ta,
                clads_tree_type *tb)
{
    // TODO
    return 0;
}

void
clads_tree_node_initialize(clads_tree_node_type *n)
{
    n->id = -1;
    n->parent = NULL;
    n->l_child = NULL;
    n->info = NULL;
    n->attr = NULL;
    n->status = off;
}

void
clads_tree_node_finalize(clads_tree_node_type *n)
{
    clads_list_type *l = n->l_child;
    clads_tree_node_type *c;

    while (l)
    {
        c = (clads_tree_node_type *) n->info;
        clads_tree_node_finalize(c);

        l = l->next;
    }

    free((void *) n);
}

clads_tree_node_type *
clads_tree_add_node(clads_tree_type *t,
                    clads_tree_node_type *p,
                    void *info)
{
    clads_tree_node_type *n;

    if (p == NULL || clads_tree_search_node(t, p->info))
    {
        n = malloc(sizeof(struct tree_node));

        clads_tree_node_initialize(n);
        n->parent = p;
        n->info = info;
        n->status = on;

        t->n_node++;

        if (p == NULL)
            t->root = n;
        else 
            clads_list_insert(&p->l_child, n);

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
    clads_list_type *l;

    /**
     * Checking for current node
     */
    if (t->f_node_eq(r->info, info))
        return r;

    /**
     * Recurssion/iteration over children
     */
    l = r->l_child;
    a = NULL;

    while (l && !a)
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
