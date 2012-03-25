/**
 * Copyright (C) 2012 Joao Paulo de Souza Medeiros
 *
 * Author(s): João Paulo de Souza Medeiros <jpsm1985@gmail.com>
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

#include "statistic.h"


clads_bool_type
clads_statistic_uniform_trial(clads_real_type p)
{
    if (p != 0.0 && clads_nrand() <= p)
        return clads_true;

    return clads_false;
}

clads_real_type
clads_statistic_mean(clads_real_type *v,
                     clads_real_type *p,
                     clads_size_type n)
{
    clads_real_type sum = 0;
    clads_size_type i;

    for (i = 0; i < n; i++)
        sum += v[i] * p[i];

    return sum;
}

clads_real_type
clads_statistic_sample_mean(clads_real_type *v,
                            clads_size_type n)
{
    clads_real_type sum = 0;
    clads_size_type i;

    for (i = 0; i < n; i++)
        sum += v[i];

    return sum / n;
}

clads_real_type
clads_statistic_variance(clads_real_type *v,
                         clads_real_type *p,
                         clads_size_type n)
{
    clads_real_type mean, sum = 0;
    clads_size_type i;

    mean = clads_statistic_mean(v, p, n);

    for (i = 0; i < n; i++)
        sum += p[i] * (v[i] - mean) * (v[i] - mean);

    return sum;
}

clads_real_type
clads_statistic_sample_variance(clads_real_type *v,
                                clads_size_type n)
{
    clads_real_type mean, sum = 0;
    clads_size_type i;

    mean = clads_statistic_sample_mean(v, n);

    for (i = 0; i < n; i++)
        sum += (v[i] - mean) * (v[i] - mean);

    return sum / (n - 1);
}
