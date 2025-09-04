/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:39:43 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/04 23:21:49 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	eform_draw(t_rgba8 color, t_entity_transform *tform,
						t_svec2 *pos, t_img_data *img)
{
	t_rgba8		*dest;

	if (color.channels.a == 0)
		return ;
	dest = &tform->color;
	if (dest->channels.r != 255)
		color.channels.r = dest->channels.r;
	if (dest->channels.g != 255)
		color.channels.g = dest->channels.g;
	if (dest->channels.b != 255)
		color.channels.b = dest->channels.b;
	draw_pixel(color, tform->x + pos->x, tform->y + pos->y, img);
}

void	draw_sprite_entity(t_entity_transform tform,
			t_sprite_sheet *spr, t_render_context *ctx)
{
	t_vec2			step;
	t_svec2			default_pos = (t_svec2){0, 0};
	t_ivec2			uv;
	t_svec2			pos;
	t_ivec2			uv_start;

	tform.width *= tform.scale;
	tform.height *= tform.scale;
	step = (t_vec2){(float)spr->width / tform.width, (float)spr->height / tform.height};
	uv_start.x = (tform.index % spr->spr_per_line) * spr->width;
	uv_start.y = (tform.index / spr->spr_per_line) * spr->height;
	pos = default_pos;
	while (pos.y < tform.height)
	{
		uv.y = (uv_start.y + (int)(pos.y * step.y)) * spr->asset->header.width;
		pos.x = default_pos.x;
		while (pos.x < tform.width)
		{
			uv.x = uv_start.x + (int)(pos.x * step.x);
			eform_draw((t_rgba8)spr->asset->pixels_8bit[uv.y + uv.x],
				&tform, &pos, ctx->frame);
			pos.x++;
		}
		pos.y++;
	}
}
