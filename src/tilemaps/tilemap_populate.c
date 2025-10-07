/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_populate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:20:32 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 18:11:07 by vdurand          ###   ########.fr       */
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

void	print_helper(size_t x, size_t y)
{
	static bool		last = false;
	static t_svec2	last_pos = {};

	printf(ANSI_DIM "HELPER : %ldx, %ldy\n" ANSI_RESET, x, y);
	if (last)
	{
		printf(ANSI_DIM "HELPER RECT : %ldx, %ldy\n" ANSI_RESET,
			x - last_pos.x, y - last_pos.y);
		last = false;
		return ;
	}
	last_pos.x = x;
	last_pos.y = y;
	last = true;
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
		if (MAP_HELPER && str[index] == SYMBOL_HELPER)
			print_helper(index, line);
		tile->info = g_base_tile_info[type];
		tile->type = type;
		tile->floor = 0.f;
		tile->ceiling = 0.25;
		tile->floor += tile->info.floor_offset;
		tile->ceiling += tile->info.ceil_offset;
		index++;
	}
}

t_tile_type	tiletype_from_symbol(char symbol)
{
	if (symbol == SYMBOL_GRASS || is_symbol_player(symbol))
		return (TILE_GRASS);
	if (symbol == SYMBOL_WALL)
		return (TILE_WALL);
	if (symbol == SYMBOL_WATER)
		return (TILE_WATER);
	if (symbol == SYMBOL_HELPER)
		return (TILE_GRASS);
	return (TILE_EMPTY);
}
