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

#include "list.h"


void
clads_list_initialize(clads_list_type *l)
{
    l->info = NULL;
    l->next = NULL;
}

void
clads_list_finalize(clads_list_type *l)
{
    clads_list_type *m, *p = l;

    while (p)
    {
        m = p->next;
        free((void *) p->info);
        free((void *) p);
        p = m;
    }
}

clads_size_type
clads_list_size(clads_list_type *l)
{
    clads_list_type *p = l;
    clads_size_type s = 0;

    while (p)
    {
        s++;
        p = p->next;
    }

    return s;
}

clads_bool_type
clads_list_insert(clads_list_type **l, void *i)
{
    clads_list_type *m;

    if (i)
    {
        if ((m = malloc(sizeof(clads_list_type))))
        {
            m->info = i;
            m->next = *l;
            *l = m;

            return true;
        }
    }

    return false;
}

clads_bool_type
clads_list_remove(clads_list_type **l, void *i)
{
    clads_list_type *m = NULL, *p = *l;

    while (p)
    {
        if (p->info == i)
        {
            if (m)
                m->next = p->next;
            else
                *l = p->next;

            free(p);

            return true;
        }

        m = p;
        p = p->next;
    }

    return false;
}
