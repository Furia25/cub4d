/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/22 18:47:44 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	draw_top_faces(t_raycast_hit *hit, int y,
		t_raycast_context *ctx, t_render_context *r_ctx)
{
	float				real_dist;
	int					buffer_idx;

	if (ctx->actual.dist <= 0.1)
		y = r_ctx->render_height - 1;
	while (y != r_ctx->halfh && y > 0)
	{
		real_dist = r_ctx->proj_dist_y
			* ((r_ctx->eye_height - hit->tile->ceiling) / (y - r_ctx->halfh))
			* (1.0f / cosf(hit->original_angle - r_ctx->direction));
		hit->pos.x = hit->o_ray.origin.x + hit->o_ray.dir_normal.x * real_dist;
		hit->pos.y = hit->o_ray.origin.y + hit->o_ray.dir_normal.y * real_dist;
		if (floor(hit->pos.x) != hit->tile_x
			|| floor(hit->pos.y) != hit->tile_y)
			break ;
		buffer_idx = y * WINDOW_WIDTH + ctx->column;
		if (real_dist < r_ctx-> z_buffer[buffer_idx])
		{
			render_horizontal_texture((t_ivec2){ctx->column, y},
				hit->pos, r_ctx, hit->tile_info->texture_topbot);
			r_ctx->z_buffer[buffer_idx] = real_dist;
		}
		y--;
	}
}

static inline void	draw_bot_faces(t_raycast_hit *hit, int y,
		t_raycast_context *ctx, t_render_context *r_ctx)
{
	float				real_dist;
	int					buffer_idx;

	y += 1;
	while (y < r_ctx->halfh)
	{
		real_dist = fabsf(r_ctx->proj_dist_y \
		* ((r_ctx->eye_height - hit->tile->floor) / (y - r_ctx->halfh)) \
		* (1.0f / cosf(hit->original_angle - r_ctx->direction)));
		hit->pos.x = hit->o_ray.origin.x + hit->o_ray.dir_normal.x * real_dist;
		hit->pos.y = hit->o_ray.origin.y + hit->o_ray.dir_normal.y * real_dist;
		if (floor(hit->pos.x) != hit->tile_x
			|| floor(hit->pos.y) != hit->tile_y)
			break ;
		buffer_idx = y * WINDOW_WIDTH + ctx->column;
		if (real_dist < r_ctx-> z_buffer[buffer_idx])
		{
			render_horizontal_texture((t_ivec2){ctx->column, y},
				hit->pos, r_ctx, hit->tile_info->texture_topbot);
			r_ctx->z_buffer[buffer_idx] = real_dist;
		}
		y++;
	}
}

static void	set_texture_orientation(t_raycast_hit *result)
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

static void	init_texture_ctx(t_vertical_tex *tex_ctx, t_raycast_hit *hit,
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
	tex_ctx->wall_height = WINDOW_HEIGHT * dist_inv;
	tex_ctx->wall_start = clamp(-y_ceiling + render->halfh, \
		0, WINDOW_HEIGHT - 1);
	tex_ctx->wall_start_actual = -y_ceiling + render->halfh;
	tex_ctx->wall_end = clamp(-y_floor + render->halfh, 0, WINDOW_HEIGHT - 1);
	tex_ctx->wall_end_actual = -y_floor + render->halfh;
}

void	render_draw_ray(
			t_raycast_hit *hit,
			t_raycast_context *ctx,
			t_render_context *render,
			char is_wall
		)
{
	float				corrected_dist;
	t_vertical_tex	tex_ctx;

	(void)(is_wall);
	corrected_dist = hit->dist
		* cosf(hit->original_angle - render->direction);
	set_texture_orientation(hit);
	init_texture_ctx(&tex_ctx, hit, render, corrected_dist);
	if (hit->tile->ceiling < render->eye_height)
		draw_top_faces(hit, tex_ctx.wall_start, ctx, render);
	if (hit->tile->floor > render->eye_height)
		draw_bot_faces(hit, tex_ctx.wall_end, ctx, render);
	hit->pos.x = hit->o_ray.origin.x \
		+ hit->o_ray.dir_normal.x * hit->dist;
	hit->pos.y = hit->o_ray.origin.y \
		+ hit->o_ray.dir_normal.y * hit->dist;
	manage_texture(hit, ctx, render, &tex_ctx);
}
