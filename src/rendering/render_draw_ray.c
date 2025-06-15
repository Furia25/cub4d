/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/16 00:37:23 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	render_draw_ray(t_raycast_hit *actual,
			t_raycast_context *ctx,
			t_render_context *render)
{
	float	corrected_dist;
	int		wall_start;
	int		wall_end;
	float	y_floor;
	float	y_ceiling;
	int		y;

	corrected_dist = actual->dist
		* cosf(actual->original_angle - render->direction);
	y_floor = ((actual->tile->floor - render->eye_height)
		/ corrected_dist) * render->proj_dist_y;
	y_ceiling = ((actual->tile->ceiling - render->eye_height)
		/ corrected_dist) * render->proj_dist_y;
	wall_start = clamp(-y_ceiling + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT - 1);
	wall_end = clamp(-y_floor + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT - 1);
	areas_add(actual->tile->floor, TEXTURE_NAN, ctx->column, (t_span){0, wall_start});
	areas_add(actual->tile->ceiling, TEXTURE_WALL, ctx->column, (t_span){wall_end, WINDOW_HEIGHT});

	y = wall_start;
	while (y < ctx->last_start && y < wall_end)
	{
		draw_pixel(
			actual->orientation ? rgba8(255, 0, 255, 255)
								: rgba8(255, 0, 140, 255),
			ctx->column, y, render->frame);
		y++;
	}

	y = wall_end;
	while (y > wall_start && y > ctx->last_end)
	{
		draw_pixel(
			actual->orientation ? rgba8(255, 0, 255, 255)
								: rgba8(255, 0, 140, 255),
			ctx->column, y, render->frame);
		y--;
	}

	ctx->last_start = min(ctx->last_start, wall_start);
	ctx->last_end = max(ctx->last_end, wall_end);
}

