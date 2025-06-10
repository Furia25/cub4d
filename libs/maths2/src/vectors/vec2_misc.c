/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:45:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/10 18:55:39 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/maths2_vec2.h"
#include "math.h"

t_vec2	vec2_from_angle(float angle)
{
	t_vec2	vec;

	vec.x = cosf(angle);
	vec.y = sinf(angle);
	return (vec);
}
