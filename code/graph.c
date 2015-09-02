/**
 * Copyright (C) 2010-2012 Joao Paulo de Souza Medeiros
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

#include "graph.h"


clads_order_type
clads_graph_default_f_compare(clads_graph_type *g,
                              clads_addr_type a,
                              clads_addr_type b)
{
    /*
     * As default threat as integer values.
     */
    if (*((int *) a) == *((int *) b))
        return clads_equal;
    if (*((int *) a) < *((int *) b))
        return clads_less;
    return clads_more;
}

clads_addr_type
clads_graph_edge_f_copy(clads_addr_type a)
{
    clads_graph_edge_type *f = CLADS_ALLOC(1, clads_graph_edge_type);
    clads_graph_edge_type *e = CLADS_CAST(a, clads_graph_edge_type *);

    f->na = e->na;
    f->nb = e->nb;
    f->info = e->info;
    f->key = e->key;

    return CLADS_CAST(f, clads_addr_type);
}

clads_addr_type
clads_graph_node_f_copy(clads_addr_type a)
{
    clads_graph_node_type *m = CLADS_ALLOC(1, clads_graph_node_type);
    clads_graph_node_type *n = CLADS_CAST(a, clads_graph_node_type *);

    m->id = n->id;
    m->clustering = n->clustering;
    m->info = n->info;
    m->key = n->key;

    return CLADS_CAST(m, clads_addr_type);
}

clads_void_type
clads_graph_initialize(clads_graph_type *g)
{
    g->n_node = 0;
    g->n_edge = 0;
    g->l_node = CLADS_ALLOC(1, clads_list_type);
    g->l_edge = CLADS_ALLOC(1, clads_list_type);
    g->allow_loop = clads_false;
    g->allow_multiple_edges = clads_false;
    g->is_directed = clads_false;
    g->l_adjacency = NULL;
    g->f_compare = &clads_graph_default_f_compare;
    g->more = NULL;

    clads_list_initialize(g->l_node);
    g->l_node->f_copy = &clads_graph_node_f_copy;
    g->l_node->do_free_info = clads_false;
    clads_list_initialize(g->l_edge);
    g->l_edge->f_copy = &clads_graph_edge_f_copy;
    g->l_edge->do_free_info = clads_false;
}

clads_graph_type *
clads_graph_copy(clads_graph_type *g)
{
    clads_graph_type *ng = CLADS_ALLOC(1, clads_graph_type);

    ng->n_node = g->n_node;
    ng->n_edge = g->n_edge;
    ng->allow_loop = g->allow_loop;
    ng->allow_multiple_edges = g->allow_multiple_edges;
    ng->is_directed = g->is_directed;
    ng->f_compare = g->f_compare;
    ng->more = g->more;

    ng->l_edge = clads_list_copy(g->l_edge);
    ng->l_node = clads_list_copy(g->l_node);

    if (g->l_adjacency != NULL)
        clads_graph_mount_adjacency(ng);
    else
        ng->l_adjacency = NULL;

    return ng;
}

clads_void_type
clads_graph_finalize(clads_graph_type *g)
{
    if (g != NULL)
    {
        clads_list_finalize(g->l_edge);
        clads_list_finalize(g->l_node);
        clads_graph_clear_adjacency(g);
        CLADS_FREE(g->l_node);
        CLADS_FREE(g->l_edge);
    }
#if CLADS_DEBUG
    else
        printf("W. [GRAPH] Trying to finalize a NULL pointer.\n");
#endif
}

clads_graph_type *
clads_graph_new_erdos_nm(clads_size_type n,
                         clads_size_type m,
                         clads_bool_type is_directed,
                         clads_bool_type allow_loop,
                         clads_bool_type allow_multiple_edges)
{
    clads_graph_node_type **v = CLADS_ALLOC(n, clads_graph_node_type *);
    clads_graph_type *g = CLADS_ALLOC(1, clads_graph_type);
    clads_graph_node_type *na, *nb;

    clads_graph_initialize(g);

    g->is_directed = is_directed;
    g->allow_loop = allow_loop;
    g->allow_multiple_edges = allow_multiple_edges;

    /*
     * Creating nodes.
     */
    while (g->n_node < n)
        v[g->n_node - 1] = clads_graph_add_node(g, NULL);

    /*
     * Creating edges.
     */
    while (g->n_edge < m)
    {
        na = v[clads_randint(0, n - 1)];
        nb = v[clads_randint(0, n - 1)];

        clads_graph_add_edge(g, na, nb, NULL);
    }

    CLADS_FREE(v);

    return g;
}

