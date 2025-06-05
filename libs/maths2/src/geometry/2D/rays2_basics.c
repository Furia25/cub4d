/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:08:53 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 19:21:33 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

t_ray2	ray2_from_angle(t_vec2 origin, float angle)
{
	t_ray2	ray;

	ray.origin = vec2_new(origin.x, origin.y);
	ray.dir_normal = vec2_new(cosf(angle), sinf(angle));
	return (ray);
}

t_ray2	ray2_from_points(t_vec2 origin, t_vec2 target)
{
	t_ray2	ray;

	ray.origin = origin;
	ray.dir_normal = vec2_normalize(vec2_sub(target, origin));
	return (ray);
}

t_vec2	ray2_point_at(t_ray2 ray, float t)
{
	return (vec2_add(ray.origin, vec2_scale(ray.dir_normal, t)));
}
