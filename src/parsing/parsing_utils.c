/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:03:47 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 19:04:59 by vdurand          ###   ########.fr       */
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

int	is_str_bool(char *str)
{
	if (ft_strcmp(str, FALSE_STR) == 0)
		return (0);
	if (ft_strcmp(str, TRUE_STR) == 0)
		return (1);
	return (-1);
}

void	map_set_player_pos(int x, int y, t_parsing *parsing, t_game *game)
{
	if (parsing->has_player)
		throw_error(ERROR_PARSING_PLAYERS, game);
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
		throw_error(ERROR_WTF, game);
}

bool	str_remove_chars(char *str, char *set)
{
	bool	in_quotes;
	int		read_pos;
	int		write_pos;

	if (!str || !set)
		return (true);
	in_quotes = false;
	read_pos = 0;
	write_pos = 0;
	while (str[read_pos])
	{
		if (str[read_pos] == '"')
		{
			in_quotes = !in_quotes;
			read_pos++;
			continue ;
		}
		if (in_quotes || ft_strchr(set, str[read_pos]) == NULL)
			str[write_pos++] = str[read_pos];
		read_pos++;
	}
	str[write_pos] = '\0';
	return (!in_quotes);
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
