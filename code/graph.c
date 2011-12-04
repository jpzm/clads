/**
 * Copyright (C) 2010-2011 Joao Paulo de Souza Medeiros
 *
 * Author(s): João Paulo de Souza Medeiros <ignotus21@gmail.com>
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

#include "graph.h"


clads_order_type
clads_graph_default_f_compare(void *a,
                              void *b)
{
    /*
     * As default threat as integer values.
     */
    if (*((int *) a) == *((int *) b))
        return equal;
    if (*((int *) a) < *((int *) b))
        return less;
    return more;
}

void
clads_graph_initialize(clads_graph_type *g)
{
    g->n_node = 0;
    g->n_edge = 0;
    g->l_node = NULL;
    g->l_edge = NULL;
    g->is_directed = false;
    g->l_adjacency = NULL;
    g->f_compare = &clads_graph_default_f_compare;

    clads_list_initialize(g->l_node);
    clads_list_initialize(g->l_edge);
}

void
clads_graph_finalize(clads_graph_type *g)
{
    if (g != NULL)
    {
        clads_list_finalize(g->l_edge);
        clads_list_finalize(g->l_node);
        clads_graph_clear_adjacency(g);
    }
#if CLADS_DEBUG
    else
        printf("W. [GRAPH] Trying to finalize a NULL pointer.\n");
#endif
}

int
clads_graph_copy(const clads_graph_type *ga,
                 clads_graph_type *gb)
{
    // TODO: what? everything!
    return 0;
}

void
clads_graph_clear_adjacency(clads_graph_type *g)
{
    clads_size_type i;

    if (g->l_adjacency != NULL)
    {
        for (i = 0; i < g->n_node; i++)
            clads_list_finalize(g->l_adjacency[i]);

        free(g->l_adjacency);
        g->l_adjacency = NULL;
    }
}

void
clads_graph_mount_adjacency(clads_graph_type *g)
{
    clads_graph_edge_type *e;
    clads_list_node_type *n, *p;
    clads_size_type i;

    /*
     * Clear the adjacency list if it already exists, and create a new one.
     */
    clads_graph_clear_adjacency(g);

    g->l_adjacency = malloc(g->n_node * sizeof(clads_list_type *));

    /*
     * Initializing lists
     */
    for (i = 0; i < g->n_node; i++)
    {
        g->l_adjacency[i] = malloc(sizeof(clads_list_type));
    }

    /*
     * Fill the adjacency list
     */
    p = g->l_edge->head;

    while (p != NULL)
    {
        e = (clads_graph_edge_type *) p->info;

        n = clads_list_node_new();
        n->info = (void *) e->nb;
        clads_list_insert(g->l_adjacency[e->na->id], n);

        if (!g->is_directed)
        {
            n = clads_list_node_new();
            n->info = (void *) e->na;
            clads_list_insert(g->l_adjacency[e->nb->id], n);
        }

        p = p->next;
    }
}

clads_graph_edge_type *
clads_graph_get_edge_by_nodes(clads_graph_type *g,
                              clads_graph_node_type *na,
                              clads_graph_node_type *nb)
{
    clads_list_node_type *l = g->l_edge->head;
    clads_graph_edge_type *e;

    while (l != NULL)
    {
        e = (clads_graph_edge_type *) l->info;

        if ((e->na == na && e->nb == nb) ||
            (!g->is_directed && e->na == nb && e->nb == na))
            return e;

        l = l->next;
    }

    return NULL;
}

clads_graph_node_type *
clads_graph_get_node(clads_graph_type *g,
                     clads_id_type id)
{
    clads_list_node_type *l = g->l_edge->head;
    clads_graph_node_type *n;

    while (l != NULL)
    {
        n = (clads_graph_node_type *) l->info;

        if (n->id == id)
            return n;

        l = l->next;
    }

    return NULL;
}

clads_graph_node_type *
clads_graph_get_node_by_info(clads_graph_type *g,
                             void *info)
{
    clads_list_node_type *l = g->l_edge->head;
    clads_graph_node_type *n;

    while (l != NULL)
    {
        n = (clads_graph_node_type *) l->info;

        if (g->f_compare(n->info, info))
            return n;

        l = l->next;
    }

    return NULL;
}

clads_graph_edge_type *
clads_graph_add_edge(clads_graph_type *g,
                     clads_graph_node_type *na,
                     clads_graph_node_type *nb,
                     void *info)
{
    clads_graph_edge_type *e = malloc(sizeof(clads_graph_edge_type));
    clads_list_node_type *p;

    g->n_edge++;

    e->na = na;
    e->nb = nb;
    e->info = info;

    p = clads_list_node_new();
    p->info = (void *) e;
    clads_list_insert(g->l_edge, p);

    return e;
}

clads_graph_node_type *
clads_graph_add_node(clads_graph_type *g,
                     void *info)
{
    clads_graph_node_type *n = malloc(sizeof(clads_graph_node_type));
    clads_list_node_type *p;

    n->id = g->n_node++;
    n->info = info;

    p = clads_list_node_new();
    p->info = (void *) n;
    clads_list_insert(g->l_node, p);

    return n;
}

clads_list_type *
clads_graph_get_edges_by_node(clads_graph_type *g,
                              clads_graph_node_type *n)
{
    clads_list_node_type *p, *l = g->l_edge->head;
    clads_list_type *r = NULL;
    clads_graph_edge_type *e;

    while (l != NULL)
    {
        e = (clads_graph_edge_type *) l->info;

        if (e->na == n || e->nb == n)
        {
            p = clads_list_node_new();
            p->info = (void *) e;
            clads_list_insert(r, p);
        }

        l = l->next;
    }

    return r;
}

clads_list_type *
clads_graph_get_node_neighbors(clads_graph_type *g,
                               clads_graph_node_type *n)
{
    clads_list_node_type *p, *l = g->l_edge->head;
    clads_list_type *r = (clads_list_type *) malloc(sizeof(clads_list_type));
    clads_graph_edge_type *e;

    while (l != NULL)
    {
        e = (clads_graph_edge_type *) l->info;

        if (e->na == n || e->nb == n)
        {
            p = clads_list_node_new();

            if (e->na == n)
                p->info = (void *) e->nb;
            else
                p->info = (void *) e->na;

            clads_list_insert(r, p);
        }

        l = l->next;
    }

    return r;
}

clads_real_type
clads_graph_clustering(clads_graph_type *g)
{
    clads_list_node_type *l = g->l_node->head;
    clads_real_type size = g->n_node;
    clads_graph_node_type *n;

    g->clustering = 0;

    while (l != NULL)
    {
        n = (clads_graph_node_type *) l->info;
        g->clustering += clads_graph_node_clustering(g, n);

        l = l->next;
    }

    g->clustering = g->clustering / size;

    return g->clustering;
}

clads_real_type
clads_graph_node_clustering(clads_graph_type *g,
                            clads_graph_node_type *n)
{
    // TODO

    return 0;
}

clads_tree_type *
clads_graph_spanning_tree(clads_graph_type *g,
                          clads_graph_node_type *n)
{
    // TODO

    return NULL;
}
