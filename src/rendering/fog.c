/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:31:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 12:37:12 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline uint8_t	get_fog_force(float depth, uint16_t	strength);

void	render_skyfog(t_rgba8 fog_color, t_rgba8 sky_color,
			uint16_t strength, t_render_context *render)
{
	float			depth;
	int				x;
	int				y;

	y = 0;
	while (y < render->render_height)
	{
		x = 0;
		while (x < render->render_width)
		{
			depth = render->z_buffer[x + y * render->render_width];
			if (depth == INFINITY)
				draw_pixel(sky_color, x, y, render->frame);
			else if (strength != 0)
			{
				fog_color.channels.a = get_fog_force(depth, strength);
				draw_pixel(fog_color, x, y, render->frame);
			}
			x++;
		}
		y++;
	}
}

static inline uint8_t	get_fog_force(float depth, uint16_t	strength)
{
	unsigned int	fog;

	fog = depth * strength;
	if (fog > 255)
		fog = 255;
	return (fog);
}
