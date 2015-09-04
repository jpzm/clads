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
#include "../code/graph.h"

void
graph_print_path(clads_addr_type *r, clads_graph_node_type *n)
{
    if (n != NULL)
    {
        graph_print_path(r, r[n->id]);
        printf(" " CLADS_UINT_STR, n->id);
    }
}

void
graph_print_paths(clads_graph_type *g, clads_addr_type *r)
{
    clads_size_type i;
    clads_list_node_type *l;
    clads_graph_node_type *n;

    l = g->l_node->head;

    printf("answer: ");
    for (i = 0; i < g->n_node; i++)
        printf("[" CLADS_UINT_STR "]-%p ", i, r[i]);
    printf("\n");

    while (l != NULL)
    {
        n = (clads_graph_node_type *) l->info;

        graph_print_path(r, n);
        printf(" (%p)\n", n);

        l = l->next;
    }
}

int main(int argc, char **argv)
{
    clads_addr_type *r;
    clads_graph_type *g;
    clads_graph_node_type *n;

    clads_initialize();

    g = clads_graph_from_tgf_file(argv[1], clads_false);

    n = CLADS_CAST(g->l_node->tail->info, clads_graph_node_type *);

    r = clads_graph_search(g, n, clads_graph_search_dfs);
    printf("DFS\n");
    graph_print_paths(g, r);
    CLADS_FREE(r);
    printf("\n");

    r = clads_graph_search(g, n, clads_graph_search_bfs);
    printf("BFS\n");
    graph_print_paths(g, r);
    CLADS_FREE(r);
    printf("\n");

    clads_graph_finalize(g);
    CLADS_FREE(g);
    clads_finalize();

    return 0;
}
