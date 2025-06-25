/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:58:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/25 01:58:26 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_rgba8 src, unsigned int x, unsigned int y, t_img_data *img)
{
	uint32_t	*pixel;
	uint8_t		*bytes;
	uint8_t		src_alpha;
	uint8_t		inv_alpha;

	pixel = (uint32_t *)(img->buffer + (y * img->size_line) + (x << 2));
	if (src.a == 255)
		*pixel = (src.a << 24) | (src.r << 16) | (src.g << 8) | src.b;
	else
	{
		bytes = (uint8_t *)pixel;
		src_alpha = src.a;
		inv_alpha = 255 - src_alpha;
		bytes[0] = (src.b * src_alpha + bytes[0] * inv_alpha) >> 8;
		bytes[1] = (src.g * src_alpha + bytes[1] * inv_alpha) >> 8;
		bytes[2] = (src.r * src_alpha + bytes[2] * inv_alpha) >> 8;
		bytes[3] = 255;
	}
}

static inline void	transformed_draw(t_rgba8 color, t_draw_transform *tform,
						t_vec2 *pos, t_img_data *img)
{
	t_rgba8		*dest;
	float		amount;

	amount = tform->color_tint;
	dest = &tform->color;
	color.r = dest->r * (1.0f - amount) + color.r * amount;
	color.g = dest->g * (1.0f - amount) + color.g * amount;
	color.b = dest->b * (1.0f - amount) + color.b * amount;
	draw_pixel(color, tform->x + pos->x, tform->y + pos->y, img);
}

void	draw_sprite_sheet(t_draw_transform tform, size_t index,
			t_sprite_sheet *spr, t_img_data *img)
{
	t_vec2	step;
	int		uv;
	t_vec2	pos;
	t_ivec2	uv_start;

	step.x = (float)spr->width / tform.width;
	step.y = (float)spr->height / tform.height;
	pos = (t_vec2){0, 0};
	uv_start.x = (index % spr->sprite_per_line) * spr->width;
	uv_start.y = (index / spr->sprite_per_line) * spr->height;
	while (pos.y < tform.height)
	{
		pos.x = 0;
		while (pos.x < tform.width)
		{
			uv = (uv_start.x + (int)(pos.x * step.x)) + (uv_start.y
					+ (int)(pos.y * step.y)) * spr->asset->header.width;
			transformed_draw(spr->asset->pixels_8bit[uv], &tform, &pos, img);
			pos.x++;
		}
		pos.y++;
	}
}
