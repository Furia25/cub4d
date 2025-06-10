/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_geometry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:07:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/11 00:07:59 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_draw_rect(t_png_pixel8 rgba, t_rect rectangle, t_img_data *img)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < rectangle.size.y)
	{
		x = 0;
		while (x < rectangle.size.x)
		{
			img_draw_pixel(rgba, rectangle.pos.x + x, rectangle.pos.y + y, img);
			x++;
		}
		y++;
	}
}
