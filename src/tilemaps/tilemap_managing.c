/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_managing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:03:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 18:06:47 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tilemap	*tilemap_new(size_t width, size_t height, size_t tile_size)
{
	t_tilemap	*result;

	result = ft_calloc(1, sizeof(t_tilemap));
	if (!result)
		return (NULL);
	result->height = height;
	result->width = width;
	result->tile_size = tile_size;
	result->tiles = ft_calloc(height, sizeof(t_tile *));
	if (!result->tiles)
	{
		tilemap_free(result);
		return (NULL);
	}
	while (height > 0)
	{
		result->tiles[height - 1] = ft_calloc(width, sizeof(t_tile));
		if (result->tiles[height - 1] == NULL)
		{
			tilemap_free(result);
			return (NULL);
		}
		height--;
	}
	return (result);
}

void	tilemap_free(t_tilemap *map)
{
	if (!map)
		return ;
	tilemap_free_tiles(map);
	free(map->tiles);
	free(map);
}

void	tilemap_free_tiles(t_tilemap *map)
{
	size_t	index;

	if (!map->tiles)
		return ;
	index = 0;
	while (index < map->height)
	{
		free(map->tiles[index]);
		index++;
	}
}
