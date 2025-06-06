/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:25:18 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/06 21:23:08 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static void	raycast_launch(t_ivec2 actual_tile, t_vec2 delta_dist,
				t_vec2 step_dist, t_raycast_hit *result);
static bool	check_tile(int tile_x, int tile_y, t_raycast_hit *result);
static void	set_dda_ray_dist(t_ray2 ray, t_ivec2 actual_tile,
			t_ivec2 step, t_raycast_hit *result);

t_raycast_hit	raycast_tilemap(t_ray2 *ray, t_tilemap *tilemap)
{
	t_raycast_hit	result;
	t_ivec2			actual_tile;
	t_vec2			delta_dist;
	t_vec2			step_dist;

	result.original_ray = *ray;
	result.hitted = false;
	result.tile_info = g_base_tile_info[TILE_EMPTY];
	result.tilemap = tilemap;
	if (ray->dir_normal.x == 0 || ray->dir_normal.y == 0)
		return (result);
	actual_tile.x = (int)ray->origin.x;
	actual_tile.y = (int)ray->origin.y;
	delta_dist.x = fabs(1 / ray->dir_normal.x);
	delta_dist.y = fabs(1 / ray->dir_normal.y);
	if (ray->dir_normal.x < 0)
		step_dist.x = (ray->origin.x - actual_tile.x) * delta_dist.x;
	else
		step_dist.x = (actual_tile.x + 1.0 - ray->origin.x) *  delta_dist.x;
	if (ray->dir_normal.y < 0)
		step_dist.y = (ray->origin.y - actual_tile.y) * delta_dist.y;
	else
		step_dist.y = (actual_tile.y + 1.0 - ray->origin.y) *  delta_dist.y;
	raycast_launch(actual_tile, delta_dist, step_dist, &result);
	return (result);
}

static void	raycast_launch(t_ivec2 actual_tile, t_vec2 delta_dist,
				t_vec2 step_dist, t_raycast_hit *result)
{
	t_ivec2	step;

	step.x = sign(result->original_ray.dir_normal.x);
	step.y = sign(result->original_ray.dir_normal.y);
	while (1)
	{
		if (step_dist.x < step_dist.y)
		{
			step_dist.x += delta_dist.x;
			actual_tile.x += step.x;
			result->orientation = 0;
		}
		else
		{
			step_dist.y += delta_dist.y;
			actual_tile.y += step.y;
			result->orientation = 1;
		}
		if (check_tile(actual_tile.x, actual_tile.y, result))
		{
			set_dda_ray_dist(result->original_ray, actual_tile, step, result);
			return ;
		}
	}
}

static bool	check_tile(int tile_x, int tile_y, t_raycast_hit *result)
{
	t_tile	*tile;

	if (!tilemap_is_tile_valid(tile_x, tile_y, &result->tilemap))
		return (false);
	tile = tilemap_get_tile(tile_x, tile_y, &result->tilemap);
	result->tile_info = tile->info;
	result->tile_type = tile->type;
	if (tile->info.blocking)
	{
		result->hitted = true;
		return (false);
	}
	return (true);
}

static void	set_dda_ray_dist(t_ray2 ray, t_ivec2 actual_tile,
			t_ivec2 step, t_raycast_hit *result)
{
	if (result->orientation == 0)
		result->dist = (actual_tile.x - ray.origin.x + (1 - step.x) / 2) / ray.dir_normal.x;
	else
		result->dist = (actual_tile.y - ray.origin.y + (1 - step.y) / 2) / ray.dir_normal.y;
}
