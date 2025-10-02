/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:03:47 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 03:09:46 by vdurand          ###   ########.fr       */
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

int	check_player(t_game *game, int i, int j, int *player)
{
	if (is_symbol_player(game->parsing.file_content[i][j]))
	{
		if (*player)
			return (0);
		game->player.position.x = (double)j + 0.5;
		game->player.position.y = (double)(i - 8) + 0.5;
		if (game->parsing.file_content[i][j] == 'S')
			game->player.yaw_rad = M_PI / 2;
		else if (game->parsing.file_content[i][j] == 'N')
			game->player.yaw_rad = 3 * M_PI / 2;
		else if (game->parsing.file_content[i][j] == 'W')
			game->player.yaw_rad = M_PI;
		else if (game->parsing.file_content[i][j] == 'E')
			game->player.yaw_rad = 0;
		rad_to_vect(&game->player.direction, game->player.yaw_rad);
		*player = 1;
	}
	return (1);
}
