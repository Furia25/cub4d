/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays3_intersects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:23:10 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 19:23:24 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

bool ray3_hit_plane(t_ray3 ray, t_plane3 plane, float *t)
{
	float	denom;
	denom = vec3_dot(plane.normal, ray.dir_normal);
	if (fabs(denom) < _FLOAT_EPSILON)
		return (false);
	*t = -(vec3_dot(plane.normal, ray.origin) + plane.d) / denom;
	return (*t >= 0);
}
