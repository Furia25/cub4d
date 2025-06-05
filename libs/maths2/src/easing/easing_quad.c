/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easing_quad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:36:31 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 22:53:00 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ease_quad_in(float t)
{
	return (t * t);
}

float	ease_quad_out(float t)
{
	return (t * (2 - t));
}

float	ease_quad_inout(float t)
{
	if (t < 0.5f)
	{
		return (2.0f * t * t);
	}
	else
	{
		return (-1.0f + (4.0f - 2.0f * t) * t);
	}
}
