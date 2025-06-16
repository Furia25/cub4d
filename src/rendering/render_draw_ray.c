/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/16 14:45:22 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	draw_wall(t_raycast_hit *hit, int wall_start,
			int wall_end, t_raycast_context *ctx)
{
	int	y;

	y = wall_start;
	while (y < ctx->last_start && y < wall_end)
	{
		draw_pixel(
			hit->orientation ? rgba8(0, 0, 255, 255) : rgba8(0, 255, 255, 255), ctx->column, y, ctx->render_ctx->frame);
		y++;
	}
	y = wall_end;
	while (y > wall_start && y > ctx->last_end)
	{
		draw_pixel(
			hit->orientation ? rgba8(0, 0, 255, 255) : rgba8(0, 255, 255, 255), ctx->column, y, ctx->render_ctx->frame);
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
	wall_start = clamp(-y_ceiling + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT - 1);
	wall_end = clamp(-y_floor + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT - 1);
	draw_wall(hit, wall_start, wall_end, ctx);
	ctx->last_start = min(ctx->last_start, wall_start);
	ctx->last_end = max(ctx->last_end, wall_end);
}

