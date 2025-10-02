/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/02 12:30:11 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_empty_tiles(t_tile_context *tile, int limit)
{
	while (tile->tile < limit)
	{
		draw_tile(tile, g_colors[C_BLACK_T], 0, 0);
		tile->tile++;
		tile->pos_x++;
	}
}

void	draw_plain_tiles(t_tile_context *tile)
{
	int	length;

	if (!tile || !tile->line)
		return ;
	length = ft_strlen(tile->line);
	while (tile->tile < length && tile->tile
		< (int)tile->game->player.position.x + 9 && tile->line[tile->tile])
	{
		if (tile->tile > (int)ft_strlen(tile->line)
			|| tile->line[tile->tile] == ' ')
			draw_tile(tile, g_colors[C_BLACK_T], 0, 0);
		else if (is_symbol_central(tile->line[tile->tile]))
			draw_tile(tile, g_colors[C_DIM_GRAY_T], 0, 0);
		else if (tile->line[tile->tile] == SYMBOL_WALL)
			draw_tile(tile, g_colors[C_DARK_TURQUOISE_T], 0, 0);
		tile->tile++;
		tile->pos_x++;
	}
}

void	draw_line(char *line, t_game *game, double pos_y)
{
	int				tile;
	int				pos_x;
	int				off_x;
	int				off_y;
	t_tile_context	tile_info;

	off_x = calculate_offset(game->player.position.x);
	off_y = calculate_offset(game->player.position.y);
	tile = floor(game->player.position.x) - 7;
	pos_x = 0;
	tile_info = (t_tile_context){game, line, tile, pos_x, pos_y,
		off_x, off_y, 0, 0};
	if (!line)
	{
		draw_empty_tiles(&tile_info,
			floor(tile_info.game->player.position.x) + 9);
		return ;
	}
	draw_empty_tiles(&tile_info, 0);
	draw_plain_tiles(&tile_info);
	draw_empty_tiles(&tile_info,
		floor(tile_info.game->player.position.x) + 9);
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		line;

	i = 0;
	line = floor(game->player.position.y) - 8;
	while (++line < 0)
		draw_line(NULL, game, i++);
	while (line < game->parsing.map_height && game->parsing.map[line]
		&& line < floor(game->player.position.y) + 9)
	{
		draw_line(game->parsing.map[line], game, i);
		line++;
		i++;
	}
	while (line < floor(game->player.position.y) + 9)
	{
		draw_line(NULL, game, i);
		line++;
		i++;
	}
	map_manage_entities(game);
	draw_border(game);
	draw_player(game);
}
