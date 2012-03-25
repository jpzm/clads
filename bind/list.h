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
#include "code/list.h"


static PyObject *CladsListError;

typedef struct clads_b_list
{
    PyObject *f_compare_callback;
} clads_b_list_type;


/**
 *
 */
static char set_compare_callback__doc__[] = "Set node compare callback";

static PyObject *
clads_b_list_set_compare_callback(PyObject *self, PyObject *args);

/**
 *
 */
static char initialize__doc__[] = "Create a new list";

static PyObject*
clads_b_list_initialize(PyObject *self, PyObject *args);

/**
 *
 */
static char size__doc__[] = "Return the size of list";

static PyObject*
clads_b_list_size(PyObject *self, PyObject *args);

/**
 *
 */
static char insert__doc__[] = "Insert a node on the list";

static PyObject*
clads_b_list_insert(PyObject *self, PyObject *args);

/**
 *
 */
static char remove__doc__[] = "Remove a node from the list";

static PyObject*
clads_b_list_remove(PyObject *self, PyObject *args);

/**
 *
 */
static char next__doc__[] = "Get the next node element from the list";

static PyObject*
clads_b_list_next(PyObject *self, PyObject *args);

/**
 *
 */
static PyMethodDef CladsListMethods[] =
{
    {"set_compare_callback",
        clads_b_list_set_compare_callback,
        METH_VARARGS,
        set_compare_callback__doc__},
    {"initialize",
        clads_b_list_initialize,
        METH_VARARGS,
        initialize__doc__},
    {"size",
        clads_b_list_size,
        METH_VARARGS,
        size__doc__},
    {"insert",
        clads_b_list_insert,
        METH_VARARGS,
        insert__doc__},
    {"remove",
        clads_b_list_remove,
        METH_VARARGS,
        remove__doc__},
    {"next",
        clads_b_list_next,
        METH_VARARGS,
        next__doc__},
    {NULL, NULL, 0, NULL}
};

/**
 *
 */
static char module__doc__[] = "CLADS list module";

PyMODINIT_FUNC
initlist(void);

#endif
