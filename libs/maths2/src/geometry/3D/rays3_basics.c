/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays3_basics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:45:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 19:23:22 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

t_ray3	ray3_from_points(t_vec3 origin, t_vec3 target)
{
	t_ray3	ray;

	ray.origin = origin;
	ray.dir_normal = vec3_normalize(vec3_sub(target, origin));
	return (ray);
}

t_ray3	ray3_from_direction(t_vec3 origin, t_vec3 direction)
{
	t_ray3	ray;

	ray.origin = origin;
	ray.dir_normal = vec3_normalize(direction);
	return (ray);
}

t_vec3	ray3_point_at(t_ray3 ray, float t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.dir_normal, t)));
}
