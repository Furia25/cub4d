/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/12 22:55:38 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	render_draw_ray(float ray_angle, int column,
		t_raycast_hit *hit, t_render_context *context)
{
	float	corrected_dist;
	int		wall_start;
	int		wall_end;
	int		y;

	corrected_dist = hit->dist * cosf(ray_angle - context->direction);
	float	y_floor  = ((hit->tile->floor  - context->eye_height)  / corrected_dist ) * context->proj_dist_y;
    float	y_ceiling= ((hit->tile->ceiling - context->eye_height)  / corrected_dist ) * context->proj_dist_y;
	wall_start = clamp( (int)(-y_ceiling + WINDOW_HEIGHT/2), 0, WINDOW_HEIGHT );
	wall_end = clamp( (int)(-y_floor   + WINDOW_HEIGHT/2), 0, WINDOW_HEIGHT );
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y > wall_start && y < wall_end)
			img_draw_pixel(rgba8(220, 0, 255 - 80 * hit->orientation, 255),
				column, y, context->frame);
		y++;
	}
}
