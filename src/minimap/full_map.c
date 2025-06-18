/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/18 09:30:50 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tiles(t_game *game, int pos_x, int pos_y, t_png_pixel8 color)
{
	int	i;
	int	j;
	int	w_tile_size;
	int	h_tile_size;
	int	tile_size;

	w_tile_size = WINDOW_WIDTH / game->width;
	h_tile_size = WINDOW_HEIGHT / game->height;
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
			img_draw_pixel(color, (pos_x * tile_size + i), \
			(pos_y * tile_size + j), game->img);
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
		if (line[tile] == '1')
			draw_tiles(game, pos_x, pos_y, rgba8(200, 10, 200, 200));
		tile++;
		pos_x++;
	}
}

void	handle_full_map(t_game *game)
{
	int	line;

	if (is_key_pressed(KEY_TAB, game))
	{
		line = 0;
		while (game->map[line])
		{
			draw_lines(game->map[line], game, line);
			line++;
		}
		draw_tiles(game, game->player.position.x, \
			game->player.position.y, rgba8(255, 0, 10, 200));
	}
}
