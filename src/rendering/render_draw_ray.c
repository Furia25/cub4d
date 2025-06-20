/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/20 15:43:12 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	draw_wall(t_raycast_hit *hit, int wall_start,
			int wall_end, t_raycast_context *ctx)
{
	register int	y;
	t_rgba8			color;

	y = wall_start;
	color = rgba8(0 + 200 * hit->orientation, 255, 255, 255);
	while (y < ctx->last_start && y < wall_end)
	{
		draw_pixel(color, ctx->column, y, ctx->render_ctx->frame);
		y++;
	}
	y = wall_end;
	while (y > wall_start && y > ctx->last_end)
	{
		draw_pixel(color, ctx->column, y, ctx->render_ctx->frame);
		y--;
	}
}

void	render_draw_ray(t_raycast_hit *hit,
			t_raycast_context *ctx,
			t_render_context *render)
{
	float	corrected_dist;
	int		wall_start;
	int		wall_end;
	float	y_floor;
	float	y_ceiling;

	corrected_dist = hit->dist
		* cosf(hit->original_angle - render->direction);
	y_floor = ((hit->tile->floor - render->eye_height)
		/ corrected_dist) * render->proj_dist_y;
	y_ceiling = ((hit->tile->ceiling - render->eye_height)
		/ corrected_dist) * render->proj_dist_y;
	wall_start = clamp(-y_ceiling + render->halfh, 0, WINDOW_HEIGHT - 1);
	wall_end = clamp(-y_floor + render->halfh, 0, WINDOW_HEIGHT - 1);
	draw_wall(hit, wall_start, wall_end, ctx);
	ctx->last_start = min(ctx->last_start, wall_start);
	ctx->last_end = max(ctx->last_end, wall_end);
}

/*
static void	render_ray(float ray_angle, int column,
	t_raycast_hit *result, t_render_context *ctx)
{
	float				corrected_dist;
	int					y;
	t_texture_context	tex_ctx;

	corrected_dist = result->dist * cosf(ray_angle - ctx->direction);
	init_texture_ctx(&tex_ctx, corrected_dist, column);
	set_texture_orientation(result);
	result->pos.x = result->original_ray.origin.x \
				+ result->original_ray.dir_normal.x * result->dist;
	result->pos.y = result->original_ray.origin.y \
				+ result->original_ray.dir_normal.y * result->dist;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < tex_ctx.wall_start)
			img_draw_pixel(ctx->game->c_color, column, y, ctx->frame);
		else if (y > tex_ctx.wall_end)
			img_draw_pixel(ctx->game->f_color, column, y, ctx->frame);
		else
			manage_texture(result, ctx, &tex_ctx, &y);
		y++;
	}
}
*/