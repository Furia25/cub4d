/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:55:31 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/12 19:16:55 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

t_circle	circle_new(t_vec2 pos, float radius)
{
	return ((t_circle){pos, radius});
}

t_rect	rect_new(t_vec2 pos, t_vec2 size)
{
	return ((t_rect){pos, size});
}

t_rect	rect_new_from_bounds(t_vec2 min, t_vec3 max)
{
	return ((t_rect){min, {max.x - min.x, max.y - min.y}});
}

t_triangle	triangle_new(t_vec2 a, t_vec2 b, t_vec2 c)
{
	return ((t_triangle){a, b, c});
}
