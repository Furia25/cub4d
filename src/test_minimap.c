/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/02 13:16:34 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_game *game, int pos_x, int pos_y, long color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_TILE_SIZE)
	{
		j = 0;
		while (j < MAP_TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, (pos_x * MAP_TILE_SIZE + i + MINIMAP_X_START + MINIMAP_BORDER), (pos_y * MAP_TILE_SIZE + j + MINIMAP_Y_START + MINIMAP_BORDER), color);
			j++;
		}
		i++;
	}
}

void	draw_line(char *line, t_game *game, int pos_y)
{
	int			tile;
	int			pos_x;

	tile = 0;
	pos_x = 0;
	while (line[tile])
	{
		if (line[tile] == '0')
			draw_tile(game, pos_x, pos_y, 0x000075255);
		if (line[tile] == '1')
			draw_tile(game, pos_x, pos_y, 0x00175250250);
		if (line[tile] == 'N' || line[tile] == 'E' || \
			line[tile] == 'S' || line[tile] == 'W')
		{
			draw_tile(game, pos_x, pos_y, 0x00FF0000);
		}
		tile++;
		pos_x++;
	}
}

void	draw_border(t_game *game)
{
	int	i;
	int	j;
	long	color;

	color = 0x00252525;
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			if (j < 5 || j > MINIMAP_SIZE - 5 || i < 5 || i > MINIMAP_SIZE - 5)
				mlx_pixel_put(game->mlx, game->win, i + MINIMAP_X_START, j + MINIMAP_Y_START, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	line;

	draw_border(game);
	line = 0;
	while (game->map[line])
	{
		draw_line(game->map[line], game, line);
		line++;
	}
}
