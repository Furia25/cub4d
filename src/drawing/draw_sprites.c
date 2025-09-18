/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:39:43 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/18 18:24:00 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "cub3d_entities.h"

static inline void	eform_draw(t_rgba8 color, t_sprite *e,
						t_svec2 *pos, t_render_context *ctx)
{
	t_rgba8			*dest;
	const t_vec2	uv = {e->transform.x + pos->x, e->transform.y + pos->y};

	if (color.channels.a == 0)
		return ;
	int	bufferidx = uv.y * ctx->render_width + uv.x;
	if (ctx->z_buffer[bufferidx] < e->transform.depth)
		return ;
	ctx->z_buffer[bufferidx] = e->transform.depth;
	dest = &e->transform.color;
	if (dest->channels.r != 255)
		color.channels.r = dest->channels.r;
	if (dest->channels.g != 255)
		color.channels.g = dest->channels.g;
	if (dest->channels.b != 255)
		color.channels.b = dest->channels.b;
	draw_pixel(color, uv.x, uv.y, ctx->frame);
}

static inline void	init_draw(t_transform *tform, t_sprite_sheet *spr,
						t_vec2 *step, t_ivec2 *uv_start)
{
	tform->width *= tform->scale;
	tform->height *= tform->scale;
	*step = (t_vec2){(float)spr->width / tform->width,
		(float)spr->height / tform->height};
	uv_start->x = (tform->index % spr->spr_per_line) * spr->width;
	uv_start->y = (tform->index / spr->spr_per_line) * spr->height;
	if (uv_start->x >= spr->asset->header.width
		|| uv_start->y >= spr->asset->header.height)
	{
		tform->index = 0;
		uv_start->x = 0;
		uv_start->y = 0;
	}
}

static inline bool	init_clipping(t_transform *tform,
						t_svec2 *default_pos, t_render_context *ctx)
{
	*default_pos = (t_svec2){0, 0};
	if (tform->x < 0)
		default_pos->x = -tform->x;
	if (tform->y < 0)
		default_pos->y = -tform->y;
	if (tform->x + tform->width >= ctx->render_width)
		tform->width = ctx->render_width - tform->x;
	if (tform->y + tform->height >= ctx->render_height)
		tform->height = ctx->render_height - tform->y;
	if (tform->width <= 0 || tform->height <= 0)
		return (0);
	return (1);
}

void	draw_sprite(t_transform tform,
			t_sprite *e, t_render_context *ctx)
{
	t_vec2			step;
	t_svec2			default_pos;
	t_ivec2			uv;
	t_svec2			pos;
	t_ivec2			uv_start;

	
	init_draw(&tform, &e->sheet, &step, &uv_start);
	if (!init_clipping(&tform, &default_pos, ctx))
		return ;
	pos = default_pos;
	while (pos.y < tform.height)
	{
		uv.y = (uv_start.y + (int)(pos.y * step.y))
			* e->sheet.asset->header.width;
		pos.x = default_pos.x;
		while (pos.x < tform.width)
		{
			uv.x = uv_start.x + (int)(pos.x * step.x);
			eform_draw((t_rgba8)e->sheet.asset->pixels_8bit[uv.y + uv.x],
				e, &pos, ctx);
			pos.x++;
		}
		pos.y++;
	}
}
