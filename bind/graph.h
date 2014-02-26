/**
 * Copyright (C) 2012 Joao Paulo de Souza Medeiros
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

#ifndef CLADS_GRAPH_BIND_H
#define CLADS_GRAPH_BIND_H


#include <Python.h>
#include "code/graph.h"


static PyObject *CladsGraphError;

typedef struct clads_b_graph
{
    PyObject *f_compare_callback;
} clads_b_graph_type;


/**
 *
 */
static char initialize__doc__[] = "Create a new graph";

static PyObject*
clads_b_graph_initialize(PyObject *self, PyObject *args);

/**
 *
 */
static char size__doc__[] = "Return the size of graph";

static PyObject*
clads_b_graph_size(PyObject *self, PyObject *args);

/**
 *
 */
static char add_node__doc__[] = "Insert a node on the graph";

static PyObject*
clads_b_graph_add_node(PyObject *self, PyObject *args);

/**
 *
 */
static char add_edge__doc__[] = "Insert an edge on the graph";

static PyObject*
clads_b_graph_add_edge(PyObject *self, PyObject *args);

/**
 *
 */
static char get_node_info__doc__[] = "Get node's info";

static PyObject*
clads_b_graph_get_node_info(PyObject *self, PyObject *args);

/**
 *
 */
static char get_edge_info__doc__[] = "Get edge's info";

static PyObject*
clads_b_graph_get_edge_info(PyObject *self, PyObject *args);

/**
 *
 */
static char get_node_id__doc__[] = "Get node's id";

static PyObject*
clads_b_graph_get_node_id(PyObject *self, PyObject *args);

/**
 *
 */
static char get_edge_id__doc__[] = "Get edge's id";

static PyObject*
clads_b_graph_get_edge_id(PyObject *self, PyObject *args);

/**
 *
 */
static char get_edge_nodes__doc__[] = "Get edge's nodes";

static PyObject*
clads_b_graph_get_edge_nodes(PyObject *self, PyObject *args);

/**
 *
 */
static PyMethodDef CladsGraphMethods[] =
{
    {"initialize",
        clads_b_graph_initialize,
        METH_VARARGS,
        initialize__doc__},
    {"size",
        clads_b_graph_size,
        METH_VARARGS,
        size__doc__},
    {"add_node",
        clads_b_graph_add_node,
        METH_VARARGS,
        add_node__doc__},
    {"add_edge",
        clads_b_graph_add_edge,
        METH_VARARGS,
        add_edge__doc__},
    {"get_node_info",
        clads_b_graph_get_node_info,
        METH_VARARGS,
        get_node_info__doc__},
    {"get_edge_info",
        clads_b_graph_get_edge_info,
        METH_VARARGS,
        get_edge_info__doc__},
    {"get_node_id",
        clads_b_graph_get_node_id,
        METH_VARARGS,
        get_node_id__doc__},
    {"get_edge_id",
        clads_b_graph_get_edge_id,
        METH_VARARGS,
        get_edge_id__doc__},
    {"get_edge_nodes",
        clads_b_graph_get_edge_nodes,
        METH_VARARGS,
        get_edge_nodes__doc__},
    {NULL, NULL, 0, NULL}
};

/**
 *
 */
static char module__doc__[] = "CLADS graph module";

PyMODINIT_FUNC
initclads_graph(void);

#endif
