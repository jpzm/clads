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

#include "clads.h"


void
clads_initialize()
{
    /*
     * Initialize random number seed.
     */
    FILE *fp = fopen("/dev/urandom", "r");
    clads_uint_type foo;
    struct timeval t;

    if (fp != NULL)
    {
        fread(&foo, sizeof(foo), 1, fp);
        fclose(fp);
    }
    else
    {
        gettimeofday(&t, NULL);
        foo = t.tv_usec;
#if CLADS_DEBUG
        printf("W. [CLADS] Unable to open /dev/urandom.\n");
#endif
    }

    srand(foo);
}

void
clads_shuffle(clads_int_type *list,
              clads_size_type length)
{
    clads_uint_type i, ri, a;

    for (i = 0; i < length; i++)
    {
        ri = (unsigned int) clads_rand(0 , length - 1);

        a = list[i];
        list[i] = list[ri];
        list[ri] = a;
    }
}

clads_real_type
clads_nrand()
{
    return rand() / (RAND_MAX + 1.0);
}

clads_real_type
clads_rand(const clads_real_type min,
           const clads_real_type max)
{
    return (max - min) * clads_nrand() + min;
}

clads_int_type
clads_randint(const clads_int_type min,
              const clads_int_type max)
{
    return (clads_int_type) rint((max - min) * clads_nrand() + min);
}

clads_uint_type
clads_factorial(const clads_uint_type v)
{
    clads_uint_type i, a = 1;

    for (i = 0; i < v; i++)
        a *= v - i;

    return a;
}

clads_uint_type
clads_binomial(const clads_uint_type n,
               const clads_uint_type k)
{
    clads_uint_type i, a = 1, b = 1;

    if (k < 0 || k > n)
        return 0;

    for (i = 0; i < k; i++)
    {
        a *= n - i;
        b *= k - i;
    }

    return (clads_uint_type) a / b;
}

clads_uint_type
clads_nextpow2(clads_uint_type n)
{
    clads_uint_type i = 2;

    if (n == 0)
        return 1;

    while (i < n)
        i *= 2;

    return i;
}
