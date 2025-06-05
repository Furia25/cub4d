/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:05:50 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 02:04:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_rng.h"

double	rng_rand(t_rng_state *rng_state)
{
	return ((rng_next(rng_state) >> 11) * (1.0 / (1ULL << 53)));
}

int	rng_int_range(t_rng_state *rng_state, int min, int max)
{
	return (min + (int)(rng_next(rng_state) % (uint64_t)(max - min + 1)));
}

float	rng_float_range(t_rng_state *rng_state, float min, float max)
{
	return (min + (float)rng_rand(rng_state) * (max - min));
}

double	rng_double_range(t_rng_state *rng_state,
				double min, double max)
{
	return (min + rng_rand(rng_state) * (max - min));
}
