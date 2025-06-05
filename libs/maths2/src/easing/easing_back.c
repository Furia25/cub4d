/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easing_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:01:23 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 22:52:38 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_easing.h"

float	ease_back_in(float t)
{
	return (_C3 * t * t * t - _C1 * t * t);
}

float	ease_back_out(float t)
{
	float	u;

	u = t - 1.0f;
	return (1.0f + _C3 * u * u * u + _C1 * u * u);
}

float	ease_back_inout(float t)
{
	float	u;

	if (t < 0.5f)
	{
		u = 2.0f * t;
		return (0.5f * (u * u * ((_C2 + 1.0f) * u - _C2)));
	}
	else
	{
		u = 2.0f * t - 2.0f;
		return (0.5f * (u * u * ((_C2 + 1.0f) * u + _C2) + 2.0f));
	}
}
