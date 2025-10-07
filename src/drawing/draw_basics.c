/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:58:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 23:50:31 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	draw_pixel(t_rgba8 src, unsigned int x, unsigned int y, t_img_data *img)
{
	uint32_t	*pixel;
	uint8_t		*bytes;
	uint8_t		src_alpha;
	uint8_t		inv_alpha;

	pixel = (uint32_t *)(img->buffer + (y * img->size_line) + (x << 2));
	if (src.channels.a == 255)
		*pixel = src.integer;
	else
	{
		bytes = (uint8_t *)pixel;
		src_alpha = src.channels.a;
		inv_alpha = 255 - src_alpha;
		bytes[0] = (src.channels.b * src_alpha + bytes[0] * inv_alpha) >> 8;
		bytes[1] = (src.channels.g * src_alpha + bytes[1] * inv_alpha) >> 8;
		bytes[2] = (src.channels.r * src_alpha + bytes[2] * inv_alpha) >> 8;
		bytes[3] = 255;
	}
}

static inline void	tform_draw(t_rgba8 color, t_draw_transform *tform,
						t_svec2 *pos, t_img_data *img)
{
	t_rgba8		*dest;

	dest = &tform->color;
	if (dest->channels.r != 255)
		color.channels.r = dest->channels.r;
	if (dest->channels.g != 255)
		color.channels.g = dest->channels.g;
	if (dest->channels.b != 255)
		color.channels.b = dest->channels.b;
	draw_pixel(color, tform->x + pos->x, tform->y + pos->y, img);
}

void	draw_spr_sheet(t_draw_transform tform, size_t index,
			t_sprite_sheet *spr, t_img_data *img)
{
	t_vec2	step;
	int		uv;
	t_svec2	pos;
	t_ivec2	uv_start;

	step.x = (float)spr->width / tform.width;
	step.y = (float)spr->height / tform.height;
	pos = (t_svec2){0, 0};
	uv_start.x = (index % spr->spr_per_line) * spr->width;
	uv_start.y = (index / spr->spr_per_line) * spr->height;
	while (pos.y < tform.height)
	{
		pos.x = 0;
		while (pos.x < tform.width)
		{
			uv = (uv_start.x + (int)(pos.x * step.x)) + (uv_start.y
					+ (int)(pos.y * step.y)) * spr->asset->header.width;
			tform_draw((t_rgba8)spr->asset->pixels_8bit[uv], &tform, &pos, img);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_rectangle(t_svec2 pos, t_svec2 size,
			t_rgba8 color, t_img_data *frame)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			draw_pixel(color, pos.x + j, pos.y + i, frame);
			j++;
		}
		i++;
	}
}
