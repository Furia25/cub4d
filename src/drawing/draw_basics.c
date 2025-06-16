/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:58:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/16 02:54:20 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	set_pixel(t_png_pixel8 src, uint8_t *bytes)
{
	uint32_t	src_alpha;
	uint32_t	inv_alpha;

	src_alpha = src.a;
	inv_alpha = 255 - src_alpha;
	bytes[0] = (src.b * src_alpha + bytes[0] * inv_alpha + 128) >> 8;
	bytes[1] = (src.g * src_alpha + bytes[1] * inv_alpha + 128) >> 8;
	bytes[2] = (src.r * src_alpha + bytes[2] * inv_alpha + 128) >> 8;
	bytes[3] = 255;
}

void	draw_pixel(t_rgba8 src, unsigned int x, unsigned int y, t_img_data *img)
{
	uint32_t	*pixel;

	pixel = (uint32_t *)(img->buffer + (y * img->size_line) + (x << 2));
	if (src.a == 255)
	{
		*pixel = (src.a << 24) | (src.r << 16) | (src.g << 8) | src.b;
		return ;
	}
	set_pixel(src, (uint8_t *)pixel);
}
