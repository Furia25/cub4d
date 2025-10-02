/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_constructors2.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 01:05:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 03:16:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_CONSTRUCTORS2_H
# define MATHS2_CONSTRUCTORS2_H
# include "maths2_objects.h"

t_bbox		bbox_new(t_vec3 min, t_vec3 max);

t_sphere	sphere_new(t_vec3 pos, float radius);

t_triangle3	triangle3_new(t_vec3 a, t_vec3 b, t_vec3 c);

#endif