/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_basics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:03:09 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/10 19:49:16 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "tilemap.h"

bool	tilemap_is_tile_valid(size_t x, size_t y, t_tilemap *map)
{
	return (x < map->width && y < map->height);
}

t_tile	*tilemap_get_tile(size_t x, size_t y, t_tilemap *map)
{
	return (&map->tiles[y][x]);
}

bool	tilemap_collision(float x, float y, t_tilemap *tilemap)
{
	t_tile	*tile;

	if (!tilemap_is_tile_valid(x, y, tilemap))
		return (true);
	tile = tilemap_get_tile((size_t) x, (size_t)  y, tilemap);
	return (!tile->info.solid);
}

bool	tilemap_collision_bbox(float x_axis, float y_axis,
			t_bbox bbox, t_tilemap *tilemap)
{
	bool	collide;

	collide = tilemap_collision(bbox.min.x + x_axis, bbox.min.y + y_axis, tilemap)
		&& tilemap_collision(bbox.max.x + x_axis, bbox.min.y + y_axis, tilemap)
		&& tilemap_collision(bbox.min.x + x_axis, bbox.max.y + y_axis, tilemap)
		&& tilemap_collision(bbox.max.x + x_axis, bbox.max.y + y_axis, tilemap);
	return (!collide);
}
