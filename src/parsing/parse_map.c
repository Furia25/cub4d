/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:34:48 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/25 00:55:02 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_through_line(t_game *game, t_parsing_content *map_content, int i)
{
	int	j;

	j = -1;
	while (game->file_content[i][++j])
	{
		if (!check_tile_validity(game->file_content[i][j]))
			return (0);
		if (center_tile(game->file_content[i][j]) && \
		!borders_around(game->file_content, i, j))
			return (0);
		if (!check_player(game, i, j, &map_content->player))
			return (0);
		if (!check_enemies(game, i, j, &map_content->enemies))
			return (0);
		if (!check_npcs(game, i, j, &map_content->npcs))
			return (0);
	}
	return (1);
}

int	loop_through_map(t_game *game, t_parsing_content *map_content)
{
	int	i;
	int	k;
	int	width;

	i = 7;
	k = -1;
	map_content->enemies = 0;
	map_content->npcs = 0;
	while (game->file_content[++i])
	{
		game->map[++k] = game->file_content[i];
		width = ft_strlen(game->file_content[i]);
		if (width > game->map_width)
			game->map_width = width;
		if (!loop_through_line(game, map_content, i))
			return (0);
	}
	game->map[++k] = NULL;
	return (1);
}

int	check_tiles_and_borders(t_game *game)
{
	t_parsing_content	map_content;

	map_content.player = 0;
	game->map_width = 0;
	game->map = (char **)malloc(sizeof(char *) * ((game->map_height -7) + 1));
	game->map_height -= 7;
	game->enemy_count = 0;
	game->npc_count = 0;
	if (!game->map)
		return (0);
	if (!loop_through_map(game, &map_content))
		return (0);
	if (!map_content.player)
	{
		printf("%d\n", map_content.player);
		return (0);
	}
	return (1);
}
