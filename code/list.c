/**
 * Copyright (C) 2011-2012 Joao Paulo de Souza Medeiros
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
clads_list_default_f_compare(clads_list_type *l,
                             clads_addr_type a,
                             clads_addr_type b)
{
    /*
     * As default threat as integer values.
     */
    if (*CLADS_CAST(a, clads_int_type *) > *CLADS_CAST(b, clads_int_type *))
        return clads_more;
    if (*CLADS_CAST(a, clads_int_type *) < *CLADS_CAST(b, clads_int_type *))
        return clads_less;
    return clads_equal;
}

clads_addr_type
clads_list_default_f_copy(clads_addr_type a)
{
    /*
     * As default threat as integer values.
     */
    clads_int_type *b = CLADS_ALLOC(1, clads_int_type);
    *b = *CLADS_CAST(a, clads_int_type *);
    return (clads_addr_type) b;
}

clads_list_node_type *
clads_list_node_new(clads_void_type)
{
    clads_list_node_type *n;

    n = CLADS_ALLOC(1, clads_list_node_type);
    clads_list_node_initialize(n);

    return n;
}

clads_void_type
clads_list_node_initialize(clads_list_node_type *n)
{
    n->prev = NULL;
    n->info = NULL;
    n->next = NULL;
}

clads_void_type
clads_list_node_finalize(clads_list_node_type *n,
                         clads_bool_type do_free_info)
{
    if (n != NULL)
    {
        if (do_free_info == clads_true && n->info != NULL)
            CLADS_FREE(n->info);

        n->info = NULL;
        n->prev = NULL;
        n->next = NULL;

        CLADS_FREE(n);
    }
#if CLADS_DEBUG
    else
        printf("W. [LIST] Trying to finalize a NULL pointer.\n");
#endif
}

clads_void_type
clads_list_initialize(clads_list_type *l)
{
    l->is_set = clads_false;
    l->head = NULL;
    l->tail = NULL;
    l->iter = NULL;
    l->do_free_info = clads_true;
    l->f_compare = &clads_list_default_f_compare;
    l->f_copy = &clads_list_default_f_copy;
}

clads_void_type
clads_list_finalize(clads_list_type *l)
{
    clads_list_node_type *m, *p;

    if (l != NULL)
    {
        p = l->head;

        while (p != NULL)
        {
            m = p->next;
            clads_list_node_finalize(p, l->do_free_info);
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

clads_list_type *
clads_list_copy(clads_list_type *l)
{
    clads_list_type *n = CLADS_ALLOC(1, clads_list_type);
    clads_list_node_type *i, *j;
    clads_list_initialize(n);

    n->is_set = l->is_set;
    n->do_free_info = l->do_free_info;
    n->f_compare = l->f_compare;
    n->f_copy = l->f_copy;

    while ((i = clads_list_next(l)))
    {
        j = clads_list_node_new();
        j->info = l->f_copy(i->info);

        clads_list_enqueue(n, j);
    }

    return n;
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
clads_list_is_empty(clads_list_type *l)
{
    if (l->head == NULL)
        return clads_true;
    return clads_false;
}

clads_bool_type
clads_list_insert(clads_list_type *l,
                  clads_list_node_type *x)
{
    if (l->is_set == clads_true)
        if (clads_list_search(l, x->info) != NULL)
            return clads_false;

    if (l->head == NULL)
        l->tail = x;
    else
        l->head->prev = x;

    x->next = l->head;
    l->head = x;

    return clads_true;
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

        clads_list_node_finalize(x, l->do_free_info);

        return clads_true;
    }

    return clads_false;
}

clads_list_node_type *
clads_list_search(clads_list_type *l,
                  clads_addr_type info)
{
    clads_list_node_type *p = l->head;
    clads_order_type r;

    while (p != NULL)
    {
        r = l->f_compare(l, p->info, info);

        if (r == clads_equal)
            return p;

        p = p->next;
    }

    return NULL;
}

clads_bool_type
clads_list_push(clads_list_type *l,
                clads_list_node_type *x)
{
    if (l->head == NULL)
        l->tail = x;
    else
        l->head->prev = x;

    x->next = l->head;
    l->head = x;

    return clads_true;
}

clads_list_node_type *
clads_list_pop(clads_list_type *l)
{
    clads_list_node_type *n = l->head;

    if (n != NULL)
    {
        l->head = n->next;
        
        if (l->head != NULL)
            l->head->prev = NULL;
    }

    return n;
}

clads_bool_type
clads_list_enqueue(clads_list_type *l,
                   clads_list_node_type *x)
{
    if (l->tail == NULL)
        l->head = x;
    else
        l->tail->next = x;

    x->prev = l->tail;
    l->tail = x;

    return clads_true;
}

clads_list_node_type *
clads_list_dequeue(clads_list_type *l)
{
    return clads_list_pop(l);
}

clads_list_node_type *
clads_list_next(clads_list_type *l)
{
    if (l->iter == l->tail)
        l->iter = NULL;
    else if (l->iter == NULL)
        l->iter = l->head;
    else
        l->iter = l->iter->next;

    return l->iter;
}
