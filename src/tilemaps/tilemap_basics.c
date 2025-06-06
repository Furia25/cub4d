/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_basics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:03:09 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/06 22:48:31 by vdurand          ###   ########.fr       */
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
