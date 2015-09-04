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
graph_print(clads_graph_type *g)
{
    clads_list_node_type *l;
    clads_graph_node_type *n;
    clads_graph_edge_type *e;

    l = g->l_node->head;

    printf("N = { ");
    while (l != NULL)
    {
        n = (clads_graph_node_type *) l->info;
        printf(CLADS_UINT_STR " ", n->id);
        l = l->next;
    }
    printf("}\n");

    l = g->l_edge->head;

    printf("E = { ");
    while (l != NULL)
    {
        e = (clads_graph_edge_type *) l->info;
        printf("(" CLADS_UINT_STR " " CLADS_UINT_STR ") ",
                e->na->id,
                e->nb->id);
        l = l->next;
    }
    printf("}\n");
}

int main(int argc, char **argv)
{
    clads_graph_type *g;

    clads_initialize();

    g = clads_graph_from_tgf_file(argv[1]);

    graph_print(g);

    clads_graph_finalize(g);
    CLADS_FREE(g);
    clads_finalize();

    return 0;
}
