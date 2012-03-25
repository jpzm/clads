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

#include "bind/graph.h"

void
clads_b_graph_finalize(clads_graph_type *g)
{
    clads_graph_finalize(g);
    free((void *) g);
}

PyObject*
clads_b_graph_initialize(PyObject *self, PyObject *args)
{
    /*
     * Call the function
     */
    clads_graph_type *g = CLADS_ALLOC(1, clads_graph_type);

    clads_graph_initialize(g);

    /*
     * Convert output
     */
    return PyCObject_FromVoidPtr(g, (void *) clads_b_graph_finalize);
}

PyObject*
clads_b_graph_size(PyObject *self, PyObject *args)
{
    return PyCObject_FromVoidPtr(NULL, (void *) NULL);
}

PyObject*
clads_b_graph_insert_node(PyObject *self, PyObject *args)
{
    return PyCObject_FromVoidPtr(NULL, (void *) NULL);
}

PyObject*
clads_b_graph_remove_node(PyObject *self, PyObject *args)
{
    return PyCObject_FromVoidPtr(NULL, (void *) NULL);
}

PyObject*
clads_b_graph_next_node(PyObject *self, PyObject *args)
{
    return PyCObject_FromVoidPtr(NULL, (void *) NULL);
}

PyObject*
clads_b_graph_insert_edge(PyObject *self, PyObject *args)
{
    return PyCObject_FromVoidPtr(NULL, (void *) NULL);
}

PyObject*
clads_b_graph_remove_edge(PyObject *self, PyObject *args)
{
    return PyCObject_FromVoidPtr(NULL, (void *) NULL);
}

PyObject*
clads_b_graph_next_edge(PyObject *self, PyObject *args)
{
    return PyCObject_FromVoidPtr(NULL, (void *) NULL);
}

PyMODINIT_FUNC
initgraph(void)
{
    PyObject *m;

    m = Py_InitModule4("graph",
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
