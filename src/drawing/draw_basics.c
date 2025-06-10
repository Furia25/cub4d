/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:58:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/11 01:15:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	set_pixel(t_png_pixel8 src,
		uint8_t *bytes, t_img_data *img)
{
	uint32_t	src_alpha;
	uint32_t	inv_alpha;

	src_alpha = src.a;
	inv_alpha = 255 - src_alpha;
	if (img->endian == 1)
	{
		bytes[0] = 255;
		bytes[1] = (src.r * src_alpha + bytes[1] * inv_alpha + 128) >> 8;
		bytes[2] = (src.g * src_alpha + bytes[2] * inv_alpha + 128) >> 8;
		bytes[3] = (src.b * src_alpha + bytes[3] * inv_alpha + 128) >> 8;
	}
	else
	{
		bytes[0] = (src.b * src_alpha + bytes[0] * inv_alpha + 128) >> 8;
		bytes[1] = (src.g * src_alpha + bytes[1] * inv_alpha + 128) >> 8;
		bytes[2] = (src.r * src_alpha + bytes[2] * inv_alpha + 128) >> 8;
		bytes[3] = 255;
	}
}

void	img_draw_pixel(t_png_pixel8 src, int x, int y, t_img_data *img)
{
	uint32_t	*pixel;

	if ((unsigned)x >= (unsigned)img->width || img->pbits != 32
		|| src.a == 0 || (unsigned)y >= (unsigned)img->height)
		return ;
	pixel = (uint32_t *)(img->buffer + (y * img->size_line + x * 4));
	if (src.a == 255)
	{
		if (img->endian == 1)
			*pixel = 0xFF000000 | (src.r << 16) | (src.g << 8) | src.b;
		else
			*pixel = (src.a << 24) | (src.r << 16) | (src.g << 8) | src.b;
		return ;
	}
	set_pixel(src, (uint8_t *)pixel, img);
}
