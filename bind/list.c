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

#include "bind/list.h"

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

clads_order_type
clads_b_list_f_compare(clads_list_type *l,
                       clads_addr_type a,
                       clads_addr_type b)
{
    clads_order_type o = clads_unknown;
    clads_b_list_type *b_l;
    PyObject *arglist;
    PyObject *result;
    int r;

    b_l = (clads_b_list_type *) l->more;

    /*
     * Time to call the callback
     */
    arglist = Py_BuildValue("(OO)", a, b);

    result = PyEval_CallObject(b_l->f_compare_callback, arglist);

    Py_DECREF(arglist);

    if (result == NULL)
        return clads_unknown;

    if (PyArg_Parse(result, "i", &r))
    {
        if (r == -1)
            o = clads_less;
        if (r == 0)
            o = clads_equal;
        if (r == 1)
            o = clads_more;
    }

    Py_DECREF(result);

    return o;
}

PyObject *
clads_b_list_set_compare_callback(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;
    PyObject *callback;
    clads_list_type *l;
    clads_b_list_type *b_l;

    if (PyArg_ParseTuple(args, "OO:set_compare_callback", &a, &callback))
    {
        l = (clads_list_type *) PyCObject_AsVoidPtr(a);
        b_l = (clads_b_list_type *) l->more;

        if (!PyCallable_Check(callback))
        {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }

        Py_XINCREF(callback);                   // Add a reference.
        Py_XDECREF(b_l->f_compare_callback);    // Dispose of previous.
        b_l->f_compare_callback = callback;     // Remember new.

        Py_RETURN_NONE;
    }

    return NULL;
}

PyObject*
clads_b_list_initialize(PyObject *self, PyObject *args)
{
    /*
     * Call the function
     */
    clads_b_list_type *b_l = CLADS_ALLOC(1, clads_b_list_type);
    clads_list_type *l; 

    b_l->f_compare_callback = (void *) NULL;

    l = CLADS_ALLOC(1, clads_list_type);
    clads_list_initialize(l);
    l->do_free_info = clads_false;

    l->f_compare = &clads_b_list_f_compare;
    l->more = b_l;

    /*
     * Convert output
     */
    return PyCObject_FromVoidPtr(l, &clads_b_list_finalize);
}

PyObject*
clads_b_list_size(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;
    clads_list_type *l;

    if (!PyArg_ParseTuple(args, "O", &a))
        Py_RETURN_NONE;

    l = (clads_list_type *) PyCObject_AsVoidPtr(a);

    /*
     * Call the function
     */
    clads_size_type s = clads_list_size(l);

    /*
     * Convert output
     */
    return Py_BuildValue("l", s);
}

PyObject*
clads_b_list_insert(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;
    PyObject *x = NULL;

    if (!PyArg_ParseTuple(args, "OO", &a, &x))
        Py_RETURN_NONE;

    clads_list_type *l;
    l = (clads_list_type *) PyCObject_AsVoidPtr(a);

    /*
     * Call the function
     */
    clads_list_node_type *n = CLADS_ALLOC(1, clads_list_node_type);

    clads_list_node_initialize(n);
    n->info = x;

    if (clads_list_insert(l, n) == clads_true)
        Py_INCREF(x);
    else
        clads_list_node_finalize(n, l->do_free_info);

    /*
     * Convert output
     */
    Py_RETURN_TRUE;
}

PyObject*
clads_b_list_remove(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;
    PyObject *x = NULL;
    clads_byte_type c;

    if (!PyArg_ParseTuple(args, "OOc", &a, &x, &c))
        Py_RETURN_NONE;

    clads_list_type *l;
    l = (clads_list_type *) PyCObject_AsVoidPtr(a);

    /*
     * Call the function
     */
    clads_list_node_type *n;

    if (c == 'T')
    {
        while ((n = clads_list_search(l, x)))
        {
            clads_list_remove(l, n);
            Py_DECREF(x);
        }
    }
    else
    {
        if ((n = clads_list_search(l, x)))
        {
            clads_list_remove(l, n);
            Py_DECREF(x);
        }
    }

    /*
     * Convert output
     */
    Py_RETURN_TRUE;
}

PyObject*
clads_b_list_next(PyObject *self, PyObject *args)
{
    /*
     * Convert input
     */
    PyObject *a = NULL;

    if (!PyArg_ParseTuple(args, "O", &a))
        Py_RETURN_NONE;

    clads_list_type *l;
    l = (clads_list_type *) PyCObject_AsVoidPtr(a);

    /*
     * Call the function
     */
    clads_list_node_type *n = clads_list_next(l);

    if (n == NULL)
        Py_RETURN_NONE;

    /*
     * Convert output
     */
    return Py_BuildValue("O", n->info);
}

PyMODINIT_FUNC
initclads_list(void)
{
    PyObject *m;

    m = Py_InitModule4("clads_list",
            CladsListMethods,
            module__doc__,
            (PyObject *) NULL,
            PYTHON_API_VERSION);

    if (m == NULL)
        return;

    CladsListError = PyErr_NewException("clads.list.error", NULL, NULL);
    Py_INCREF(CladsListError);
    PyModule_AddObject(m, "error", CladsListError);

    if (PyErr_Occurred())
        Py_FatalError("Can't initialize CLADS list module");
}
