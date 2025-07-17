/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:34:48 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/17 15:05:48 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_through_line(t_game *game, int *player, int i, int *enemies, int *pnjs)
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
		if (!check_player(game, i, j, player))
			return (0);
		if (!check_enemies(game, i, j, enemies))
			return (0);
		if (!check_pnjs(game, i, j, pnjs))
			return (0);
	}
	return (1);
}

int	loop_through_map(t_game *game, int *player)
{
	int	i;
	int	k;
	int	enemies;
	int	pnjs;
	int	width;

	i = 7;
	k = -1;
	enemies = 0;
	pnjs = 0;
	while (game->file_content[++i])
	{
		game->map[++k] = game->file_content[i];
		width = ft_strlen(game->file_content[i]);
		if (width > game->width)
			game->width = width;
		if (!loop_through_line(game, player, i, &enemies, &pnjs))
			return (0);
	}
	game->map[++k] = NULL;
	return (1);
}

int	check_tiles_and_borders(t_game *game)
{
	int	player;

	player = 0;
	game->width = 0;
	game->map = (char **)malloc(sizeof(char *) * ((game->height -7) + 1));
	game->height -= 7;
	game->enemy_count = 0;
	game->pnj_count = 0;
	if (!game->map)
		return (0);
	if (!loop_through_map(game, &player))
		return (0);
	if (!player)
		return (0);
	return (1);
}