/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_constructors.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 01:05:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 03:14:21 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_CONSTRUCTORS_H
# define MATHS2_CONSTRUCTORS_H
# include "maths2_objects.h"

t_circle	circle_new(t_vec2 pos, float radius);

t_rect		rect_new(t_vec2 pos, t_vec2 size);

t_rect		rect_new_from_bounds(t_vec2 min, t_vec3 max);

t_triangle	triangle_new(t_vec2 a, t_vec2 b, t_vec2 c);

#endif