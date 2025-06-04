/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/04 09:53:03 by halnuma          ###   ########.fr       */
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

	tile = game->pos_x - 7;
	pos_x = 0;
	while (tile < 0)
	{
		tile++;
		pos_x++;
	}
	if (!line)
	{
		while (tile < game->pos_x + 8)
		{
			tile++;
			pos_x++;
		}
		return ;
	}
	while (line[tile] && tile < game->pos_x + 8)
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
			if (j < MINIMAP_BORDER || j > MINIMAP_SIZE - MINIMAP_BORDER || i < MINIMAP_BORDER || i > MINIMAP_SIZE - MINIMAP_BORDER)
				mlx_pixel_put(game->mlx, game->win, i + MINIMAP_X_START, j + MINIMAP_Y_START, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_TILE_SIZE)
	{
		j = 0;
		while (j < MAP_TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, ((7 * MAP_TILE_SIZE) + i + MINIMAP_X_START + MINIMAP_BORDER), ((7 * MAP_TILE_SIZE) + j + MINIMAP_Y_START + MINIMAP_BORDER), 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	i;
	// int	j;
	int	line;

	draw_border(game);
	// draw_player(game);
	// printf("%d %d\n", game->pos_x, game->pos_y);
	i = 0;
	line = game->pos_y - 7;
	while (line < 0)
	{
		draw_line(NULL, game, i);
		line++;
		i++;
	}
	while (game->map[line] && line < game->pos_y + 8)
	{
		draw_line(game->map[line], game, i);
		line++;
		i++;
	}
}
