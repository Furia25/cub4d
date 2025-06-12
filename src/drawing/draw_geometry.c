/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_geometry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:07:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/13 00:21:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_rgba8 rgba, t_rect rectangle, t_img_data *img)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < rectangle.size.y)
	{
		x = 0;
		while (x < rectangle.size.x)
		{
			draw_pixel(rgba, rectangle.pos.x + x, rectangle.pos.y + y, img);
			x++;
		}
		y++;
	}
}
