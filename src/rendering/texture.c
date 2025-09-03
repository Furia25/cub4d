/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:41:26 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/02 16:03:42 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"
#include "cub3d.h"

inline static void	render_texture(t_vertical_tex *tex_ctx, t_raycast_hit *hit,
				t_raycast_context *ctx, uint8_t *zbuf)
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
	uint8_t		*zbuf;
	float		offset;

	zbuf = ctx->render_ctx->z_buffer;
	tex_ctx->texture = render->game->textures[hit->tile_info->texture];
	if (!hit->orientation)
		offset = hit->pos.y - (int)hit->pos.y;
	else
		offset = hit->pos.x - (int)hit->pos.x;
	tex_ctx->tex_x = (int)(offset * tex_ctx->texture->header.width);
	if ((hit->orientation == 0 && hit->o_ray.dir_normal.x > 0) || \
		(hit->orientation == 1 && hit->o_ray.dir_normal.y < 0))
		tex_ctx->tex_x = tex_ctx->texture->header.width - tex_ctx->tex_x - 1;
	render_texture(tex_ctx, hit, ctx, zbuf);
}

void	render_horizontal_texture(t_ivec2 pixel, t_vec2 real_pos,
			t_render_context *r_ctx, t_texture_type texture_type)
{
	t_png	*texture;
	t_vec2	off;
	t_ivec2	tex;
	
	texture = r_ctx->textures[texture_type];
	off.x = real_pos.x - floor(real_pos.x);
	off.y = real_pos.y - floor(real_pos.y);
	tex.x = fmodf(off.x * texture->header.width, texture->header.width);
	tex.y = fmodf(off.y * texture->header.height, texture->header.height);
	draw_pixel(
		(t_rgba8)texture->pixels_8bit[tex.y * texture->header.width + tex.x],
		pixel.x, pixel.y, r_ctx->frame);
}
