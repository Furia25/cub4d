/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:41:26 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/03 16:29:05 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"
#include "cub3d.h"

static inline void	render_texture(t_vertical_tex *tex_ctx, t_raycast_hit *hit,
				t_raycast_context *ctx, float *zbuf)
{
	int		buffer_idx;
	int		tex_y;
	float	tex_pos;
	float	step;
	int		y;

	step = (float)tex_ctx->texture->header.height / (float)tex_ctx->wall_height;
	tex_pos = tex_ctx->texture->header.height
		- ((tex_ctx->wall_end_actual - tex_ctx->wall_end) * step);
	y = tex_ctx->wall_end + 1;
	while (--y > tex_ctx->wall_start)
	{
		buffer_idx = y * ctx->render_ctx->render_width + ctx->column;
		if (hit->dist < zbuf[buffer_idx])
		{
			tex_y = ((int)tex_pos) % tex_ctx->texture->header.height;
			draw_pixel(
				(t_rgba8)tex_ctx->texture->pixels_8bit[
				tex_y * tex_ctx->texture->header.width + tex_ctx->tex_x],
				ctx->column, y, ctx->render_ctx->frame);
			zbuf[buffer_idx] = hit->dist;
		}
		tex_pos -= step;
	}
}

void	manage_texture(t_raycast_hit *hit, t_raycast_context *ctx,
			t_render_context *render, t_vertical_tex *tex_ctx)
{
	float		*zbuf;
	float		offset;

	zbuf = ctx->render_ctx->z_buffer;
	tex_ctx->texture = render->game->textures[hit->tile_info->texture];
	if (!hit->orientation)
		offset = hit->pos.y - (int)hit->pos.y;
	else
		offset = hit->pos.x - (int)hit->pos.x;
	tex_ctx->tex_x = (int)(offset * tex_ctx->texture->header.width);
	if ((hit->orientation == 0 && hit->o_ray.dir_normal.x > 0)
		|| (hit->orientation == 1 && hit->o_ray.dir_normal.y < 0))
		tex_ctx->tex_x = tex_ctx->texture->header.width - tex_ctx->tex_x - 1;
	render_texture(tex_ctx, hit, ctx, zbuf);
}