clads_graph_type *
clads_graph_new_erdos_np(clads_size_type n,
                         clads_real_type p,
                         clads_bool_type is_directed,
                         clads_bool_type allow_loop,
                         clads_bool_type allow_multiple_edges)
{
    clads_graph_node_type **v = CLADS_ALLOC(n, clads_graph_node_type *);
    clads_graph_type *g = CLADS_ALLOC(1, clads_graph_type);
    clads_size_type i, j, start;

    clads_graph_initialize(g);

    g->is_directed = is_directed;
    g->allow_loop = allow_loop;
    g->allow_multiple_edges = allow_multiple_edges;

    /*
     * Creating nodes.
     */
    while (g->n_node < n)
        v[g->n_node - 1] = clads_graph_add_node(g, NULL);

    /*
     * Creating edges.
     */
    for (i = 0; i < g->n_node; i++)
    {
        start = (g->is_directed == clads_true) ? 0 : i;

        for (j = start; j < g->n_node; j++)
        {
            if (clads_statistic_uniform_trial(p))
                clads_graph_add_edge(g, v[i], v[j], NULL);
        }
    }

    CLADS_FREE(v);

    return g;
}

clads_graph_type *
clads_graph_new_watts(clads_size_type n,
                      clads_size_type k,
                      clads_real_type p,
                      clads_bool_type is_directed,
                      clads_bool_type allow_loop,
                      clads_bool_type allow_multiple_edges)
{
    clads_graph_node_type *r, **v = CLADS_ALLOC(n, clads_graph_node_type *);
    clads_graph_type *g = CLADS_ALLOC(1, clads_graph_type);
    clads_graph_edge_type *e;
    clads_list_node_type *l;
    clads_size_type i, j;

    clads_graph_initialize(g);

    g->is_directed = is_directed;
    g->allow_loop = allow_loop;
    g->allow_multiple_edges = allow_multiple_edges;

    /*
     * Creating nodes.
     */
    while (g->n_node < n)
        v[g->n_node - 1] = clads_graph_add_node(g, NULL);

    /*
     * Creating edges (multiple edges and loops are threated by
     * `clads_graph_add_edge' function).
     */
    for (i = 0; i < g->n_node; i++)
    {
        clads_graph_add_edge(g, v[i], v[i], NULL);

        for (j = 1; j <= k / 2; j++)
        {
            clads_graph_add_edge(g, v[i], v[clads_loop_index(i + j, n)], NULL);
            clads_graph_add_edge(g, v[i], v[clads_loop_index(i - j, n)], NULL);
        }
    }

    /*
     * Rewiring edges.
     */
    while ((l = clads_list_next(g->l_edge)))
    {
        e = (clads_graph_edge_type *) l->info;

        if (clads_statistic_uniform_trial(p))
        {
            r = v[clads_randint(0, n - 1)];

            if (clads_statistic_uniform_trial(0.5))
                e->na = r;
            else
                e->nb = r;
        }
    }

    CLADS_FREE(v);

    return g;
}

clads_graph_type *
clads_graph_new_barabasi(clads_size_type n,
                         clads_size_type m,
                         clads_bool_type is_directed,
                         clads_bool_type allow_loop,
                         clads_bool_type allow_multiple_edges)
{
    clads_graph_node_type **v = CLADS_ALLOC(n, clads_graph_node_type *);
    clads_graph_type *g = CLADS_ALLOC(1, clads_graph_type);
    clads_size_type count, index, drawn;

    clads_graph_initialize(g);

    g->is_directed = is_directed;
    g->allow_loop = allow_loop;
    g->allow_multiple_edges = allow_multiple_edges;

    /*
     * Creating the first `m' nodes.
     */
    while (g->n_node < m)
        v[g->n_node - 1] = clads_graph_add_node(g, NULL);

    /*
     * Creating the remaining `n' - `m' nodes.
     */
    while (g->n_node < n)
    {
        count = 0;
        index = g->n_node;

        v[index] = clads_graph_add_node(g, NULL);

        while (count < m)
        {
            // TODO: probabilistic function.
            drawn = 0;

            if (clads_graph_add_edge(g, v[index], v[drawn], NULL))
                count++;
        }
    }

    CLADS_FREE(v);

    return g;
}

clads_graph_edge_type *
clads_graph_edge_new(clads_void_type)
{
    clads_graph_edge_type *e = CLADS_ALLOC(1, clads_graph_edge_type);

    e->na = NULL;
    e->nb = NULL;
    e->info = NULL;
    e->key = clads_off;

    return e;
}

