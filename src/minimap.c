/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/09 16:04:22 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_game *game, int pos_x, int pos_y, int off_x, int off_y, t_png_pixel8 color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < MAP_TILE_SIZE)
	{
		j = 0;
		while (j < MAP_TILE_SIZE)
		{
			x = (pos_x * MAP_TILE_SIZE + i - off_x + MINIMAP_X_START + MINIMAP_BORDER);
			y = (pos_y * MAP_TILE_SIZE + j - off_y + MINIMAP_Y_START + MINIMAP_BORDER);
			if (x >= MINIMAP_X_START + MINIMAP_BORDER && \
				x < MINIMAP_X_START + MINIMAP_SIZE && \
				y >= MINIMAP_Y_START + MINIMAP_BORDER && \
				y < MINIMAP_Y_START + MINIMAP_SIZE)
				img_draw_pixel(color, x, y, game->img);
			j++;
		}
		i++;
	}
}

int	calculate_offset(double g_pos)
{
	int		offset;
	double	diff;

	diff = g_pos - (int)g_pos;
	offset = (int)(MAP_TILE_SIZE * diff);
	return (offset);
}

void	draw_line(char *line, t_game *game, double pos_y)
{
	int		tile;
	int		pos_x;
	int		off_x;
	int		off_y;

	off_x = calculate_offset(game->player.position.x);
	off_y = calculate_offset(game->player.position.y);
	tile = (int)game->player.position.x - 7;
	pos_x = 0;
	while (tile < 0)
	{
		draw_tile(game, pos_x, pos_y, off_x, off_y, rgba8(0, 0, 0, 255));
		tile++;
		pos_x++;
	}
	if (!line)
	{
		while (tile < (int)game->player.position.x + 9)
		{
			draw_tile(game, pos_x, pos_y, off_x, off_y, rgba8(0, 0, 0, 255));
			tile++;
			pos_x++;
		}
		return ;
	}
	while (line[tile] && tile < (int)game->player.position.x + 9)
	{
		if (center_tile(line[tile]))
			draw_tile(game, pos_x, pos_y, off_x, off_y, rgba8(255, 150, 100, 255));
		if (line[tile] == '1')
			draw_tile(game, pos_x, pos_y, off_x, off_y, rgba8(200, 10, 40, 255));
		if (line[tile] == ' ' || line[tile] == '\n')
			draw_tile(game, pos_x, pos_y, off_x, off_y, rgba8(0, 0, 0, 0));
		tile++;
		pos_x++;
	}
	while (tile < (int)game->player.position.x + 9)
	{
		draw_tile(game, pos_x, pos_y, off_x, off_y, rgba8(0, 0, 0, 0));
		tile++;
		pos_x++;
	}
}

void	draw_border(t_game *game)
{
	int				i;
	int				j;
	t_png_pixel8	color;

	color = rgba8(25, 255, 25, 255);
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			if (j < MINIMAP_BORDER || \
				j > MINIMAP_SIZE - MINIMAP_BORDER || \
				i < MINIMAP_BORDER || \
				i > MINIMAP_SIZE - MINIMAP_BORDER)
			{
				img_draw_pixel(color, i + MINIMAP_X_START, j + MINIMAP_Y_START, game->img);
			}
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
	while (i < MINIMAP_P_SIZE)
	{
		j = 0;
		while (j < MINIMAP_P_SIZE)
		{
			img_draw_pixel(
				rgba8(255, 0, 10, 255),
				((7 * MAP_TILE_SIZE) + i + MINIMAP_X_START + MINIMAP_BORDER - (MINIMAP_P_SIZE / 2)),
				((7 * MAP_TILE_SIZE) + j + MINIMAP_Y_START + MINIMAP_BORDER - (MINIMAP_P_SIZE / 2)),
				game->img
				);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		line;

	printf("x:%f y:%f\n", game->player.position.x, game->player.position.y);
	i = 0;
	line = (int)game->player.position.y - 7;
	while (line < 0)
	{
		draw_line(NULL, game, i);
		line++;
		i++;
	}
	while (game->map[line] && line < (int)game->player.position.y + 9)
	{
		draw_line(game->map[line], game, i);
		line++;
		i++;
	}
	while (line < (int)game->player.position.y + 9)
	{
		draw_line(NULL, game, i);
		line++;
		i++;
	}
	draw_border(game);
	draw_player(game);
}
