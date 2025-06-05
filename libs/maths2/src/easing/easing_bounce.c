/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easing_bounce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:09:05 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 22:52:41 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline float	bounce_out(float t)
{
	float	u;

	if (t < 1.0f / 2.75f)
	{
		return (7.5625f * t * t);
	}
	else if (t < 2.0f / 2.75f)
	{
		u = t - (1.5f / 2.75f);
		return (7.5625f * u * u + 0.75f);
	}
	else if (t < 2.5f / 2.75f)
	{
		u = t - (2.25f / 2.75f);
		return (7.5625f * u * u + 0.9375f);
	}
	else
	{
		u = t - (2.625f / 2.75f);
		return (7.5625f * u * u + 0.984375f);
	}
}

float	ease_bounce_in(float t)
{
	return (1.0f - bounce_out(1.0f - t));
}

float	ease_bounce_out(float t)
{
	return (bounce_out(t));
}

float	ease_bounce_inout(float t)
{
	if (t < 0.5)
	{
		return (0.5f * (1.0f - bounce_out(1.0f - 2.0f * t)));
	}
	else
	{
		return (0.5f * (1.0f + bounce_out(2.0f * t - 1.0f)));
	}
}
