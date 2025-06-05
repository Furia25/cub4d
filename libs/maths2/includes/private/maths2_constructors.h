/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_constructors.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 01:05:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 01:09:41 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_CONSTRUCTORS_H
# define MATHS2_CONSTRUCTORS_H
# include "maths2_objects.h"

static inline t_circle	circle_new(t_vec2 pos, float radius)
{
	return ((t_circle){pos, radius});
}

static inline t_rect	rect_new(t_vec2 pos, t_vec2 size)
{
	return ((t_rect){pos, size});
}

static inline t_rect	rect_new_from_bounds(t_vec2 min, t_vec3 max)
{
	return ((t_rect){min, {max.x - min.x, max.y - min.y}});
}

static inline t_triangle	triangle_new(t_vec2 a, t_vec2 b, t_vec2 c)
{
	return ((t_triangle){a, b, c});
}

#endif