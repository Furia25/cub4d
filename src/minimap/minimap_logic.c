/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:58:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/04 15:59:12 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_offset(double p_pos)
{
	int		offset;
	double	diff;

	diff = p_pos - (int)p_pos;
	offset = (int)(MMAP_TILE_SIZE * diff);
	return (offset);
}


void	draw_empty_tiles(t_tile_context *tile, int limit)
{
	while (tile->tile < limit)
	{
		draw_tile(tile, rgba8(0, 0, 0, 200), 0);
		tile->tile++;
		tile->pos_x++;
	}
}

void	draw_plain_tiles(t_tile_context *tile)
{
	while (tile->line[tile->tile]
		&& tile->tile < (int)tile->game->player.position.x + 9)
	{
		if (tile->line[tile->tile] == ' '
			|| tile->line[tile->tile] == '\n'
			|| tile->tile > (int)ft_strlen(tile->line))
			draw_tile(tile, rgba8(0, 0, 0, 200), 0);
		else if (center_tile(tile->line[tile->tile]))
			draw_tile(tile, rgba8(255, 150, 100, 200), 0);
		else if (tile->line[tile->tile] == '1')
			draw_tile(tile, rgba8(200, 10, 40, 200), 0);
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
	tile = (int)game->player.position.x - 7;
	pos_x = 0;
	tile_info = (t_tile_context){game, line, tile, pos_x, pos_y, off_x, off_y};
	if (!line)
	{
		draw_empty_tiles(&tile_info, \
			(int)tile_info.game->player.position.x + 9);
		return ;
	}
	draw_empty_tiles(&tile_info, 0);
	draw_plain_tiles(&tile_info);
	draw_empty_tiles(&tile_info, (int)tile_info.game->player.position.x + 9);
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		line;

	i = 0;
	line = (int)game->player.position.y - 8;
	while (++line < 0)
	{
		draw_line(NULL, game, i);
		i++;
	}
	while (line < game->parsing.map_height \
		&& game->parsing.map[line] && line < (int)game->player.position.y + 9)
	{
		draw_line(game->parsing.map[line], game, i);
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
	draw_entities(game);
	draw_player(game);
}
