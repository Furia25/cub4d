/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:03:47 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/27 02:35:11 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_str_empty(char *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}

void	map_set_player_pos(int x, int y, t_parsing *parsing, t_game *game)
{
	if (parsing->has_player)
		throw_error(game, ERROR_PARSING_PLAYER);
	parsing->has_player = true;
	game->player.position.x = (float)x + 0.5;
	game->player.position.y = (float)(y - parsing->map_start) + 0.5;
	if (game->parsing.file_content[y][x] == 'S')
		game->player.yaw_rad = M_PI / 2;
	else if (game->parsing.file_content[y][x] == 'N')
		game->player.yaw_rad = 3 * M_PI / 2;
	else if (game->parsing.file_content[y][x] == 'W')
		game->player.yaw_rad = M_PI;
	else if (game->parsing.file_content[y][x] == 'E')
		game->player.yaw_rad = 0;
	else
		throw_error(game, ERROR_WTF);
}

void	property_pass_token(size_t *index, t_property_type type)
{
	index += ft_strlen(g_property_token[type]);
}
