/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/25 13:41:19 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	draw_top_faces(t_raycast_hit *hit, int y,
		t_raycast_context *ctx, t_render_context *r_ctx)
{
	float	real_dist;
	t_rgba8	color;
	int		buffer_idx;

	color = (t_rgba8){255, 0, 255, 255};
	while (y != r_ctx->halfh)
	{
		real_dist = r_ctx->proj_dist_y
			* ((r_ctx->eye_height - hit->tile->ceiling) / (y - r_ctx->halfh))
			* (1.0f / cosf(hit->original_angle - r_ctx->direction));
		hit->pos.x = hit->original_ray.origin.x \
			+ hit->original_ray.dir_normal.x * real_dist;
		hit->pos.y = hit->original_ray.origin.y \
			+ hit->original_ray.dir_normal.y * real_dist;
		if (floor(hit->pos.x) != hit->tile_x \
		|| floor(hit->pos.y) != hit->tile_y)
			break ;
		buffer_idx = y * WINDOW_WIDTH + ctx->column;
		if (real_dist < r_ctx-> z_buffer[buffer_idx])
		{
			draw_pixel(color, ctx->column, y, r_ctx->frame);
			r_ctx->z_buffer[buffer_idx] = real_dist;
		}
		y--;
	}
}

static inline void	draw_bot_faces(t_raycast_hit *hit, int y,
		t_raycast_context *ctx, t_render_context *r_ctx)
{
	float	real_dist;
	t_rgba8	color;
	int		buffer_idx;

	color = (t_rgba8){255, 0, 255, 255};
	y += 1;
	while (y < r_ctx->halfh)
	{
		real_dist = fabsf(r_ctx->proj_dist_y \
		* ((r_ctx->eye_height - hit->tile->floor) / (y - r_ctx->halfh)) \
		* (1.0f / cosf(hit->original_angle - r_ctx->direction)));
		hit->pos.x = hit->original_ray.origin.x \
			+ hit->original_ray.dir_normal.x * real_dist;
		hit->pos.y = hit->original_ray.origin.y \
			+ hit->original_ray.dir_normal.y * real_dist;
		if (floor(hit->pos.x) != hit->tile_x \
		|| floor(hit->pos.y) != hit->tile_y)
			break ;
		buffer_idx = y * WINDOW_WIDTH + ctx->column;
		if (real_dist < r_ctx-> z_buffer[buffer_idx])
		{
			draw_pixel(color, ctx->column, y, r_ctx->frame);
			r_ctx->z_buffer[buffer_idx] = real_dist;
		}
		y++;
	}
}

static void	set_texture_orientation(t_raycast_hit *result)
{
	if (result->orientation == 0 && result->original_ray.dir_normal.x < 0)
		result->tile_info->texture = TEXTURE_WEST;
	else if (result->orientation == 0 && result->original_ray.dir_normal.x > 0)
		result->tile_info->texture = TEXTURE_EAST;
	else if (result->orientation == 1 && result->original_ray.dir_normal.y < 0)
		result->tile_info->texture = TEXTURE_NORTH;
	else if (result->orientation == 1 && result->original_ray.dir_normal.y > 0)
		result->tile_info->texture = TEXTURE_SOUTH;
}

static void	init_texture_ctx(t_texture_context *tex_ctx, t_raycast_hit *hit,
	t_render_context *render, float dist)
{
	float				y_floor;
	float				y_ceiling;

	y_floor = ((hit->tile->floor - render->eye_height) \
		/ dist) * render->proj_dist_y;
	y_ceiling = ((hit->tile->ceiling - render->eye_height) \
		/ dist) * render->proj_dist_y;
	tex_ctx->wall_height = WINDOW_HEIGHT / dist;
	tex_ctx->wall_start = clamp(-y_ceiling + render->halfh, \
		0, WINDOW_HEIGHT - 1);
	tex_ctx->wall_start_actual = -y_ceiling + render->halfh;
	tex_ctx->wall_end = clamp(-y_floor + render->halfh, 0, WINDOW_HEIGHT - 1);
	tex_ctx->wall_end_actual = -y_floor + render->halfh;
}

void	render_draw_ray(t_raycast_hit *hit,
			t_raycast_context *ctx,
			t_render_context *render)
{
	float				corrected_dist;
	t_texture_context	tex_ctx;

	corrected_dist = hit->dist
		* cosf(hit->original_angle - render->direction);
	set_texture_orientation(hit);
	init_texture_ctx(&tex_ctx, hit, render, corrected_dist);
	if (hit->tile->ceiling < render->eye_height)
		draw_top_faces(hit, tex_ctx.wall_start, ctx, render);
	if (hit->tile->floor > render->eye_height)
		draw_bot_faces(hit, tex_ctx.wall_end, ctx, render);
	hit->pos.x = hit->original_ray.origin.x \
		+ hit->original_ray.dir_normal.x * hit->dist;
	hit->pos.y = hit->original_ray.origin.y \
		+ hit->original_ray.dir_normal.y * hit->dist;
	manage_texture(hit, ctx, render, &tex_ctx);
}
