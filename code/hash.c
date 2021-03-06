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

#include "hash.h"

clads_size_type
clads_hash_default_f_hash(clads_size_type m,
                          clads_id_type key)
{
    /*
     * As default threat as integer values.
     */
    return key & (m - 1);
}

clads_order_type
clads_hash_default_f_compare(clads_list_type *l,
                             clads_addr_type a,
                             clads_addr_type b)
{
    clads_hash_node_type *x;
    clads_id_type k;

    x = CLADS_CAST(a, clads_hash_node_type *);
    k = *CLADS_CAST(b, clads_id_type *);

    if (x->key > k)
        return clads_more;
    if (x->key < k)
        return clads_less;
    return clads_equal;
}

clads_hash_node_type *
clads_hash_node_new(clads_void_type)
{
    clads_hash_node_type *n;

    n = CLADS_ALLOC(1, clads_hash_node_type);
    clads_hash_node_initialize(n);

    return n;
}

clads_void_type
clads_hash_node_initialize(clads_hash_node_type *n)
{
    n->key = 0;
    n->info = NULL;
}

clads_void_type
clads_hash_node_finalize(clads_hash_node_type *n)
{
    if (n->info != NULL)
    {
        CLADS_FREE(n->info);
        n->info = NULL;
    }
}

clads_void_type
clads_hash_initialize(clads_hash_type *h)
{
    clads_size_type i;

    h->size = CLADS_HASH_INITIAL_TABLE_SIZE;
    h->table = CLADS_ALLOC(h->size, clads_list_type *);
    h->is_set = clads_false;

    for (i = 0; i < h->size; i++)
    {
        h->table[i] = CLADS_ALLOC(1, clads_list_type);
        clads_list_initialize(h->table[i]);
        h->table[i]->f_compare = &clads_hash_default_f_compare;
    }

    h->n_node = 0;
    h->f_hash = &clads_hash_default_f_hash;
}

clads_void_type
clads_hash_finalize(clads_hash_type *h)
{
    clads_size_type i;

    if (h != NULL)
    {
        for (i = 0; i < h->size; i++)
        {
            clads_list_finalize(h->table[i]);
            CLADS_FREE(h->table[i]);
        }

        CLADS_FREE(h->table);

        h->table = NULL;
        h->size = 0;
        h->n_node = 0;
    }
#if CLADS_DEBUG
    else
        printf("W. [HASH] Trying to finalize a NULL pointer.\n");
#endif
}

clads_void_type
clads_hash_rehash(clads_hash_type *h)
{
    clads_list_node_type *n, *m;
    clads_list_type **table;
    clads_hash_node_type *e;
    clads_size_type i, j, size;

    size = h->size * 2;
    table = CLADS_ALLOC(size, clads_list_type *);

    for (i = 0; i < size; i++)
    {
        table[i] = CLADS_ALLOC(1, clads_list_type);
        clads_list_initialize(table[i]);
        table[i]->f_compare = &clads_hash_default_f_compare;
    }

    for (i = 0; i < h->size; i++)
    {
        n = h->table[i]->head;

        while (n != NULL)
        {
            m = n->next;

            e = CLADS_CAST(n->info, clads_hash_node_type *);
            j = h->f_hash(size, e->key);
            n->prev = NULL;
            n->next = NULL;
            clads_list_insert(table[j], n);

            n = m;
        }

        CLADS_FREE(h->table[i]);
    }

    CLADS_FREE(h->table);

    h->size = size;
    h->table = table;
}

clads_bool_type
clads_hash_insert(clads_hash_type *h,
                  clads_hash_node_type *n)
{
    clads_list_node_type *e;
    clads_size_type i;

    if (h->is_set == clads_true)
        if (clads_hash_search(h, n->key) != NULL)
            return clads_false;

    if (h->size == h->n_node)
        clads_hash_rehash(h);

    i = h->f_hash(h->size, n->key);
    e = clads_list_node_new();
    e->info = n;
    clads_list_insert(h->table[i], e);
    h->n_node++;

    return clads_true;
}

clads_bool_type
clads_hash_remove(clads_hash_type *h,
                  clads_hash_node_type *n)
{
    if (n != NULL)
    {
        clads_size_type i = h->f_hash(h->size, n->key);
        clads_list_node_type *e = clads_list_search(h->table[i], &n->key);

        if (e != NULL)
        {
            clads_list_remove(h->table[i], e);
            h->n_node--;

            return clads_true;
        }
    }

    return clads_false;
}

clads_hash_node_type *
clads_hash_search(clads_hash_type *h,
                  clads_id_type key)
{
    clads_list_node_type *n;
    clads_size_type i;

    i = h->f_hash(h->size, key);
    n = clads_list_search(h->table[i], &key);

    if (n != NULL)
        return CLADS_CAST(n->info, clads_hash_node_type *);

    return NULL;
}
