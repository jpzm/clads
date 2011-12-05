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

#include "list.h"


clads_order_type
clads_list_default_f_compare(void *a,
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

clads_list_node_type *
clads_list_node_new()
{
    clads_list_node_type *n;

    n = CLADS_ALLOC(1, clads_list_node_type);
    clads_list_node_initialize(n, NULL);

    return n;
}

void
clads_list_node_initialize(clads_list_node_type *n,
                           void *info)
{
    n->prev = NULL;
    n->info = info;
    n->next = NULL;
}

void
clads_list_node_finalize(clads_list_node_type *n)
{
    if (n != NULL)
    {
        if (n->info != NULL)
            free((void *) n->info);

        n->info = NULL;
        n->prev = NULL;
        n->next = NULL;
    }
#if CLADS_DEBUG
    else
        printf("W. [LIST] Trying to finalize a NULL pointer.\n");
#endif
}

void
clads_list_initialize(clads_list_type *l)
{
    l->is_set = false;
    l->head = NULL;
    l->tail = NULL;
    l->f_compare = &clads_list_default_f_compare;
}

void
clads_list_finalize(clads_list_type *l)
{
    clads_list_node_type *m, *p;

    if (l != NULL)
    {
        p = l->head;

        while (p != NULL)
        {
            m = p->next;
            clads_list_node_finalize(p);
            p = m;
        }

        l->head = NULL;
        l->tail = NULL;
    }
#if CLADS_DEBUG
    else
        printf("W. [LIST] Trying to finalize a NULL pointer.\n");
#endif
}

clads_size_type
clads_list_size(clads_list_type *l)
{
    clads_list_node_type *p = l->head;
    clads_size_type s = 0;

    while (p != NULL)
    {
        s++;
        p = p->next;
    }

    return s;
}

clads_bool_type
clads_list_insert(clads_list_type *l,
                  clads_list_node_type *x)
{
    if (l->is_set == true)
        if (clads_list_search(l, x->info) != NULL)
            return false;

    if (l->head == NULL)
        l->tail = x;
    else
        l->head->prev = x;

    x->next = l->head;
    l->head = x;

    return true;
}

clads_bool_type
clads_list_remove(clads_list_type *l,
                  clads_list_node_type *x)
{
    if (x != NULL)
    {
        if (x == l->tail)
            l->tail = x->prev;

        if (x->prev != NULL)
            x->prev->next = x->next;
        if (x->next != NULL)
            x->next->prev = x->prev;

        if (x == l->head)
            l->head = x->next;

        clads_list_node_finalize(x);

        return true;
    }

    return false;
}

clads_list_node_type *
clads_list_search(clads_list_type *l,
                  void *info)
{
    clads_list_node_type *p = l->head;

    while (p != NULL)
    {
        if (l->f_compare(p->info, info) == equal)
            return p;

        p = p->next;
    }

    return NULL;
}
