/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_overlapping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:49:06 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 23:40:30 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

bool	bbox_in_bbox(const t_bbox b1, const t_bbox b2)
{
	return (!((b1.max.x <= b2.min.x) || (b1.min.x >= b2.max.x)
		|| (b1.max.y <= b2.min.y) || (b1.min.y >= b2.max.y) 
		|| (b1.max.z <= b2.min.z) || (b1.min.z >= b2.max.z)));
}

bool	sphere_in_sphere(const t_sphere s1, const t_sphere s2)
{
	float	dx;
	float	dy;
	float	dz;
	float	rad_sum;

	dx = s1.pos.x - s2.pos.x;
	dy = s1.pos.y - s2.pos.y;
	dz = s1.pos.z - s2.pos.z;
	rad_sum = s1.radius + s2.radius;
	return ((dx * dx + dy * dy + dz * dz) <= (rad_sum * rad_sum));
}

bool	sphere_in_bbox(const t_sphere sphere, const t_bbox bbox)
{
	t_vec3	closest;
	t_vec3	delta;
	double	dist_sq;

	closest.x = fmax(bbox.min.x, fmin(sphere.pos.x, bbox.max.x));
	closest.y = fmax(bbox.min.y, fmin(sphere.pos.y, bbox.max.y));
	closest.z = fmax(bbox.min.z, fmin(sphere.pos.z, bbox.max.z));
	delta.x = sphere.pos.x - closest.x;
	delta.y = sphere.pos.y - closest.y;
	delta.z = sphere.pos.z - closest.z;
	dist_sq = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
	return (dist_sq <= (sphere.radius * sphere.radius));
}
