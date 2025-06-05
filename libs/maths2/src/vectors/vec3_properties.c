/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:06:36 by val               #+#    #+#             */
/*   Updated: 2025/06/04 02:29:12 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2.h"
#include "private/maths2_vec3.h"

#ifdef _USE_STANDARD_MATH

float	vec3_length(const t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
#else

float	vec3_length(const t_vec3 v)
{
	return (m2_sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
#endif

float	vec3_distance(const t_vec3 a, const t_vec3 b)
{
	t_vec3	diff;

	diff = vec3_sub(a, b);
	return (vec3_length(diff));
}

float	vec3_distance2(const t_vec3 a, const t_vec3 b)
{
	t_vec3	d;

	d = vec3_sub(a, b);
	return (d.x * d.x + d.y * d.y + d.z * d.z);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	length;

	length = vec3_length(v);
	if (length > 0.0f)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return (v);
}
