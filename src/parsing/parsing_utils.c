/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:03:47 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/29 19:11:23 by vdurand          ###   ########.fr       */
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
		throw_error(game, ERROR_PARSING_PLAYERS);
	parsing->has_player = true;
	game->player.position.x = (float)x + 0.5;
	game->player.position.y = (float)y + 0.5;
	if (game->parsing.map[y][x] == 'S')
		game->player.yaw_rad = M_PI / 2;
	else if (game->parsing.map[y][x] == 'N')
		game->player.yaw_rad = 3 * M_PI / 2;
	else if (game->parsing.map[y][x] == 'W')
		game->player.yaw_rad = M_PI;
	else if (game->parsing.map[y][x] == 'E')
		game->player.yaw_rad = 0;
	else
		throw_error(game, ERROR_WTF);
}

void	str_remove_chars(char *str, char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !set)
		return ;
	while (str && str[i])
	{
		if (ft_strchr(set, str[i]) == NULL)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}
