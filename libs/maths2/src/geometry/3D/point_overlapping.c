/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_overlapping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:29:49 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 22:54:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

bool	point_in_plane3(t_vec3 point, t_plane3 plane)
{
	return (float_equal(point_plane_signed_distance(point, plane), 0.0f));
}

bool	point_in_bbox(t_vec3 point, t_bbox bbox)
{
	return (point.x >= bbox.min.x
		&& point.x <= bbox.max.x
		&& point.y >= bbox.min.y
		&& point.y <= bbox.max.y
		&& point.z >= bbox.min.z
		&& point.z <= bbox.max.z);
}

bool	point_in_sphere(t_vec3 point, t_sphere sphere)
{
	float	dx;
	float	dy;
	float	dz;

	dx = point.x - sphere.pos.x;
	dy = point.y - sphere.pos.y;
	dz = point.z - sphere.pos.z;
	return ((dx * dx + dy * dy + dz * dz) <= (sphere.radius * sphere.radius));
}

bool	point_in_triangle3(t_vec3 point, t_triangle3 triangle)
{
	t_vec3	normal;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	u;

	normal = vec3_normalize(
			vec3_cross(
				vec3_sub(triangle.b, triangle.a),
				vec3_sub(triangle.c, triangle.a)
				)
			);
	if (fabsf(vec3_dot(vec3_sub(point, triangle.a), normal)) > _FLOAT_EPSILON)
		return (false);
	a = vec3_sub(triangle.a, point);
	b = vec3_sub(triangle.b, point);
	c = vec3_sub(triangle.c, point);
	u = vec3_cross(b, c);
	return (vec3_dot(u, vec3_cross(c, a)) >= 0
		&& vec3_dot(u, vec3_cross(a, b)) >= 0);
}
