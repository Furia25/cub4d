/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_vec2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 01:48:16 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/10 18:48:48 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_VEC2_H
# define MATHS2_VEC2_H
# include <stdbool.h>
# include "maths2_objects.h"

extern t_vec2		vec2_add(const t_vec2 a, const t_vec2 b);
extern t_vec2		vec2_sub(const t_vec2 a, const t_vec2 b);
extern t_vec2		vec2_scale(const t_vec2 v, const float scalar);
extern float		vec2_cross(const t_vec2 a, const t_vec2 b);
extern float		vec2_dot(const t_vec2 a, const t_vec2 b);
extern float		vec2_length(const t_vec2 v);
extern float		vec2_distance(const t_vec2 a, const t_vec2 b);
extern float		vec2_distance2(const t_vec2 a, const t_vec2 b);
extern t_vec2		vec2_normalize(t_vec2 v);
extern t_quaternion	vec2_to_homogeneous(const t_vec2 v);
extern bool			vec2_equal(t_vec2 a, t_vec2 b);
extern t_vec2		vec2_from_angle(float angle);

#endif