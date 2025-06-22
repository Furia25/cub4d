/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:58:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/23 00:35:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_pixel(t_rgba8 src, unsigned int x, unsigned int y, t_img_data *img) 
{
	uint32_t	*pixel;
	uint8_t		*bytes;
	uint32_t	src_alpha;
	uint32_t	inv_alpha;

	pixel = (uint32_t *)(img->buffer + (y * img->size_line) + (x << 2));
	if (src.pixel.a == 255)
		*pixel = src.value;
	else
	{
		bytes = (uint8_t *)pixel;
		src_alpha = src.pixel.a;
		inv_alpha = 255 - src_alpha;
		bytes[0] = (src.pixel.b * src_alpha + bytes[0] * inv_alpha + 128) >> 8;
		bytes[1] = (src.pixel.g * src_alpha + bytes[1] * inv_alpha + 128) >> 8;
		bytes[2] = (src.pixel.r * src_alpha + bytes[2] * inv_alpha + 128) >> 8;
		bytes[3] = 255;
	}
}
