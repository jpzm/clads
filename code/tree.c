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

#include "tree.h"


clads_order_type
clads_tree_default_f_compare(clads_addr_type a,
                             clads_addr_type b)
{
    /*
     * As default threat as integer values.
     */
    if (*CLADS_CAST(a, int *) > *CLADS_CAST(b, int *))
        return more;
    if (*CLADS_CAST(a, int *) < *CLADS_CAST(b, int *))
        return less;
    return equal;
}

clads_tree_node_type *
clads_tree_node_new(clads_void_type)
{
    clads_tree_node_type *n;

    n = CLADS_ALLOC(1, clads_tree_node_type);
    clads_tree_node_initialize(n);

    return n;
}

clads_void_type
clads_tree_node_initialize(clads_tree_node_type *n)
{
    n->parent = NULL;
    n->info = NULL;
    n->lchild = NULL;
    n->rchild = NULL;
}

clads_void_type
clads_tree_node_finalize(clads_tree_node_type *n)
{
    if (n != NULL)
    {
        /*
         * Finalize the children first.
         */
        if (n->lchild != NULL)
            clads_tree_node_finalize(n->lchild);
        if (n->rchild != NULL)
            clads_tree_node_finalize(n->rchild);

        if (n->info != NULL)
            CLADS_FREE((clads_addr_type) n->info);

        n->info = NULL;
    }
#if CLADS_DEBUG
    else
        printf("W. [TREE] Trying to finalize a NULL pointer.\n");
#endif
}

clads_void_type
clads_tree_initialize(clads_tree_type *t)
{
    t->root = NULL;
    t->n_node = 0;
    t->is_set = false;
    t->f_compare = &clads_tree_default_f_compare;
}

clads_void_type
clads_tree_finalize(clads_tree_type *t)
{
    if (t != NULL)
        clads_tree_node_finalize(t->root);
#if CLADS_DEBUG
    else
        printf("W. [TREE] Trying to finalize a NULL tree.\n");
#endif
}

int
clads_tree_copy(const clads_tree_type *ta,
                clads_tree_type *tb)
{
    // TODO
    return 0;
}

clads_tree_node_type *
clads_tree_insert(clads_tree_type *t,
                  clads_tree_node_type *n)
{
    clads_tree_node_type *p = t->root;
    clads_tree_node_type *m = NULL;
    clads_order_type o;

    /*
     * Find `n' position.
     */
    while (p != NULL)
    {
        o = t->f_compare(p->info, n->info);
        m = p;

        if (o == equal && t->is_set == true)
            return NULL;

        if (o == more)
            p = p->lchild;
        else
            p = p->rchild;
    }

    /*
     * Build references.
     */
    n->parent = m;

    if (m == NULL)
        t->root = n;
    else if (o == more)
        m->lchild = n;
    else
        m->rchild = n;

    t->n_node++;
    n->height = 0;
    // TODO update height;

    return n;
}

clads_void_type
clads_tree_transplant(clads_tree_type *t,
                      clads_tree_node_type *u,
                      clads_tree_node_type *v)
{
    if (u->parent == NULL)
        t->root = v;
    else if (u == u->parent->lchild)
        u->parent->lchild = v;
    else
        u->parent->rchild = v;

    if (v != NULL)
        v->parent = u->parent;
}

clads_tree_node_type *
clads_tree_remove(clads_tree_type *t,
                  clads_tree_node_type *n)
{
    clads_tree_node_type *p;

    if (n != NULL)
    {
        if (n->lchild == NULL)
        {
            p = n->rchild;
            clads_tree_transplant(t, n, p);
        }
        else if (n->rchild == NULL)
        {
            p = n->lchild;
            clads_tree_transplant(t, n, p);
        }
        else
        {
            p = clads_tree_minimun_from_node(t, n->rchild);

            if (p->parent != n)
            {
                clads_tree_transplant(t, p, p->rchild);
                p->rchild = n->rchild;
                p->rchild->parent = p;
            }

            clads_tree_transplant(t, n, p);
            p->lchild = n->lchild;
            p->lchild->parent = p;
        }

        t->n_node--;
        // TODO update height;
        n->lchild = NULL;
        n->rchild = NULL;
        clads_tree_node_finalize(n);

        return p;
    }

    return NULL;
}

clads_tree_node_type *
clads_tree_search(clads_tree_type *t,
                  clads_addr_type info)
{
    clads_tree_node_type *p;
    clads_order_type o;

    p = t->root;

    while (p != NULL)
    {
        o = t->f_compare(p->info, info);

        if (o == equal)
            return p;

        if (o == more)
            p = p->lchild;
        else
            p = p->rchild;
    }

    return NULL;
}

clads_tree_node_type *
clads_tree_minimun(clads_tree_type *t)
{
    return clads_tree_minimun_from_node(t, t->root);
}

clads_tree_node_type *
clads_tree_minimun_from_node(clads_tree_type *t,
                             clads_tree_node_type *n)
{
    clads_tree_node_type *m = n;

    while (m->lchild != NULL)
        m = m->lchild;

    return m;
}

clads_tree_node_type *
clads_tree_maximun(clads_tree_type *t)
{
    return clads_tree_maximun_from_node(t, t->root);
}

clads_tree_node_type *
clads_tree_maximun_from_node(clads_tree_type *t,
                             clads_tree_node_type *n)
{
    clads_tree_node_type *m = n;

    while (m->rchild != NULL)
        m = m->rchild;

    return m;
}
