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

bool	tilemap_collision(float x, float y, t_vec2 z_range, t_tilemap *tilemap)
{
	t_tile	*tile;

	if (x < 0 || y < 0 || x > tilemap->width || y > tilemap->height)
		return (false);
	tile = tilemap_get_tile(x, (size_t)y, tilemap);
	if (tile->info.solid == SOLID_NONE)
		return (false);
	if (tile->info.solid & SOLID_FLOOR
		&& z_range.x <= tile->floor && z_range.y >= tile->floor)
			return (true);
	if (tile->info.solid & SOLID_CEIL
		&& z_range.x <= tile->ceiling && z_range.y >= tile->ceiling)
			return (true);
	if (tile->info.solid & SOLID_ALL
		&& z_range.x >= tile->floor && z_range.y <= tile->ceiling)
			return (true);
	return (false);
}

bool tilemap_collide_bbox(t_vec3 axis, t_bbox bbox, t_tilemap *map)
{
	bool	collide;
	t_vec2	z;

	z.x = bbox.max.z + axis.z;
	z.y = bbox.min.z + axis.z;
	collide = \
		tilemap_collision(bbox.min.x + axis.x, bbox.min.y + axis.y, z, map)
		|| tilemap_collision(bbox.max.x + axis.x, bbox.min.y + axis.y, z, map)
		|| tilemap_collision(bbox.min.x + axis.x, bbox.max.y + axis.y, z, map)
		|| tilemap_collision(bbox.max.x + axis.x, bbox.max.y + axis.y, z, map);
	return (collide);
}
