/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/03 23:21:03 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_rng.h"

void	rng_init(t_rng_state *rng_state, uint64_t seed)
{
	int	index;

	if (seed == 0)
		seed = 0xBEEFCACA54345678ULL;
	index = 0;
	while (index < 4)
	{
		rng_state->state[index] = rng_splitmix64(&seed);
		index++;
	}
}

static inline uint64_t	rotl(const uint64_t x, int k)
{
	return ((x << k) | (x >> (64 - k)));
}

uint64_t	rng_next(t_rng_state *rng_state)
{
	uint64_t	*s;
	uint64_t	result;
	uint64_t	t;

	s = rng_state->state;
	result = rotl(s[1] * 5, 7) * 9;
	t = s[1] << 17;
	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];
	s[2] ^= t;
	s[3] = rotl(s[3], 45);
	return (result);
}
