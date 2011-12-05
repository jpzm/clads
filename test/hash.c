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

#include "../code/clads.h"
#include "../code/hash.h"

#define SIZE    8


void list_print(clads_list_type *l)
{
    clads_list_node_type *n = l->head;

    while (n != NULL)
    {
        printf("%d ", *CLADS_CAST(n->info, int *));
        n = n->next;
    }

    printf("\n");
}

void hash_print(clads_hash_type *h)
{
    clads_size_type i;

    for (i = 0; i < h->size; i++)
    {
        printf(" [%d] ", CLADS_CAST(i, int));
        list_print(h->table[i]);
    }
}

int main(void)
{
    clads_hash_node_type *n;
    clads_hash_type h;
    clads_size_type i;

    clads_initialize();
    clads_hash_initialize(&h);

    printf("NUMBERS: ");
    for (i = 0; i < SIZE; i++)
    {
        n = clads_hash_node_new();
        n->key = CLADS_CAST(clads_randint(0, 10 * SIZE), clads_id_type);

        printf("%d ", CLADS_CAST(n->key, int));
        clads_hash_insert(&h, n);
    }
    printf("\n");

    printf("OLD HASH: \n");
    hash_print(&h);

    i = clads_randint(0, 10 * SIZE);
    printf("REMOVING: %d\n", CLADS_CAST(i, int));

    n = clads_hash_search(&h, i);
    clads_hash_remove(&h, n);

    printf("NEW HASH: \n");
    hash_print(&h);

    clads_hash_finalize(&h);

    return 0;
}
