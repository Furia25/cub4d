/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:58:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 23:41:49 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgba_to_int(t_png_pixel8 rgba)
{
	return (rgba.a << 24 | rgba.r << 16 | rgba.g << 8 | rgba.b);
}

void	img_draw_pixel(t_png_pixel8 rgba, int x, int y, t_img_data *img)
{
	int	pixel;
	int	color;

	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return ;
	pixel = ((int) y * img->size_line) + ((int) x * 4);
	color = rgba_to_int(rgba);
	if (img->pbits != 32)
		color = mlx_get_color_value(img->connection, color);
	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = (color >> 24);
		img->buffer[pixel + 1] = (color >> 16) & 0xFF;
		img->buffer[pixel + 2] = (color >> 8) & 0xFF;
		img->buffer[pixel + 3] = (color) & 0xFF;
	}
	else
	{
		img->buffer[pixel + 0] = (color) & 0xFF;
		img->buffer[pixel + 1] = (color >> 8) & 0xFF;
		img->buffer[pixel + 2] = (color >> 16) & 0xFF;
		img->buffer[pixel + 3] = (color >> 24);
	}
}

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