clads_void_type
clads_graph_clear_adjacency(clads_graph_type *g)
{
    clads_size_type i;

    if (g->l_adjacency != NULL)
    {
        for (i = 0; i < g->n_node; i++)
        {
            clads_list_finalize(g->l_adjacency[i]);
            CLADS_FREE(g->l_adjacency[i]);
        }

        CLADS_FREE(g->l_adjacency);
        g->l_adjacency = NULL;
    }
}

clads_void_type
clads_graph_mount_adjacency(clads_graph_type *g)
{
    clads_graph_edge_type *e;
    clads_list_node_type *n, *p;
    clads_size_type i;

    /*
     * Clear the adjacency list if it already exists, and create a new one.
     */
    clads_graph_clear_adjacency(g);

    g->l_adjacency = CLADS_ALLOC(g->n_node, clads_list_type *);

    /*
     * Initializing lists.
     */
    for (i = 0; i < g->n_node; i++)
    {
        g->l_adjacency[i] = CLADS_ALLOC(1, clads_list_type);
        clads_list_initialize(g->l_adjacency[i]);
    }

    /*
     * Fill the adjacency list.
     */
    while ((p = clads_list_next(g->l_edge)))
    {
        e = (clads_graph_edge_type *) p->info;

        n = clads_list_node_new();
        n->info = (clads_addr_type) e->nb;
        clads_list_insert(g->l_adjacency[e->na->id], n);

        if (!g->is_directed)
        {
            n = clads_list_node_new();
            n->info = (clads_addr_type) e->na;
            clads_list_insert(g->l_adjacency[e->nb->id], n);
        }
    }
}

clads_list_type *
clads_graph_get_edges_by_nodes(clads_graph_type *g,
                               clads_graph_node_type *na,
                               clads_graph_node_type *nb)
{
    clads_list_node_type *l = g->l_edge->head;
    clads_graph_edge_type *e;
    clads_list_node_type *p;

    clads_list_type *r = CLADS_ALLOC(1, clads_list_type);
    clads_list_initialize(r);

    while (l != NULL)
    {
        e = (clads_graph_edge_type *) l->info;

        if ((e->na == na && e->nb == nb) ||
            (!g->is_directed && e->na == nb && e->nb == na))
        {
            p = clads_list_node_new();
            p->info = e;
            clads_list_insert(r, p);
        }

        l = l->next;
    }

    if (clads_list_is_empty(r) == clads_true)
    {
        clads_list_finalize(r);
        CLADS_FREE(r);
        r = NULL;
    }

    return r;
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
    clads_list_node_type *l = g->l_node->head;
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
                             clads_addr_type info)
{
    clads_list_node_type *l = g->l_node->head;
    clads_graph_node_type *n;

    while (l != NULL)
    {
        n = (clads_graph_node_type *) l->info;

        if (g->f_compare(g, n->info, info) == clads_equal)
            return n;

        l = l->next;
    }

    return NULL;
}

clads_graph_edge_type *
clads_graph_add_edge(clads_graph_type *g,
                     clads_graph_node_type *na,
                     clads_graph_node_type *nb,
                     clads_addr_type info)
{
    clads_graph_edge_type *e;
    clads_list_node_type *p;

    if (g->allow_loop == clads_false && na == nb)
        return NULL;

    if (g->allow_multiple_edges == clads_false &&
        clads_graph_get_edge_by_nodes(g, na, nb) != NULL)
        return NULL;

    e = CLADS_ALLOC(1, clads_graph_edge_type);

    e->id = g->n_edge++;

    e->na = na;
    e->nb = nb;
    e->info = info;

    p = clads_list_node_new();
    p->info = (clads_addr_type) e;
    clads_list_insert(g->l_edge, p);

    return e;
}

clads_graph_node_type *
clads_graph_add_node(clads_graph_type *g,
                     clads_addr_type info)
{
    clads_graph_node_type *n = CLADS_ALLOC(1, clads_graph_node_type);
    clads_list_node_type *p;

    n->id = g->n_node++;
    n->info = info;

    p = clads_list_node_new();
    p->info = (clads_addr_type) n;
    clads_list_insert(g->l_node, p);

    return n;
}

