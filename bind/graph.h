/**
 * Copyright (C) 2012 Joao Paulo de Souza Medeiros
 *
 * Author(s): Joao Paulo de Souza Medeiros <jpsm1985@gmail.com>
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

#ifndef CLADS_LIST_BIND_H
#define CLADS_LIST_BIND_H


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
static char insert_node__doc__[] = "Insert a node on the graph";

static PyObject*
clads_b_graph_insert_node(PyObject *self, PyObject *args);

/**
 *
 */
static char remove_node__doc__[] = "Remove a node from the graph";

static PyObject*
clads_b_graph_remove_node(PyObject *self, PyObject *args);

/**
 *
 */
static char next_node__doc__[] = "Get the next node element from the graph";

static PyObject*
clads_b_graph_next_node(PyObject *self, PyObject *args);

/**
 *
 */
static char insert_edge__doc__[] = "Insert an edge on the graph";

static PyObject*
clads_b_graph_insert_edge(PyObject *self, PyObject *args);

/**
 *
 */
static char remove_edge__doc__[] = "Remove a edge from the graph";

static PyObject*
clads_b_graph_remove_edge(PyObject *self, PyObject *args);

/**
 *
 */
static char next_edge__doc__[] = "Get the next edge element from the graph";

static PyObject*
clads_b_graph_next_edge(PyObject *self, PyObject *args);

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
    {"insert_node",
        clads_b_graph_insert_node,
        METH_VARARGS,
        insert_node__doc__},
    {"remove_node",
        clads_b_graph_remove_node,
        METH_VARARGS,
        remove_node__doc__},
    {"next_node",
        clads_b_graph_next_node,
        METH_VARARGS,
        next_node__doc__},
    {"insert_edge",
        clads_b_graph_insert_edge,
        METH_VARARGS,
        insert_edge__doc__},
    {"remove_edge",
        clads_b_graph_remove_edge,
        METH_VARARGS,
        remove_edge__doc__},
    {"next_edge",
        clads_b_graph_next_edge,
        METH_VARARGS,
        next_edge__doc__},
    {NULL, NULL, 0, NULL}
};

/**
 *
 */
static char module__doc__[] = "CLADS graph module";

PyMODINIT_FUNC
initgraph(void);

#endif
