/**
 * Copyright (C) 2010 Joao Paulo de Souza Medeiros
 * Copyright (C) 2011 Joao Paulo de Souza Medeiros
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


inline clads_bool_type
clads_graph_default_f_node_eq(clads_graph_node_type *a,
                              clads_graph_node_type *b)
{
    return a == b;
}

void
clads_graph_initialize(clads_graph_type *g)
{
    g->n_node = 0;
    g->n_edge = 0;
    g->l_node = NULL;
    g->l_edge = NULL;
    g->directed = false;
    g->f_node_eq = &clads_graph_default_f_node_eq;
}

void
clads_graph_finalize(clads_graph_type *g)
{
    clads_list_finalize(clads_graph_get_edge_list(g));
    clads_list_finalize(clads_graph_get_node_list(g));
    clads_graph_destroy_adjacency(g);
    free((void *) g);
}

int
clads_graph_copy(const clads_graph_type *ga,
                 clads_graph_type *gb)
{
    // TODO: what? everything!
    return 0;
}

void
clads_graph_destroy_adjacency(clads_graph_type *g)
{
    clads_size_type i;

    if (g->l_near != NULL)
    {
        for (i = 0; i < g->n_node; i++)
            clads_list_finalize(g->l_near[i]);

        free(g->l_near);
    }
}

void
clads_graph_create_adjacency(clads_graph_type *g)
{
    clads_size_type i;

    /**
     * Clear list if it already exists
     */
    clads_graph_destroy_adjacency(g);

    /**
     * Create a new adjacency list
     */
    clads_graph_adjacency_type *a;

    g->l_near = malloc(g->n_node * sizeof(clads_list_type *));

    // Initializing lists
    for (i = 0; i < g->n_edge; i++)
        g->l_near[i] = NULL;

    for (i = 0; i < g->n_edge; i++)
    {
        a = malloc(sizeof(clads_graph_adjacency_type));
        a->e = (clads_graph_edge_type *) g->l_edge[i].info;
        a->n = a->e->nb;
        clads_list_insert(&g->l_near[a->e->na->id], (void *) a);

        if (!g->directed)
        {
            a = malloc(sizeof(clads_graph_adjacency_type));
            a->e = (clads_graph_edge_type *) g->l_edge[i].info;
            a->n = a->e->na;
            clads_list_insert(&g->l_near[a->e->nb->id], (void *) a);
        }
    }
}

clads_graph_edge_type *
clads_graph_get_edge(clads_graph_type *g,
                     clads_id_type id)
{
    clads_list_type *l = clads_graph_get_edge_list(g);
    clads_graph_edge_type *e;

    while (l)
    {
        e = (clads_graph_edge_type *) l->info;

        if (e->id == id)
            return e;

        l = l->next;
    }

    return NULL;
}

clads_graph_edge_type *
clads_graph_get_edge_by_nodes(clads_graph_type *g,
                              clads_graph_node_type *na,
                              clads_graph_node_type *nb)
{
    clads_list_type *l = clads_graph_get_edge_list(g);
    clads_graph_edge_type *e;

    while (l)
    {
        e = (clads_graph_edge_type *) l->info;

        if ((e->na == na && e->nb == nb) ||
            (!g->directed && e->na == nb && e->nb == na))
            return e;

        l = l->next;
    }

    return NULL;
}

