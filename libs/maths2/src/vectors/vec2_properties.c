/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:06:36 by val               #+#    #+#             */
/*   Updated: 2025/06/04 02:28:21 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2.h"
#include "private/maths2_vec2.h"

#ifdef _USE_STANDARD_MATH

float	vec2_length(const t_vec2 v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}
#else

float	vec2_length(const t_vec2 v)
{
	return (m2_sqrt(v.x * v.x + v.y * v.y));
}
#endif

float	vec2_distance(const t_vec2 a, const t_vec2 b)
{
	t_vec2	diff;

	diff = vec2_sub(a, b);
	return (vec2_length(diff));
}

float	vec2_distance2(const t_vec2 a, const t_vec2 b)
{
	t_vec2	d;

	d = vec2_sub(a, b);
	return (d.x * d.x + d.y * d.y);
}

t_vec2	vec2_normalize(t_vec2 v)
{
	float	length;

	length = vec2_length(v);
	if (length > 0.0f)
	{
		v.x /= length;
		v.y /= length;
	}
	return (v);
}
