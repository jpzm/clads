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

#ifndef CLADS_STATISTIC_H
#define CLADS_STATISTIC_H

#include <math.h>
#include "clads.h"

/**
 *
 */
clads_bool_type
clads_statistic_uniform_trial(clads_real_type p);

/**
 *
 */
clads_real_type
clads_statistic_mean(clads_real_type *v,
                     clads_real_type *p,
                     clads_size_type n);

/**
 *
 */
clads_real_type
clads_statistic_sample_mean(clads_real_type *v,
                            clads_size_type n);

/**
 *
 */
clads_real_type
clads_statistic_variance(clads_real_type *v,
                         clads_real_type *p,
                         clads_size_type n);

/**
 *
 */
clads_real_type
clads_statistic_sample_variance(clads_real_type *v,
                                clads_size_type n);

#endif
