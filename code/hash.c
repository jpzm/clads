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
                          void *key)
{
    /*
     * As default threat as integer values.
     */
    return (*CLADS_CAST(key, int *)) & (m - 1);
}

clads_order_type
clads_hash_default_f_compare(void *a,
                             void *b)
{
    clads_hash_node_type *x;
    clads_id_type k;

    x = CLADS_CAST(a, clads_hash_node_type *);
    k = *CLADS_CAST(b, clads_id_type *);

    if (x->key > k)
        return more;
    if (x->key < k)
        return less;
    return equal;
}

void
clads_hash_node_initialize(clads_hash_node_type *n)
{
    n->info = NULL;
}

void
clads_hash_node_finalize(clads_hash_node_type *n)
{
    if (n != NULL)
    {
        free(n->info);
        n->info = NULL;
    }
}

void
clads_hash_initialize(clads_hash_type *h)
{
    clads_size_type i;

    h->size = CLADS_HASH_INITIAL_TABLE_SIZE;
    h->table = CLADS_ALLOC(h->size, clads_list_type *);
    h->is_set = false;

    for (i = 0; i < h->size; i++)
        h->table[i]->f_compare = &clads_hash_default_f_compare;

    h->n_node = 0;
    h->f_hash = &clads_hash_default_f_hash;
}

void
clads_hash_finalize(clads_hash_type *h)
{
    if (h != NULL)
    {
        h->size = 0;
        h->n_node = 0;
        free(h->table);
        h->table = NULL;
    }
#if CLADS_DEBUG
    else
        printf("W. [HASH] Trying to finalize a NULL pointer.\n");
#endif
}

clads_bool_type
clads_hash_rehash(clads_hash_type *h);

clads_bool_type
clads_hash_insert(clads_hash_type *h,
                  clads_hash_node_type *n)
{
    clads_list_node_type *e;
    clads_size_type i;

    if (h->is_set == true)
        if (clads_hash_search(h, n->key) != NULL)
            return false;

    if (h->size == h->n_node)
        clads_hash_rehash(h);

    i = h->f_hash(h->size, &(n->key));
    e = clads_list_node_new();
    e->info = n;
    clads_list_insert(h->table[i], e);
    h->n_node++;

    return true;
}

clads_bool_type
clads_hash_remove(clads_hash_type *h,
                  clads_hash_node_type *n)
{
    clads_size_type i = h->f_hash(h->size, &n->key);
    clads_list_node_type *e = clads_list_search(h->table[i], &n->key);

    if (e != NULL)
    {
        clads_list_remove(h->table[i], e);
        h->n_node--;

        return true;
    }

    return false;
}

clads_hash_node_type *
clads_hash_search(clads_hash_type *h,
                  clads_id_type key)
{
    clads_list_node_type *n;
    clads_size_type i;

    i = h->f_hash(h->size, &key);
    n = clads_list_search(h->table[i], &key);

    if (n != NULL)
        return CLADS_CAST(n->info, clads_hash_node_type *);

    return NULL;
}
