/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 01:18:35 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 02:24:42 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/maths2_objects.h"

t_vec2	vec2_add(const t_vec2 a, const t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}

t_vec2	vec2_sub(const t_vec2 a, const t_vec2 b)
{
	return ((t_vec2){a.x - b.x, a.y - b.y});
}

t_vec2	vec2_scale(const t_vec2 v, const float scalar)
{
	return ((t_vec2){v.x * scalar, v.y * scalar});
}

float	vec2_cross(const t_vec2 a, const t_vec2 b)
{
	return (a.x * b.y - a.y * b.x);
}

float	vec2_dot(const t_vec2 a, const t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}
