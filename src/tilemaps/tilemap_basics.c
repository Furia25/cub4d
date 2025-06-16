/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   tilemap_basics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:03:09 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/16 16:35:27 by vdurand          ###   ########.fr       */
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

bool	tilemap_collision(float x, float y, float z, t_tilemap *tilemap)
{
	t_tile	*tile;

	if (!tilemap_is_tile_valid(x, y, tilemap))
		return (true);
	tile = tilemap_get_tile((size_t) x, (size_t)  y, tilemap);
	return (!tile->info.solid || (tile->ceiling < z || tile->floor > z));
}

bool tilemap_collision_bbox(t_vec3 axis, t_bbox bbox, t_tilemap *map)
{
	bool	collide;
	float	z_top;
	float	z_bot;

	z_bot = bbox.min.z + axis.z;
	z_top = bbox.max.z + axis.z;
	collide = \
	tilemap_collision(bbox.min.x + axis.x, bbox.min.y + axis.y, z_bot, map)
	&& tilemap_collision(bbox.max.x + axis.x, bbox.min.y + axis.y, z_bot, map)
	&& tilemap_collision(bbox.min.x + axis.x, bbox.max.y + axis.y, z_bot, map)
	&& tilemap_collision(bbox.max.x + axis.x, bbox.max.y + axis.y, z_bot, map)
	&& tilemap_collision(bbox.min.x + axis.x, bbox.min.y + axis.y, z_top, map)
	&& tilemap_collision(bbox.max.x + axis.x, bbox.min.y + axis.y, z_top, map)
	&& tilemap_collision(bbox.min.x + axis.x, bbox.max.y + axis.y, z_top, map)
	&& tilemap_collision(bbox.max.x + axis.x, bbox.max.y + axis.y, z_top, map);

	return (!collide);
}
