/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easing_cubic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:52:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 22:53:03 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ease_cubic_in(float t)
{
	return (t * t * t);
}

float	ease_cubic_out(float t)
{
	float	u;

	u = t - 1.0f;
	return (u * u * u + 1.0f);
}

float	ease_cubic_inout(float t)
{
	float	u;

	if (t < 0.5f)
	{
		return (4.0f * t * t * t);
	}
	else
	{
		u = (2.0f * t) - 2.0f;
		return (0.5f * (u * u * u + 2.0f));
	}
}
