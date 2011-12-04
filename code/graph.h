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

#ifndef CLADS_GRAPH_H
#define CLADS_GRAPH_H

#include "clads.h"
#include "list.h"


/**
 *
 */
typedef struct clads_graph_node
{
    clads_id_type id;
    clads_real_type clustering;
    void *info; // used by external libraries and applications
} clads_graph_node_type;

/**
 *
 */
typedef struct clads_graph_edge
{
    clads_graph_node_type *na;
    clads_graph_node_type *nb;
    void *info; // used by external libraries and applications
} clads_graph_edge_type;

/**
 * Graph structure
 */
typedef struct clads_graph
{
    clads_uint_type n_node;
    clads_uint_type n_edge;
    clads_list_type *l_node;
    clads_list_type *l_edge;
    clads_bool_type is_directed;
    clads_real_type clustering;

    /**
     * The adjacency list is indexed by the node's id.
     */
    clads_list_type **l_adjacency;

    /**
     * This function tell if two nodes have the same information
     * (i.e. are equal).
     */
    clads_order_type (*f_compare)(void *, void *);
} clads_graph_type;


/**
 * Initialize an given graph
 */
inline void
clads_graph_initialize(clads_graph_type *g);

/**
 * Finalize an given graph
 */
inline void
clads_graph_finalize(clads_graph_type *g);

/**
 * Creates a copy of a graph.
 *
 * @param ga    Pointer to a graph structure.
 * @param gb    Pointer to a uninitialized graph structure.
 * @return      Return 0 (zero) for error and 1 (one) for success.
 */
int
clads_graph_copy(const clads_graph_type *ga,
                 clads_graph_type *gb);

/**
 *
 */
void
clads_graph_mount_adjacency(clads_graph_type *g);

/**
 *
 */
void
clads_graph_clear_adjacency(clads_graph_type *g);

/**
 *
 */
clads_graph_edge_type *
clads_graph_add_edge(clads_graph_type *g,
                     clads_graph_node_type *na,
                     clads_graph_node_type *nb,
                     void *info);

/**
 *
 */
clads_graph_node_type *
clads_graph_add_node(clads_graph_type *g,
                     void *info);

/**
 *
 */
clads_graph_edge_type *
clads_graph_get_edge_by_nodes(clads_graph_type *g,
                              clads_graph_node_type *na,
                              clads_graph_node_type *nb);

/**
 *
 */
clads_list_type *
clads_graph_get_edges_by_node(clads_graph_type *g,
                              clads_graph_node_type *n);

/**
 *
 */
clads_graph_node_type *
clads_graph_get_node(clads_graph_type *g,
                     clads_id_type id);

/**
 *
 */
clads_graph_node_type *
clads_graph_get_node_by_info(clads_graph_type *g,
                             void *info);

/**
 *
 */
clads_list_type *
clads_graph_get_node_neighbors(clads_graph_type *g,
                               clads_graph_node_type *n);

/**
 *
 */
clads_real_type
clads_graph_clustering(clads_graph_type *g);

/**
 *
 */
clads_real_type
clads_graph_node_clustering(clads_graph_type *g,
                            clads_graph_node_type *n);

/**
 *
 */
clads_list_type *
clads_graph_spanning_tree(clads_graph_type *g,
                          clads_graph_node_type *n);


#endif
