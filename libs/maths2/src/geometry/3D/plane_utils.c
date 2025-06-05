/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:11:50 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 19:18:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

float	point_plane_signed_distance(t_vec3 point, t_plane3 plane)
{
	return (vec3_dot(plane.normal, point) + plane.d);
}

t_vec3	project_point_on_plane(t_vec3 point, t_plane3 plane)
{
	float	dist;

	dist = point_plane_signed_distance(point, plane);
	return (vec3_sub(point, vec3_scale(plane.normal, dist)));
}
