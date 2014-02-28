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
#include "../code/list.h"

#define SIZE    10
#define LIMIT   99


void
list_print(clads_list_type *l)
{
    clads_list_node_type *n = l->head;

    while (n != NULL)
    {
        printf("%2d ", *CLADS_CAST(n->info, int *));
        n = n->next;
    }

    printf("\n");
}

int main(void)
{
    clads_list_node_type *n;
    clads_list_type l, *c;
    clads_size_type i;

    clads_initialize();
    clads_list_initialize(&l);

    for (i = 0; i < SIZE; i++)
    {
        n = clads_list_node_new();
        n->info = CLADS_ALLOC(1, int);
        *CLADS_CAST(n->info, int *) = clads_randint(0, LIMIT);

        clads_list_insert(&l, n);
    }

    printf("OLD LIST: ");
    list_print(&l);
    c = clads_list_copy(&l);

    i = clads_randint(0, LIMIT);
    printf("REMOVING: %2d\n", CLADS_CAST(i, int));

    n = clads_list_search(&l, &i);
    clads_list_remove(&l, n);

    printf("NEW LIST: ");
    list_print(&l);

    printf("OLD COPY: ");
    list_print(c);

    clads_list_finalize(&l);
    clads_list_finalize(c);

    clads_finalize();

    return 0;
}
