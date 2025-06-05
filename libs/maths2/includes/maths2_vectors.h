/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_vectors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 02:18:35 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 01:14:24 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_VECTORS_H
# define MATHS2_VECTORS_H

# include "private/maths2_vec2.h"
# include "private/maths2_vec3.h"

static inline t_vec2	vec2_new(float x, float y)
{
	return ((t_vec2){x, y});
}

static inline t_vec3	vec3_new(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

static inline t_vec3	vec2_to_vec3(t_vec2 v)
{
	return ((t_vec3){v.x, v.y, 0});
}

static inline t_vec2	vec3_to_vec2(t_vec3 v)
{
	return ((t_vec2){v.x, v.y});
}

#endif