clads_graph_node_type *
clads_graph_get_node(clads_graph_type *g,
                     clads_id_type id)
{
    clads_list_type *l = clads_graph_get_node_list(g);
    clads_graph_node_type *n;

    while (l)
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
    clads_list_type *l = clads_graph_get_node_list(g);
    clads_graph_node_type *n;

    while (l)
    {
        n = (clads_graph_node_type *) l->info;

        if (g->f_node_eq(n->info, info))
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

    e->id = g->n_edge++;
    e->na = na;
    e->nb = nb;
    e->info = info;
    e->status = on;

    clads_list_insert(&g->l_edge, e);

    return e;
}

clads_graph_node_type *
clads_graph_add_node(clads_graph_type *g,
                     void *info)
{
    clads_graph_node_type *n = malloc(sizeof(clads_graph_node_type));

    n->id = g->n_node++;
    n->info = info;
    n->status = on;

    clads_list_insert(&g->l_node, n);

    return n;
}

clads_list_type *
clads_graph_get_edges_by_node(clads_graph_type *g,
                              clads_graph_node_type *n)
{
    clads_list_type *l = clads_graph_get_edge_list(g);
    clads_list_type *r = NULL;
    clads_graph_edge_type *e;

    while (l)
    {
        e = (clads_graph_edge_type *) l->info;

        if (e->na == n || e->nb == n)
            clads_list_insert(&r, e);

        l = l->next;
    }

    return r;
}

clads_list_type *
clads_graph_get_edge_list(clads_graph_type *g)
{
    return g->l_edge;
}

clads_list_type *
clads_graph_get_node_list(clads_graph_type *g)
{
    return g->l_node;
}

clads_list_type *
clads_graph_get_node_neighbors(clads_graph_type *g,
                               clads_graph_node_type *n)
{
    clads_list_type *l = clads_graph_get_edge_list(g);
    clads_list_type *r = NULL;
    clads_graph_edge_type *e;

    while (l)
    {
        e = (clads_graph_edge_type *) l->info;

        if (e->na == n)
            clads_list_insert(&r, e->nb);
        else if (e->nb == n)
            clads_list_insert(&r, e->na);

        l = l->next;
    }

    return r;
}

clads_real_type
clads_graph_clustering(clads_graph_type *g)
{
    clads_list_type *l = clads_graph_get_node_list(g);
    clads_real_type size = g->n_node;
    clads_graph_node_type *n;

    g->clustering = 0;

    while (l)
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
    clads_list_type *l, *i, *j;
    clads_list_type *neighbors = clads_graph_get_node_neighbors(g, n);
    clads_real_type k, e = 0;
    clads_real_type r;
    clads_graph_node_type *x, *y;
    clads_graph_edge_type *o;

    k = clads_list_size(neighbors);
    j = neighbors;

    if (g->directed)
    {
        // TODO: compute clustering of direted graphs
        r = 0;
    }
    else
    {
        while (j)
        {
            x = (clads_graph_node_type *) j->info;
            i = neighbors;

            while (i)
            {
                y = (clads_graph_node_type *) i->info;
                l = clads_graph_get_edge_list(g);

                while (l)
                {
                    o = (clads_graph_edge_type *) l->info;

                    if (
                        (o->na == x && o->nb == y) ||
                        (o->nb == x && o->na == y)
                       )
                        e++;

                    l = l->next;
                }

                i = i->next;
            }

            j = j->next;
        }

        r = (k * (k - 1));

        if (r > 0)
            r = 2 * e / r;
    }

    n->clustering = r;

    return n->clustering;
}

clads_tree_type *
clads_graph_spanning_tree(clads_graph_type *g,
                          clads_graph_node_type *n)
{
    clads_tree_type *t = malloc(sizeof(clads_tree_type));
    clads_tree_node_type *f, *p;
    clads_graph_node_type *m;
    clads_list_type *list, *e;
    clads_list_type *neighbor;

    clads_tree_initialize(t);
    f = clads_tree_add_node(t, NULL, (void *) n);
    clads_list_insert(&list, f);

    /**
     *
     */
    do
    {
        e = list;
        p = (clads_tree_node_type *) e->info;
        m = (clads_graph_node_type *) p->info;
        neighbor = clads_graph_get_node_neighbors(g, m);

        while (neighbor)
        {
            m = (clads_graph_node_type *) neighbor->info;
            f = clads_tree_add_node(t, p, (void *) m);
            clads_list_insert(&list, f);

            neighbor = neighbor->next;
        }

        clads_list_remove(&list, e);
    }
    while (clads_list_size(list));

    return t;
}
