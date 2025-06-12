/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:56:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/12 19:17:07 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

t_bbox	bbox_new(t_vec3 min, t_vec3 max)
{
	return ((t_bbox){min, max});
}

t_sphere	sphere_new(t_vec3 pos, float radius)
{
	return ((t_sphere){pos, radius});
}

t_triangle3	triangle3_new(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return ((t_triangle3){a, b, c});
}
