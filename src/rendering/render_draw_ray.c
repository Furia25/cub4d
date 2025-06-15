/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/15 20:50:07 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	render_draw_ray(t_raycast_hit *actual, t_raycast_context *ctx, t_render_context *render)
{
	float	corrected_dist;
	int		wall_start;
	int		wall_end;
	int		y;

	corrected_dist = actual->dist * cosf(actual->original_angle - render->direction);
	float	y_floor  = ((actual->tile->floor - render->eye_height)  / corrected_dist ) * render->proj_dist_y;
	float	y_ceiling = ((actual->tile->ceiling - render->eye_height)  / corrected_dist ) * render->proj_dist_y;
	wall_start = clamp(-y_ceiling + WINDOW_HEIGHT/2, 0, WINDOW_HEIGHT);
	wall_end = clamp(-y_floor + WINDOW_HEIGHT/2, 0, WINDOW_HEIGHT);
	if (wall_start >= 0)
		areas_add(actual->tile->ceiling, TEXTURE_NAN, ctx->column, (t_span){0, wall_start});
	if (wall_end < WINDOW_HEIGHT)
		areas_add(actual->tile->floor, TEXTURE_WALL, ctx->column, (t_span){wall_end, WINDOW_HEIGHT});
	y = wall_start;
	while (y < wall_end)
	{
		if (actual->orientation)
			draw_pixel(rgba8(255, 0, 255, 255),
				ctx->column, y, render->frame);
		else
			draw_pixel(rgba8(255, 0, 140, 255),
				ctx->column, y, render->frame);
		y++;
	}
}
