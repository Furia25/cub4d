/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_constructors2.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 01:05:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 01:10:35 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_CONSTRUCTORS2_H
# define MATHS2_CONSTRUCTORS2_H
# include "maths2_objects.h"

static inline t_bbox	bbox_new(t_vec3 min, t_vec3 max)
{
	return ((t_bbox){min, max});
}

static inline t_sphere	sphere_new(t_vec3 pos, float radius)
{
	return ((t_sphere){pos, radius});
}

static inline t_triangle3	triangle3_new(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return ((t_triangle3){a, b, c});
}

#endif