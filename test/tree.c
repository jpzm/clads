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
#include "../code/tree.h"

#define SIZE    8
#define LIMIT   99


void
tree_print(clads_tree_type *t,
           clads_tree_node_type *n)
{
    if (n != NULL)
    {
        tree_print(t, n->lchild);
        printf("%2d ", *CLADS_CAST(n->info, int *));
        tree_print(t, n->rchild);
    }
}

int main(void)
{
    clads_tree_node_type *n;
    clads_tree_type t;
    clads_size_type i;

    clads_initialize();
    clads_tree_initialize(&t);

    printf("NUMBERS: ");
    for (i = 0; i < SIZE; i++)
    {
        n = clads_tree_node_new();
        n->info = CLADS_ALLOC(1, int);
        *CLADS_CAST(n->info, int *) = clads_randint(0, LIMIT);

        printf("%2d ", *CLADS_CAST(n->info, int *));
        clads_tree_insert(&t, n);
    }
    printf("\n");

    printf("OLD TREE: ");
    tree_print(&t, t.root);
    printf("\n");

    i = clads_randint(0, LIMIT);
    printf("REMOVING: %2d\n", CLADS_CAST(i, int));

    n = clads_tree_search(&t, &i);
    clads_tree_remove(&t, n);

    printf("NEW TREE: ");
    tree_print(&t, t.root);
    printf("\n");

    clads_tree_finalize(&t);

    return 0;
}
