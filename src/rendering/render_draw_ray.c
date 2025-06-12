/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/13 01:04:15 by vdurand          ###   ########.fr       */
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
	float	y_floor  = ((actual->tile->floor  - render->eye_height)  / corrected_dist ) * render->proj_dist_y;
	float	y_ceiling = ((actual->tile->ceiling - render->eye_height)  / corrected_dist ) * render->proj_dist_y;
	wall_start = clamp( (int)(-y_ceiling + WINDOW_HEIGHT/2), 0, WINDOW_HEIGHT );
	wall_end = clamp( (int)(-y_floor   + WINDOW_HEIGHT/2), 0, WINDOW_HEIGHT );
	/*if (ctx->last_wall_end < wall_start)
	{
		y = ctx->last_wall_end;
		while (y++ < wall_start)
			draw_pixel(rgba8(220, 150, 0, 255), ctx->column, y, render->frame);
	}*/
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y > wall_start && y < wall_end)
			draw_pixel(rgba8(220, 0, 255 - 80 * actual->orientation, 255),
				ctx->column, y, render->frame);
		y++;
	}
	ctx->last_wall_end = wall_end;
}
