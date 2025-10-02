/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_rng.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:57:06 by val               #+#    #+#             */
/*   Updated: 2025/10/01 10:27:41 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_RNG_H
# define MATHS2_RNG_H
# include <stdint.h>

typedef struct s_rng_state
{
	uint64_t	state[4];
}	t_rng_state;

uint64_t		rng_splitmix64(uint64_t *seed);
void			rng_init(t_rng_state *rng_state, uint64_t seed);
uint64_t		rng_next(t_rng_state *rng_state);

extern double	rng_rand(t_rng_state *rng_state);
extern int		rng_int_range(t_rng_state *rng_state, int min, int max);
extern float	rng_float_range(t_rng_state *rng_state, float min, float max);
extern double	rng_double_range(t_rng_state *rng_state,
					double min, double max);

#endif