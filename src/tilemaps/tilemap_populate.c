/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_populate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:20:32 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/26 17:20:51 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "tilemap.h"

t_tilemap	*tilemap_from_tab(char **tab, size_t width,
				size_t height, size_t tile_size)
{
	t_tilemap		*result;
	size_t			y;

	result = tilemap_new(width, height, tile_size);
	if (!result)
		return (NULL);
	y = 0;
	while (y < height)
	{
		tilemap_tiles_from_str(tab[y], y, result);
		y++;
	}
	return (result);
}

void	tilemap_tiles_from_str(char *str, size_t line, t_tilemap *map)
{
	size_t		index;
	t_tile_type	type;
	t_tile		*tile;

	if (!str || line >= map->height)
		return ;
	index = 0;
	while (index < map->width && str[index])
	{
		type = tiletype_from_symbol(str[index]);
		tile = &map->tiles[line][index];
		tile->info = g_base_tile_info[type];
		tile->type = type;
		tile->floor = 0.f;
		tile->ceiling = 0.25;
		if (tile->info.wall)
			tile->ceiling = 2 + rand() % 4 * 0.5f + tile->floor;
		tile->floor += tile->info.floor_offset;
		tile->ceiling += tile->info.ceil_offset;
		index++;
	}
}

t_tile_type	tiletype_from_symbol(char symbol)
{
	if (symbol == '1')
		return (TILE_WALL);
	if (symbol == '2')
		return (TILE_WATER);
	return (TILE_EMPTY);
}
