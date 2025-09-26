/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/26 03:18:15 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

void	draw_tiles(t_game *game, int pos_x, int pos_y, t_rgba8 color)
{
	int	i;
	int	j;
	int	w_tile_size;
	int	h_tile_size;
	int	tile_size;

	w_tile_size = game->win.width / game->parsing.map_width;
	h_tile_size = game->win.height / game->parsing.map_height;
	if (w_tile_size > h_tile_size)
		tile_size = h_tile_size;
	else
		tile_size = w_tile_size;
	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			draw_pixel(color, (pos_x * tile_size + i), 
				(pos_y * tile_size + j), game->frame);
			j++;
		}
		i++;
	}
}

void	draw_lines(char *line, t_game *game, int pos_y)
{
	int			tile;
	int			pos_x;

	tile = 0;
	pos_x = 0;
	while (line[tile])
	{
		if (center_tile(line[tile]))
			draw_tiles(game, pos_x, pos_y, rgba8(0, 150, 255, 200));
		else if (line[tile] == '1')
			draw_tiles(game, pos_x, pos_y, rgba8(200, 10, 200, 200));
		tile++;
		pos_x++;
	}
}

void	draw_full_map(t_game *game)
{
	int	line;

	line = 0;
	while (game->parsing.map[line])
	{
		draw_lines(game->parsing.map[line], game, line);
		line++;
	}
	draw_tiles(game, game->player.position.x, \
		game->player.position.y, rgba8(255, 0, 10, 200));
}
