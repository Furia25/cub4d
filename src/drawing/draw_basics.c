/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:58:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/23 23:00:08 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_rgba8 src, unsigned int x, unsigned int y, t_img_data *img)
{
	uint32_t	*pixel;
	uint8_t		*bytes;
	uint32_t	src_alpha;
	uint32_t	inv_alpha;

	pixel = (uint32_t *)(img->buffer + (y * img->size_line) + (x << 2));
	if (src.a == 255)
		*pixel = (src.a << 24) | (src.r << 16) | (src.g << 8) | src.b;
	else
	{
		bytes = (uint8_t *)pixel;
		src_alpha = src.a;
		inv_alpha = 255 - src_alpha;
		bytes[0] = (src.b * src_alpha + bytes[0] * inv_alpha + 128) >> 8;
		bytes[1] = (src.g * src_alpha + bytes[1] * inv_alpha + 128) >> 8;
		bytes[2] = (src.r * src_alpha + bytes[2] * inv_alpha + 128) >> 8;
		bytes[3] = 255;
	}
}

void	draw_sprite_sheet(t_transform tform, size_t index,
			t_sprite_sheet *sprite, t_img_data *img)
{
	t_vec2	step;
	t_ivec2	uv;
	t_vec2	pos;
	size_t	uv_start_x;
	size_t	uv_start_y;

	step.x = (float)sprite->width / tform.width;
	step.y = (float)sprite->height / tform.height;
	pos = (t_vec2){0, 0};
	uv_start_x = (index % sprite->sprite_per_line) * sprite->width;
	uv_start_y = (index / sprite->sprite_per_line) * sprite->height;
	while (pos.y < tform.height)
	{
		pos.x = 0;
		while (pos.x < tform.width)
		{
			uv.x = uv_start_x + pos.x * step.x;
			uv.y = uv_start_y + pos.y * step.y;
			draw_pixel(
				sprite->asset->pixels_8bit[uv.x + uv.y * sprite->asset->header.width],
				tform.x + pos.x, tform.y + pos.y, img);
			pos.x += 1;
		}
		pos.y += 1;
	}
}
