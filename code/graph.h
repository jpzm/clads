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

#ifndef CLADS_GRAPH_H
#define CLADS_GRAPH_H

#include "clads.h"
#include "list.h"
#include "statistic.h"


/**
 *
 */
typedef struct clads_graph_node
{
    clads_id_type id;
    clads_real_type clustering;
    clads_size_type degree;
    clads_addr_type info; // used by external libraries and applications
    clads_key_type key;
} clads_graph_node_type;

/**
 *
 */
typedef struct clads_graph_edge
{
    clads_id_type id;
    clads_graph_node_type *na;
    clads_graph_node_type *nb;
    clads_addr_type info; // used by external libraries and applications
    clads_key_type key;
} clads_graph_edge_type;

/**
 * Graph structure
 */
typedef struct clads_graph
{
    clads_size_type n_node;
    clads_size_type n_edge;
    clads_list_type *l_node;
    clads_list_type *l_edge;
    clads_bool_type allow_loop;             // Loops are allowed.
    clads_bool_type allow_multiple_edges;   // Multiple edges are allowed.
    clads_bool_type is_directed;
    clads_real_type clustering;
    /*
     * The adjacency list is indexed by the node's id.
     */
    clads_list_type **l_adjacency;
    /*
     * This function tell if two nodes have the same information
     * (i.e. are equal).
     */
    clads_order_type (*f_compare)(struct clads_graph *,
                                  clads_addr_type,
                                  clads_addr_type);
    /*
     * Used by external programs to store extra information (e.g. bindings).
     */
    clads_addr_type more;
} clads_graph_type;


/**
 * Initialize an given graph
 */
inline clads_void_type
clads_graph_initialize(clads_graph_type *g);

/**
 * Finalize an given graph
 */
inline clads_void_type
clads_graph_finalize(clads_graph_type *g);

/**
 * Create a new graph based on Erdos-Renyi G(n, m) network model.
 */
clads_graph_type *
clads_graph_new_erdos_nm(clads_size_type n,
                         clads_size_type m,
                         clads_bool_type is_directed,
                         clads_bool_type allow_loop,
                         clads_bool_type allow_multiple_edges);

/**
 * Create a new graph based on Erdos-Renyi G(n, p) network model.
 */
clads_graph_type *
clads_graph_new_erdos_np(clads_size_type n,
                         clads_real_type p,
                         clads_bool_type is_directed,
                         clads_bool_type allow_loop,
                         clads_bool_type allow_multiple_edges);

/**
 * Create a new graph based on Watts-Strogatz network model (small-world).
 */
clads_graph_type *
clads_graph_new_watts(clads_size_type n,    // Size.
                      clads_size_type k,    // Neighborhood.
                      clads_real_type p,    // Rewiring probability.
                      clads_bool_type is_directed,
                      clads_bool_type allow_loop,
                      clads_bool_type allow_multiple_edges);

/**
 * Create a new graph based on Barabasi-Albert network model (scale-free).
 */
clads_graph_type *
clads_graph_new_barabasi(clads_size_type n,
                         clads_size_type m,
                         clads_bool_type is_directed,
                         clads_bool_type allow_loop,
                         clads_bool_type allow_multiple_edges);

/**
 * Creates a copy of a graph.
 */
clads_graph_type *
clads_graph_copy(clads_graph_type *g);

/**
 * Clear the adjacency list of the graph.
 * Time complexity: O(n * E{b}).
 * Where `n' is the number of nodes and `E{b}' is the expected number of
 * neighbors.
 */
clads_void_type
clads_graph_clear_adjacency(clads_graph_type *g);

/**
 * Create the adjacency list of the graph.
 * Time complexity: O((n + e) + (n * E{b})).
 * Where `n' is the number of nodes, `e' the number of edges and `E{b}' is the
 * expected number of neighbors.
 * The right side of complexity is due to the call of
 * `clads_graph_clear_adjacency()'.
 */
clads_void_type
clads_graph_mount_adjacency(clads_graph_type *g);

/**
 *
 */
clads_graph_edge_type *
clads_graph_edge_new(clads_void_type);

/**
 *
 */
clads_graph_edge_type *
clads_graph_add_edge(clads_graph_type *g,
                     clads_graph_node_type *na,
                     clads_graph_node_type *nb,
                     clads_addr_type info);

/**
 *
 */
clads_graph_node_type *
clads_graph_add_node(clads_graph_type *g,
                     clads_addr_type info);

/**
 *
 */
clads_list_type *
clads_graph_get_edges_by_nodes(clads_graph_type *g,
                               clads_graph_node_type *na,
                               clads_graph_node_type *nb);

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
                             clads_addr_type info);

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
 * Return a list of edges that describe a spanning tree.
 * Time complexity: O(n + e).
 * Where `n' is the number of nodes a `e' the number of edges.
 */
clads_list_type *
clads_graph_spanning_tree(clads_graph_type *g);


#endif
