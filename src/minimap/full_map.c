/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/08 00:10:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

void	draw_tiles(t_game *game, int pos_x, int pos_y, t_rgba8 color)
{
	size_t	w_tile_size;
	size_t	h_tile_size;
	size_t	tile_size;
	size_t	hwidth;
	size_t	hheight;

	w_tile_size = (game->win.width * 0.75) / game->parsing.map_width;
	h_tile_size = (game->win.height * 0.75) / game->parsing.map_height;
	tile_size = min(w_tile_size, h_tile_size);
	hwidth = tile_size * game->parsing.map_width;
	hheight = tile_size * game->parsing.map_height;
	draw_rectangle(
		(t_svec2){pos_x * tile_size + (game->win.width * 0.5 - hwidth * 0.5),
			pos_y * tile_size + (game->win.height * 0.5 - hheight * 0.5)},
		(t_svec2){tile_size, tile_size},
		color,
		game->frame);
}

void	draw_lines(char *line, t_game *game, int pos_y)
{
	int			tile;
	int			pos_x;

	tile = 0;
	pos_x = 0;
	while (line[tile])
	{
		if (is_symbol_central(line[tile]))
			draw_tiles(game, pos_x, pos_y, g_colors[C_DIM_GRAY_T]);
		else if (line[tile] == SYMBOL_WALL)
			draw_tiles(game, pos_x, pos_y, g_colors[C_DARK_TURQUOISE_T]);
		tile++;
		pos_x++;
	}
}

void	draw_full_map(t_game *game)
{
	int	line;

	line = 0;
	while (line < game->parsing.map_height && game->parsing.map[line])
	{
		draw_lines(game->parsing.map[line], game, line);
		line++;
	}
	if (game->player.position.x > 0 && game->player.position.y > 0)
		draw_tiles(game, game->player.position.x, game->player.position.y,
			g_colors[C_RED_T]);
}
