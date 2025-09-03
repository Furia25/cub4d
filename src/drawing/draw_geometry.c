/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_geometry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:07:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/03 19:42:05 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_rgba8 rgba, t_rect rectangle, t_img_data *img)
{
	size_t	x;
	size_t	y;
	t_vec2	pos;

	y = 0;
	while (y < rectangle.size.y)
	{
		x = 0;
		while (x < rectangle.size.x)
		{
			pos.x = rectangle.pos.x + x;
			pos.y = rectangle.pos.y + y;
			if (pos.x >= 0 && pos.x <= img->width && pos.y >= 0 && pos.y <= img->height)
				draw_pixel(rgba, pos.x, pos.y, img);
			x++;
		}
		y++;
	}
}
