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

#include "bind/graph.h"

void
clads_b_list_finalize(clads_addr_type l)
{
    if (l != NULL)
    {
        clads_list_finalize(CLADS_CAST(l, clads_list_type *));
        free((void *) CLADS_CAST(l, clads_list_type *)->more);
        free((void *) CLADS_CAST(l, clads_list_type *));
    }
}

void
clads_b_graph_finalize(clads_addr_type g)
{
    if (g != NULL)
    {
        clads_graph_finalize(CLADS_CAST(g, clads_graph_type *));
        free((void *) g);
    }
}

void
clads_b_graph_node_finalize(clads_addr_type n)
{
    if (n != NULL)
        free((void *) n);
}

void
clads_b_graph_edge_finalize(clads_addr_type e)
{
    if (e != NULL)
        free((void *) e);
}

PyObject*
clads_b_graph_initialize(PyObject *self, PyObject *args)
{
    /*
     * Call the function
     */
    PyObject *a = NULL;
    clads_graph_type *g;

    if (PyArg_ParseTuple(args, "O", &a))
        g = (clads_graph_type *) PyCObject_AsVoidPtr(a);
    else
        g = CLADS_ALLOC(1, clads_graph_type);

    clads_graph_initialize(g);

    /*
     * Convert output
     */
    return PyCObject_FromVoidPtr(g, &clads_b_graph_finalize);
}

PyObject*
clads_b_graph_size(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;
    clads_graph_type *g;

    if (!PyArg_ParseTuple(args, "O", &a))
        Py_RETURN_NONE;

    g = (clads_graph_type *) PyCObject_AsVoidPtr(a);

    /*
     * Convert output
     */
    return Py_BuildValue("(ll)", (long int) g->n_node, (long int) g->n_edge);
}

PyObject*
clads_b_graph_add_node(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;
    PyObject *x = NULL;

    if (!PyArg_ParseTuple(args, "OO", &a, &x))
        Py_RETURN_NONE;

    clads_graph_node_type *n;
    clads_graph_type *g;
    g = (clads_graph_type *) PyCObject_AsVoidPtr(a);

    /*
     * Call the function
     */
    n = clads_graph_add_node(g, x);
    Py_INCREF(x);

    /*
     * Convert output
     */
    return PyCObject_FromVoidPtr(n, &clads_b_graph_node_finalize);
}

PyObject*
clads_b_graph_add_edge(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;
    PyObject *x = NULL;
    PyObject *y = NULL;
    PyObject *i = NULL;

    if (!PyArg_ParseTuple(args, "OOOO", &a, &x, &y, &i))
        Py_RETURN_NONE;

    clads_graph_type *g;
    clads_graph_edge_type *e;
    clads_graph_node_type *na, *nb;

    g = (clads_graph_type *) PyCObject_AsVoidPtr(a);
    na = (clads_graph_node_type *) PyCObject_AsVoidPtr(x);
    nb = (clads_graph_node_type *) PyCObject_AsVoidPtr(y);

    /*
     * Call the function
     */
    e = clads_graph_add_edge(g, na, nb, i);

    if (e == NULL)
        Py_RETURN_NONE;

    Py_INCREF(x);
    Py_INCREF(y);
    Py_INCREF(i);

    /*
     * Convert output
     */
    return PyCObject_FromVoidPtr(e, &clads_b_graph_edge_finalize);
}

PyObject*
clads_b_graph_get_node_info(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;

    if (!PyArg_ParseTuple(args, "O", &a))
        Py_RETURN_NONE;

    clads_graph_node_type *n;
    n = (clads_graph_node_type *) PyCObject_AsVoidPtr(a);

    /*
     * Call the function
     */
    if (n->info == NULL)
        Py_RETURN_NONE;

    /*
     * Convert output
     */
    return n->info;
}

PyObject*
clads_b_graph_get_edge_info(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;

    if (!PyArg_ParseTuple(args, "O", &a))
        Py_RETURN_NONE;

    clads_graph_edge_type *e;
    e = (clads_graph_edge_type *) PyCObject_AsVoidPtr(a);

    /*
     * Call the function
     */
    clads_addr_type i = e->info;

    if (i == NULL)
        Py_RETURN_NONE;

    /*
     * Convert output
     */
    return i;
}

PyObject*
clads_b_graph_get_node_id(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;

    if (!PyArg_ParseTuple(args, "O", &a))
        Py_RETURN_NONE;

    clads_graph_node_type *n;
    n = (clads_graph_node_type *) PyCObject_AsVoidPtr(a);

    /*
     * Convert output
     */
    return Py_BuildValue("l", (long int) n->id);
}

PyObject*
clads_b_graph_get_edge_id(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;

    if (!PyArg_ParseTuple(args, "O", &a))
        Py_RETURN_NONE;

    clads_graph_edge_type *e;
    e = (clads_graph_edge_type *) PyCObject_AsVoidPtr(a);

    /*
     * Convert output
     */
    return Py_BuildValue("l", (long int) e->id);
}

PyObject*
clads_b_graph_get_edge_nodes(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;

    if (!PyArg_ParseTuple(args, "O", &a))
        Py_RETURN_NONE;

    clads_graph_edge_type *e;
    e = (clads_graph_edge_type *) PyCObject_AsVoidPtr(a);

    /*
     * Convert output
     */
    return Py_BuildValue("(OO)",
        PyCObject_FromVoidPtr(e->na, &clads_b_graph_node_finalize),
        PyCObject_FromVoidPtr(e->nb, &clads_b_graph_node_finalize));
}

PyMODINIT_FUNC
initclads_graph(void)
{
    PyObject *m;

    m = Py_InitModule4("clads_graph",
            CladsGraphMethods,
            module__doc__,
            (PyObject *) NULL,
            PYTHON_API_VERSION);

    if (m == NULL)
        return;

    CladsGraphError = PyErr_NewException("clads.graph.error", NULL, NULL);
    Py_INCREF(CladsGraphError);
    PyModule_AddObject(m, "error", CladsGraphError);

    if (PyErr_Occurred())
        Py_FatalError("Can't initialize CLADS graph module");
}
