/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 02:28:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 22:52:28 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2.h"
#include "private/maths2_objects.h"

t_quaternion	vec2_to_homogeneous(const t_vec2 v)
{
	return ((t_quaternion){v.x, v.y, 0.0f, 1.0f});
}

t_quaternion	vec3_to_homogeneous(const t_vec3 v)
{
	return ((t_quaternion){v.x, v.y, v.z, 1.0f});
}

bool	vec2_equal(t_vec2 a, t_vec2 b)
{
	return (fabsf(a.x - b.x) < _FLOAT_EPSILON
		&& fabsf(a.y - b.y) < _FLOAT_EPSILON);
}

bool	vec3_equal(t_vec3 a, t_vec3 b)
{
	return (fabsf(a.x - b.x) < _FLOAT_EPSILON
		&& fabsf(a.y - b.y) < _FLOAT_EPSILON
		&& fabsf(a.z - b.z) < _FLOAT_EPSILON);
}
