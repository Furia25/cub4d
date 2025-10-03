/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_horizontals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:43:01 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 16:43:26 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	render_horizontal_texture(t_ivec2 pixel, t_vec2 real_pos,
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

void	draw_top_faces(t_raycast_hit *h, int y,
		t_raycast_context *ctx, t_render_context *r)
{
	float				real_dist;
	int					buffer_idx;
	float				inv_proj_cos;
	float				z;

	inv_proj_cos = (1.0f / cosf(h->base_angle - r->direction)) * r->proj_y;
	z = (h->tile->ceiling - r->player->position.z);
	if (ctx->actual.dist <= 0.01)
		y = r->render_height - 1;
	while (y != r->halfh && y >= 0)
	{
		real_dist = (z / (r->halfh - y)) * inv_proj_cos;
		buffer_idx = y * r->render_width + ctx->column;
		if (real_dist < r->z_buffer[buffer_idx])
		{
			h->pos.x = h->o_ray.origin.x + h->o_ray.dir_normal.x * real_dist;
			h->pos.y = h->o_ray.origin.y + h->o_ray.dir_normal.y * real_dist;
			if (floor(h->pos.x) != h->tile_x || floor(h->pos.y) != h->tile_y)
				break ;
			render_horizontal_texture((t_ivec2){ctx->column, y},
				h->pos, r, h->tile_info->texture_topbot);
			r->z_buffer[buffer_idx] = real_dist;
		}
		y--;
	}
}

void	draw_bot_faces(t_raycast_hit *h, int y,
		t_raycast_context *ctx, t_render_context *r)
{
	float				real_dist;
	int					buffer_idx;
	float				inv_proj_cos;
	float				z;

	inv_proj_cos = 1.0f / cosf(fabsf(h->base_angle - r->direction)) * r->proj_y;
	z = (r->player->position.z - h->tile->floor);
	if (ctx->actual.dist <= 0.01)
		y = 1;
	while (y <= r->halfh)
	{
		real_dist = (z / (y - r->halfh)) * inv_proj_cos;
		buffer_idx = y * r->render_width + ctx->column;
		if (real_dist < r-> z_buffer[buffer_idx])
		{
			h->pos.x = h->o_ray.origin.x + h->o_ray.dir_normal.x * real_dist;
			h->pos.y = h->o_ray.origin.y + h->o_ray.dir_normal.y * real_dist;
			if (floor(h->pos.x) != h->tile_x || floor(h->pos.y) != h->tile_y)
				break ;
			render_horizontal_texture((t_ivec2){ctx->column, y},
				h->pos, r, h->tile_info->texture_topbot);
			r->z_buffer[buffer_idx] = real_dist;
		}
		y++;
	}
}
