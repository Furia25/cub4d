/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:18:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/20 16:06:07 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

/*static void	init_texture_ctx(t_texture_context *tex_ctx, float dist, int column)
{
	tex_ctx->wall_height = WINDOW_HEIGHT / dist;
	tex_ctx->wall_start = clamp(-tex_ctx->wall_height \
		/ 2 + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT);
	tex_ctx->wall_end = clamp(tex_ctx->wall_height \
		/ 2 + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT);
	tex_ctx->column = column;
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
}*/

static inline void	draw_wall(t_raycast_hit *hit, int wall_start,
			int wall_end, t_raycast_context *ctx)
{
	int	y;
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
	/*init_texture_ctx(&tex_ctx, corrected_dist, ctx->column);
	set_texture_orientation(hit);*/
	y_floor = ((hit->tile->floor - render->eye_height)
		/ corrected_dist) * render->proj_dist_y;
	y_ceiling = ((hit->tile->ceiling - render->eye_height)
		/ corrected_dist) * render->proj_dist_y;
	hit->pos.x = hit->original_ray.origin.x \
		+ hit->original_ray.dir_normal.x * hit->dist;
	hit->pos.y = hit->original_ray.origin.y \
		+ hit->original_ray.dir_normal.y * hit->dist;
	wall_start = clamp(-y_ceiling + render->halfh, 0, WINDOW_HEIGHT - 1);
	wall_end = clamp(-y_floor + render->halfh, 0, WINDOW_HEIGHT - 1);
	draw_wall(hit, wall_start, wall_end, ctx);
	ctx->last_start = min(ctx->last_start, wall_start);
	ctx->last_end = max(ctx->last_end, wall_end);
}
