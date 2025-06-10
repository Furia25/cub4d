/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:47:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/10 18:55:44 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/maths2_vec3.h"
#include "math.h"

t_vec3	vec3_from_angle(float angle)
{
	t_vec3	vec;

	vec.x = cosf(angle);
	vec.y = 0.0f;
	vec.z = sinf(angle);
	return (vec);
}
