/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/20 17:49:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	draw_top_faces(t_raycast_hit *h, int y,
		t_raycast_context *ctx, t_render_context *r_ctx)
{
	float				real_dist;
	int					buffer_idx;
	float				inv_cos;
	float				z;

	inv_cos = (1.0f / cos(h->original_angle - r_ctx->direction))
		* r_ctx->proj_dist_y + 0.006;
	z = (r_ctx->eye_height - h->tile->ceiling);
	if (ctx->actual.dist <= 0.01)
		y = r_ctx->render_height - 1;
	while (y != r_ctx->halfh && y > 0)
	{
		real_dist = (z / (y - r_ctx->halfh)) * inv_cos ;
		h->pos.x = h->o_ray.origin.x + h->o_ray.dir_normal.x * real_dist;
		h->pos.y = h->o_ray.origin.y + h->o_ray.dir_normal.y * real_dist;
		if (floor(h->pos.x) != h->tile_x || floor(h->pos.y) != h->tile_y)
			break ;
		buffer_idx = y * r_ctx->render_width + ctx->column;
		if (real_dist < r_ctx-> z_buffer[buffer_idx])
		{
			render_horizontal_texture((t_ivec2){ctx->column, y},
				h->pos, r_ctx, h->tile_info->texture_topbot);
			r_ctx->z_buffer[buffer_idx] = real_dist;
		}
		y--;
	}
}

static inline void	draw_bot_faces(t_raycast_hit *h, int y,
		t_raycast_context *ctx, t_render_context *r_ctx)
{
	float				real_dist;
	int					buffer_idx;
	float				inv_cos;
	float				z;

	inv_cos = (1.0f / cosf(fabsf(h->original_angle - r_ctx->direction)))
		* r_ctx->proj_dist_y;
	z = (r_ctx->eye_height - h->tile->floor);
	if (ctx->actual.dist <= 0.01)
		y = 1;
	while (y <= r_ctx->halfh)
	{
		real_dist = (z / (y - r_ctx->halfh)) * inv_cos;
		h->pos.x = h->o_ray.origin.x + h->o_ray.dir_normal.x * real_dist;
		h->pos.y = h->o_ray.origin.y + h->o_ray.dir_normal.y * real_dist;
		if (floor(h->pos.x) != h->tile_x || floor(h->pos.y) != h->tile_y)
			break ;
		buffer_idx = y * r_ctx->render_width + ctx->column;
		if (real_dist < r_ctx-> z_buffer[buffer_idx])
		{
			render_horizontal_texture((t_ivec2){ctx->column, y},
				h->pos, r_ctx, h->tile_info->texture_topbot);
			r_ctx->z_buffer[buffer_idx] = real_dist;
		}
		y++;
	}
}

static inline void	set_texture_orientation(t_raycast_hit *result)
{
	if (result->tile_info->type != TILE_WALL)
		return ;
	if (result->orientation == 0 && result->o_ray.dir_normal.x < 0)
		result->tile_info->texture = TEXTURE_WEST;
	else if (result->orientation == 0 && result->o_ray.dir_normal.x > 0)
		result->tile_info->texture = TEXTURE_EAST;
	else if (result->orientation == 1 && result->o_ray.dir_normal.y < 0)
		result->tile_info->texture = TEXTURE_NORTH;
	else if (result->orientation == 1 && result->o_ray.dir_normal.y > 0)
		result->tile_info->texture = TEXTURE_SOUTH;
}

static inline void	init_texture_ctx(t_vertical_tex *tex_ctx, t_raycast_hit *hit,
	t_render_context *render, float dist)
{
	float				dist_inv;
	float				y_floor;
	float				y_ceiling;

	dist_inv = 1 / dist;
	y_floor = ((hit->tile->floor - render->eye_height) \
		* dist_inv) * render->proj_dist_y;
	y_ceiling = ((hit->tile->ceiling - render->eye_height) \
		* dist_inv) * render->proj_dist_y;
	tex_ctx->wall_height = render->render_height * dist_inv;
	tex_ctx->wall_start = clamp(-y_ceiling + render->halfh, \
		0, render->render_height - 1);
	tex_ctx->wall_start_actual = -y_ceiling + render->halfh;
	tex_ctx->wall_end = clamp(-y_floor + render->halfh,
		0, render->render_height - 1);
	tex_ctx->wall_end_actual = -y_floor + render->halfh;
}

void	render_draw_ray(t_raycast_hit *hit, t_raycast_context *ctx,
			t_render_context *render)
{
	float			corrected_dist;
	t_vertical_tex	tex_ctx;

	corrected_dist = hit->dist
		* cosf(hit->original_angle - render->direction);
	set_texture_orientation(hit);
	init_texture_ctx(&tex_ctx, hit, render, corrected_dist);
	if (hit->tile->ceiling < render->eye_height)
		draw_top_faces(hit, tex_ctx.wall_start, ctx, render);
	else if (hit->tile->floor > render->eye_height)
		draw_bot_faces(hit, tex_ctx.wall_end + 1, ctx, render);
	if (hit->draw_walls)
	{
		hit->pos.x = hit->o_ray.origin.x 
			+ hit->o_ray.dir_normal.x * hit->dist;
		hit->pos.y = hit->o_ray.origin.y 
			+ hit->o_ray.dir_normal.y * hit->dist;
		manage_texture(hit, ctx, render, &tex_ctx);
	}
}