clads_list_type *
clads_graph_get_edges_by_node(clads_graph_type *g,
                              clads_graph_node_type *n)
{
    clads_list_node_type *p, *l = g->l_edge->head;
    clads_list_type *r = CLADS_ALLOC(1, clads_list_type);
    clads_graph_edge_type *e;

    clads_list_initialize(r);

    while (l != NULL)
    {
        e = (clads_graph_edge_type *) l->info;

        if (e->na == n || e->nb == n)
        {
            p = clads_list_node_new();
            p->info = (clads_addr_type) e;
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
    clads_list_type *r = CLADS_ALLOC(1, clads_list_type);
    clads_graph_edge_type *e;

    clads_list_initialize(r);

    while (l != NULL)
    {
        e = (clads_graph_edge_type *) l->info;

        if (e->na == n || e->nb == n)
        {
            p = clads_list_node_new();

            if (e->na == n)
                p->info = (clads_addr_type) e->nb;
            else
                p->info = (clads_addr_type) e->na;

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

clads_list_type *
clads_graph_spanning_tree(clads_graph_type *g)
{
    clads_graph_node_type *a, *b;
    clads_graph_edge_type *e;
    clads_list_node_type *l;
    clads_list_type *q = CLADS_ALLOC(1, clads_list_type);
    clads_list_type *r = CLADS_ALLOC(1, clads_list_type);

    clads_list_initialize(q);
    clads_list_initialize(r);

    /*
     * Initialize nodes as unvisited.
     */
    while ((l = clads_list_next(g->l_node)))
    {
        a = CLADS_CAST(l->info, clads_graph_node_type *);
        a->key = clads_off;
    }

    /*
     * Using breadth-first-search to select the edges for the spanning tree.
     */
    clads_graph_mount_adjacency(g);

    a = CLADS_CAST(g->l_node->head->info, clads_graph_node_type *);
    a->key = clads_on;

    l = clads_list_node_new();
    l->info = a;

    clads_list_enqueue(q, l);

    while (clads_list_is_empty(q) == clads_false)
    {
        l = clads_list_dequeue(q);
        a = CLADS_CAST(l->info, clads_graph_node_type *);

        /*
         * Iterate over each neighbor of node `a'.
         */
        while ((l = clads_list_next(g->l_adjacency[a->id])))
        {
            b = CLADS_CAST(l, clads_graph_node_type *);

            /*
             * If node `b' not visited yet, do it.
             */
            if (b->key == clads_off)
            {
                b->key = clads_on;

                l = clads_list_node_new();
                l->info = b;
                clads_list_enqueue(q, l);

                e = clads_graph_edge_new();
                e->na = a;
                e->nb = b;
                l = clads_list_node_new();
                l->info = e;
                clads_list_insert(r, l);
            }
        }
    }

    if (clads_list_is_empty(r) == clads_true)
    {
        clads_list_finalize(r);
        CLADS_FREE(r);
        r = NULL;
    }

    return r;
}

clads_graph_type *
clads_graph_from_tgf_file(clads_string_type filename)
{
    clads_file_type handle = fopen(filename, "r");

    if (handle != NULL)
    {
        clads_id_type id_o, id_d;
        clads_addr_type *map = NULL;
        clads_size_t_type length = 0;
        clads_string_type line = NULL;
        clads_graph_node_type *n;

        clads_graph_type *g = CLADS_ALLOC(1, clads_graph_type);
        clads_graph_initialize(g);

        clads_bool_type mode = clads_true; // True to read node lines.

        while (getline(&line, &length, handle) != -1)
        {
            if (line[0] != '#')
            {
                if (mode == clads_true)
                {
                    /*
                     * Read line with node description.
                     */
                    clads_graph_add_node(g, NULL);

                    // TODO: read optional info and add it to node structure.
                }
                else
                {
                    /*
                     * Read line with edge description.
                     */
                    sscanf(line, CLADS_UINT_STR " " CLADS_UINT_STR,
                            &id_o, &id_d);

                    clads_graph_add_edge(g, map[id_o], map[id_d], NULL);

                    // TODO: read optional info and add it to edge structure.
                }
            }
            else
            {
                mode = clads_false; // Switch to edge mode.

                /*
                 * Bulid node addess vector indexed by id
                 */
                if (g->n_node > 0)
                {
                    map = CLADS_ALLOC(g->n_node, clads_addr_type);

                    clads_list_node_type *l = g->l_node->head;

                    while (l != NULL)
                    {
                        n = (clads_graph_node_type *) l->info;
                        map[n->id] = n;
                        l = l->next;
                    }
                }
            }

            free(line); // Memory allocated by the `getline' function.
            line = NULL;
            length = 0;
        }

        if (map != NULL)
            CLADS_FREE(map);

        fclose(handle);

        return g;
    }

    return NULL;
}
